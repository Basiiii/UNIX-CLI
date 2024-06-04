/**
 * @file execute.h
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Header file for functions that execute files.
 * @version 0.1
 * @date 2024-04-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef EXECUTE_H
#define EXECUTE_H

/**
 * @brief Executes a command with the given arguments.
 *
 * This function creates a child process using fork() and executes the specified
 * command with the provided arguments using execvp(). If the fork or execvp
 * operation fails, an error message is printed, and the function returns.
 *
 * @param command_path The path to the command to be executed.
 * @param args An array of strings containing the arguments for the command.
 */
void executeCommand(const char *command_path, char *args[]);

#endif /* EXECUTE_H */
