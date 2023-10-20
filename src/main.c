#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char** argv) {

    FILE* fp_in;
    char* ext;

    struct TokenList* tokens = NULL;
    struct ASTNode*   ast    = NULL;

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
        printf("\nLexing %s...\n", argv[i]);
        tokens = tokenlist_create(); // malloc tokens linked list

        if (lex(fp_in, tokens) != 0) {
            // lexing error
            tokenlist_destroy(&tokens);
            fclose(fp_in);
            exit(4);
        }

        printf("Done.\n");
        //tokenlist_display(tokens);  // display tokens linked list


        // Step 2: Parse
        printf("Parsing %s...\n", argv[i]);

        if (!(ast = parse(tokens))) {
            // parsing error
            tokenlist_destroy(&tokens);
            fclose(fp_in);
            exit(5);
        }
        tokenlist_destroy(&tokens); // destroy tokens linked list
        printf("Done.\n");

        astnode_display(ast, 0);    // display AST

        print("\nAST\n");
        astnode_destroy(&ast);      // destroy ast
        



        // Step 3: Write
        //printf("Writing %s...\n", argv[i]);
        // takes AST and out file

        fclose(fp_in);
    }

    return 0;
}
