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

struct TokenList {
    struct Token*      head;
    struct Token*      tail;
    size_t             len;
};

struct TokenMap {
    enum TokenType     type;
    char*              literal;
    char*              description;
};

// Token functions
struct Token*     token_create(enum TokenType type, struct SafeString* ss);
int               token_destroy(struct Token** tok);
void              token_display(struct Token* tok);

// TokenList functions
struct TokenList* tokenlist_create(void);
int               tokenlist_destroy(struct TokenList** tl);
int               tokenlist_append(struct TokenList* tl, enum TokenType type, struct SafeString* ss);
void              tokenlist_display(struct TokenList* tl);

// TokenMap functions
enum TokenType    get_token_type(struct SafeString* ss);
const char*       get_token_name(enum TokenType type);

#endif // TOKEN_H
