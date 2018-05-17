#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "suggestion.h"
#include "dictionary.h"


// Test has_children for success
Test(suggestion, has_children_s0) {
    dict_t *d = dict_new();
    dict_add(d, "abc");

    cr_assert_eq(has_children(d, "ab"), 0, "has_children failed");
}

// Test has_children for failure
Test(suggestion, has_children_f0) {
    dict_t *d = dict_new();
    dict_add(d, "abc");

    cr_assert_eq(has_children(d, "ac"), 1, "has_children failed");
}

/*************   These functions individually test helpers of suggestions()   *************/

// Test a simple move_on
Test(suggestion, move_s0) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "893bf");

    suggestions(set, d, "893b", "f", 1);

    cr_assert_eq(zset_rank(set, "893bf"), 0, "move_on failed");

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

// Test a full move_on
Test(suggestion, move_s1) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "vdf894jkls");

    suggestions(set, d, "", "vdf894jkls", 1);

    cr_assert_eq(zset_rank(set, "vdf894jkls"), 0, "move_on failed");

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

// Test a simple delete
Test(suggestion, delete_s0) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "cds8Dfk");

    suggestions(set, d, "cds", "c8Dfk", 1);

    cr_assert_eq(zset_rank(set, "cds8Dfk"), 0, "try_delete failed %s", zset_rank(set, "cds8Dfk"));

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

// Test a double delete
Test(suggestion, delete_s1) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "cds8Dfk");

    suggestions(set, d, "", "cdisc8Dfk", 1);

    cr_assert_eq(zset_rank(set, "cds8Dfk"), 0, "try_delete failed %i", zset_rank(set, "cds8Dfk"));

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

// Test a simple replace
Test(suggestion, replace_s0) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "vjikd8-");

    suggestions(set, d, "vji", "ad8-", 1);

    cr_assert_eq(zset_rank(set, "vjiad8-"), 0, "try_replace failed");

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

// Test a double replace
Test(suggestion, replace_s1) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "vjikd8-");

    suggestions(set, d, "", "vTik=8?", 1);

    cr_assert_eq(zset_rank(set, "vjikd8-"), 0, "try_replace failed");

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

// Test a simple swap
Test(suggestion, swap_s0) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "vjk48sw");

    suggestions(set, d, "vj4", "k8sw", 1);

    cr_assert_eq(zset_rank(set, "vjk48sw"), 0, "try_swap failed");

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

// Test a double swap 
Test(suggestion, swap_s1) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "4uiwifnw");

    suggestions(set, d, "", "4uiwnfiw", 1);

    cr_assert_eq(zset_rank(set, "4uiwifnw"), 0, "try_swap failed");

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

// Test a simple insert
Test(suggestion, insert_s0) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "jvd84+1");

    suggestions(set, d, "jvd", "4+1", 1);

    cr_assert_eq(zset_rank(set, "jvd84+1"), 0, "try_insert failed");

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

// Test a double insert
Test(suggestion, insert_s1) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "kj3fsjk]fui");

    suggestions(set, d, "", "kj3sjk]fi", 1);

    cr_assert_eq(zset_rank(set, "kj3fsjk]fui"), 0, "try_insert failed");

    // cleanup
    zset_remrangebyrank(set, 0, -1);
}

