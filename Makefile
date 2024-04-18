# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -D_POSIX_C_SOURCE=200112L

# Directories
BUILD_DIR = build
COMMANDS_DIR = commands
CLI_DIR = CLI
INCLUDE_DIR = $(CLI_DIR)/include
SRC_DIR = $(CLI_DIR)/src

# Program name
PROGRAM_NAME = unix-cli

# Find all source files in commands/
COMMAND_SOURCES := $(wildcard $(COMMANDS_DIR)/*.c)

# Object files for commands
COMMAND_OBJECTS := $(patsubst $(COMMANDS_DIR)/%.c,$(BUILD_DIR)/commands/%.o,$(COMMAND_SOURCES))

# Source files for the main program in CLI/
CLI_SOURCES := $(wildcard $(SRC_DIR)/*.c)

# Header files for the main program in CLI/
CLI_HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)

# Object files for the main program
CLI_OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(CLI_SOURCES))

# Default rule to build the executable
$(PROGRAM_NAME): cli commands

# Rule to compile the CLI
.PHONY: cli
cli: $(CLI_OBJECTS)
	$(CC) $(CFLAGS) $(CLI_OBJECTS) -o $(BUILD_DIR)/$(PROGRAM_NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(CLI_HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< -c -o $@

# Rule to compile each .c file in commands folder into separate executables
.PHONY: commands
commands: $(COMMAND_OBJECTS)
	@for obj in $(COMMAND_OBJECTS); do \
		exe=$$(basename $$obj .o); \
		echo "Linking $$exe from $$obj"; \
		$(CC) $(CFLAGS) $$obj -o $(BUILD_DIR)/commands/$$exe; \
	done

# Pattern rule to compile .c files in commands directory into .o files
$(BUILD_DIR)/commands/%.o: $(COMMANDS_DIR)/%.c | $(BUILD_DIR)/commands
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< -c -o $@

# Create build directories if they don't exist
$(BUILD_DIR)/commands:
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

# Rule to clean the project
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Delete build directory
.PHONY: cleanall
cleanall:
	rm -rf $(BUILD_DIR)
