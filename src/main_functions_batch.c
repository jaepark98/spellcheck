#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "dictionary.h"
#include "word.h"
#include "main_functions_batch.h"
#include "main_functions_edit.h"
#include "main_functions_home.h"
#include "log.c/src/log.h"

/* See main_functions_batch.h */
char *edit_batch(char *line, dict_t *dict, int verbosity, int lnum) {
    log_info("(edit_batch) Batch mode started successfully.");

	char *line_copy = strdup(line);
    int max_no_suggestions = 4;
    int max_edits = 2;

    // Generates an empty array where the misspelled words in a line will be stored
    char **misspelled = calloc(strlen(line), sizeof(char *));
    if (misspelled == NULL) {
        log_fatal("(edit_batch) calloc() failed.");
        exit(0);
    }

    // Generates an empty array where the underline will go
    char *underline = (char *)malloc(sizeof(char) * (strlen(line) + 1));
    if (underline == NULL) {
        log_fatal("(edit_batch) calloc() failed.");
        exit(0);
    }
    underline[0] = '\0';

    // Identifies misspelled words and add to misspelled
    parse_string(line, dict, underline, misspelled);
    log_info("(edit_batch) File parsing completed.");

    int i = 0;
    int j;

    //Replacing words, printing if batch mode
    while (misspelled[i] != NULL) {
        // Generates suggestions
        char **suggestions = generate_suggestions(dict, misspelled[i], max_edits, max_no_suggestions);

        /*
         * If no suggestions are generated:
         *  - In verbose mode, print "No suggestions".
         *  - In quiet mode, save the word as is (without corrections).
         */
        if (suggestions == NULL) {
            suggestions = calloc(max_no_suggestions, sizeof(char *));
        }

        if (suggestions[0] == NULL) {
            if (verbosity == VERBOSE_MODE) {
                suggestions[0] = strdup("No suggestions generated");
            }
        }

        if (verbosity == QUIET_MODE) {
            log_trace("(edit_batch) Correcting misspelled line.");
            if (suggestions[0] != NULL)
                correct_line(line_copy, misspelled[i], suggestions[0]);
        }

        // In verbose mode, edit the file and also print a replacement chart
        if (verbosity == VERBOSE_MODE) {
            log_trace("(edit_batch) Printing batch mode correction chart.");
            shell_verbose_chart(lnum, line_copy, misspelled[i], suggestions);
        }

        j = 0;

        if (suggestions != NULL) {
            while (suggestions[j] != NULL) {
                free(suggestions[j]);
                
                j++;
            }

            free(suggestions);
        }

        i++;
    }

    return line_copy;
}

/* See main_functions_batch.h */
char **batch_mode(char *filename, dict_t *dict, bool *quit, int verbosity) {
    char **lines = parse_file(filename);

    log_debug("(batch_mode) File parsed into a char array.");

    // If lineparse_file returns NULL
    if (lines == NULL) {
        shell_error("Failed to parse file.", false);
        log_error("(batch_mode) file parse failed.");
        *quit = true;

        return NULL;
    }

    if (verbosity == VERBOSE_MODE) {
        printf("LINE:CHAR\t\tWORD\t\t\tSUGGESTIONS\n");
    }

    int i = 0;

    while (lines[i] != NULL) {
        log_trace("Starting loop for line %d.", i + 1);

        lines[i] = edit_batch(lines[i], dict, verbosity, i + 1);

        i++;
    }

    *quit = false;

    return lines;
}