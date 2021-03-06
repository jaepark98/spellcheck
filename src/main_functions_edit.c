#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "dictionary.h"
#include "word.h"
#include "main_functions_edit.h"
#include "log.c/src/log.h"

// Given an array of misspelled words, generates an underline
// for an occurence in sentence

/* See main_functions_edit.h */
char *underline_misspelled_sentence(char *misspelled, char *sentence, char *underline) {
	underline[0] = '\0';
	char* ptr = strstr(sentence, misspelled);

	assert(misspelled != NULL);
	assert(ptr != NULL);

	int pos = ptr - sentence;
	int i;

	for (i = 0; i < pos; i++) {
		strcat(underline, " ");
	}

	int slen = strlen(misspelled);

	for ( ; i < slen + pos; i++) {
		strcat(underline, "^");
	}

	underline[i] = '\0';

	log_debug("underline is %s", underline);
	log_debug("returning from underline_misspelled_sentence");
	return underline;
}

/* See main_functions_edit.h */
int add_to_misspelled(char *word, char** misspelled) {
	if (word == NULL || misspelled == NULL) {
		log_error("add_to_misspelled misspelled word, or array, is NULL.");
		return EXIT_FAILURE;
	}

	int i = 0;

	while (misspelled[i] != NULL) {
		i++;
	}

	log_info("add_to_misspelled word position is %d.", i);

	misspelled[i] = word;

	return EXIT_SUCCESS;
}

/* See main_functions_edit.h */
bool is_in_punct_array(char letter) {
	char punctuation_array[] = "+, .-\'&!?:;#~=/$^\n_<>\"";
	int num_punctuation = sizeof(punctuation_array) / sizeof(punctuation_array[0]);
	int i;

	for (i = 0; i < num_punctuation ; i++) {
		if ((punctuation_array[i] - letter) == 0) {
			log_trace("is_in_punct_array character is a punctuation.");
			return true;
		}
	}

    log_trace("is_in_punct_array character is not a punctuation."); 
    return false;
}

/* See main_functions_edit.h */
void remove_prefix_punctuation(char *word) {
	char prefix_char;
	prefix_char = word[0];
	log_trace("remove_prefix_punctuation before removing any prefixed punctuation, the word is '%s'.", word);

	while (is_in_punct_array(prefix_char) == true) {
		memmove(word, word + 1, strlen(word)); 
		log_trace("remove_prefix_punctuation word is now %s", word);
		prefix_char = word[0];
	}
}

/* See main_functions_edit.h */
void remove_trailing_punctuation(char *word) {
	char trailing_char;
	log_trace("remove_trailing_punctuation before removing trailing punctuation, the word is '%s'.", word);
	trailing_char = word[(strlen(word) - 1)];

	while (is_in_punct_array(trailing_char) == true) {
		word[strlen(word) - 1] = '\0';
		trailing_char = word[strlen(word) - 1]; //check next trailing character
		log_trace("remove_trailing_punctuation word is now set to '%s'.", word);
	}
}

/* See main_functions_edit.h */
char *remove_punctuation(char *word) { //removes trailing and prefix punctuation without modifying original word
	char *shaved_word = (char *)malloc(strlen(word));
    
	strcpy(shaved_word, word);
	remove_prefix_punctuation(shaved_word);
	remove_trailing_punctuation(shaved_word);

	log_debug("remove_punctuation word is now set to '%s'.", shaved_word);
	return shaved_word;
}

/* See main_functions_edit.h */
void parse_string(char *string, dict_t *dict, char *underline, char **misspelled) {
	char *string_copy = strdup(string);
	char *tkn = strtok(string," \n"); //words only separated by spaces and newline
	
	while (tkn != NULL) {
		log_trace("Token: %s", tkn);
		char *shaved_word = remove_punctuation(tkn);

		if (valid_word(dict, shaved_word) == false){
			log_trace("parse_string word is misspelled.");
			add_to_misspelled(shaved_word, misspelled);
		}
		else if (valid_word(dict, shaved_word) == true) {
			log_trace("parse_string word is spelled correctly.");
		}
		else {
			log_error("log_error text processing failed.");
			shell_error("Error processing text.", false);
		}

		tkn = strtok(NULL," \n"); //spaces and \n are the only delimeters
	}

	log_debug("String was parsed successfully.");
	underline_misspelled_sentence(misspelled[0], string_copy, underline);
}

/* See main_functions_edit.h */
char *correct_line(char *line, char *old_word, char *new_word) {
	char buffer[2000] = {0}; // Might need to modify the size estimate
	log_debug("correct_line line before correction: %s", line);

	char *insert_point = &buffer[0];
	char *tmp = line;

	int old_length = strlen(old_word);
	int new_length = strlen(new_word);

	while(1) {
		char *p = strstr(tmp, old_word);

		if (p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}

		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;

		memcpy(insert_point, new_word, new_length);
		insert_point += new_length;

		tmp = p + old_length;
	}

	strcpy(line, buffer);

	log_debug("Line after corrections: %s", line);
	return line;
}