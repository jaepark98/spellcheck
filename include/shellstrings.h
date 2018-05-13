#ifndef _SHELLSTRINGS_H
#define _SHELLSTRINGS_H

/* Strings to be used in shell
   Jaewan Park
*/
#include <stdio.h>
#include <stdlib.h>

/* Home Page */
void greet();

void main_help_text();

/* Help Page */
void help_page_text();

/* Save Page */
void save_page_text();

/* Print error, allowing for description depending on context */
void error_shell(char* s);

/* Command Line Input Format */
void usage();

/* Shell Prompt */
void shell_prompt();

/* Final message */
void bye();

/* File input in Terminal */
void input(char* input_file, char* status);
#endif
