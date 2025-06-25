#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

typedef enum {
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL
} CommandType;

typedef struct {
    char command[BUFSIZ];
    char arg1[BUFSIZ];
    char arg2[BUFSIZ];
} ParsedCommand;

ParsedCommand parse_command(const char *line);
CommandType get_command_type(const char *cmd);

#endif