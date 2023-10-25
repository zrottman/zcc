#include "lexer.h"

struct TokenList* lex(FILE* fp) {
    signed char c;
    struct SafeString* cur_tok = safestring_create(MAX_TOKEN_SIZE);
    struct TokenList* tokenlist = tokenlist_create();

    
    c = fgetc(fp);
    while (1) {
        safestring_set(cur_tok, ""); // reset safestring
    
        // ignore whitespace
        /*
        if (is_whitespace(c)) {
            while ((c = fgetc(fp)) != EOF && is_whitespace(c)) {
                ;
            }
        }
        */
        if (is_whitespace(c)) {
            while (c != EOF && is_whitespace((c = fgetc(fp)))) {
                ;
            }
        }

        // break if end of file
        if (c == EOF) {
            break;
        }

        // tokenize integer literal
        if (is_numeric(c)) {
            if (safestring_appendc(cur_tok, c) != 0) {
                // error
            }
            while ((c = fgetc(fp)) != EOF && is_numeric(c)) {
                if (safestring_appendc(cur_tok, c) != 0) {
                    // error
                }
            }

            if (tokenlist_append(tokenlist, TOKEN_LITERAL_INT, cur_tok) != 0) {
                safestring_destroy(&cur_tok);
                tokenlist_destroy(&tokenlist);
                return NULL;
            }
            continue;
        }
        
        // tokenize identifier or keyword
        if (is_alpha(c)) {
            if (safestring_appendc(cur_tok, c) != 0) {
                // error
            }
            while ((c = fgetc(fp)) != EOF && (is_alpha(c) || is_numeric(c))) {
                if (safestring_appendc(cur_tok, c) != 0) {
                    // error
                }
            }
            if (tokenlist_append(tokenlist, get_token_type(cur_tok), cur_tok) != 0) {
                safestring_destroy(&cur_tok);
                tokenlist_destroy(&tokenlist);
                return NULL;
            }
            continue;
        }

        // tokenize opening brace
        if (c == '{') {
            if (safestring_appendc(cur_tok, c) != 0) {
                // error
            }
            if (tokenlist_append(tokenlist, TOKEN_SYMBOL_OPENBRACE, cur_tok) != 0) {
                safestring_destroy(&cur_tok);
                tokenlist_destroy(&tokenlist);
                return NULL;
            }
            c = fgetc(fp);
            continue;
        }

        // tokenize closing brace
        if (c == '}') {
            if (safestring_appendc(cur_tok, c) != 0) {
                // error
            }
            if (tokenlist_append(tokenlist, TOKEN_SYMBOL_CLOSEBRACE, cur_tok) != 0) {
                safestring_destroy(&cur_tok);
                tokenlist_destroy(&tokenlist);
                return NULL;
            }
            c = fgetc(fp);
            continue;
        }

        // tokenize opening paren
        if (c == '(') {
            if (safestring_appendc(cur_tok, c) != 0) {
                // error
            }
            if (tokenlist_append(tokenlist, TOKEN_SYMBOL_OPENPAREN, cur_tok) != 0) {
                safestring_destroy(&cur_tok);
                tokenlist_destroy(&tokenlist);
                return NULL;
            }
            c = fgetc(fp);
            continue;
        }

        // tokenize closing paren
        if (c == ')') {
            if (safestring_appendc(cur_tok, c) != 0) {
                // error
            }
            if (tokenlist_append(tokenlist, TOKEN_SYMBOL_CLOSEPAREN, cur_tok) != 0) {
                safestring_destroy(&cur_tok);
                tokenlist_destroy(&tokenlist);
                return NULL;
            }
            c = fgetc(fp);
            continue;
        }

        // semicolon
        if (c == ';') {
            if (safestring_appendc(cur_tok, c) != 0) {
                // error
            }
            if (tokenlist_append(tokenlist, TOKEN_SYMBOL_SEMICOLON, cur_tok) != 0) {
                safestring_destroy(&cur_tok);
                tokenlist_destroy(&tokenlist);
                return NULL;
            }
            c = fgetc(fp);
            continue;
        }
        
        // error
        printf("No token matching pattern `%c`.\n", c);
        safestring_destroy(&cur_tok);
        tokenlist_destroy(&tokenlist);
        return NULL;
    }

    safestring_destroy(&cur_tok);

    return tokenlist;
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

