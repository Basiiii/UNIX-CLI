/**
 * @file conta.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Counts the number of lines in a file.
 *
 * This function opens the specified file in read-only mode and counts the
 * number of lines in the file. It reads the file in chunks and increments a
 * line counter each time a newline character is encountered. The line count is
 * stored in the memory location pointed to by the `numLines` parameter.
 *
 * If the file does not exist or cannot be opened for reading, the program
 * prints the error using perror() from the errno.h header and returns 1.
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
#define PROGRAM_NAME "conta"

/* Size of buffer when reading from file */
#define BUFFER_SIZE_BYTES 4096  // 4KB buffer size

/* Help message explaining usage. */
#define HELP_MESSAGE                              \
  "Usage: conta <file>\n"                         \
  "Counts the number of lines a file contains.\n" \
  "Arguments:\n"                                  \
  "  <file>  The file to be counted.\n"           \
  "\n"                                            \
  "Options:\n"                                    \
  "  --help      Display this help message.\n"

/**
 * @brief Counts the number of lines in a file.
 *
 * This function opens the specified file in read-only mode and counts the
 * number of lines in the file. It reads the file in chunks and increments a
 * line counter each time a newline character is encountered. The line count is
 * stored in the memory location pointed to by the `numLines` parameter.
 *
 * If the file does not exist or cannot be opened for reading, the program
 * prints the error using perror() from the errno.h header and returns 1.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of strings containing the command-line arguments.
 *
 * @return int Returns 0 if the file is successfully counted. If an
 * error occurs, prints the error using perror (see the errno.h header for more
 * information) and returns 1.
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

  const char *src_file = argv[1];
  int num_lines = 0;

  // Open the file in read-only mode
  int fd = open(src_file, O_RDONLY);
  if (fd == -1) {
    perror("Error");
    return EXIT_FAILURE;
  }

  char buffer[BUFFER_SIZE_BYTES];
  ssize_t bytes_read = 0;

  // Read the file in chunks
  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
    // Iterate through buffer and count new lines
    for (ssize_t i = 0; i < bytes_read; i++) {
      if (buffer[i] == '\n') {
        num_lines++;
      }
    }
  }

  // Check for read error
  if (bytes_read == -1) {
    perror("Error");
    close(fd);
    return EXIT_FAILURE;
  }

  // Close the file
  if (close(fd) == -1) {
    perror("Error");
    return EXIT_FAILURE;
  }

  fprintf(stdout, "%d\n", num_lines);

  return EXIT_SUCCESS;
}
