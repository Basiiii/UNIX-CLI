/**
 * @file main.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief  This file contains the main entry point of the program.
 *
 * The program is a command-line utility that provides various functionalities
 * for file manipulation and filesystem management. It includes commands for
 * displaying file contents, copying files, appending file contents, counting
 * lines in files, deleting files, displaying filesystem information, and
 * listing directories.
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
#include <string.h>

#include "constants.h"
#include "error_codes.h"
#include "file_ctrl.h"
#include "handle_errors.h"

/**
 * @brief Main entry point of the program.
 *
 * The main function serves as the entry point of the program. It executes the
 * command-line utility, which provides various functionalities for file
 * manipulation and filesystem management. This includes commands for displaying
 * file contents, copying files, appending file contents, counting lines in
 * files, deleting files, displaying filesystem information, and listing
 * directories. Additionally, the program includes a custom command interpreter
 * for executing these commands. Each command is implemented using system calls
 * to perform low-level file and filesystem operations.
 *
 * @return int Returns 0 upon successful execution.
 */
int main() {
  printf("%s version %s.\n\n", PROGRAM_NAME, VERSION);

  // int result = ShowFile("test");
  // if (result != SUCCESS) {
  //   perror("Error");
  // }

  // int result1 = CopyFile("test");
  // if (result1 != SUCCESS) {
  //   perror("Error");
  // }

  // int result2 = AppendFile("source", "dest");
  // if (result2 != SUCCESS) {
  //   perror("Error");
  // }

  // int numLines = 0;
  // int result3 = CountLines("test", &numLines);
  // if (result3 < SUCCESS) {
  //   PrintError(result3);
  // } else if (result3 > SUCCESS) {
  //   perror("Error");
  // }
  // printf("Number of lines: %d\n", numLines);

  // int result4 = DeleteFile("test");
  // if (result4 != SUCCESS) {
  //   perror("Error");
  // }

  return 0;
}
