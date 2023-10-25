#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <string.h>

struct SafeString {
    char*  buf;
    size_t len; // does not include null byte
    size_t cap; // includes null byte
};

struct SafeString* safestring_create(size_t capacity);
int                safestring_destroy(struct SafeString** ss);

int                safestring_set(struct SafeString* dest, const char* src);
int                safestring_appendc(struct SafeString* ss, const char c);
int                safestring_append(struct SafeString* ss, const char* s);

#endif // STRING_H

