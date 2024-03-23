#include <stdio.h>
//"COLONSSEMICOLONS                          : ::  : :sauran";
size_t my_strcspn(const char *str, const char *reject) {
    size_t length = 0;
    while (str[length] != '\0') {
        int found = 0;
        for (size_t i = 0; reject[i] != '\0'; i++) {
            if (str[length] == reject[i]) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
        length++;
    }
    return length;
}

size_t my_strspn(const char *str, const char *accept) {
    size_t length = 0;
    while (str[length] != '\0') {
        int found = 0;
        for (size_t i = 0; accept[i] != '\0'; i++) {
            if (str[length] == accept[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            break;
        }
        length++;
    }
    return length;
}


//"COLONS:SEMICOLONS                          : ::  : :sauran";
char* strtok_m(char* s, const char* delimiters)
{
    static char* save_ptr = NULL;
    char* end = NULL;
    if (s == NULL) {
        s = save_ptr;
    }
    
    if (*s == 0) {
        save_ptr = s;
        return NULL;
    }

    s += my_strspn(s, delimiters); //skip delimiters
    if (*s == 0)
    {
        save_ptr = s;
        return NULL;
    }

    end = s + my_strcspn(s, delimiters);//skip non delimiters
    if (*end == 0)
    {
        save_ptr = end;
        return s;
    }

    *end = 0;
    save_ptr = end + 1;
    return s;
}

int main()
{
char str[] = "COLONS:SEMICOLONS:GODDAMICONL                          : ::  : :sauran";
    //char str[] = "        :  ";
    char *ptr = strtok_m(str, " ,:");
    while (ptr)
    {
        printf("%s\n", ptr);
        ptr = strtok_m(NULL, " ,:");
    }
    return 0;
}