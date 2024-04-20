/**
 * @file lista.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Lists the contents of a directory.
 *
 * This function lists all files and directories in the specified directory or
 * in the current directory if not specified. It distinguishes between regular
 * files and directories, printing their names along with a textual indication
 * of their type.
 *
 * @version 0.1
 * @date 2024-04-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#define _XOPEN_SOURCE 700

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Name of the utility program. */
#define PROGRAM_NAME "lista"

/* Size of buffer when reading from file */
#define BUFFER_SIZE 4096  // 4KB buffer size

/* Help message explaining usage. */
#define HELP_MESSAGE                                 \
  "Usage: list (directory)\n"                        \
  "Counts the number of lines a file contains.\n"    \
  "Arguments:\n"                                     \
  "  (file)  OPTIONAL directory, default is `.` .\n" \
  "\n"                                               \
  "Options:\n"                                       \
  "  --help      Display this help message.\n"

/**
 * @brief Lists the contents of a directory.
 *
 * This function lists all files and directories in the specified directory or
 * in the current directory if not specified. It distinguishes between regular
 * files and directories, printing their names along with a textual indication
 * of their type.
 *
 * If the specified directory cannot be opened or an error occurs while reading
 * its contents, the program prints an error message and returns 1.
 *
 * @return Returns 0 if the directory contents are successfully listed. If an
 * error occurs, prints an error message and returns 1.
 */
int main(const int argc, const char *argv[]) {
  // Display help command
  if (argc > 1 && strcmp(argv[1], "--help") == 0) {
    fputs(HELP_MESSAGE, stdout);
    return EXIT_SUCCESS;
  }

  // Set directory name
  const char *dir_name = (argc > 1) ? argv[1] : ".";

  DIR *dir;              // directory pointer
  struct dirent *entry;  // directory entry structure

  // Open the specified directory
  dir = opendir(dir_name);
  if (dir == NULL) {
    fprintf(stderr, "Error opening directory '%s': %s\n", dir_name,
            strerror(errno));
    return EXIT_FAILURE;
  }

  // Print the directory name
  printf("%-30s\t[directory]\n", dir_name);

  // Read directory entries
  while ((entry = readdir(dir)) != NULL) {
    // Ignore "." and ".." entries
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    printf("%-30s\t[file]\n", entry->d_name);
  }

  // Close directory
  if (closedir(dir) == -1) {
    fprintf(stderr, "Error closing directory '%s': %s\n", dir_name,
            strerror(errno));
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
