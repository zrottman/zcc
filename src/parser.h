#ifndef PARSER_H
#define PARSER_H

#include "safestring.h"
#include "lexer.h"

int parse(FILE* fp_in);
int parse_function(FILE* fp_in, struct token* tok);

#endif // PARSER_H
