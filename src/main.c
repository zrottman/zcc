#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "token.h"
#include "lexer.h"

int main(int argc, char** argv) {

    FILE* fp_in;
    char* ext;

    struct TokenList* tokens;
    // struct ast_t* AST = ast;

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

    // parse each file
    for(int i=1; i<argc; ++i) {
        if ((fp_in = fopen(argv[i], "r")) == NULL) {
            printf("Input file `%s` could not be opened or found.\n", argv[i]);
            exit(3);
        }

        
        // Step 1: Lex
        printf("\nLexing %s\n", argv[i]);
        tokens = tokenlist_create(); // malloc tokens linked list

        if (lex(fp_in, tokens) != 0) {
            // lexing error
            tokenlist_destroy(&tokens);
            fclose(fp_in);
            exit(4);
        }

        tokenlist_display(tokens);  // display tokens linked list
        tokenlist_destroy(&tokens); // destroy tokens linked list
        

        // Step 2: Parse
        //printf("Parsing %s\n", argv[i]);
        // takes token linked list head and returns AST


        // Step 3: Write
        //printf("Writing %s\n", argv[i]);
        // takes AST and out file

        fclose(fp_in);
    }

    return 0;
}
