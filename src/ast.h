#ifndef AST_H
#define AST_H

#include <stdio.h>
#include "safestring.h"

enum ASTNodeType {
    PROGRAM,
    FUNCTION_DECL,
    STATEMENT,
    EXP
};

struct ASTNode {
    enum ASTNodeType    type;
    struct SafeString*  ss;
    //struct ASTNodeList* children;
    struct ASTNode*     children;  // points to first child
    struct ASTNode*     next;      // points to next sibling
};

/*
struct ASTNodeList {
    struct ASTNode* head;
    struct ASTNode* tail;
    size_t          len;
};
*/

struct ASTNode* astnode_create(enum ASTNodeType, struct SafeString* ss);
int             astnode_destroy(struct ASTNode** n);
int             astnode_append_child(struct ASTNode* parent, enum ASTNodeType type, struct SafeString* ss);
int             astnode_append_sibling(struct ASTNode* node, enum ASTNodeType type, struct SafeString* ss);
void astnode_display(struct ASTNode* node, size_t indent);

/*
struct ASTNodeList* astnodelist_create(void);
int                 astnodelist_destroy(struct ASTNodeList** nl);
int                 astnodelist_append_child(struct ASTNodeList* nl, enum ASTNodeType type, struct SafeString* ss);

*/
#endif // AST_H
