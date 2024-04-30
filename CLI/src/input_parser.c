/**
 * @file input_parser.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Contains functions for parsing input strings into arguments.
 * @version 0.1
 * @date 2024-04-21
 * @copyright Copyright (c) 2024
 */
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Parses an input string into arguments.
 *
 * This function tokenizes the input string by spaces and stores the tokens
 * in the provided array of strings (`args`). The maximum number of arguments
 * that can be stored in the `args` array is specified by `max_args`.
 *
 * @param input The input string to be parsed.
 * @param args An array of strings to store the parsed arguments.
 * @param max_args The maximum number of arguments that can be stored.
 * @return int The number of arguments parsed and stored in the `args` array.
 */
int parse_input(char *input, char *args[], int max_args) {
  char *token;
  int arg_count = 0;
  char *rest = input;  // Pointer to keep track of the remaining string

  // Tokenize the input string by spaces using strsep()
  while ((token = strsep(&rest, " ")) != NULL && arg_count < max_args) {
    // Ignore empty tokens
    if (*token == '\0') {
      continue;
    }
    // Store the token in the args array
    args[arg_count++] = token;
  }

  // Ensure the last element of args is NULL
  args[arg_count] = NULL;

  return arg_count;
}
