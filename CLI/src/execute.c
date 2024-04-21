/**
 * @file execute.c
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Contains functions for executing external commands.
 * @version 0.1
 * @date 2024-04-21
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
void execute_command(const char *command_path, char *args[]) {
  pid_t pid = fork();
  if (pid < 0) {
    fputs("Error executing program.", stderr);
    return;
  }
  if (pid == 0) {
    // Child process
    execvp(command_path, args);
    perror("Error executing command");
    exit(EXIT_FAILURE);
  } else {
    // Parent process
    wait(NULL);           // Wait for the child process to finish
    fputs("\n", stdout);  // Put newline
  }
}
