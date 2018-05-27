
/* 
 * String output functions to be used in the shell
 *
 * See shellstrings.h for function documentation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellstrings.h"

/* See shellstrings.h */
void shell_prompt() {
    printf(BOLDWHITE "\nspellcheck >" RESET " ");
}

/* See shellstrings.h */
void shell_main_menu() {
    printf(BOLDWHITE "------- Welcome to Spellcheck! ------\n\n" RESET);

    printf(BLUE "Please load a file to begin. "
                "Additionally, select an output mode and/or "
                "choose dictionary before running the program.\n\n" RESET);

    printf("f [/path/file.txt]           : open file\n");
    printf("d [/path/dictionary.txt]     : input custom dictionary file\n");
    printf("h                            : help\n");
    printf("q                            : quit program\n");
}

/* See shellstrings.h */
void shell_save() {
    printf("p: print all changes\n");
    printf("s: save changes to existing file\n");
    printf("c: save changes to custom file\n");
    printf("r: return to home screen (without saving)\n");
    printf("q: quit program (without saving)\n\n");
}

/* See shellstrings.h */
void shell_edit_success() {
     printf(GREEN "Spellchecking Successful!\n\n" RESET);
}

/* See shellstrings.h */
void shell_print(char** lines) {
    int i = 0;

    printf("\n\n");
    while (lines[i] != NULL) {
        printf("%s", lines[i]);
        i++;
    }
    printf("\n\n");
}


/* See shellstrings.h */
void shell_error(char* error_text) {
	printf(RED "ERROR:" RESET " %s\n", error_text);
}

/* See shellstrings.h */
char *shell_error_format() {
    char *error_format =
    "Please use designated format:\n"
    "./spellcheck [-f /path/file.txt] [-d /path/dictionary.txt] [-q or -v]\n"
    "For help, run without command line arguments and enter help page.";

    return error_format;
}

/* See shellstrings.h */
void shell_input(char* input_file, char* status) {
    char *input = "has been accepted as the input file for";
    printf("%s %s %s!\n", input_file, input, status);
}

/* See shellstrings.h */
char *shell_error_dict(char *dict_file) {
    char *error_dict =
    "Trouble reading dictionary file ";
    strcat(error_dict, dict_file);

    return error_dict;
}

/* See shellstrings.h */
char *shell_error_exit() {
    char *error_exit =
    "Encountered an error -  Program exiting automatically.";

    return error_exit;
}

/* See shellstrings.h */
void shell_help() {
    printf(BLUE "Spellcheck is a tool which searches for misspelled words "
           "and suggests alternative spellings given a text file.\n" RESET);
    printf("Currently, you are in the interactive mode.\n");
    printf("To run in batch mode, exit the program with the command " BOLDWHITE "exit" RESET
           ", and run: " BOLDWHITE "$ ./spellcheck -f /path/file.txt\n" RESET);
    printf("Flags: " BOLDWHITE "-q" RESET " is for quiet, and " BOLDWHITE
           "-v" RESET " is for verbose.\n");
    printf("To input a custom dictionary to the program, include " BOLDWHITE 
           "-d /path/dictionary.txt" RESET " at the end of the command line.\n");
    printf(BLUE "\nEnter any command to return to the previous page." RESET "\n");
}

void shell_start_interactive(char* file_name, char* dict_name, char* md) {
    printf("\n\n" BOLDWHITE "------------------------------------------------------------\n" RESET);
    printf(BOLDWHITE "--------------------EDITING STARTED WITH--------------------\n" RESET);
    printf("\n" BOLDWHITE "------------------------------------------------------------\n" RESET);
    printf(GREEN "file: %s\ndictionary: %s\nmode: %s\n\n" RESET, file_name, dict_name, md);
    printf(BOLDWHITE "Enter any command to start interactive\n\n" RESET);
    shell_prompt();
}

void shell_start_batch(char* file_name, char* dict_name, char* md) {
    printf(BOLDWHITE "--------------------EDITING STARTED WITH--------------------\n" RESET);
    printf("file: %s\ndictionary: %s\nmode: %s\n\n", file_name, dict_name, md);
}

char* shell_modename(int mode) {
    switch (mode) {
        case 1: return "quiet batch mode";
        case 2: return "verbose batch mode";
        case 3: return "interactive mode";
        default: break;
    }
    return "interactive mode";
}

void shell_interactive_line_print(int lnum, char* line, char* underline, int returnflag) {
    printf("Line: %d\n", lnum);
    printf(BOLDWHITE "%s" RESET, line);
    if (returnflag) printf("\n");
    printf(BOLDRED "%s" RESET, underline);
    printf("\n\n");
}


void shell_interactive_replacements(char* word, char** sug, int flag) {
    if (flag == EXIT_FAILURE) {
        suggestions[0] = flag; // to avoid error
        suggestions[1] = flag;
        printf("\nNo suggestions have been generated for %s.\n", misspelled[i]);
        printf("\nd : Delete Word.\n");
        printf("i : Input Word.\n");
        printf("s : Skip.\n");
    } else {
        printf("\nPossible replacements for word %s are:\n\n", word);
        int j = 0;
        while (sug[j] != NULL) {
            printf("%d : %s \n", j + 1, sug[j]);
            j++;
        printf("\nd : Delete Word.\n");
        printf("i : Input Word.\n");
        printf("s : Skip.\n");
        }
    }
}


void shell_verbose_chart(int lnum, char* misspelled, char** suggestions) {
    printf(BOLDWHITE "%d\t\t\t" RESET, lnum); // print line number
    int ntab = 3 - (strlen(misspelled) / 8); // number of tabs
    int j;
    printf(RED "%s" RESET, misspelled);
    for (j = 0; j < ntab; j++) printf("\t");

    j = 0;
    while (suggestions[j] != NULL) {
        printf(GREEN "%s" RESET, suggestions[j]);
        if (suggestions[j + 1] != NULL) printf(", ");
        j++;

    }
    printf("\n"); // print list of replacement
}

void shell_save_message() {
    printf("\n\n Enter a viable file name [path/*.txt] or enter 'r' to return to previous page.\n\n");
    shell_prompt();
}

/* See shellstrings.h */
void shell_outro() {
    printf("Spellcheck ran successfully. Goodbye!\n");
}