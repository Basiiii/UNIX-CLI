/**
 * @file apaga.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Deletes a file from the filesystem.
 *
 * This function attempts to remove the specified file from the filesystem. If
 * the file is successfully removed, the function returns 0. If the
 * file cannot be removed, for example, due to insufficient permissions or
 * because the file is in use, the program prints the error using perror (see
 * the errno.h header for more information) and returns 1.
 *
 * @version 0.1
 * @date 2024-04-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#define _XOPEN_SOURCE 700

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Name of the utility program. */
#define PROGRAM_NAME "apaga"

/* Help message explaining usage. */
#define HELP_MESSAGE                                    \
  "Usage: apaga <filename>\n"                           \
  "Deletes a given file.\n"                             \
  "Arguments:\n"                                        \
  "  <filename>  The name of the file to be deleted.\n" \
  "\n"                                                  \
  "Options:\n"                                          \
  "  --help      Display this help message.\n"

/**
 * @brief Deletes a file from the filesystem.
 *
 * This function attempts to remove the specified file from the filesystem. If
 * the file is successfully removed, the function returns 0. If the
 * file cannot be removed, for example, due to insufficient permissions or
 * because the file is in use, the program prints the error using perror (see
 * the errno.h header for more information) and returns 1.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of strings containing the command-line arguments.
 *
 * @return int If the file is successfully removed, the function returns 0. If
 * the file cannot be removed, for example, due to insufficient permissions or
 * because the file is in use, the program prints the error using perror (see
 * the errno.h header for more information) and returns 1.
 */
int main(const int argc, const char *argv[]) {
  // Control incorrect usage
  if (argc < 2) {
    fputs("Error: Incorrect usage.\n", stderr);
    fputs(HELP_MESSAGE, stderr);
    return EXIT_FAILURE;
  }

  // Display help command
  if (strcmp(argv[1], "--help") == 0) {
    fputs(HELP_MESSAGE, stdout);
    return EXIT_SUCCESS;
  }

  const char *file_name = argv[1];

  // Delete the file
  if (unlink(file_name) != 0) {
    perror("Error");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
