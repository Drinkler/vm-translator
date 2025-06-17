#include <dirent.h>
#include <sys/stat.h>

#include "codewriter.h"
#include "parser.h"
#include "util.h"

void process_file(FILE *input_file, FILE *output_file, TranslatorContext *tcx) {
    char line[BUFSIZ];
    while (advance(input_file, line)) {
        fprintf(output_file, "// %s\n", line);

        ParsedCommand cmd = parse_command(line);
        CommandType cmd_type = get_command_type(cmd.command);

        switch (cmd_type) {
            case C_GOTO:
                write_goto(output_file, cmd.arg1);
                break;
            case C_LABEL:
                write_label(output_file, cmd.arg1);
                break;
            case C_IF:
                write_if(output_file, cmd.arg1);
                break;
            case C_FUNCTION:
                write_function(output_file, cmd.arg1, cmd.arg2, tcx);
                break;
            case C_ARITHMETIC:
                write_arithmetic(output_file, cmd.command, tcx);
                break;
            case C_PUSH:
                write_push(output_file, cmd.arg1, cmd.arg2, tcx);
                break;
            case C_POP:
                write_pop(output_file, cmd.arg1, cmd.arg2, tcx);
                break;
            case C_CALL:
                write_call(output_file, cmd.arg1, cmd.arg2, tcx);
                break;
            case C_RETURN:
                write_return(output_file, tcx);
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if correct arguments are given
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename.vm>|<directory>\n", argv[0]);
        return 1;
    }

    // Obtain information about file
    struct stat path_stat;
    if (stat(argv[1], &path_stat) != 0) {
        perror("stat");
        return 1;
    }

    char output_path[BUFSIZ];
    FILE *output_file;

    // Handle single .vm file
    if (S_ISREG(path_stat.st_mode)) {
        if (!has_vm_extension(argv[1])) {
            fprintf(stderr, "Error: File must have a .vm extension.\n");
            return 1;
        }

        FILE *input_file = open_file(argv[1], "r");

        // Open output file
        TranslatorContext ctx = {0};
        strip_vm_extension(argv[1], ctx.file_prefix, sizeof(ctx.file_prefix));
        snprintf(output_path, sizeof(output_path), "%s.asm", ctx.file_prefix);
        output_file = open_file(output_path, "w");

        process_file(input_file, output_file, &ctx);

        fclose(input_file);
    }

    // Handle directory
    else if (S_ISDIR(path_stat.st_mode)) {
        // Try to open the directory
        DIR *dir;
        if ((dir = opendir(argv[1])) == NULL) {
            perror("opendir");
            return 1;
        }

        // Open output file
        const char *basename_dir = basename(argv[1]);  // Uses libgen.h, returns the last component of a pathname using regex
        snprintf(output_path, sizeof(output_path), "%s/%s.asm", argv[1], basename_dir);
        output_file = open_file(output_path, "w");

        write_bootstrap(output_file);

        // Loop every file in directory
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            // Check if file contains .vm extension
            if (has_vm_extension(entry->d_name)) {
                // Open input file
                char fullpath[BUFSIZ];
                snprintf(fullpath, sizeof(fullpath), "%s/%s", argv[1], entry->d_name);
                FILE *input_file = open_file(fullpath, "r");

                TranslatorContext ctx = {0};
                strip_vm_extension(entry->d_name, ctx.file_prefix, sizeof(ctx.file_prefix));
                process_file(input_file, output_file, &ctx);

                fclose(input_file);
            }
        }

        closedir(dir);
    }

    else {
        fprintf(stderr, "Invalid input: not a file or directory\n");
        return 1;
    }

    fclose(output_file);

    return 0;
}
