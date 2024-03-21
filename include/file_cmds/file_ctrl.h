/**
 * @file file_ctrl.h
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Header file for file control functions.
 *
 * This header file declares the interface for various functions used to control
 * files. These functions provide functionalities such as reading, writing,
 * copying, appending, and deleting files. Additionally, the file control module
 * includes functions for retrieving information about files, such as file size,
 * permissions, and timestamps.
 *
 * The functions declared in this header file are intended to perform low-level
 * file operations using system calls and provide error handling to ensure
 * robust file manipulation functionalities. They are designed to be used by
 * other modules or applications requiring file management capabilities.
 *
 * Functions in this header file:
 * - ShowFile: Display the contents of a file to stdout.
 * - CopyFile: Copy the contents of one file to another.
 * - AppendToFile: Append the contents of one file to another.
 * - CountLines: Count the number of lines in a file.
 * - DeleteFile: Delete a file from the filesystem.
 * - GetFileInfo: Retrieve information about a file (size, permissions,
 * timestamps).
 * - ListDirectory: List the contents of a directory.
 *
 * @version 0.1
 * @date 2024-03-20
 *
 * @see file_ctrl.c
 */
#ifndef FILE_CTRL_H
#define FILE_CTRL_H

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
int ShowFile(const char *filename);

/**
 * @brief Creates a copy of the specified file.
 *
 * This function creates a new file named "ficheiro.copia" with the content
 * copied from the specified file. If the specified file does not exist or
 * cannot be opened for reading, the function returns the corresponding error
 * code stored in errno.
 *
 * @param filename The name of the file to be copied.
 * @return Returns 0 if the file is successfully copied. If an error occurs,
 * returns the error code stored in errno. See the errno.h header file for
 * possible error codes.
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
int CopyFile(const char *filename);

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
 * @return Returns 0 if the file is successfully copied. If an error occurs,
 * returns the error code stored in errno. See the errno.h header file for
 * possible error codes.
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
int AppendFile(const char *source, const char *destination);

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
 * @return Returns 0 if successful. If an error occurs, returns an error
 * code. The specific error code can be obtained by checking `errno`. For a null
 * pointer error, the function returns a custom error code defined by
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
int CountLines(const char *filename, int *numLines);

#endif /* FILE_CTRL_H */
