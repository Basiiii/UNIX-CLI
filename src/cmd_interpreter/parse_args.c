/**
 * @file parse_args.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Contains functions for parsing command-line arguments.
 *
 * This file includes functions related to parsing command-line
 * arguments, preparing them for execution.
 *
 * @version 0.1
 * @date 2024-04-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <stdio.h>
#include <string.h>

/**
 * @brief Parses the arguments for the ShowFile command.
 *
 * This function parses the arguments provided to the ShowFile command. It finds
 * the first space character in the arguments string and replaces it with a null
 * terminator, effectively separating the command name from the filename.
 *
 * @param args The string containing the arguments for the ShowFile command.
 */
void ParseShowFile(char *args) {
  // Find the first space character
  char *space_ptr = strchr(args, ' ');

  // If a space is found, replace it with null terminator
  if (space_ptr != NULL) {
    *space_ptr = '\0';
  }
}

/**
 * @brief Parses the arguments for the ShowDir command.
 *
 * This function parses the arguments provided to the ShowDir command. It finds
 * the first space character in the arguments string and replaces it with a null
 * terminator, effectively separating the command name from the filename.
 *
 * @param args The string containing the arguments for the ShowDir command.
 */
void ParseShowDir(char *args) {
  // Find the first space character
  char *space_ptr = strchr(args, ' ');

  // If a space is found, replace it with null terminator
  if (space_ptr != NULL) {
    *space_ptr = '\0';
  }
}
