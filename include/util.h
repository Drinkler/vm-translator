#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdio.h>

char *remove_comment(char *line);
char *remove_whitespace(char *line);
bool advance(FILE *in, char *line);
bool has_vm_extension(const char *filename);
void strip_vm_extension(const char *input, char *output, size_t size);
FILE *open_file(const char *filename, const char *mode);

#endif