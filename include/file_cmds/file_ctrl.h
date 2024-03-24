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

#include "constants.h"

/**
 * @brief Structure that holds information of a file.
 *
 * The structure includes the following fields:
 * - `fileType`: The type of the file (e.g., regular file, directory, etc)
 * - `inode`: A long integer that represents the inode number of the file.
 * - `owner`: The name of the file's owner.
 * - `creationTime`: The time the file was created, as a string.
 * - `lastAccessTime`: The last time the file was accessed, as a string.
 * - `lastModificationTime`: The last time the file was modified, as a string.
 *
 * This structure is designed to encapsulate various pieces of information about
 * a file, making it easier to manage and manipulate file metadata in a
 * structured manner.
 */
typedef struct FileInfo {
  char fileType[FILE_INFO_STR_SIZE];             // type of the file
  long inode;                                    // inode value of the file
  char owner[FILE_INFO_STR_SIZE];                // name of the file's owner
  char creationTime[FILE_INFO_STR_SIZE];         // time file was created
  char lastAccessTime[FILE_INFO_STR_SIZE];       // time file was last accessed
  char lastModificationTime[FILE_INFO_STR_SIZE]; // time file was last modified
} FileInfo;

/**
 * @brief Displays the contents of a file to stdout.
 *
 * This function opens the specified file in read-only mode and displays its
 * contents to the standard output (stdout). It reads the file in chunks and
 * writes them to stdout until the end of file is reached.
 *
 * If the file does not exist or cannot be opened for reading, this function
 * prints the error using perror() from the errno.h header and returns a failure
 * error code.
 *
 * @param filename The name of the file who's content is to be displayed.
 * @return Returns a success code if the file is successfully displayed. If an
 * error occurs, prints the error using perror (see the errno.h header for more
 * information) and returns failure error code.
 *
 * @code{.c}
 * // Example usage:
 * int result = ShowFile("example.txt");
 * if (result != SUCCESS) {
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
int CountLines(const char *filename, int *numLines);

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
int DeleteFile(const char *filename);

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
 * FileInfo *info = FileInformation("example.txt");
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
FileInfo *GetFileInfo(const char *filename);

/**
 * @brief Lists the contents of a directory.
 *
 * This function lists all files and directories in the specified directory or
 * in the current directory if not specified. It distinguishes between regular
 * files and directories, printing their names along with a textual indication
 * of their type.
 *
 * If the specified directory cannot be opened or an error occurs while reading
 * its contents, the function returns the corresponding error code stored in
 * errno.
 *
 * @param directory The path of the directory whose contents are to be listed.
 * @return Returns a success code if the directory contents are successfully
 * listed. If an error occurs, returns the error code stored in errno. See the
 * errno.h header file for possible error codes.
 *
 * @code{.c}
 * // Example usage:
 * int result = ListDir("/path/to/directory");
 * if (result != SUCCESS) {
 *     fprintf(stderr, "Error listing directory contents: %s\n",
 *             strerror(result)); return 1;
 * }
 * @endcode
 */
int ListDir(const char *directory);

#endif /* FILE_CTRL_H */
