#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "safestring.h"
#include "token.h"

#define MAX_TOKEN_SIZE 32

int  lex(FILE* fp, struct TokenList* tokenlist);

bool is_whitespace(const int c);
bool is_alpha(const int c);
bool is_numeric(const int c);

//bool is_keyword(const char* s);

# endif // LEXER_H
