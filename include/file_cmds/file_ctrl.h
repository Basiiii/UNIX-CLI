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

#endif /* FILE_CTRL_H */
