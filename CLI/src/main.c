/**
 * @file main.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief  This file contains the main entry point of the program.
 *
 * Unix-CLI is a versatile command-line utility featuring a custom command
 * interpreter, allowing users to execute a variety of commands directly from
 * the terminal. With a focus on efficiency and user-friendliness, Unix-CLI
 * utilizes system calls for low-level operations, ensuring broad compatibility
 * across Unix-like operating systems.
 *
 * @version 0.2
 * @date 2024-03-20
 *
 * @section Modifications
 * - 2024-04-18: Updated program to v0.2, documented on the Github repo.
 *   Enrique George Rodrigues (a28602@alunos.ipca.pt)
 *
 */
#define _XOPEN_SOURCE 700

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "constants.h"

/**
 * @brief Main entry point of the program.
 *
 * The main function serves as the entry point of the program. It executes the
 * command-line interface, allowing users to execute commands and programs.
 *
 * @return int Returns 0 upon successful execution or 1 in the case of error.
 */
int main() {
  printf("%s version %s.\n\n", PROGRAM_NAME, VERSION);

  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;
  char *args[MAX_ARGS];  // Array to hold arguments
  int arg_count;

  while (1) {
    // Print a prompt
    printf("%% ");
    fflush(stdout);  // Ensure the prompt is displayed

    // Read user input
    bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
      perror("Error");
      return EXIT_FAILURE;
    } else if (bytes_read == 0 || (bytes_read == 1 && buffer[0] == '\n')) {
      // No input received, ignore and continue
      continue;
    }

    // Null-terminate the string
    buffer[bytes_read - 1] = '\0';

    // Check for termination
    if (strncmp(buffer, EXIT_CMD, strlen(EXIT_CMD)) == 0) {
      return EXIT_SUCCESS;  // Terminate the program
    }

    // Split the input string into tokens
    args[0] = strtok(buffer, " ");
    arg_count = 1;
    while ((args[arg_count] = strtok(NULL, " ")) != NULL &&
           arg_count < MAX_ARGS - 1) {
      arg_count++;
    }
    args[arg_count] = NULL;  // Ensure the last argument is NULL

    // Search for the command in the PATH
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");
    char command_path[BUFFER_SIZE];
    int command_found = 0;

    while (dir != NULL) {
      snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);
      if (access(command_path, X_OK) == 0) {
        command_found = 1;
        break;
      }
      dir = strtok(NULL, ":");
    }

    free(path_copy);

    if (!command_found) {
      fprintf(stderr, "%s: command not found\n", args[0]);
      continue;
    }

    // // Check if the file exists and is executable
    // if (access(args[0], X_OK) == -1) {
    //   perror("Error");
    //   continue;  // Skip to the next iteration if the file is not executable
    // }

    // Execute the file with the provided arguments
    pid_t pid = fork();
    if (pid < 0) {
      fputs("Error executing program.", stderr);
      continue;
    }
    if (pid == 0) {
      // Child process
      execvp(command_path, args);
      perror("Error executing command");
      exit(EXIT_FAILURE);
    } else {
      // Parent process
      wait(NULL);           // Wait for the child process to finish
      fputs("\n", stdout);  // Put newline
    }
  }

  return 0;
}
