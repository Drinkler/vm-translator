#include "util.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *remove_comment(char *line) {
    char *comment = strstr(line, "//");
    if (comment) *comment = '\0';
    return line;
}

char *remove_whitespace(char *line) {
    // Trim leading whitespaces
    while (isspace((unsigned char)*line)) line++;

    // Trim trailing whitespaces
    char *end = line + strlen(line) - 1;
    while (end >= line && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';

    return line;
}

bool advance(FILE *in, char *line) {
    while (fgets(line, BUFSIZ, in)) {
        char *clean_line = remove_comment(line);
        clean_line = remove_whitespace(clean_line);
        if (*clean_line != '\0') return true;
    }
    return false;
}

bool has_vm_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');  // Find the last occurrence of '.', if found it returns the pointer to '.' otherwise NULL.
    return dot && strcmp(dot, ".vm") == 0;     // Did it find the dot and is the char pointer (dot and the following array) same as '.vm'?
}

void strip_vm_extension(const char *input, char *output, size_t size) {
    strncpy(output, input, size);  // strncpy instead of strcpy to have a boundary check and not get a buffer overflow
    char *dot = strrchr(output, '.');
    if (dot) *dot = '\0';
}

FILE *open_file(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (!file) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    return file;
}