#include "lexer.h"

struct map types[] = {
    { BRACE_OPEN,  "opening brace" },
    { BRACE_CLOSE, "closing brace" },
    { PAREN_OPEN,  "opening paren" },
    { PAREN_CLOSE, "closing paren" },
    { SEMICOLON,   "semicolon"     },
    { KEYWORD,     "keyword"       },
    { IDENTIFIER,  "identifier"    },
    { INT_LITERAL, "int literal"   },
    { UNKNOWN,     NULL            }
};

struct map lookup(struct map target) {
    int i;
    for (i=0; types[i].name != NULL; ++i) {
        if (target.type == types[i].type) {
            break;
        }
    }
    return types[i];
}

bool is_whitespace(const int c) {
    return c == ' ' || c == '\r' || c == '\t' || c == '\n';
}

bool is_alpha(const int c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool is_numeric(const int c) {
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

int next_token(FILE* fp, struct token* tok) {
    int c;
    string_set(tok->val, "");
    
    c = fgetc(fp);
    
    // whitespace
    if (is_whitespace(c)) {
        while ((c = fgetc(fp)) != EOF && is_whitespace(c)) {
            ;
        }
    }

    if (c == EOF) {
        return 1;
    }

    // integer literal
    if (is_numeric(c)) {
        tok->type = INT_LITERAL;
        if (string_appendc(tok->val, c) != 0) {
            // error
        }
        while ((c = fgetc(fp)) != EOF && is_numeric(c)) {
            if (string_appendc(tok->val, c) != 0) {
                // error
            }
        }
        ungetc(c, fp);
    
    // identifier or keyword
    } else if (is_alpha(c)) {
        tok->type = IDENTIFIER;
        if (string_appendc(tok->val, c) != 0) {
            // error
        }
        while ((c = fgetc(fp)) != EOF && (is_alpha(c) || is_numeric(c))) {
            if (string_appendc(tok->val, c) != 0) {
                // error
            }
        }

        // check to see if this is a reserved term
        if (is_keyword(tok->val->buf)) {
            tok->type = KEYWORD;
        }
        ungetc(c, fp);
        
    // opening brace
    } else if (c == '{') {
        tok->type = BRACE_OPEN;
        if (string_appendc(tok->val, c) != 0) {
            // error
        }

    // closing brace
    } else if (c == '}') {
        tok->type = BRACE_CLOSE;
        if (string_appendc(tok->val, c) != 0) {
            // error
        }

    // opening paren
    } else if (c == '(') {
        tok->type = PAREN_OPEN;
        if (string_appendc(tok->val, c) != 0) {
            // error
        }

    // closing paren
    } else if (c == ')') {
        tok->type = PAREN_CLOSE;
        if (string_appendc(tok->val, c) != 0) {
            // error
        }

    // semicolon
    } else if (c == ';') {
        tok->type = SEMICOLON;
        if (string_appendc(tok->val, c) != 0) {
            // error
        }
    
    // error
    } else {
        printf("`%c` is unrecognized token\n", c);
        return 1;
    }

    return 0;
}
