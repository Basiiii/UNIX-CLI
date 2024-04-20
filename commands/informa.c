/**
 * @file informa.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Retrieves and stores various pieces of information about a specified
 * file.
 *
 * This program retrieves file information such as file type, owner, creation
 * time, last access time, last modification time, and inode number.
 *
 * @version 0.1
 * @date 2024-04-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#define _XOPEN_SOURCE 700

#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/* Name of the utility program. */
#define PROGRAM_NAME "informa"

/* Size of buffer when reading from file */
#define BUFFER_SIZE 4096  // 4KB buffer size

/* Name of input file. */
static char const *file_name;

/* Help message explaining usage. */
#define HELP_MESSAGE                                            \
  "Usage: informa <file_name>\n"                                \
  "Displays information for a given file..\n"                   \
  "Arguments:\n"                                                \
  "  <filename>  The name of the file to get information of.\n" \
  "\n"                                                          \
  "Options:\n"                                                  \
  "  --help      Display this help message.\n"

/* Size of the file name string used in the file info structure */
#define FILE_NAME_STR_SIZE 256

/* Size of the file type string used in the file info structure */
#define FILE_TYPE_STR_SIZE 32

/* Size of the owner name string used in the file info structure */
#define FILE_OWNER_STR_SIZE 256

/**
 * @brief Structure that holds information of a file.
 *
 * The structure includes the following fields:
 * - `file_name`: The name of the file.
 * - `owner`: The name of the file's owner.
 * - `file_type`: The type of the file (e.g., regular file, directory, etc).
 * - `inode`: A value representing the inode number of the file.
 * - `creation_time`: The time the file was created, as a Unix timestamp.
 * - `last_access_time`: The last time the file was accessed, as a Unix
 *      timestamp.
 * - `last_modification_time`: The last time the file was modified, as a Unix
 *      timestamp.
 *
 * This structure is designed to encapsulate various pieces of information about
 * a file, making it easier to manage and manipulate file metadata in a
 * structured manner.
 */
typedef struct FileInfo {
  char file_name[FILE_NAME_STR_SIZE];  // name of the file
  char owner[FILE_OWNER_STR_SIZE];     // name of the file's owner
  char file_type[FILE_TYPE_STR_SIZE];  // type of the file
  ino_t inode;                         // inode value of the file
  time_t creation_time;                // time file was created
  time_t last_access_time;             // time file was last accessed
  time_t last_modification_time;       // time file was last modified
} FileInfo;

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
 * @param file_name The name of the file to retrieve information about.
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
 * // Remember to free the allocated memory
 * free(info);
 * @endcode
 */
static FileInfo *getFileInfo(const char *file_name) {
  struct stat file_stat;  // structure to hold stat() function return
  struct passwd *pw;      // structure to hold user information

  FileInfo *info = (FileInfo *)malloc(sizeof(FileInfo));
  if (info == NULL) {
    return NULL;  // Memory allocation failure
  }

  // Set file name value
  strcpy(info->file_name, file_name);

  // Retrieve file information
  if (stat(file_name, &file_stat) == -1) {
    perror("Error");
    free(info);
    return NULL;
  }

  // Determine file type
  switch (file_stat.st_mode & S_IFMT) {
    case S_IFREG:
      strcpy(info->file_type, "regular file");
      break;
    case S_IFDIR:
      strcpy(info->file_type, "directory");
      break;
    case S_IFLNK:
      strcpy(info->file_type, "symbolic link");
      break;
    default:
      strcpy(info->file_type, "unknown");
      break;
  }

  // Get the owner's name from user ID
  pw = getpwuid(file_stat.st_uid);
  if (pw == NULL) {
    free(info);
    return NULL;
  }
  strcpy(info->owner, pw->pw_name);

  // Store timestamps
  info->creation_time = file_stat.st_ctime;
  info->last_access_time = file_stat.st_atime;
  info->last_modification_time = file_stat.st_mtime;

  // Store inode number
  info->inode = file_stat.st_ino;

  return info;
}

/**
 * @brief Prints information stored in a FileInfo structure in a formatted
 * manner.
 *
 * This function takes a pointer to a FileInfo structure and prints out the
 * details of the file, including the owner's name, file type, inode number,
 * creation time, last access time, and last modification time. The information
 * is printed with appropriate labels and formatting to enhance readability.
 *
 * @param info A pointer to a FileInfo structure containing information about a
 * file.
 */
static void printFileInfo(const FileInfo *info) {
  printf("     File: %s\n", info->file_name);
  printf("     Type: %s\n", info->file_type);
  printf("    Owner: %s\n", info->owner);
  printf("    Inode: %ld\n", (long)info->inode);
  printf(" Creation: %s", ctime(&info->creation_time));
  printf("   Access: %s", ctime(&info->last_access_time));
  printf("   Change: %s", ctime(&info->last_modification_time));
}

/**
 * @brief Retrieves and stores various pieces of information about a specified
 * file.
 *
 * This program retrieves file information such as file type, owner, creation
 * time, last access time, last modification time, and inode number.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of strings containing the command-line arguments.
 *
 * @return int Returns 0 if the file information is successfully fetched. If an
 * error occurs, prints the error using perror (see the errno.h header for more
 * information) and returns 1.
 *
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

  // Set variable to value of given parameter
  file_name = argv[1];

  FileInfo *file_info = getFileInfo(file_name);
  if (file_info == NULL) {
    fputs("Memory error while fetching file information.", stderr);
    return EXIT_FAILURE;
  }

  printFileInfo(file_info);

  free(file_info);

  return EXIT_SUCCESS;
}
