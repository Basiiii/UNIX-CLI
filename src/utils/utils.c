/**
 * @file utils.c
 * @brief Utility functions for various purposes.
 *
 * This file contains a collection of utility functions designed to assist in
 * various tasks across different modules of the application. The functions
 * provided here offer functionality for tasks such as string manipulation,
 * memory management, and other common operations required by different parts
 * of the program.
 *
 * @version 0.1
 * @date 2024-03-24
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
char *DuplicateString(const char *str) {
  size_t len = strlen(str) + 1;
  char *copy = malloc(len);
  if (copy != NULL) {
    memcpy(copy, str, len);
  }
  return copy;
}
