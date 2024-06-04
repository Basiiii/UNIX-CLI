/**
 * @file input_parser.h
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Header file for input parsing functions.
 * @version 0.1
 * @date 2024-04-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

/**
 * @brief Parses an input string into arguments.
 *
 * This function tokenizes the input string by spaces and stores the tokens
 * in the provided array of strings (`args`). The maximum number of arguments
 * that can be stored in the `args` array is specified by `max_args`.
 *
 * @param input The input string to be parsed.
 * @param args An array of strings to store the parsed arguments.
 * @param max_args The maximum number of arguments that can be stored.
 * @return int The number of arguments parsed and stored in the `args` array.
 */
int parseInput(char *input, char *args[], int max_args);

#endif /* INPUT_PARSER_H */
