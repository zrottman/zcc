#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "safestring.h"

#define MAX_TOKEN_SIZE 32

enum token_type { BRACE_OPEN, BRACE_CLOSE, PAREN_OPEN, PAREN_CLOSE,
                 SEMICOLON, KEYWORD, IDENTIFIER, INT_LITERAL, UNKNOWN };

struct map {
    enum token_type type;
    const char*     name;
};

struct token {
    struct string_t* val;
    enum token_type  type;
};

bool is_whitespace(const int c);
bool is_alpha(const int c);
bool is_numeric(const int c);
bool is_keyword(const char* s);
void display_token(struct token *tok);
int  next_token(FILE* fp, struct token *tok);
struct map lookup(struct map target);

# endif // LEXER_H
