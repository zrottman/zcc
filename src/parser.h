#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "safestring.h"
#include "token.h"
#include "ast.h"

struct Token*   eat(struct TokenList* tokens, enum TokenType expected);

struct ASTNode* parse(struct TokenList* tokens);
struct ASTNode* parse_function(struct TokenList* tokens);
struct ASTNode* parse_statement(struct TokenList* tokens);
struct ASTNode* parse_expression(struct TokenList* tokens);

#endif // PARSER_H
