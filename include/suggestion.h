/*
 * A module to generate suggestions for a word
 */

#ifndef INCLUDE_SUGGESTION_H_
#define INCLUDE_SUGGESTION_H_

#include "zset_api.h"
#include "dictionary.h"

// The maximum length of a string we're willing to process
// Longest word in english dictionary is 45 letters lol
#define MAXLEN 60

/*
 * Does a fuzzy sting match on all the words in a dictionary
 * 
 * Parameters:
 *  - set: A Redis Sorted Set. Must point to a zset allocated with zset_new()
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *  - prefix: A prefix of a word. Must be contained in a dictionary or ""
 *  - suffix: A suffix of a word. Can also be ""
 *  - edits_left: The maximum levenshtein distance a word can be from prefix+suffix
 * 
 * Returns:
 *  - 0 for success, or a positive integer n for the number of errors encountered
 * 
 */
int suggestions(zset_t *set, dict_t *d, char *prefix, char *suffix, int edits_left);

#endif