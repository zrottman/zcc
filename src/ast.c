#include "ast.h"

// TODO:
// have append functions return pointer to appended node, which may come in handy down the road

struct ASTNode* astnode_create(enum ASTNodeType type, struct SafeString* ss) {

    struct ASTNode* node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    if (!node) {
        return NULL; // malloc error
    }

    if (ss->len == 0) {
        free(node);
        return NULL; // invalid safestring
    }

    node->ss = safestring_create(ss->len+1);
    if (safestring_set(node->ss, ss->buf) != 0) {
        // error
        safestring_destroy(&(node->ss));
        free(node);
        return NULL;
    }

    //node->children = astnodelist_create();
    node->children = NULL;
    node->next     = NULL;


    node->type     = type;

    return node;
}

int astnode_destroy(struct ASTNode** n) {

    struct ASTNode* cur   = *n;
    struct ASTNode* next  = cur->next;

    // destroy children
    if (cur->children) {
        astnode_destroy(&(cur->children));
    }
    
    // destroy self
    safestring_destroy(&cur->ss);
    free(cur);
    *n = NULL;

    // destroy siblings
    if (next) {
        astnode_destroy(&next);
    }

    return 0;
}

int astnode_append_child(struct ASTNode* parent, enum ASTNodeType type, struct SafeString* ss) {

    // if parent already has children, append
    if (parent->children) {
        astnode_append_sibling(parent->children, type, ss);
        return 0;
    }

    // otherwise malloc new child here
    struct ASTNode* newchild = astnode_create(type, ss);
    parent->children = newchild;
    return 0;
}

int astnode_append_sibling(struct ASTNode* node, enum ASTNodeType type, struct SafeString* ss) {
    struct ASTNode* new_sib = astnode_create(type, ss);

    while (node->next) {
        node = node->next;
    }

    node->next = new_sib;

    return 0;
}

void astnode_display(struct ASTNode* node, size_t indent) {
    if (!node) {
        return;
    }
    int i;
    struct ASTNode* cur = node;

    // print self
    for (i=0; i<indent; ++i) {
        printf(" ");
    }
    printf("%s\n", node->ss->buf);

    // print children
    if (node->children) {
        astnode_display(node->children, indent + 2);
    }

    // print sibs
    if (node->next) {
        astnode_display(node->next, indent);
    }


    
}

/*
struct ASTNodeList* astnodelist_create(void) {
    struct ASTNodeList* nl = (struct ASTNodeList*)malloc(sizeof(struct ASTNodeList));
    if (!nl) {
        return NULL; // malloc error
    }

    nl->head = NULL;
    nl->tail = NULL;
    nl->len  = 0;

    return nl;
}

int astnodelist_destroy(struct ASTNodeList** nl) {
    struct ASTNode* cur = (*nl)->head;
    struct ASTNode* next;

    while (cur) {
        next = cur->next;

        astnode_destroy(&cur);
        cur->next;
    }


    return 0;
}

int astnodelist_append_child(struct ASTNodeList* nl, enum ASTNodeType type, struct SafeString* ss) {
    return 0;
}
*/
