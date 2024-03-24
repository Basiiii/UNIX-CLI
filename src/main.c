/**
 * @file main.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief  This file contains the main entry point of the program.
 *
 * The program is a command-line utility that provides various functionalities
 * for file manipulation. It includes commands for displaying file contents,
 * copying files, appending file contents, counting lines in files, deleting
 * files, displaying filesystem information, and listing directories.
 *
 * The program also includes a custom command interpreter
 * for executing these commands. Each command is implemented using system calls
 * to perform low-level file and filesystem operations.
 * @version 0.1
 * @date 2024-03-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "constants.h"
#include "error_codes.h"
#include "file_ctrl.h"
#include "handle_errors.h"
#include <sys/types.h>

/**
 * @brief Main entry point of the program.
 *
 * The main function serves as the entry point of the program. It executes the
 * command-line utility, which provides various functionalities for file
 * manipulation. This includes commands for displaying file contents, copying
 * files, appending file contents, counting lines in files, deleting files,
 * displaying filesystem information, and listing directories. Additionally, the
 * program includes a custom command interpreter for executing these commands.
 * Each command is implemented using system calls to perform low-level file and
 * filesystem operations.
 *
 * @return int Returns 0 upon successful execution.
 */
int main() {
  printf("%s version %s.\n\n", PROGRAM_NAME, VERSION);

  char buffer[BUFFER_SIZE];
  ssize_t bytesRead;

  while (1) {
    // Print a prompt
    printf("%% ");
    fflush(stdout); // Ensure the prompt is displayed

    // Read user input
    bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
    if (bytesRead <= 0) {
      perror("Erro");
      return 1;
    }

    // Null-terminate the string
    buffer[bytesRead - 1] = '\0';

    // Check for termination
    if (strncmp(buffer, "termina", strlen("termina")) == 0) {
      break; // Exit the loop
    }

    // Echo the input back to the user
    printf("echo: %s\n", buffer);

    // Parse input and look for commands

    // Create process

    // Call specific function with params on new process
  }

  return 0;
}
