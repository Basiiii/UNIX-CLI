/**
 * @file find.h
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Header file for functions that find and check for executable files.
 * @version 0.1
 * @date 2024-04-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef FIND_H
#define FIND_H

#include <stdbool.h>

/**
 * @brief Checks if a file is executable.
 *
 * This function checks if the file at the specified path is executable.
 *
 * @param path The path to the file.
 * @return true if the file is executable, false otherwise.
 */
bool isExecutableFile(const char *path);

/**
 * @brief Finds the full path of a command in the PATH environment variable.
 *
 * This function searches for the specified command in the directories listed
 * in the PATH environment variable. If the command is found, its full path is
 * copied to the provided buffer.
 *
 * @param command The name of the command to search for.
 * @param command_path A buffer to store the full path of the command.
 * @return true if the command is found, false otherwise.
 */
bool findCommandInPath(const char *command, char *command_path);

#endif /* FIND_H */
