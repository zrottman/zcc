#include "utils.h"

// Function:    mystrrchr
// Description: Home-rolled version of strrchr(). Searches for last
//              occurrence of `target` in string `s` and returns a
//              pointer to its location.
// Arguments:   s      : input string
//              target : target char
// Returns:     Pointer to last location in `s` of `target`
char* mystrrchr(const char* s, const char target) {
    if (s == NULL) {
        return NULL;
    }

    char *last_occurrence = NULL;

    while (*s != '\0') {
        if (*s == target) { last_occurrence = (char *)s; }
        s++;
    }

    return last_occurrence;
}

// Function:    mystrcmp
// Description: Home-rolled version of strcmp(). Compares two input strings,
//              returnin 0 if they are identical else 1.
// Arguments:   s1 : string one
//              s2 : string two
// Returns:     0 if they are identical, else 1.
int mystrcmp(const char* s1, const char* s2) {
    // handle NULL pointers
    if (s1 == 0 && s2 == 0) {
        return 0; 
    } else if (s1 == 0) {
        return -1;
    } else if (s2 == 0) {
        return 1;
    }

    while (*s1 != '\0' || *s2 != '\0') {
        if (*s1 != *s2) {
            return (*s1 > *s2) ? 1 : -1;
        }
        s1++;
        s2++;
    }

    return 0;
}
