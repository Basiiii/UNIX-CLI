/**
 * @file parse_args.h
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Function declarations for parsing command-line arguments.
 * @version 0.1
 * @date 2024-04-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

/**
 * @brief Parses the arguments for the ShowFile command.
 *
 * This function parses the arguments provided to the ShowFile command. It finds
 * the first space character in the arguments string and replaces it with a null
 * terminator, effectively separating the command name from the filename.
 *
 * @param args The string containing the arguments for the ShowFile command.
 */
void ParseShowFile(char *args);

#endif /* PARSE_ARGS_H */
