#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "lexer.h"

int main(int argc, char** argv) {

    FILE* fp_in;
    char* ext;

    // validate argc
    if (argc < 2) {
        printf("Expecting at least one .c filename.\n");
        printf("Usage: ./zcc <file.c>+\n");
        exit(1);
    }

    // validate argv extensions
    for(int i=1; i<argc; ++i) {
        ext = mystrrchr(argv[i], '.');
        if (ext == NULL || mystrcmp(ext, ".c") != 0) {
            printf("Expected .c file, got %s.\n", argv[i]);
            exit(2);
        }
    }

    // lex each file
    for(int i=1; i<argc; ++i) {
        if ((fp_in = fopen(argv[i], "r")) == NULL) {
            printf("Input file `%s` could not be opened or found.\n", argv[i]);
            exit(3);
        }
        printf("Lexing %s...\n", argv[i]);
        lex(fp_in);
        fclose(fp_in);
    }

    return 0;
}
