/**
 * @file utils.h
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Contains utility declarations.
 * @version 0.1
 * @date 2024-04-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * @brief Checks if the input string indicates the program should exit.
 *
 * This function checks if the input string starts with the exit command
 * defined in the constants header file. If the input string matches the
 * exit command, the function returns true; otherwise, it returns false.
 *
 * @param input The input string to check.
 * @return true if the input string indicates program exit, false otherwise.
 */
bool should_exit(const char *input);

#endif /* UTILS_H */
