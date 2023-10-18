#include "token.h"

struct token_map TOKEN_MAP[] = {

    // Symbols
    { TOKEN_SYMBOL_OPENBRACE,  "{"           },
    { TOKEN_SYMBOL_CLOSEBRACE, "}"           },
    { TOKEN_SYMBOL_OPENPAREN,  "("           },
    { TOKEN_SYMBOL_CLOSEPAREN, ")"           },
    { TOKEN_SYMBOL_SEMICOLON,  ";"           },

    // Keywords
    { TOKEN_KEYWORD_RETURN,    "return"      },
    { TOKEN_KEYWORD_INT,       "int"         },

    // Identifiers
    { TOKEN_IDENTIFIER,        "identifier"  }, 

    // Literals
    { TOKEN_LITERAL_INT,       "int literal" },

    { TOKEN_END,               NULL          }

};

enum token_type get_token_type(char* s) {
    size_t i;
    for (i=0; TOKEN_MAP[i].val != NULL; ++i) {
        if (strcmp(TOKEN_MAP[i].val, s) == 0) {
            return TOKEN_MAP[i].type;
        }
    }
    return TOKEN_IDENTIFIER;
}

const char* get_token_name(enum token_type type) {
    size_t i;
    for (i=0; TOKEN_MAP[i].val != NULL; ++i) {
        if (TOKEN_MAP[i].type == type) {
            return TOKEN_MAP[i].val;
        }
    }
    return "UNKNOWN";

}

void display_token(struct token* tok) {
    printf("token_type: %d\n", tok->type);
    printf("token_val : %s\n\n", tok->val->buf);
}
