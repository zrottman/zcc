#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include "utils.h"
#include "safestring.h"
#include "token.h"

int  next_token(FILE* fp, struct token *tok);

bool is_whitespace(const int c);
bool is_alpha(const int c);
bool is_numeric(const int c);
bool is_keyword(const char* s);

# endif // LEXER_H
