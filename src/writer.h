#ifndef WRITER_H
#define WRITER_H

#include <string.h>
#include "utils.h"
#include "safestring.h"
#include "ast.h"

#define MAX_FILENAME_LENGTH 64

void               generate(struct ASTNode* root, char* file_in);
void               generate_inner(struct ASTNode* root, FILE* fp);
void               emit_function_prologue(struct ASTNode* node, FILE* fp);
void               emit_return(FILE* fp);
struct SafeString* make_filename(char* file_in);

#endif // WRITER_H
