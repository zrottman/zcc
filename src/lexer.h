#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "safestring.h"

#define MAX_TOKEN_SIZE 32

enum token_type { BRACE_OPEN, BRACE_CLOSE, PAREN_OPEN, PAREN_CLOSE,
                 SEMICOLON, KEYWORD, IDENTIFIER, INT_LITERAL };


struct token {
    struct string_t* val;
    enum token_type  type;
};

bool is_whitespace(const char c);
bool is_alpha(const char c);
bool is_numeric(const char c);
bool is_keyword(const char* s);
void display_token(struct token *tok);
int lex(FILE* fp);

# endif // LEXER_H
