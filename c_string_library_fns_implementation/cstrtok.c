#include <stdio.h>

int is_delim(char c, char* delim)
{
    while (*delim) {
        if (c == *delim) {
            return 1;
        }
        delim++;
    }
    return 0;
}

char* m_strtok(char* str, char* delim)
{
    static char* begin_ptr = NULL;
    if (str == NULL) {
        str = begin_ptr;
    }
    
    if (str == NULL) {
        return NULL;
    }

    while (1) {
        // Skipping delimiter till i get a valid character
        if (is_delim(*str, delim)) {
            str++;
            continue;
        }
        
        // After skipping i reached end so return NULL
        if (*str == '\0') {
            return NULL;
        }
        // Found some character not part of delimeter
        break;
    }

    char* res = str;

    while (1) {
        if (is_delim(*str, delim)) {
            *str = '\0';
            begin_ptr = str + 1;
            return res;
        }

        if (*str == '\0') {
            begin_ptr = str;
            return res;
        }
        str++;
    }
}

int main(int argc, char const *argv[])
{
    char str[] = "--- This-is a|separted_string";
    char del[] = "- |_";
    char *ptr = m_strtok(str, del);
    while (ptr) {
        printf("%s\n", ptr);
        ptr = m_strtok(NULL, del);
    }
    return 0;
}
