#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dictionary.h"
#include "log.c/src/log.h"

Test(dictionary, new) {
    dict_t *d;

    d = dict_new();

    cr_assert_not_null(d, "dict_new() failed");
}

Test(dictionary, init) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_init(d);

    cr_assert_eq(rc, EXIT_SUCCESS, "dict_init() failed");
}

Test(dictionary, free) {
    dict_t *d;
    int rc;

    d = dict_new();

    cr_assert_not_null(d, "dict_new() failed");

    rc = dict_free(d);

    cr_assert_eq(rc, EXIT_SUCCESS, "dict_free() failed");
}

/*
************ dict_chars_exists tests ****************************
*/

Test(dictionary, dict_chars_list_f0) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_chars_exists(d, 'c');

    cr_assert_eq(rc, EXIT_FAILURE, "dict_chars_exists succeeded when it shouldn't have");
}

Test(dictionary, dict_chars_list_f1) {
    dict_t *d;
    int rc;

    d = dict_new();

    dict_add(d, "candy");

    rc = dict_chars_exists(d, '7');

    cr_assert_eq(rc, EXIT_FAILURE, "dict_chars_exists succeeded when it shouldn't have");
}

Test(dictionary, dict_chars_list_s0) {
    dict_t *d;
    int rc;

    d = dict_new();

    dict_add(d, "jkl538-yfv");

    rc = dict_chars_exists(d, '-');

    cr_assert_eq(rc, EXIT_SUCCESS, "dict_chars_exists failed when it should have succeeded");
}

Test(dictionary, dict_chars_list_s1) {
    dict_t *d;
    int rc;

    d = dict_new();

    dict_add(d, "candy");

    rc = dict_chars_exists(d, 'd');

    cr_assert_eq(rc, EXIT_SUCCESS, "dict_chars_exists failed when it should have succeeded");
}

Test(dictionary, dict_chars_list_null) {
    dict_t *d;
    int rc;

    d = dict_new();

    dict_add(d, "");

    rc = dict_chars_exists(d, '\0');

    cr_assert_eq(rc, EXIT_FAILURE, "dict_chars_exists succeeded when it shouldn't have");
}

/*
************ dict_add tests ****************************
*/

/* Test arg 1 for null input for dict_add */
Test(dictionary, dict_add_null0) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_add(d, NULL);

    cr_assert_eq(rc, EXIT_FAILURE, "Passing NULL in as a string in dict_add should have "
                 "returned EXIT_FAILURE, but it returned %d", rc);
}

/* Test arg 2 for null input for dict_add */
Test(dictionary, dict_add_null1) {
    int rc;

    rc = dict_add(NULL, "hi");

    cr_assert_eq(rc, EXIT_FAILURE, "Passing NULL in as a dictionary in dict_add should have "
                 "returned -1, but it returned %d", rc);
}

/* Test empty string input for dict_add */
Test(dictionary, dict_add_empty) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_add(d, "");

    cr_assert_eq(rc, EXIT_SUCCESS, "Passing an empty string in as a dictionary to dict_add "
                 "should have returned EXIT_SUCCESS, but it returned %d", rc);
}

/* Helper function for testing regular input for dict_add */
void check_dict_add(char *file, char *str, int expected) {
    dict_t *d;
    int rc;

    d = dict_new();

    if (file != NULL) {
        cr_assert_eq(EXIT_SUCCESS, dict_read(d, file), "Read to dict failed");
    }

    rc = dict_add(d, str);

    cr_assert_eq(rc, expected, "Putting string %s in dictionary from %s"
                 "should return %d but dict_add returned %d",
                 str, file, expected, rc);
}

/* Test adding a small string for failure (already in dict) */
Test(dictionary, dict_add_dup0) {
    char *s = (char*)malloc(sizeof(char) * 3);
    s = "hi";
    check_dict_add("./tests/dict_test0.txt", s, EXIT_SUCCESS);
}

/* Test adding a long string for failure (already in dict) */
Test(dictionary, dict_add_dup1) {
    char *s = (char*)malloc(sizeof(char) * 53);
    s = "dictionaryverysuperduperlongwordyayitssolongwowcrazy";
    check_dict_add("./tests/dict_test0.txt", s, EXIT_SUCCESS);
}

/* Test adding a small string for success (not in dict) */
Test(dictionary, dict_add_s0) {
    char *s = (char*)malloc(sizeof(char) * 3);
    s = "no";
    check_dict_add(NULL, s, EXIT_SUCCESS);
}

/* Test adding a long string for success (not in dict) */
Test(dictionary, dict_add_s1) {
    char *s = (char*)malloc(sizeof(char) * 53);
    s = "nojfkdsjfksdjfdsjfkdsjfjfkdsjfkdsjfkdsjkfiejkdjskfsd";
    check_dict_add(NULL, s, EXIT_SUCCESS);
}

/*
************ dict_read tests ****************************
*/

/* Test arg 1 for null input in dict_read */
Test(dictionary, dict_read_null0) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_read(d, NULL);

    cr_assert_eq(rc, EXIT_FAILURE, "Passing NULL in as a string in dict_read should have "
                 "returned EXIT_FAILURE, but it returned %d", rc);
}

/* Test arg 2 for null input in dict_read */
Test(dictionary, dict_read_null1) {
    int rc;

    rc = dict_read(NULL, "./tests/dict_test0.txt");

    cr_assert_eq(rc, EXIT_FAILURE, "Passing NULL in as a dictionary in dict_read should have "
                 "returned EXIT_FAILURE, but it returned %d", rc);
}

/* Test bad filename input in dict_read */
Test(dictionary, dict_read_noname) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_read(d, "DNE.txt");

    cr_assert_eq(rc, EXIT_FAILURE, "Passing NULL in as a string in dict_read should have "
                 "returned EXIT_FAILURE, but it returned %d", rc);
}

void check_dict_read(char *file, int expected) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_read(d, file);

    cr_assert_eq(rc, expected, "Passing file %s in dict_read should have "
                 "returned %d, but it returned %d", file, expected, rc);
}

/* Test for regular input in dict_read 1 */
Test(dictionary, dict_read0) {
    check_dict_read("./tests/dict_test0.txt", EXIT_SUCCESS);
}



/*
************ dict_exists tests ****************************
*/

/* Test arg 1 for null input for dict_exists */
Test(dictionary, dict_exists_null0) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_exists(d, NULL);

    cr_assert_eq(rc, EXIT_FAILURE, "Passing NULL in as a string in dict_exists should have "
                 "returned -1, but it returned %d", rc);
}

/* Test arg 2 for null input for dict_exists */
Test(dictionary, dict_exists_null1) {
    int rc;

    rc = dict_exists(NULL, "hi");

    cr_assert_eq(rc, EXIT_FAILURE, "Passing NULL in as a dictionary in dict_exists should have "
                 "returned EXIT_FAILURE, but it returned %d", rc);
}

/* Test empty string input for dict_exists */
Test(dictionary, dict_exists_empty) {
    dict_t *d;
    int rc;

    d = dict_new();

    dict_read(d, "./tests/dict_test0.txt");

    rc = dict_exists(d, "");

    cr_assert_eq(rc, EXIT_FAILURE, "Passing an empty string in as a dictionary to dict_exists "
                 "should have returned EXIT_FAILURE, but it returned %d", rc);
}

/* Helper function for testing regular input for dict_exists */
void check_dict_exists(char *file, char *str, int expected) {
    dict_t *d;
    int rc;

    d = dict_new();

    if (file != NULL) {
        cr_assert_eq(EXIT_SUCCESS, dict_read(d, file), "Read to dict failed");
    }

    rc = dict_exists(d, str);

    cr_assert_eq(rc, expected, "String %s in dictionary from %s"
                 "should return %d but dict_exists returned %d",
                 str, file, expected, rc);
}

/* Test a small string for success */
Test(dictionary, dict_exists_s0) {
    char *s = (char*)malloc(sizeof(char) * 3);
    s = "hi";
    check_dict_exists("./tests/dict_test0.txt", s, EXIT_SUCCESS);
}

/* Test a long string for success */
Test(dictionary, dict_exists_s1) {
    char *s = (char*)malloc(sizeof(char) * 53);
    s = "dictionaryverysuperduperlongwordyayitssolongwowcrazy";
    check_dict_exists("./tests/dict_test0.txt", s, EXIT_SUCCESS);
}

/* Test a small string for failure */
Test(dictionary, dict_exists_f0) {
    char *s = (char*)malloc(sizeof(char) * 3);
    s = "nah";
    check_dict_exists("./tests/dict_test0.txt", s, EXIT_FAILURE);
}

/* Test a long string for failure */
Test(dictionary, dict_exists_f1) {
    char *s = (char*)malloc(sizeof(char) * 53);
    s = "notindictionarypleasedontpassifthispassesdictpersists";
    check_dict_exists("./tests/dict_test0.txt", s, EXIT_FAILURE);
}
