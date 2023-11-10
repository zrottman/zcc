#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "writer.h"

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

    // compile each file
    for(int i=1; i<argc; ++i) {
        if ((fp_in = fopen(argv[i], "r")) == NULL) {
            printf("Input file `%s` could not be opened or found.\n", argv[i]);
            exit(3);
        }
        
        // Step 1: Lex
        printf("Lexing %s...  ", argv[i]);
        if (!(tokens = lex(fp_in))) {
            // lexing error
            fclose(fp_in);
            exit(4);
        }
        fclose(fp_in);
        printf("done.\n");

        printf("TOKENS\n");
        tokenlist_display(tokens);    // display tokens linked list
        printf("\n");

        // Step 2: Parse
        printf("Parsing %s... ", argv[i]);
        if (!(ast = parse(tokens))) {
            // parsing error
            tokenlist_destroy(&tokens);
            exit(5);
        }
        printf("done.\n");

        printf("AST\n");
        astnode_pretty_print(ast, 0); // pretty print AST
        printf("\n");

        // Step 3: Write
        printf("Writing %s... ", argv[i]);
        generate(ast, argv[i]);
        printf("done\n");

        // Destroy data structures
        tokenlist_destroy(&tokens); // destroy tokens linked list
        astnode_destroy(&ast);      // destroy ast
    }

    return 0;
}
