#include "codewriter.h"

#include <stdio.h>

void write_bootstrap(FILE *output_file) {
    fputs("@256\nD=A\n@SP\nM=D\n", output_file);

    fputs(
        "@Sys.init$ret.bootstrap\n"
        "D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
        "@LCL\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
        "@ARG\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
        "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
        "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n"
        "@SP\nD=M\n@5\nD=D-A\n@ARG\nM=D\n"
        "@SP\nD=M\n@LCL\nM=D\n"
        "@Sys.init\n0;JMP\n"
        "(Sys.init$ret.bootstrap)\n\n",
        output_file);
}

void write_goto(FILE *out, char *arg1) {
    fprintf(out, "@%s\n0;JMP\n\n", arg1);
}

void write_label(FILE *out, char *arg1) {
    fprintf(out, "(%s)\n\n", arg1);
}

void write_if(FILE *out, char *arg1) {
    fprintf(out, "@SP\nAM=M-1\nD=M\n@%s\nD;JNE\n\n", arg1);
}

void write_function(FILE *out, char *arg1, char *arg2, TranslatorContext *tcx) {
    int n_vars = (int)strtol(arg2, NULL, 10);
    snprintf(tcx->current_function, BUFSIZ, "%s", arg1);
    tcx->return_counter = 0;
    fprintf(out, "(%s)\n", arg1);
    for (int i = 0; i < n_vars; i++) {
        fprintf(out, "@SP\nA=M\nM=0\n@SP\nM=M+1\n");
    }
    fprintf(out, "\n");
}

void write_arithmetic(FILE *out, char *cmd, TranslatorContext *tcx) {
    if (strcmp(cmd, "add") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\nA=A-1\nM=D+M\n\n");
    } else if (strcmp(cmd, "sub") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D\n\n");
    } else if (strcmp(cmd, "neg") == 0) {
        fprintf(out, "@SP\nA=M-1\nM=-M\n\n");
    } else if (strcmp(cmd, "eq") == 0 || strcmp(cmd, "gt") == 0 || strcmp(cmd, "lt") == 0) {
        const char *jump = strcmp(cmd, "eq") == 0 ? "JEQ" : strcmp(cmd, "gt") == 0 ? "JGT"
                                                                                   : "JLT";
        int n = tcx->label_counter++;
        fprintf(out,
                "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n"
                "@TRUE%d\nD;%s\n"
                "@SP\nA=M-1\nM=0\n"
                "@CONTINUE%d\n0;JMP\n"
                "(TRUE%d)\n@SP\nA=M-1\nM=-1\n"
                "(CONTINUE%d)\n\n",
                n, jump, n, n, n);
    } else if (strcmp(cmd, "and") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\nA=A-1\nM=D&M\n\n");
    } else if (strcmp(cmd, "or") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\nA=A-1\nM=D|M\n\n");
    } else if (strcmp(cmd, "not") == 0) {
        fprintf(out, "@SP\nA=M-1\nM=!M\n\n");
    }
}

void write_push(FILE *out, char *arg1, char *arg2, TranslatorContext *tcx) {
    int index = (int)strtol(arg2, NULL, 10);

    if (strcmp(arg1, "constant") == 0) {
        fprintf(out, "@%d\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n\n", index);
    } else if (strcmp(arg1, "pointer") == 0) {
        fprintf(out, "@%s\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n\n", index == 0 ? "THIS" : "THAT");
    } else if (strcmp(arg1, "temp") == 0) {
        fprintf(out, "@%d\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n\n", index + 5);
    } else if (strcmp(arg1, "static") == 0) {
        fprintf(out, "@%s.%d\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n\n", tcx->file_prefix, index);
    }
    // local/argument/this/that
    else {
        const char *seg = strcmp(arg1, "local") == 0 ? "LCL" : strcmp(arg1, "argument") == 0 ? "ARG"
                                                           : strcmp(arg1, "this") == 0       ? "THIS"
                                                                                             : "THAT";
        fprintf(out, "@%d\nD=A\n@%s\nA=D+M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n\n", index, seg);
    }
}

void write_pop(FILE *out, char *arg1, char *arg2, TranslatorContext *tcx) {
    int index = (int)strtol(arg2, NULL, 10);

    if (strcmp(arg1, "pointer") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\n@%s\nM=D\n\n", index == 0 ? "THIS" : "THAT");
    } else if (strcmp(arg1, "temp") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\n@%d\nM=D\n\n", index + 5);
    } else if (strcmp(arg1, "static") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\n@%s.%d\nM=D\n\n", tcx->file_prefix, index);
    } else {
        const char *seg = strcmp(arg1, "local") == 0 ? "LCL" : strcmp(arg1, "argument") == 0 ? "ARG"
                                                           : strcmp(arg1, "this") == 0       ? "THIS"
                                                                                             : "THAT";
        fprintf(out,
                "@%d\nD=A\n@%s\nD=D+M\n@R13\nM=D\n"
                "@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n\n",
                index, seg);
    }
}

void write_call(FILE *out, char *arg1, char *arg2, TranslatorContext *tcx) {
    int n_args = (int)strtol(arg2, NULL, 10);
    fprintf(out, "@%s$ret.%d\n", tcx->current_function, tcx->call_counter);
    fprintf(out, "D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    fprintf(out, "@LCL\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    fprintf(out, "@ARG\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    fprintf(out, "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    fprintf(out, "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    fprintf(out, "@SP\nD=M\n@%d\nD=D-A\n@ARG\nM=D\n", n_args + 5);
    fprintf(out, "@SP\nD=M\n@LCL\nM=D\n");
    fprintf(out, "@%s\n0;JMP\n", arg1);
    fprintf(out, "(%s$ret.%d)\n\n", tcx->current_function, tcx->call_counter++);
}

void write_return(FILE *out, TranslatorContext *tcx) {
    // Generate unique FRAME and RETADDR labels
    char frame_label[BUFSIZ], retaddr_label[BUFSIZ];
    snprintf(frame_label, BUFSIZ, "%s$FRAME.%d", tcx->current_function, tcx->return_counter);
    snprintf(retaddr_label, BUFSIZ, "%s$RETADDR.%d", tcx->current_function, tcx->return_counter);

    // endFrame = LCL
    fprintf(out, "@LCL\nD=M\n@%s\nM=D\n", frame_label);

    // retAddr = *(endFrame - 5)
    fprintf(out, "@5\nA=D-A\nD=M\n@%s\nM=D\n", retaddr_label);

    // *ARG = pop()
    fprintf(out, "@SP\nAM=M-1\nD=M\n@ARG\nA=M\nM=D\n");

    // SP = ARG + 1
    fprintf(out, "@ARG\nD=M+1\n@SP\nM=D\n");

    // THAT = *(endFrame - 1)
    fprintf(out, "@%s\nAM=M-1\nD=M\n@THAT\nM=D\n", frame_label);

    // THIS = *(endFrame - 2)
    fprintf(out, "@%s\nAM=M-1\nD=M\n@THIS\nM=D\n", frame_label);

    // ARG = *(endFrame - 3)
    fprintf(out, "@%s\nAM=M-1\nD=M\n@ARG\nM=D\n", frame_label);

    // LCL = *(endFrame - 4)
    fprintf(out, "@%s\nAM=M-1\nD=M\n@LCL\nM=D\n", frame_label);

    // goto retAddr
    fprintf(out, "@%s\nA=M\n0;JMP\n\n", retaddr_label);

    tcx->return_counter++;
}
