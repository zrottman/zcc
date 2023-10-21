#include "parser.h"

struct Token* eat(struct TokenList *tokens, enum TokenType expected) {
    struct Token* tok = tokens->p;
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

struct ASTNode* parse(struct TokenList* tokens) {
    /*
     * <program> ::= <function>
     */

    struct ASTNode* program_node  = NULL;
    struct ASTNode* function_node = NULL;

    tokens->p = tokens->head; // set tokenlist pointer
                              
    if (!(function_node = parse_function(tokens))) { return NULL; }

    program_node = astnode_create(PROGRAM, "program");
    astnode_append_child(program_node, function_node);

    return program_node;
}

struct ASTNode* parse_function(struct TokenList* tokens) {
    /* 
     * <function> ::= "int" <id> "(" ")" "{" "}" <statement> "}"
     */

    struct ASTNode* function_node  = NULL;
    struct ASTNode* statement_node = NULL;
    struct Token*   tok            = NULL;

    if (!(eat(tokens, TOKEN_KEYWORD_INT)))           { return NULL; }
    if (!(tok = eat(tokens, TOKEN_IDENTIFIER)))      { return NULL; } // get func name from here
    if (!(eat(tokens, TOKEN_SYMBOL_OPENPAREN)))      { return NULL; }
    if (!(eat(tokens, TOKEN_SYMBOL_CLOSEPAREN)))     { return NULL; }
    if (!(eat(tokens, TOKEN_SYMBOL_OPENBRACE)))      { return NULL; }
    if (!(statement_node = parse_statement(tokens))) { return NULL; }
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
    if (!(expression_node = parse_expression(tokens))) { return NULL; }
    if (!(eat(tokens, TOKEN_SYMBOL_SEMICOLON)))  { return NULL; }

    statement_node = astnode_create(STATEMENT, tok->ss->buf);
    astnode_append_child(statement_node, expression_node);

    return statement_node;
}

struct ASTNode* parse_expression(struct TokenList* tokens) {
    /*
     * <exp> ::= <int>
     */

    struct ASTNode* expression_node = NULL;
    struct Token*   tok             = NULL;

    if (!(tok = eat(tokens, TOKEN_LITERAL_INT))) { return NULL; }

    expression_node = astnode_create(EXPRESSION, tok->ss->buf);

    return expression_node;

}
