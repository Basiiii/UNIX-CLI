/**
 * @file copia.c
 *
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @author Diogo Araujo Machado (a26042@alunos.ipca.pt)
 *
 * @brief Creates a copy of the specified file.
 *
 * This program utility creates a new file named "ficheiro.copia" with the
 * content copied from the specified file. If the specified file does not exist
 * or cannot be opened for reading, the utility program returns 1.
 *
 * @version 0.2
 * @date 2024-04-18
 *
 * @section Modifications
 * - 2024-04-22: Added optional copy name parameter.
 *   Diogo Araujo Machado (a26042@alunos.ipca.pt)
 *
 */
#define _XOPEN_SOURCE 700

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Name of the utility program. */
#define PROGRAM_NAME "copia"

/* Size of buffer when reading from file */
#define BUFFER_SIZE 4096  // 4KB buffer size

/* Name of input file. */
static char const *src_file_name = NULL;

/* Name of destination file. */
static char *dest_file_name = NULL;

/* Help message explaining usage. */
#define HELP_MESSAGE                                          \
  "Usage: copia <filename> <destination file>\n"              \
  "Creates a copy of a given file.\n"                         \
  "Arguments:\n"                                              \
  "  <file_name>  The name of the file to create a copy of.\n" \
  "  (copy_name)  The name of the copy (optional).\n"           \
  "\n"                                                        \
  "Options:\n"                                                \
  "  --help      Display this help message.\n"

/**
 * @brief Creates a copy of the specified file.
 *
 * This program utility creates a new file named "ficheiro.copia" with the
 * content copied from the specified file. If the specified file does not exist
 * or cannot be opened for reading, the program prints the error using perror()
 * from the errno.h header and returns 1.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of strings containing the command-line arguments.
 *
 * @return int Returns 0 if the file is successfully copied. If an
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

  // Set `sourcefilename` to given name
  src_file_name = argv[1];

  // in case the user gives a name for the destination file
  if (argc == 3 && strcmp(argv[2], "--help") != 0) {
    dest_file_name = argv[2];
  } else {  // in case the user doesn't give a name for the destination file
    dest_file_name =
        (char *)malloc(strlen(src_file_name) + strlen(".copia") + 1);
    if (dest_file_name == NULL) {
      fputs("Error: Memory allocation failed.\n", stderr);
      return EXIT_FAILURE;
    }
    strcpy(dest_file_name, src_file_name);
    strcat(dest_file_name, ".copia");
  }

  // Open the source file in read-only mode
  int srcfd = open(src_file_name, O_RDONLY);
  if (srcfd == -1) {
    perror("Error");
    return EXIT_FAILURE;
  }

  // Open and set destination file permissions to match the source file
  int destfd =
      open(dest_file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
  if (destfd == -1) {
    close(srcfd);
    perror("Error");
    return EXIT_FAILURE;
  }

  // Read data from source file and write to destination file
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;
  while ((bytes_read = read(srcfd, buffer, sizeof(buffer))) > 0) {
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

  // Free memory
  if (dest_file_name != NULL && argc == 2) {
    free(dest_file_name);
    dest_file_name = NULL;
  }
  return EXIT_SUCCESS;
}
