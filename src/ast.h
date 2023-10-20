#ifndef AST_H
#define AST_H

#include <stdio.h>
#include "safestring.h"

#define MAX_NODE_LENGTH 32

enum ASTNodeType {
    PROGRAM,
    FUNCTION_DEC,
    STATEMENT,
    EXPRESSION
};

struct ASTNode {
    enum ASTNodeType    type;
    struct SafeString*  ss;
    struct ASTNode*     children;  // points to first child
    struct ASTNode*     next;      // points to next sibling
};

struct ASTNode* astnode_create(enum ASTNodeType, char* name);
int             astnode_destroy(struct ASTNode** n);
int             astnode_append_child(struct ASTNode* parent, struct ASTNode* child);
int             astnode_append_sibling(struct ASTNode* node, struct ASTNode* sibling);
void            astnode_display(struct ASTNode* node, size_t indent);

#endif // AST_H
