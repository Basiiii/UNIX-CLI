/**
 * @file parser.c
 * @brief Implementation of command parsing and execution.
 * @version 0.1
 * @date 2024-03-24
 *
 * This file contains the implementation of functions for parsing and executing
 * commands. It defines functions necessary for command processing.
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"
#include "file_ctrl.h"
#include "parse_args.h"
#include "utils.h"

/**
 * @brief Array of Command structures.
 *
 * This array contains the definitions of various commands available in the
 * CLI, where each command structure consists of a command name, a parsing
 * function, and a command function.
 */
Command commands[] = {
    {"show", ParseShowFile, ShowFile},
};

/**
 * @brief A macro to define the number of commands that exist.
 */
#define NUM_COMMANDS (sizeof(commands) / sizeof(Command))

/**
 * @brief Identifies a command based on the input string.
 *
 * This function parses the input string to identify a command by extracting the
 * first word (command name) using the strtok_r function. It compares the
 * command name with the names of commands stored in the global commands array.
 *
 * @param input The input string containing the command to be identified.
 * @return A pointer to the identified command structure if found; otherwise,
 * returns NULL.
 */
static Command *IdentifyCommand(const char *input) {
  char *saveptr;  // Pointer to maintain context for strtok_r
  char *command =
      strtok_r((char *)input, " ",
               &saveptr);  // Split the input string at the first space

  for (size_t i = 0; i < NUM_COMMANDS; i++) {
    if (strcmp(command, commands[i].name) == 0) {
      return &commands[i];
    }
  }

  printf("Unknown command: %s\n", command);
  return NULL;  // Return NULL if command is not found
}

/**
 * @brief Parses and executes a command.
 *
 * This function parses the input string to identify the command and its
 * arguments, then executes the corresponding command function. It splits the
 * input string at the first space character using strtok_r and identifies the
 * command using the IdentifyCommand function. If the command is found, it calls
 * the parsing function and the command function associated with the identified
 * command.
 *
 * @param input The input string containing the command and its arguments.
 */
void ParseAndExecuteCommand(const char *input) {
  // Pointer to maintain context for strtok_r
  char *saveptr;
  // Split the input string at the first space
  strtok_r((char *)input, " ", &saveptr);
  // Get the rest of the string as arguments
  char *args = strtok_r(NULL, "", &saveptr);

  Command *cmd = IdentifyCommand(input);
  if (cmd) {
    cmd->parseFunc(args);  // Call parsing function
    cmd->func(args);       // Call command function
  }
}
