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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Name of the utility program. */
#define PROGRAM_NAME "acrescenta"

/* Size of buffer when reading from file */
#define BUFFER_SIZE_BYTES 4096  // 4KB buffer size

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
 * @brief Cleans up resources associated with file descriptors.
 *
 * This function closes the file descriptors passed as arguments and returns a
 * boolean indicating whether the cleanup was successful.
 *
 * @param src_fd The file descriptor of the source file. If `-1`, the source
 *              file is not opened or has been closed already.
 * @param dest_fd The file descriptor of the destination file. If `-1`, the
 *                destination file is not opened or has been closed already.
 * @return true If the cleanup was successful (i.e., both file descriptors were
 *              closed successfully).
 * @return false If an error occurred during cleanup (i.e., one or both file
 *               descriptors failed to close).
 */
bool cleanup(int src_fd, int dest_fd) {
  bool success = true;  // Initialize success flag

  if (src_fd != -1) {
    if (close(src_fd) == -1) {
      perror("Error closing source file");
      success = false;  // Set success flag to false if close fails
    }
  }

  if (dest_fd != -1) {
    if (close(dest_fd) == -1) {
      perror("Error closing destination file");
      success = false;  // Set success flag to false if close fails
    }
  }

  return success;  // Return success flag
}

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

  const char *src_file = argv[1];
  const char *dest_file = argv[2];

  // Open source file in read-only mode
  int src_fd = open(src_file, O_RDONLY);
  if (src_fd == -1) {
    perror("Error opening source file");
    return EXIT_FAILURE;
  }

  // Open destination file in write-only append mode
  int dest_fd = open(dest_file, O_WRONLY | O_APPEND);
  if (dest_fd == -1) {
    perror("Error opening destination file");
    cleanup(src_fd, dest_fd);
    return EXIT_FAILURE;
  }

  // Read data from source file and append to destination file
  char buffer[BUFFER_SIZE_BYTES];
  ssize_t bytes_read;
  while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE_BYTES)) > 0) {
    ssize_t bytes_written = write(dest_fd, buffer, bytes_read);
    if (bytes_written != bytes_read) {
      perror("Error writing to file");
      cleanup(src_fd, dest_fd);
      return EXIT_FAILURE;
    }
  }

  // Check for read error
  if (bytes_read == -1) {
    perror("Error reading from source file");
    cleanup(src_fd, dest_fd);
    return EXIT_FAILURE;
  }

  // Close files and cleanup program
  if (cleanup(src_fd, dest_fd) == false) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
