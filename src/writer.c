#include "writer.h"

void generate(struct ASTNode* root, char* file_in) {
    struct SafeString* file_out;
    FILE* fp;

    file_out= make_filename(file_in);
    fp = fopen(file_out->buf, "w");
    safestring_destroy(&file_out);

    fputs("hello world", fp);
    
    fclose(fp);
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
