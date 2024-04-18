/**
 * @file acrescenta.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Appends the content of one file to another.
 *
 * This program utility appends the content of the source file to the end of the
 * destination file. If either of the files does not exist or cannot be opened
 * for reading or writing, the function returns an error code.
 *
 * @version 0.1
 * @date 2024-04-18
 */
#define _XOPEN_SOURCE 700

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Name of the utility program. */
#define PROGRAM_NAME "acrescenta"

/* Size of buffer when reading from file */
#define BUFFER_SIZE 4096  // 4KB buffer size

/* Name of input file. */
static char const *src_file_name;

/* Name of destination file. */
static char const *dest_file_name;

/* Help message explaining usage. */
#define HELP_MESSAGE                                                        \
  "Usage: acrescenta <file_with_contents> <destination>\n"                  \
  "Appends content of a file to another file.\n"                            \
  "Arguments:\n"                                                            \
  "  <file_with_contents>  The file with the contents to append.\n"         \
  "  <destination>         The file where the contents will be appended.\n" \
  "\n"                                                                      \
  "Options:\n"                                                              \
  "  --help      Display this help message.\n"

/**
 * @brief Appends the content of one file to another.
 *
 * This program utility appends the content of the source file to the end of the
 * destination file. If either of the files does not exist or cannot be opened
 * for reading or writing, the function returns an error code.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of strings containing the command-line arguments.
 *
 * @return Returns 0 if the file is successfully copied. If an error occurs,
 * returns 1.
 */
int main(const int argc, const char *argv[]) {
  // Display help command
  if ((argc == 2) && (strcmp(argv[1], "--help") == 0)) {
    fputs(HELP_MESSAGE, stdout);
    return EXIT_SUCCESS;
  }

  // Control incorrect usage
  if (argc < 3) {
    fputs("Error: Incorrect usage.\n", stderr);
    fputs(HELP_MESSAGE, stderr);
    return EXIT_FAILURE;
  }

  // Set `source_file_name` and `dest_file_name` to parameter values
  src_file_name = argv[1];
  dest_file_name = argv[2];

  // Open source file in read-only mode
  int srcfd = open(src_file_name, O_RDONLY);
  if (srcfd == -1) {
    perror("Error");
    return EXIT_FAILURE;
  }

  // Open destination file in write-only append mode
  int destfd = open(dest_file_name, O_WRONLY | O_APPEND);
  if (destfd == -1) {
    perror("Error");
    close(srcfd);
    return EXIT_FAILURE;
  }

  // Read data from source file and append to destination file
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;
  while ((bytes_read = read(srcfd, buffer, BUFFER_SIZE)) > 0) {
    ssize_t bytes_written = write(destfd, buffer, bytes_read);
    if (bytes_written != bytes_read) {
      perror("Error");
      close(srcfd);
      close(destfd);
      return EXIT_FAILURE;
    }
  }

  // Check for read error
  if (bytes_read == -1) {
    perror("Error:");
    close(srcfd);
    close(destfd);
    return EXIT_FAILURE;
  }

  // Close files
  if (close(srcfd) == -1 || close(destfd) == -1) {
    perror("Error:");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
