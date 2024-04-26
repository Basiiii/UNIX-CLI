# UNIX-CLI

## Overview

This project involves the implementation of a set of commands for file manipulation and a custom command-line interpreter. This project comes with specific requirements and constraints, aiming to test and enhance our understanding of low level system calls to the Linux operating system and, process management.

## Features

1. Implement file manipulation commands:

   - Show file contents
   - Copy files
   - Append contents of one file to another
   - Count lines in a file
   - Delete files
   - Display filesystem information for a file
   - List files and directories in a specified or current directory

2. Develop a custom command-line interpreter:

   - Read and execute user-entered commands
   - Indicate readiness with "%" symbol
   - Execute commands using process execution primitives
   - Suspend interpreter until command completion
   - Support sequential execution of multiple commands
   - Terminate interpreter with a special command

## Usage

1. **Add to PATH:** Ensure that the folder containing the compiled commands is added to your system's PATH variable. This step allows the system to recognize and execute the custom commands. You can achieve this by appending the directory path to your PATH variable in your shell configuration file (e.g., `~/.bashrc`, `~/.bash_profile`, `~/.zshrc`).
2. **Launch UNIX-CLI:** Once the directory is added to the PATH, launch the UNIX-CLI executable file located inside the `build` folder. You'll be greeted with a command-line interface similar to the standard Bash shell, denoted by the "%" symbol indicating readiness for command input.
3. **Enjoy:** Enjoy the enhanced functionality of UNIX-CLI for file manipulation and command execution.

## Compilation

To compile UNIX-CLI, run the `make` command. This command will compile both the custom commands and the command-line interpreter (CLI) together. Alternatively, if you wish to compile only the CLI, you can execute `make cli`. Similarly, to compile only the custom commands, use `make commands`.

```bash
# Compile both the CLI and custom commands
make

# Compile only the CLI
make cli

# Compile only the custom commands
make commands
```

Upon successful compilation, the compiled program and the different commands will be placed inside the `build` folder for easy access and execution.

## Commands

Coming soon.

## Example Usage

Coming soon.
