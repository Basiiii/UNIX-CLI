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
 * - 2024-04-22: CLI tries to execute as a file first and if it fails it looks
 *               in the users PATH variable.
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
#include "execute.h"
#include "find.h"
#include "input_parser.h"
#include "utils.h"

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

  char buffer[BUFFER_SIZE_BYTES];
  ssize_t bytes_read;
  char *args[MAX_ARGS + 1];
  char command_path[BUFFER_SIZE_BYTES];
  int arg_count;

  while (1) {
    // Print a prompt
    printf("%% ");
    fflush(stdout);  // Ensure the prompt is displayed

    // Read user input
    bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE_BYTES - 1);
    if (bytes_read < 0) {
      perror("Error");
      return EXIT_FAILURE;
    } else if (bytes_read == 0 || (bytes_read == 1 && buffer[0] == '\n')) {
      // No input received, ignore and continue
      continue;
    }

    // Null-terminate the string
    buffer[bytes_read - 1] = '\0';

    // Check if user wants to end the program
    if (should_exit(buffer)) {
      exit(EXIT_SUCCESS);
    }

    // Parse the input
    arg_count = parse_input(buffer, args, MAX_ARGS);
    if (arg_count == 0) {
      // No arguments found, continue to the next iteration
      continue;
    }

    // Find the command as an executable file
    if (is_executable_file(args[0])) {
      // Execute the command with the provided arguments
      execute_command(args[0], args);
    } else {
      // Find the command in the PATH
      if (!find_command_in_path(args[0], command_path)) {
        fprintf(stderr, "%s: command not found\n", args[0]);
        continue;
      }

      // Execute the command with the provided arguments
      execute_command(command_path, args);
    }
  }

  return 0;
}
