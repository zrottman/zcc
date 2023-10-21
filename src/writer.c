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
            // emit_function_prologue
            fprintf(fp, ".globl _%s\n", node->ss->buf);
            fprintf(fp, "_%s:\n", node->ss->buf);
            generate_inner(node->children, fp);
            break;
        case STATEMENT:
            generate_inner(node->children, fp);
            // emit return
            fprintf(fp, "ret\n");
            break;
        case EXPRESSION:
            fprintf(fp, "movl\t$%s, %%eax\n", node->ss->buf);
            break;
    }

    generate_inner(node->next, fp);
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
