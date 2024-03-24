/**
 * @file parser.h
 * @brief Declarations for command parsing and execution.
 * @version 0.1
 * @date 2024-03-24
 *
 * This file contains declarations for parsing and executing commands.
 * It defines structures and functions necessary for command processing.
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef PARSER_H
#define PARSER_H

/**
 * @brief Function pointer type for parsing command arguments
 *
 */
typedef void (*ParseFunc)(char *args);

/**
 * @brief Structure representing a command.
 *
 * This structure defines a command, which consists of a name, a function
 * pointer for parsing command arguments, and a function pointer for executing
 * the command.
 *
 */
typedef struct Command {
  const char *name;              /**< The name of the command. */
  ParseFunc parseFunc;           /**< Function pointer for parsing args. */
  int (*func)(const char *args); /**< Function pointer for executing command. */
} Command;

/**
 * @brief Parses and executes a command.
 *
 * This function parses the input string to identify the command and its
 * arguments, then executes the corresponding command function. It splits the
 * input string at the first space character using strtok_r and identifies the
 * command using the IdentifyCommand function. If the command is found, it calls
 * the parsing function and the command function associated with the identified
 * command.
 *
 * @param input The input string containing the command and its arguments.
 */
void ParseAndExecuteCommand(const char *input);

#endif /* PARSER_H */