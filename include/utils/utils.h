/**
 * @file utils.h
 * @brief Utility function prototypes.
 *
 * This header file declares the prototypes for utility functions defined in
 * the corresponding utils.c file. These functions provide common functionality
 * such as string manipulation, memory management, and other useful operations
 * for various parts of the program.
 *
 * @version 0.1
 * @date 2024-03-24
 * @copyright Copyright (c) 2024
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Creates a duplicate of the input string.
 *
 * This function allocates memory for a new string containing a duplicate of
 * the input string `str`. It calculates the length of the input string,
 * including the null terminator, allocates memory for the duplicate string,
 * copies the contents of the input string into the newly allocated memory, and
 * returns a pointer to the duplicate string. It is the responsibility of the
 * caller to free the memory allocated for the duplicate string when it is no
 * longer needed.
 *
 * @param str The input string to be duplicated.
 * @return A pointer to the duplicate string if memory allocation succeeds,
 * otherwise returns NULL.
 */
char *DuplicateString(const char *str);

#endif /* UTILS_H */
