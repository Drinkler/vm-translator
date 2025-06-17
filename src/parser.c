#include "parser.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

CommandType get_command_type(const char *cmd) {
    if (strcmp(cmd, "push") == 0) return C_PUSH;
    if (strcmp(cmd, "pop") == 0) return C_POP;
    if (strcmp(cmd, "label") == 0) return C_LABEL;
    if (strcmp(cmd, "goto") == 0) return C_GOTO;
    if (strcmp(cmd, "if-goto") == 0) return C_IF;
    if (strcmp(cmd, "function") == 0) return C_FUNCTION;
    if (strcmp(cmd, "call") == 0) return C_CALL;
    if (strcmp(cmd, "return") == 0) return C_RETURN;
    return C_ARITHMETIC;
}

ParsedCommand parse_command(const char *line) {
    char temp[BUFSIZ];
    strncpy(temp, line, BUFSIZ);
    temp[BUFSIZ - 1] = '\0';

    ParsedCommand pc = {"", "", ""};

    char *token = strtok(temp, " \t\r\n");
    if (token) strncpy(pc.command, token, BUFSIZ);
    token = strtok(NULL, " \t\r\n");
    if (token) strncpy(pc.arg1, token, BUFSIZ);
    token = strtok(NULL, " \t\r\n");
    if (token) strncpy(pc.arg2, token, BUFSIZ);

    return pc;
}