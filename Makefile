# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -std=c99

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Program name
PROGRAM_NAME = sys-ctrl

# Find all source files recursively in src/
SOURCES := $(shell find $(SRC_DIR) -type f -name '*.c')

# Find all header files recursively in include/
HEADERS := $(shell find $(INCLUDE_DIR) -type f -name '*.h' -exec dirname {} \; | uniq)

# Object files
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Create necessary directories for object files
OBJECT_DIRS := $(sort $(dir $(OBJECTS)))

# Executable name
EXECUTABLE = $(BUILD_DIR)/$(PROGRAM_NAME)

# Default rule to build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Rule to compile each source file into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJECT_DIRS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(patsubst %,-I%,$(HEADERS)) -c $< -o $@

# Create build directories if they don't exist
$(OBJECT_DIRS):
	mkdir -p $@

# Rule to clean the project
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

# Delete build directory
.PHONY: cleanall
cleanall:
	rm -rf $(BUILD_DIR)
