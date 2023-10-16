#include "lexer.h"

bool is_whitespace(const char c) {
    return c == ' ' || c == '\r' || c == '\t' || c == '\n';
}

bool is_alpha(const char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool is_numeric(const char c) {
    return '0' <= c && c <= '9';
}

bool is_keyword(const char* s) {
    char* keywords[] = { "return", "int" , NULL };

    for (int i=0; keywords[i] != NULL; ++i) {
        if (strcmp(s, keywords[i]) == 0) {
            return true;
        }
    }

    return false;

}

void display_token(struct token* tok) {
    printf("token_type: %d\n", tok->type);
    printf("token_val : %s\n\n", tok->val->buf);
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
        if (is_numeric(c)) {
            tok.type = INT_LITERAL;
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            while ((c = fgetc(fp)) != EOF && is_numeric(c)) {
                if (string_appendc(tok.val, c) != 0) {
                    // error
                }
            }
        
        // identifier or keyword
        } else if (is_alpha(c)) {
            tok.type = IDENTIFIER;
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            while ((c = fgetc(fp)) != EOF && (is_alpha(c) || is_numeric(c))) {
                if (string_appendc(tok.val, c) != 0) {
                    // error
                }
            }

            // check to see if this is a reserved term
            if (is_keyword(tok.val->buf)) {
                tok.type = KEYWORD;
            }
            
        // opening brace
        } else if (c == '{') {
            tok.type = BRACE_OPEN;
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);

        // closing brace
        } else if (c == '}') {
            tok.type = BRACE_CLOSE;
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);

        // opening paren
        } else if (c == '(') {
            tok.type = PAREN_OPEN;
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);

        // closing paren
        } else if (c == ')') {
            tok.type = PAREN_CLOSE;
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);

        // semicolon
        } else if (c == ';') {
            tok.type = SEMICOLON;
            if (string_appendc(tok.val, c) != 0) {
                // error
            }
            c = fgetc(fp);
        
        // error
        } else {
            printf("`%c` is unrecognized token\n", c);
            return 1;
        }

        //printf("token: %s\n", tok.val->buf);
        display_token(&tok);
        string_set(tok.val, "");

    }

    return 0;
}

