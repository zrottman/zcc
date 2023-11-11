#include "writer.h"

void generate(struct ASTNode* root, char* file_in) {
    struct SafeString* file_out;
    FILE* fp;

    file_out= make_filename(file_in);
    fp = fopen(file_out->buf, "w");
    safestring_destroy(&file_out);

    generate_inner(root, fp);

    fclose(fp);
    return;
}

void generate_inner(struct ASTNode* node, FILE* fp) {
    if (!node) {
        return;
    }

    switch (node->type) {
        case PROGRAM:
            generate_inner(node->children, fp);
            break;
        case FUNCTION_DEC:
            emit_function_prologue(node, fp);
            generate_inner(node->children, fp);
            // emit function epilogue?
            break;
        case STATEMENT:
            generate_inner(node->children, fp);
            emit_return(fp);
            break;
        case EXPRESSION:
            generate_inner(node->children, fp);
            break;
        case INT_LITERAL:
            emit_int_literal(node, fp);
            break;
        case UNARY_OP:
            generate_inner(node->children, fp);
            emit_unary_op(node, fp);
            break;
    }

    generate_inner(node->next, fp);
}

void emit_function_prologue(struct ASTNode* node, FILE* fp) {
    fprintf(fp, ".globl _%s\n", node->ss->buf);
    fprintf(fp, "_%s:\n", node->ss->buf);
    return;
}

void emit_return(FILE* fp) {
    fprintf(fp, "ret\n");
    return;
}

void emit_int_literal(struct ASTNode* node, FILE* fp) {
    fprintf(fp, "movl\t$%s, %%eax\n", node->ss->buf);
    return;
}

void emit_unary_op(struct ASTNode* node, FILE* fp) {
    /* not sure if I like this solution of going to the string buf and comparing
     * chars. It works, but there's a tradeoff. The advantage is having a single
     * enum for UNARY_OP rather than 3 different enums for each kind.
     */
    switch (node->ss->buf[0]) {
        case '-':
            fprintf(fp, "neg \t%%eax\n");
            break;
        case '!':
            fprintf(fp, "\n");
            break;
        case '~':
            fprintf(fp, "it's tilde\n");
            break;
    }
    return;
}

struct SafeString* make_filename(char* file_in) {
    struct SafeString* ss = safestring_create(MAX_FILENAME_LENGTH);
    char* p = mystrrchr(file_in, '.');
    *p = 0;
    if (safestring_set(ss, file_in) != 0) {
        // error
    }
    if (safestring_append(ss, ".asm") != 0) {
        // error
    }

    return ss;
}
