/**
 * @file find.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Contains functions for finding executable files in the PATH.
 * @version 0.1
 * @date 2024-04-21
 * @copyright Copyright (c) 2024
 */
#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE

#include <constants.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Checks if a file is executable.
 *
 * This function checks if the file at the specified path is executable.
 *
 * @param path The path to the file.
 * @return true if the file is executable, false otherwise.
 */
bool isExecutableFile(const char *path) { return access(path, X_OK) == 0; }

/**
 * @brief Finds the full path of a command in the PATH environment variable.
 *
 * This function searches for the specified command in the directories listed
 * in the PATH environment variable. If the command is found, its full path is
 * copied to the provided buffer.
 *
 * @param command The name of the command to search for.
 * @param command_path A buffer to store the full path of the command.
 * @return true if the command is found, false otherwise.
 */
bool findCommandInPath(const char *command, char *command_path) {
  // Check if the command is executable in the current directory
  if (isExecutableFile(command)) {
    strcpy(command_path, command);
    return true;
  }

  // Search for the command in the PATH
  char *path = getenv("PATH");
  char *path_copy = strdup(path);
  char *rest = path_copy;  // Pointer to keep track of the remaining string

  char *dir = strsep(&rest, ":");
  while (dir != NULL) {
    snprintf(command_path, BUFFER_SIZE_BYTES, "%s/%s", dir, command);
    if (isExecutableFile(command_path)) {
      free(path_copy);
      return true;
    }
    dir = strsep(&rest, ":");
  }

  free(path_copy);
  return false;
}
