#ifndef TOKENLIST_H
#define TOKENLIST_H

#include "token.h"

struct TokenList {
    struct Token* head;
    struct Token* tail;
    size_t len;
};

struct TokenList* tokenlist_create(void);
int               tokenlist_destroy(struct TokenList **tl);

int               tokenlist_append(struct TokenList *tl, enum TokenType type, struct SafeString *ss);
void              tokenlist_display(struct TokenList *tl);

#endif // TOKENLIST_H
