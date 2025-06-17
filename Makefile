CC = gcc # Compiler
CFLAGS = -std=c2x -Wall -Wextra -pedantic -g # Compiler flags
SRC = main.c util.c parser.c codewriter.c # Source files
OBJ = $(SRC:.c=.o) # Translates .c to .o filenames
EXEC = VMTranslator # Executable filename

# Directories
BUILD_DIR = build
RELEASE_DIR = $(BUILD_DIR)/release
DEBUG_DIR = $(BUILD_DIR)/debug

# Targets with directory prefixes
RELEASE_TARGET = $(RELEASE_DIR)/VMTranslator
DEBUG_TARGET = $(DEBUG_DIR)/VMTranslator-debug

all: $(EXEC) # Default target

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
