#include "parser.h"

struct Token* eat(struct TokenList *tokens, enum TokenType expected) {
    struct Token* tok = tokens->p;
    if (tok == NULL) {
        printf("Error, unexpected end of file.\n");
        return NULL;
    }

    if (expected != tok->type) {
        // use lookups here to print out str equiv for enum
        printf("Error, expected `%s`, got `%s`\n", get_token_name(expected), tokens->p->ss->buf);
        return NULL;
    }
    //token_display(tok);
    
    /*
     * would be nice to deallocate/free each token as it's consumed. however, then
     * I'd need a destroy single token function and a recursive destroy so that,
     * in the even of an error, I can recursively destroy. Maybe it's the same
     * function with a boolean flag for recursive of no.
     */
    tokens->p = tokens->p->next; // advance token

    return tok;
}

struct Token* peek(struct TokenList *tokens) {
    return tokens->p;
}

struct ASTNode* parse(struct TokenList* tokens) {
    /*
     * <program> ::= <function>
     */

    struct ASTNode* program_node  = NULL;
    struct ASTNode* function_node = NULL;

    tokens->p = tokens->head; // set tokenlist pointer
                              
    if (!(function_node = parse_function_dec(tokens))) { 
        printf("Error parsing function declaration.\n");
        return NULL; 
    }

    program_node = astnode_create(PROGRAM, "");
    astnode_append_child(program_node, function_node);

    return program_node;
}

struct ASTNode* parse_function_dec(struct TokenList* tokens) {
    /* 
     * <function> ::= "int" <id> "(" ")" "{" <statement> "}"
     */

    struct ASTNode* function_node  = NULL;
    struct ASTNode* statement_node = NULL;
    struct Token*   tok            = NULL;

    if (!(eat(tokens, TOKEN_KEYWORD_INT)))           { return NULL; }
    if (!(tok = eat(tokens, TOKEN_IDENTIFIER)))      { return NULL; } // get func name from here
    if (!(eat(tokens, TOKEN_SYMBOL_OPENPAREN)))      { return NULL; }
    if (!(eat(tokens, TOKEN_SYMBOL_CLOSEPAREN)))     { return NULL; }
    if (!(eat(tokens, TOKEN_SYMBOL_OPENBRACE)))      { return NULL; }
    if (!(statement_node = parse_statement(tokens))) { 
        printf("Error parsing statement.\n");
        return NULL; 
    }
    if (!(eat(tokens, TOKEN_SYMBOL_CLOSEBRACE)))     { return NULL; }

    function_node = astnode_create(FUNCTION_DEC, tok->ss->buf);
    astnode_append_child(function_node, statement_node);

    return function_node;
}

struct ASTNode* parse_statement(struct TokenList* tokens) {
    /*
     * <statement> ::= "return" <exp> ";"
     */

    struct ASTNode* statement_node  = NULL;
    struct ASTNode* expression_node = NULL;
    struct Token*   tok             = NULL;

    if (!(tok = eat(tokens, TOKEN_KEYWORD_RETURN)))    { return NULL; }
    if (!(expression_node = parse_expression(tokens))) { 
        printf("Error parsing expression.\n");
        return NULL; 
    }
    if (!(eat(tokens, TOKEN_SYMBOL_SEMICOLON)))  { return NULL; }

    statement_node = astnode_create(STATEMENT, tok->ss->buf);
    astnode_append_child(statement_node, expression_node);

    return statement_node;
}

struct ASTNode* parse_expression(struct TokenList* tokens) {
    /*
     * <exp> ::= <unary_op> <exp> | <int>
     */

    /*
     * an expression has children. it can have a single <int> child or
     * a <unary_op> and <exp> childrenj
     * 
     */

    struct ASTNode* expression_node = NULL;
    struct ASTNode* expression_child_node = NULL;


    switch (peek(tokens)->type) { // TODO need lookahead here
                                             
        case TOKEN_LITERAL_INT:
            if (!(expression_child_node = parse_int_literal(tokens))) { 
                printf("Error parsing int literal.\n");
                return NULL; 
            }
            break;
        case TOKEN_SYMBOL_UNARY_OP:
            if (!(expression_child_node = parse_unary_op(tokens))) { 
                printf("Error parsing unary op.\n");
                return NULL; 
            }
            break;
        default:
            printf("Unexpected token in expression\n");
            return NULL;
    }
    
    expression_node = astnode_create(EXPRESSION, "");
    astnode_append_child(expression_node, expression_child_node);

    return expression_node;

}

struct ASTNode* parse_int_literal(struct TokenList* tokens) {
    struct Token* tok = NULL;
    if (!(tok = eat(tokens, TOKEN_LITERAL_INT))) { return NULL; }
    return astnode_create(INT_LITERAL, tok->ss->buf);
}

struct ASTNode* parse_unary_op(struct TokenList* tokens) {
    /*
     * <unary_op> ::= "!" | "~" | "-"
     */

    struct ASTNode* unary_op_node = NULL;
    struct ASTNode* unary_op_child_node = NULL;
    struct Token* tok = NULL;

    if (!(tok = eat(tokens, TOKEN_SYMBOL_UNARY_OP))) { return NULL; }

    if (!(unary_op_child_node = parse_expression(tokens))) {
        printf("Error parsing expression\n");
        return NULL;
    }

    unary_op_node = astnode_create(UNARY_OP, tok->ss->buf);
    astnode_append_child(unary_op_node, unary_op_child_node);
    
    return unary_op_node;
}
