#include "parser.h"

int eat(struct token *tok, enum token_type expected) {
    if (expected != tok->type) {
        // use lookups here to print out str equiv for enum
        printf("Error, expected %d, got %d for token `%s`\n", expected, tok->type, tok->val->buf);
        return 1;
    }
    return 0;
}

int parse(FILE* fp_in) {

    struct token *tok = (struct token*)malloc(sizeof(struct token));
    tok->val = string_create(MAX_TOKEN_SIZE);

    if (parse_function(fp_in, tok) != 0) {
        // error
        return 1;
    }

    return 0;
}

int parse_function(FILE* fp_in, struct token* tok) {

    next_token(fp_in, tok);
    if (eat(tok, KEYWORD) != 0) {
        //error
        return 1;
    }
    display_token(tok);

    next_token(fp_in, tok);
    if (eat(tok, IDENTIFIER) != 0) {
        //error
        return 2;
    }
    display_token(tok);

    next_token(fp_in, tok);
    if (eat(tok, PAREN_OPEN) != 0) {
        //error
        return 2;
    }
    display_token(tok);

    next_token(fp_in, tok);
    if (eat(tok, PAREN_CLOSE) != 0) {
        //error
        return 2;
    }
    display_token(tok);

    return 0;
}
