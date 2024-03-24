/**
 * @file error_codes.h
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Header file containing error code definitions.
 *
 * This header file defines error codes that are used throughout the
 * application. Error codes are integer values that represent different types of
 * errors that may occur during program execution. By using predefined error
 * codes, it becomes easier to identify and handle errors in a consistent manner
 * across the codebase.
 *
 * Error codes in this file are organized into logical groups based on their
 * purpose or usage. Each error code is given a descriptive name to indicate
 * the type of error it represents.
 *
 * For example, error codes related to null pointers may be grouped together,
 * while codes representing file I/O errors may be in a separate group.
 *
 * Error codes defined in this file are intended to improve error handling,
 * facilitate debugging, and provide a standardized way to communicate errors
 * between different parts of the application.
 *
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 */
#ifndef ERROR_CODES_H
#define ERROR_CODES_H

/* GENERAL SUCCESS */
#define SUCCESS 0 // operation success code

/* GENERAL FAILURE */
#define FAILURE 1 // operation failure code

/* MEMORY ERRORS */
#define NULL_POINTER 2 // null pointer error

/* ERROR CODE MESSAGES */
#define DEFAULT_ERROR_MSG "Ocorreu um erro desconhecido.\n"
#define NULL_POINTER_ERROR_MSG "Um apontador tem um valor nullo.\n"

#endif
