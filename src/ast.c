#include "ast.h"

// TODO:
// have append functions return pointer to appended node, which may come in handy down the road

struct {
    enum ASTNodeType type;
    char*            description;
} ASTNODEMAP[] = {
    { PROGRAM,      "<program>"      },
    { FUNCTION_DEC, "<function dec>" },
    { STATEMENT,    "<statement>"    },
    { EXPRESSION,   "<exp>"          },
    { UNARY_OP,     "<unary op>"     },
    { INT_LITERAL,  "<int literal>"  },
};

struct ASTNode* astnode_create(enum ASTNodeType type, char* name) {

    struct ASTNode* node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    if (!node) {
        return NULL; // malloc error
    }

    node->ss = safestring_create(MAX_NODE_LENGTH);
    if (safestring_set(node->ss, name) != 0) {
        // error
        safestring_destroy(&(node->ss));
        free(node);
        return NULL;
    }

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

int astnode_append_child(struct ASTNode* parent, struct ASTNode* child) {

    // if parent already has children, append
    if (parent->children) {
        astnode_append_sibling(parent->children, child);
        return 0;
    }

    // otherwise add child
    parent->children = child;
    return 0;
}

int astnode_append_sibling(struct ASTNode* node, struct ASTNode* sibling) {

    while (node->next) {
        node = node->next;
    }

    node->next = sibling;

    return 0;
}

void astnode_pretty_print(struct ASTNode* node, size_t indent) {
    if (!node) {
        return;
    }
    int i;

    // print self
    for (i=0; i<indent; ++i) {
        printf(" ");
    }

    // TODO: print enum node type (translated to string) AND value
    printf("%s %s\n", get_astnode_name(node->type), node->ss->buf);

    // print children
    if (node->children) {
        astnode_pretty_print(node->children, indent + 2);
    }

    // print sibs
    if (node->next) {
        astnode_pretty_print(node->next, indent);
    }
    
}

const char* get_astnode_name(enum ASTNodeType type) {
    size_t i;
    for (i=0; ASTNODEMAP[i].description != NULL; ++i) {
        if (ASTNODEMAP[i].type == type) {
            return ASTNODEMAP[i].description;
        }
    }
    return "UNKNOWN";

}
