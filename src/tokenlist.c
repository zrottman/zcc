#include "tokenlist.h"

struct TokenList* tokenlist_create(void) {
    struct TokenList *tl = (struct TokenList*)malloc(sizeof(struct TokenList));

    if (!tl) {
        return NULL; // malloc error
    }

    tl->head = NULL;
    tl->tail = NULL;
    tl->len  = 0;

    return tl;
}

int tokenlist_destroy(struct TokenList **tl) {
    struct Token* cur = (*tl)->head;

    token_destroy(&cur);

    (*tl)->head = NULL;
    (*tl)->tail = NULL;
    free(*tl);

    *tl = NULL;

    return 0;
}

int tokenlist_append(struct TokenList *tl, enum TokenType type, struct SafeString *ss) {
    if (tl == NULL)    { 
        // invalid tokenlist
        return 1; 
    }

    struct Token *tok = token_create(type, ss);
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

void tokenlist_display(struct TokenList *tl) {
    struct Token* cur = tl->head;
    while (cur) {
        token_display(cur);
        cur = cur->next;
    }
}
