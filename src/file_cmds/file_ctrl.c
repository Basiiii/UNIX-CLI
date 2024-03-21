/**
 * @file file_ctrl.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Implementation of functions for controlling files.
 *
 * This file contains the implementation of various functions for controlling
 * files. These functions provide functionalities such as reading, writing,
 * copying, appending, and deleting files. Additionally, the file_ctrl module
 * includes functions for retrieving information about files, such as file size,
 * permissions, and timestamps.
 *
 * The functions in this module are designed to perform low-level file
 * operations using system calls and provide error handling to ensure robust
 * file manipulation functionalities. They are intended to be used by other
 * modules or applications requiring file management capabilities.
 * @version 0.1
 * @date 2024-03-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "constants.h"

/**
 * @brief Displays the contents of a file to stdout.
 *
 * This function opens the specified file in read-only mode and displays its
 * contents to the standard output (stdout). It reads the file in chunks of
 * 4096 bytes and writes them to stdout until the end of file is reached.
 *
 * If the file does not exist or cannot be opened for reading, this function
 * returns the corresponding error code stored in errno. You can use the
 * strerror() function to convert the error code to a human-readable error
 * message.
 *
 * @param filename The name of the file who's content is to be displayed.
 * @return Returns 0 if the file is successfully displayed. If an error occurs,
 * returns the error code stored in errno. See the errno.h header file for
 * possible error codes.
 *
 * @code{.c}
 * // Example usage:
 * int result = ShowFile("example.txt");
 * if (result != SUCCESS) {
 *     fprintf(stderr, "Error displaying file: %s\n", strerror(result));
 *     return 1;
 * }
 * @endcode
 */
int ShowFile(const char *filename) {
  // Open the file in read only
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    return errno;
  }

  // Read and output the contents of the file
  char buffer[4096]; // Buffer to store read data
  ssize_t bytes_read;
  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
    if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
      // If there is an error writing to stdout, close the file and return errno
      close(fd);
      return errno;
    }
  }

  // Check for read error
  if (bytes_read == -1) {
    close(fd);
    return errno;
  }

  // Close the file
  if (close(fd) == -1) {
    return errno;
  }

  return SUCCESS;
}
