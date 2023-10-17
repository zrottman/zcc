#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include "safestring.h"

#define MAX_TOKEN_SIZE 32

enum token_type { 
    TOKEN_NONE,

    // Symbols
    TOKEN_SYMBOL_OPENBRACE,
    TOKEN_SYMBOL_CLOSEBRACE,
    TOKEN_SYMBOL_OPENPAREN,
    TOKEN_SYMBOL_CLOSEPAREN,
    TOKEN_SYMBOL_SEMICOLON,

    // Keywords
    TOKEN_KEYWORD_RETURN,
    TOKEN_KEYWORD_INT,

    // Identifiers
    TOKEN_IDENTIFIER,

    // Literals
    TOKEN_LITERAL_INT,

    // End
    TOKEN_END
};

struct token {
    struct string_t* val;
    enum token_type  type;
};

struct token_map {
    enum token_type  type;
    char*            val;
};

enum token_type get_token_type(char* s);
const char*     get_token_name(enum token_type type);
void            display_token(struct token *tok);

#endif // TOKEN_H
