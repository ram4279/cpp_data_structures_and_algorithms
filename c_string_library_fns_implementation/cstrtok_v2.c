#include <stdio.h>
#include <stdlib.h>

char *my_strtok(char *str, const char *delim) {
    static char *p = NULL;
    if (str != NULL) {
        p = str;
    }
    if (p == NULL) {
        return NULL;
    }
    // skip any initial delimiters
    char *d;
    while (*p) {
        for (d = (char *)delim; *d; d++) {
            if (*p == *d) {
                p++;
                break;
            }
        }
        if (*d == '\0') {
            break;
        }
    }
    char *start = p;
    while (*p) {
        for (d = (char *)delim; *d; d++) {
            if (*p == *d) {
                *p = '\0';
                char *temp = p;
                p++;
                if (*p == '\0') {
                    p = NULL;
                }
                return start;
            }
        }
        p++;
    }
    if (*start == '\0') {
        return NULL;
    }
    p = NULL;
    return start;
}



int main() {
    char str[] = "  -- This is a-test  of iage - | ";
    const char *delim = " -";
    char *ptr = my_strtok(str, delim);

    while (ptr != NULL) {
        printf("%s\n", ptr);
        ptr = my_strtok(NULL, delim);
    }

    return 0;
}
