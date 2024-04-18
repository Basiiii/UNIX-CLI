/**
 * @file mostra.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Displays the contents of a file to stdout.
 *
 * This program opens the specified file in read-only mode and displays its
 * contents to the standard output (stdout). It reads the file in chunks and
 * writes them to stdout until the end of file is reached.
 *
 * If the file does not exist or cannot be opened for reading, this program
 * prints the error using perror() from the errno.h header and returns a failure
 * error code.
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
#define PROGRAM_NAME "mostra"

/* Size of buffer when reading from file */
#define BUFFER_SIZE 4096  // 4KB buffer size

/* Name of input file. */
static char const *src_file_name;

/* Help message explaining usage. */
#define HELP_MESSAGE                                 \
  "Usage: mostra <filename>\n"                       \
  "Displays the contents of a file to stdout.\n"     \
  "Arguments:\n"                                     \
  "  <filename>  The name of the file to display.\n" \
  "\n"                                               \
  "Options:\n"                                       \
  "  --help      Display this help message.\n"

/**
 * @brief Displays the contents of a file to stdout.
 *
 * This program opens the specified file in read-only mode and displays its
 * contents to the standard output (stdout). It reads the file in chunks and
 * writes them to stdout until the end of file is reached.
 *
 * If the file does not exist or cannot be opened for reading, this program
 * prints the error using perror() from the errno.h header and returns a failure
 * error code.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of strings containing the command-line arguments.
 *
 * @return int Returns 0 if the file is successfully displayed. If an
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

  // Set filename to given name
  src_file_name = argv[1];

  // Open the file in read-only mode
  int fd = open(src_file_name, O_RDONLY);
  if (fd == -1) {
    perror("Error");
    return EXIT_FAILURE;
  }

  // Read and output the contents of the file
  char buffer[BUFFER_SIZE];  // Buffer to store read data
  ssize_t bytes_read;
  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
    if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
      // If there is an error writing to stdout, close the file and exit
      close(fd);
      perror("Error");
      return EXIT_FAILURE;
    }
  }

  // Check for read error
  if (bytes_read == -1) {
    close(fd);
    perror("Error");
    return EXIT_FAILURE;
  }

  // Close the file
  if (close(fd) == -1) {
    perror("Error");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
