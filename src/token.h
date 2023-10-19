#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <string.h>
#include "safestring.h"


enum TokenType { 
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

struct Token {
    struct SafeString* ss;
    enum TokenType     type;
    struct Token*      next;
};

struct TokenMap {
    enum TokenType     type;
    char*              match;
    char*              val;
};

struct Token*   token_create(enum TokenType type, struct SafeString* ss);
int             token_destroy(struct Token** tok);

enum TokenType  get_token_type(struct SafeString *ss);
const char*     get_token_name(enum TokenType type);
void            token_display(struct Token *tok);

#endif // TOKEN_H
