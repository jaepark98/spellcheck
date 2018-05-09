
/*
 * A dictionary data structure based on tries
 *
 * See dictionary.h for function documentation.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include "utils.h"
#include "dictionary.h"

/* See dictionary.h */
dict_t* dict_new() {

    dict_t *d;
    int rc;

    d = malloc(sizeof(dict_t));

    if (d == NULL) {
        error("Could not allocate memory");
        return NULL;
    }

    rc = dict_init(d);
    if (rc != 0) {
        error("Could not initialize dict");
        return NULL;
    }

    return d;
}

/* See dictionary.h */
int dict_init(dict_t *d) {
    assert(d != NULL);

    trie_t *t = trie_new();
    if (t == NULL) {
        return 1;
    }
    d->dict = t;

    return 0;
}

/* See dictionary.h */
int dict_free(dict_t *d) {
    assert(d != NULL);
    assert(d->dict != NULL);

    trie_free(d->dict);
    free(d);

    return 0;
}

/* See dictionary.h */
int dict_exists(dict_t *d, char *str) {
    if (d == NULL || d->dict == NULL || str == NULL || str[0] == '\0') {
        error("Invalid input to in_dict");
        return -1;
    }

    return trie_exists(d->dict, str);
}

/* See dictionary.h */
int dict_add(dict_t *d, char *str) {
    if (d == NULL || d->dict == NULL || str == NULL) {
        error("Invalid arguments to add_to_dict");
        return -1;
    }

    return trie_add(d->dict, str);
}

/* See dictionary.h */
int dict_read(dict_t *d, char *file) {

    int rc = 1;

    // From here: https://stackoverflow.com/questions/16400886/reading-from-a-file-word-by-word
    char buffer[1024];
    FILE *f = fopen(file, "r");

    if (f == NULL) {
        return 0;
    }

    while (fscanf(f, "%1023s", buffer) == 1) {
        if (dict_add(buffer, d) != 1) {
            rc = -1;
        }
    }

    fclose(f);

    return rc;
}
