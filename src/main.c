#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char** argv) {

    char* ext;

    // validate argc
    if (argc < 2) {
        printf("Must pass at least one .c filename.\n");
        exit(1);
    }

    // validate argv extensions
    for(int i=1; i<argc; ++i) {
        ext = mystrrchr(argv[i], '.');
        if (mystrcmp(ext, ".c") != 0) {
            printf("Usage: ./zcc <my_file.c>+\n");
            exit(2);
        }
    }

    printf("success\n");

    return 0;
}
