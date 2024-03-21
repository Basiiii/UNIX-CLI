/**
 * @file handle_errors.h
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Header file for error handling functions.
 *
 * This header file declares the function prototypes for handling errors.
 * For example, PrintError, which is responsible for printing error messages
 * based on error codes.
 *
 * Error codes and their associated messages are defined in the error_codes.h
 * header file.
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef HANDLE_ERRORS_H
#define HANDLE_ERRORS_H

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
void PrintError(const int errorCode);

#endif
