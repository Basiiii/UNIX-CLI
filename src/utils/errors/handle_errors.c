/**
 * @file handle_errors.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Implementation of functions for handling errors.
 *
 * This file contains the implementation of a function for printing error
 * messages based on error codes. The function PrintError is designed to handle
 * specific error codes and print corresponding error messages to the standard
 * output (stdout).
 *
 * Error codes and their corresponding messages are defined in the error_codes.h
 * header file. The function PrintError serves as a utility for displaying error
 * messages in a consistent format across different parts of the codebase.
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 * @see handle_errors.h
 */
#include <stdio.h>

#include "error_codes.h"

/**
 * @brief Prints error messages based on error codes.
 *
 * This function takes an error code as input and prints the corresponding error
 * message to the standard output (stdout). Error codes and their associated
 * messages are defined in the error_codes.h header file. If the provided error
 * code does not match any known error, a default error message is printed.
 *
 * @param errorCode The error code indicating the type of error.
 *
 * @code{.c}
 * // Example usage:
 * int errorCode = NULL_POINTER;
 * PrintError(errorCode);
 * @endcode
 */
void PrintError(const int errorCode) {
  switch (errorCode) {
  case NULL_POINTER:
    printf(NULL_POINTER_ERROR_MSG);
    break;
  default:
    printf(DEFAULT_ERROR_MSG);
    break;
  }
}
