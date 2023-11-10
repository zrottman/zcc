#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "safestring.h"
#include "token.h"
#include "ast.h"

struct Token*   eat(struct TokenList* tokens, enum TokenType expected);
struct Token*   peek(struct TokenList *tokens);

struct ASTNode* parse(struct TokenList* tokens);
struct ASTNode* parse_function_dec(struct TokenList* tokens);
struct ASTNode* parse_statement(struct TokenList* tokens);
struct ASTNode* parse_expression(struct TokenList* tokens);
struct ASTNode* parse_int_literal(struct TokenList* tokens);
struct ASTNode* parse_unary_op(struct TokenList* tokens);

#endif // PARSER_H
