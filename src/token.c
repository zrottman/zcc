#include "token.h"

struct TokenMap TOKEN_MAP[] = {

    // Symbols
    { TOKEN_SYMBOL_OPENBRACE,  "{",      "symbol -> open brace"  },
    { TOKEN_SYMBOL_CLOSEBRACE, "}",      "symbol -> close brace" },
    { TOKEN_SYMBOL_OPENPAREN,  "(",      "symbol -> open paren"  },
    { TOKEN_SYMBOL_CLOSEPAREN, ")",      "symbol -> close paren" },
    { TOKEN_SYMBOL_SEMICOLON,  ";",      "symbols -> semi-colon" },

    // Keywords
    { TOKEN_KEYWORD_RETURN,    "return", "keyword -> return"     },
    { TOKEN_KEYWORD_INT,       "int",    "keyword -> int"        },

    // Identifiers
    { TOKEN_IDENTIFIER,        NULL,     "identifier"            },

    // Literals
    { TOKEN_LITERAL_INT,       NULL,     "int literal"           },

    { TOKEN_END,               NULL,     NULL                    }

};

struct Token* token_create(enum TokenType type, struct SafeString* ss) {

    struct Token *tok = (struct Token*)malloc(sizeof(struct Token));

    if (!tok) {
        // malloc error
        return NULL;
    }

    if (ss->len == 0) {
        // invalid safestring
        free(tok);
        return NULL;
    }

    tok->ss = safestring_create(ss->len + 1);
    if (safestring_set(tok->ss, ss->buf) != 0) {
        // this scenario should never happen since we are creating a safestring from a valid safestring
        safestring_destroy(&(tok->ss));
        free(tok);
        return NULL;
    }

    tok->type = type;
    tok->next = NULL;

    return tok;
}

int token_destroy(struct Token** tok) {
    struct Token *t = *tok;
    struct Token *next;

    while (t != NULL) {
        next = t->next;

        safestring_destroy(&(t->ss));

        t->next = NULL;

        free(t);
        t = next;
    }

    *tok = NULL;
    return 0;
}


enum TokenType get_token_type(struct SafeString *ss) {
    size_t i;
    for (i=0; TOKEN_MAP[i].val != NULL; ++i) {
        if (!TOKEN_MAP[i].match) {
            continue;
        }
        if (strcmp(TOKEN_MAP[i].match, ss->buf) == 0) {
            return TOKEN_MAP[i].type;
        }
    }
    return TOKEN_IDENTIFIER;
}

const char* get_token_name(enum TokenType type) {
    size_t i;
    for (i=0; TOKEN_MAP[i].val != NULL; ++i) {
        if (TOKEN_MAP[i].type == type) {
            return TOKEN_MAP[i].val;
        }
    }
    return "UNKNOWN";

}

void token_display(struct Token* tok) {
    printf("Token value : %s\n", tok->ss->buf);
    printf("Token type  : %s\n\n", get_token_name(tok->type));
}
