#include "safestring.h"

struct SafeString* safestring_create(size_t capacity) {

    // caller can handle errors by checking for nullity
    
    struct SafeString* ss = (struct SafeString*)malloc(sizeof(struct SafeString));

    if (!ss) {
        return NULL; // malloc failure
    }

    ss->buf = malloc(capacity);
    if (!ss->buf) {
        free(ss);
        return NULL; // malloc failure
    }

    ss->len    = 0;        // does not include null byte
    ss->cap    = capacity; // includes null byte
    ss->buf[0] = '\0';

    return ss;
}

int safestring_destroy(struct SafeString** ss) {
    struct SafeString* s = *ss;
    if (s) {
        if (s->buf) {
            free(s->buf);
            s->buf = NULL;
        }
        free(s);
        //s = NULL;
        *ss = NULL;
    }
    return 0;
}

int safestring_set(struct SafeString* dest, const char* src) {
    size_t src_len = strlen(src); // strlen does not include null byte
    if (src_len >= dest->cap) {
        return 1; // insufficient space
    }

    strcpy(dest->buf, src); // strcpy does include null byte
    dest->len = src_len;
    return 0;
}

int safestring_appendc(struct SafeString* ss, const char c) {
    if (ss->len + 1 == ss->cap) {
        return 1; // not enough space
    }
    ss->buf[ss->len++] = c;
    ss->buf[ss->len] = 0;
    return 0;
}

int safestring_append(struct SafeString* ss, const char* s) {
    // ensure there's enough room
    size_t s_len = strlen(s);
    if (ss->len + s_len >= ss->cap) {
        return 1; // not enough space
    }
    for (int i=0; i<s_len; ++i) {
        if (safestring_appendc(ss, s[i]) != 0) {
            return 2; // error
        }
    }
    return 0;
}

