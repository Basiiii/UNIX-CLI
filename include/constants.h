/**
 * @file constants.h
 * @author Enrique Rodrigues (a28602@alunos.ipca.pt)
 * @brief Header file containing constant definitions.
 *
 * This header file defines various constants that are used throughout the
 * application. These constants are used to represent specific values or
 * settings that are used in multiple parts of the codebase.
 *
 * Constants in this file are organized into logical groups based on their
 * purpose or usage. Each constant is given a descriptive name to indicate
 * its meaning or significance.
 *
 * For example, constants related to file permissions may be grouped together,
 * while constants representing error codes may be in a separate group.
 *
 * Constants defined in this file are intended to improve code readability,
 * reduce the risk of errors due to magic numbers, and provide a centralized
 * location for managing shared values.
 *
 * @version 0.1
 * @date 2024-03-20
 *
 * @copyright Copyright (c) 2024
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H

/* GENERAL CONSTANTS */
#define PROGRAM_NAME "UNIX-CLI"  // program name
#define VERSION "0.1"            // current version number
#define EXIT_CMD "termina"       // command to exit CLI

/* BUFFERS */
#define BUFFER_SIZE 4096  // max buffer size

/* FILE INFORMATION */
#define FILE_INFO_STR_SIZE 50  // size of strings in `FileInfo` structure

#endif /* CONSTANTS_H */
