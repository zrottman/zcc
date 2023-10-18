#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "safestring.h"
#include "lexer.h"
#include "token.h"

int parse(FILE* fp_in);
int parse_function(FILE* fp_in, struct token* tok);
int parse_statement(FILE* fp_in, struct token* tok);

#endif // PARSER_H
