#include "parser.h"

int eat(struct token *tok, enum token_type expected, FILE* fp_in) {
    if (expected != tok->type) {
        // use lookups here to print out str equiv for enum
        printf("Error, expected `%s`, got `%s`\n", get_token_name(expected), tok->val->buf);
        return 1;
    }
    display_token(tok);
    next_token(fp_in, tok);
    return 0;
}

int parse(FILE* fp_in) {

    struct token *tok = (struct token*)malloc(sizeof(struct token));
    tok->val = string_create(MAX_TOKEN_SIZE);

    next_token(fp_in, tok);
    if (parse_function(fp_in, tok) != 0) { return 1; }

    return 0;
}

int parse_function(FILE* fp_in, struct token* tok) {

    if (eat(tok, TOKEN_KEYWORD_INT, fp_in) != 0)       { return 1; }
    if (eat(tok, TOKEN_IDENTIFIER, fp_in) != 0)        { return 2; }
    if (eat(tok, TOKEN_SYMBOL_OPENPAREN, fp_in) != 0)  { return 3; }
    if (eat(tok, TOKEN_SYMBOL_CLOSEPAREN, fp_in) != 0) { return 5; }
    if (eat(tok, TOKEN_SYMBOL_OPENBRACE, fp_in) != 0)  { return 6; }
    parse_statement(fp_in, tok);
    if (eat(tok, TOKEN_SYMBOL_CLOSEBRACE, fp_in) != 0) { return 7; }

    return 0;
}

int parse_statement(FILE* fp_in, struct token* tok) {

    if (eat(tok, TOKEN_KEYWORD_RETURN, fp_in) != 0)   { return 1; }
    if (eat(tok, TOKEN_LITERAL_INT, fp_in) != 0)      { return 2; }
    if (eat(tok, TOKEN_SYMBOL_SEMICOLON, fp_in) != 0) { return 3; }

    return 0;

}
