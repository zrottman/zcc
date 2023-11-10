#include "token.h"

struct TokenMap TOKEN_MAP[] = {

    // Symbols
    { TOKEN_SYMBOL_OPENBRACE,          "{",      "symbols: {"      },
    { TOKEN_SYMBOL_CLOSEBRACE,         "}",      "symbols: }"      },
    { TOKEN_SYMBOL_OPENPAREN,          "(",      "symbols: ("      },
    { TOKEN_SYMBOL_CLOSEPAREN,         ")",      "symbols: )"      },
    { TOKEN_SYMBOL_SEMICOLON,          ";",      "symbols: ;"      },
    { TOKEN_SYMBOL_NEGATION,           "-",      "symbols: -"      },
    { TOKEN_SYMBOL_BITWISE_COMPLEMENT, "~",      "symbols: ~"      },
    { TOKEN_SYMBOL_LOGICAL_NEGATION,   "~",      "symbols: !"      },

    // Keywords
    { TOKEN_KEYWORD_RETURN,            "return", "keyword: return" },
    { TOKEN_KEYWORD_INT,               "int",    "keyword: int"    },

    // Identifiers
    { TOKEN_IDENTIFIER,                NULL,     "identifier"      },

    // Literals
    { TOKEN_LITERAL_INT,               NULL,     "int literal"     },

    { TOKEN_END,                       NULL,     NULL              }

};

/* Token functions */
struct Token* token_create(enum TokenType type, struct SafeString* ss) {

    struct Token* tok = (struct Token*)malloc(sizeof(struct Token));

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
    struct Token* t = *tok;
    struct Token* next;

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

void token_display(struct Token* tok) {
    printf("%s / ", tok->ss->buf);
    printf("%s -> ", get_token_name(tok->type));
}


/* Token List functions */
struct TokenList* tokenlist_create(void) {
    struct TokenList* tl = (struct TokenList*)malloc(sizeof(struct TokenList));

    if (!tl) {
        return NULL; // malloc error
    }

    tl->head = NULL;
    tl->tail = NULL;
    tl->p    = NULL;
    tl->len  = 0;

    return tl;
}

int tokenlist_destroy(struct TokenList** tl) {
    struct Token* cur = (*tl)->head;

    token_destroy(&cur);

    (*tl)->head = NULL;
    (*tl)->tail = NULL;
    (*tl)->p    = NULL;
    free(*tl);

    *tl = NULL;

    return 0;
}

int tokenlist_append(struct TokenList* tl, enum TokenType type, struct SafeString* ss) {
    if (tl == NULL)    { 
        // invalid tokenlist
        return 1; 
    }

    struct Token* tok = token_create(type, ss);
    if (!tok) {
        // malloc error
        return 2;
    }

    if (tl->head == NULL) {
        tl->head = tl->tail = tok;
    } else {
        tl->tail->next = tok;
        tl->tail = tl->tail->next;
    }

    tl->len++;

    return 0;
}

void tokenlist_display(struct TokenList* tl) {
    struct Token* cur = tl->head;
    while (cur) {
        token_display(cur);
        cur = cur->next;
    }
}

/* TokenMap functions */
enum TokenType get_token_type(struct SafeString* ss) {
    size_t i;
    for (i=0; TOKEN_MAP[i].description != NULL; ++i) {
        if (!TOKEN_MAP[i].literal) {
            continue;
        }
        if (strcmp(TOKEN_MAP[i].literal, ss->buf) == 0) {
            return TOKEN_MAP[i].type;
        }
    }
    return TOKEN_IDENTIFIER;
}

const char* get_token_name(enum TokenType type) {
    size_t i;
    for (i=0; TOKEN_MAP[i].description != NULL; ++i) {
        if (TOKEN_MAP[i].type == type) {
            return TOKEN_MAP[i].description;
        }
    }
    return "UNKNOWN";

}
