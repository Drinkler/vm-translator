#ifndef CODEWRITER_H
#define CODEWRITER_H

#include "parser.h"

typedef struct {
    int label_counter;
    int call_counter;
    int return_counter;
    char file_prefix[BUFSIZ];
    char current_function[BUFSIZ];
} TranslatorContext;

void write_bootstrap(FILE *out);

void write_goto(FILE *out, char *arg1);
void write_label(FILE *out, char *arg1);
void write_if(FILE *out, char *arg1);
void write_function(FILE *out, char *arg1, char *arg2, TranslatorContext *tcx);
void write_arithmetic(FILE *out, char *cmd, TranslatorContext *tcx);
void write_push(FILE *out, char *arg1, char *arg2, TranslatorContext *tcx);
void write_pop(FILE *out, char *arg1, char *arg2, TranslatorContext *tcx);
void write_call(FILE *out, char *arg1, char *arg2, TranslatorContext *tcx);
void write_return(FILE *out, TranslatorContext *tcx);
#endif
