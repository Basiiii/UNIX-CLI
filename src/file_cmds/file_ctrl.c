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
#define _XOPEN_SOURCE 700

#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "constants.h"
#include "error_codes.h"
#include "file_ctrl.h"

/**
 * @brief Displays the contents of a file to stdout.
 *
 * This function opens the specified file in read-only mode and displays its
 * contents to the standard output (stdout). It reads the file in chunks and
 * writes them to stdout until the end of file is reached.
 *
 * If the file does not exist or cannot be opened for reading, this function
 * returns the corresponding error code stored in errno. You can use the
 * strerror() function to convert the error code to a human-readable error
 * message.
 *
 * @param filename The name of the file who's content is to be displayed.
 * @return Returns a success code if the file is successfully displayed. If an
 * error occurs, returns the error code stored in errno. See the errno.h header
 * file for possible error codes.
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
  // Open the file in read-only mode
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    return errno;
  }

  // Read and output the contents of the file
  char buffer[BUFFER_SIZE]; // Buffer to store read data
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

/**
 * @brief Creates a copy of the specified file.
 *
 * This function creates a new file named "ficheiro.copia" with the content
 * copied from the specified file. If the specified file does not exist or
 * cannot be opened for reading, the function returns the corresponding error
 * code stored in errno.
 *
 * @param filename The name of the file to be copied.
 * @return Returns a success code if the file is successfully copied. If an
 * error occurs, returns the error code stored in errno. See the errno.h header
 * file for possible error codes.
 *
 * @code{.c}
 * // Example usage:
 * int result = CopyFile("ficheiro.txt");
 * if (result != SUCCESS) {
 *     fprintf(stderr, "Error copying file: %s\n", strerror(result));
 *     return 1;
 * }
 * @endcode
 */
int CopyFile(const char *filename) {
  // TODO: Nome do ficheiro literalmente `ficheiro.copia`?
  // TODO: Diretoria do ficheiro na dir atual ou permitimos que o utilizador
  // possa escolher?
  // TODO: Podemos utilizar perror() para apresentar o erro ao utilizador?

  // Open the source file in read-only mode
  int srcfd = open(filename, O_RDONLY);
  if (srcfd == -1) {
    return errno;
  }

  // Create or truncate the destination file and set its permissions to match
  // the source file
  int destfd =
      open("ficheiro.copia", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
  if (destfd == -1) {
    close(srcfd);
    return errno;
  }

  // Read data from source file and write to destination file
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;
  while ((bytes_read = read(srcfd, buffer, sizeof(buffer))) > 0) {
    ssize_t bytes_written = write(destfd, buffer, bytes_read);
    if (bytes_written != bytes_read) {
      close(srcfd);
      close(destfd);
      return errno;
    }
  }

  // Check for read error
  if (bytes_read == -1) {
    close(srcfd);
    close(destfd);
    return errno;
  }

  // Close files
  if (close(srcfd) == -1 || close(destfd) == -1) {
    return errno;
  }

  return SUCCESS;
}

/**
 * @brief Appends the content of one file to another.
 *
 * This function appends the content of the source file to the end of the
 * destination file. If either of the files does not exist or cannot be opened
 * for reading or writing, the function returns the corresponding error
 * code stored in errno.
 *
 * @param source The name of the file whose content is to be appended.
 * @param destination The name of the file to which the content is to be
 * appended.
 * @return Returns a success code if the file is successfully copied. If an
 * error occurs, returns the error code stored in errno. See the errno.h header
 * file for possible error codes.
 *
 * @code{.c}
 * // Example usage:
 * int result = AppendFile("source.txt", "destination.txt");
 * if (result != SUCCESS) {
 *     fprintf(stderr, "Error appending file: %s\n", strerror(result));
 *     return 1;
 * }
 * @endcode
 */
int AppendFile(const char *source, const char *destination) {
  // Open source file in read-only mode
  int sourcefd = open(source, O_RDONLY);
  if (sourcefd == -1) {
    return errno;
  }

  // Open destination file in read-only append mode
  int destfd = open(destination, O_WRONLY | O_APPEND);
  if (destfd == -1) {
    close(sourcefd);
    return errno;
  }

  char buffer[BUFFER_SIZE];
  ssize_t bytesRead;

  // Read data from source file and append to destination file
  while ((bytesRead = read(sourcefd, buffer, BUFFER_SIZE)) > 0) {
    ssize_t bytesWritten = write(destfd, buffer, bytesRead);
    if (bytesWritten == -1) {
      close(sourcefd);
      close(destfd);
      return errno;
    }
  }

  // Check for read error
  if (bytesRead == -1) {
    close(sourcefd);
    close(destfd);
    return errno;
  }

  // Close files
  close(sourcefd);
  close(destfd);

  return SUCCESS;
}

/**
 * @brief Counts the number of lines in a file.
 *
 * This function opens the specified file in read-only mode and counts the
 * number of lines in the file. It reads the file in chunks and increments a
 * line counter each time a newline character is encountered. The line count is
 * stored in the memory location pointed to by the `numLines` parameter.
 *
 * If the file does not exist or cannot be opened for reading, this function
 * returns an error code and sets `errno` to the appropriate error code. If the
 * `numLines` pointer is NULL, the function returns a custom error code
 * indicating a null pointer error.
 *
 * @param filename The name of the file whose lines are to be counted.
 * @param numLines Pointer to an int where the number of lines will be stored.
 * @return Returns a success code if successful. If an error occurs, returns an
 * error code. The specific error code can be obtained by checking `errno`. For
 * a null pointer error, the function returns a custom error code defined by
 * `NULL_POINTER`.
 *
 * @code{.c}
 * // Example usage:
 * int lineCount;
 * int result = CountLines("example.txt", &lineCount);
 * if (result != SUCCESS) {
 *     if (result == NULL_POINTER) {
 *         fprintf(stderr, "Error: Null pointer provided.\n");
 *     } else {
 *         fprintf(stderr, "Error counting lines: %s\n", strerror(errno));
 *     }
 *     return 1;
 * }
 * printf("Number of lines: %d\n", lineCount);
 * @endcode
 */
int CountLines(const char *filename, int *numLines) {
  // Check if pointer is NULL
  if (numLines == NULL) {
    return NULL_POINTER;
  }

  // Initialize number of lines
  *numLines = 0;

  // Open the file in read-only mode
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    return errno;
  }

  // Buffer to store read data
  char buffer[BUFFER_SIZE];
  ssize_t bytesRead;

  // Read the file character by character
  while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
    // Iterate through buffer and count new lines
    for (ssize_t i = 0; i < bytesRead; i++) {
      if (buffer[i] == '\n') {
        (*numLines)++;
      }
    }
  }

  // Check for read error
  if (bytesRead == -1) {
    close(fd);
    return errno;
  }

  // Close the file
  if (close(fd) == -1) {
    return errno;
  }

  return SUCCESS;
}

/**
 * @brief Deletes a file from the filesystem.
 *
 * This function attempts to remove the specified file from the filesystem. If
 * the file is successfully removed, the function returns a success code. If the
 * file cannot be removed, for example, due to insufficient permissions or
 * because the file is in use, the function returns an error code. The specific
 * error code can be obtained by checking `errno`.
 *
 * @param filename The name of the file to be deleted.
 * @return Returns a success code if the file is successfully deleted. If an
 * error occurs, returns an error code. The specific error code can be obtained
 * by checking `errno`.
 *
 * @code{.c}
 * // Example usage:
 * int result = DeleteFile("example.txt");
 * if (result != 0) {
 *     fprintf(stderr, "Error deleting file: %s\n", strerror(errno));
 *     return 1;
 * }
 * printf("File deleted successfully.\n");
 * @endcode
 */
int DeleteFile(const char *filename) {
  // Delete the file
  int result = unlink(filename);

  // If we cannot delete return error code
  if (result != 0) {
    return errno;
  }

  return SUCCESS;
}

/**
 * @brief Retrieves and stores various pieces of information about a specified
 * file.
 *
 * This function retrieves file information such as file type, owner, creation
 * time, last access time, last modification time, and inode number. It
 * allocates memory for a `FileInfo` struct, fills it with the retrieved
 * information, and returns a pointer to this struct. If any error occurs during
 * the process, such as failing to retrieve file information or allocating
 * memory, the function frees any allocated memory and returns NULL.
 *
 * @param filename The name of the file to retrieve information about.
 * @return A pointer to a `FileInfo` struct containing the file information.
 * Returns NULL if an error occurs.
 *
 * @code{.c}
 * // Example usage:
 * FileInfo *info = GetFileInfo("example.txt");
 * if (info == NULL) {
 *     fprintf(stderr, "Error retrieving file information.\n");
 *     return 1;
 * }
 * printf("File type: %s\n", info->fileType);
 * printf("Owner: %s\n", info->owner);
 * printf("Creation time: %s", info->creationTime);
 * printf("Last access time: %s", info->lastAccessTime);
 * printf("Last modification time: %s", info->lastModificationTime);
 * printf("Inode: %ld\n", info->inode);
 * // Remember to free the allocated memory
 * free(info);
 * @endcode
 */
FileInfo *GetFileInfo(const char *filename) {
  struct stat fileStat; // structure to hold stat() function return
  struct passwd *pw;    // structure to hold user information

  FileInfo *info = (FileInfo *)malloc(sizeof(FileInfo));
  if (info == NULL) {
    return NULL; // Memory allocation failure
  }

  // Retrieve file information
  if (stat(filename, &fileStat) == -1) {
    free(info);
    return NULL;
  }

  // Determine file type
  switch (fileStat.st_mode & S_IFMT) {
  case S_IFREG:
    strcpy(info->fileType, "regular file");
    break;
  case S_IFDIR:
    strcpy(info->fileType, "directory");
    break;
  case S_IFLNK:
    strcpy(info->fileType, "symbolic link");
    break;
  default:
    strcpy(info->fileType, "unknown");
    break;
  }

  // Get the owner's name from user ID
  pw = getpwuid(fileStat.st_uid);
  if (pw == NULL) {
    free(info);
    return NULL;
  }
  strcpy(info->owner, pw->pw_name);

  // Store timestamps
  strcpy(info->creationTime, ctime(&fileStat.st_ctime));
  strcpy(info->lastAccessTime, ctime(&fileStat.st_atime));
  strcpy(info->lastModificationTime, ctime(&fileStat.st_mtime));

  // Store inode number
  info->inode = fileStat.st_ino;

  return info;
}
