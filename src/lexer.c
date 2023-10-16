#include "lexer.h"

bool is_whitespace(const char c) {
    return c == ' ' || c == '\r' || c == '\t' || c == '\n';
}

int lex(FILE* fp) {
    char c;
    struct token tok = {.val = string_create(MAX_TOKEN_SIZE) };
    size_t i = 0;

    c = fgetc(fp);
    while (1) {

        // whitespace
        if (is_whitespace(c)) {
            while ((c = fgetc(fp)) != EOF && is_whitespace(c)) {
                ;
            }
            continue;
        }

        if (c == EOF) {
            break;
        }

        // integer literal
        if ('0' <= c && c <= '9') {
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            while ((c = fgetc(fp)) != EOF && '0' <= c && c <= '9') {
                if (string_appendc(tok.val, c) != 0) {
                    // error
                }
            }
        
        // identifier or keyword
        } else if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            while ((c = fgetc(fp)) != EOF && !is_whitespace(c)) {
                if (string_appendc(tok.val, c) != 0) {
                    // error
                }
            }

            // check to see if this is a reserved term
            
        // opening brace
        } else if (c == '{') {
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);

        // closing brace
        } else if (c == '}') {
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);

        // opening paren
        } else if (c == '(') {
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);

        // closing paren
        } else if (c == ')') {
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);

        // semicolon
        } else if (c == ';') {
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);
        
        // error
        } else {
            printf("`%c` is unrecognized token\n", c);
            return 1;
        }

        printf("token: %s\n", tok.val->buf);
        string_set(tok.val, "");

    }

    return 0;
}

