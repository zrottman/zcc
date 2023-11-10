#ifndef AST_H
#define AST_H

#include <stdio.h>
#include "safestring.h"

#define MAX_NODE_LENGTH 32

// TODO: create map of enums to string representations and
// function to translate
//
enum ASTNodeType {
    PROGRAM,
    FUNCTION_DEC,
    STATEMENT,
    EXPRESSION,
    UNARY_OP,
    INT_LITERAL
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
void            astnode_pretty_print(struct ASTNode* node, size_t indent);

#endif // AST_H
