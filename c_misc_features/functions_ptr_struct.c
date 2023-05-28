#include <stdio.h>
#include <string.h>

typedef void (*func_ptr) (char* str);

struct string
{
    char name[20];
    func_ptr func;
};

typedef struct string string_t;

void to_uppercase(char *name) {
    for (int i = 0; i < strlen(name); i++) {
        if (name[i] >= 'a' && name[i] <= 'z') {
            name[i] = name[i] - 32;
        }
    }
}

void to_lowercase(char *name) {
    for (int i = 0; i < strlen(name); i++) {
        if (name[i] >= 'A' && name[i] <= 'Z') {
            name[i] = name[i] + 32;
        }
    }
}


int main(int argc, char const *argv[])
{
    string_t s1 = {
        .name = "Sairam",
        .func = to_uppercase
    };

    printf("name before calling functions = %s\n", s1.name);
    s1.func(s1.name);
    printf("name after calling functions = %s\n", s1.name);


    string_t s2;
    s2.func = to_lowercase;
    printf("Enter word in capital letters\n");
    fgets(s2.name, sizeof(s2.name), stdin);
    s2.func(s2.name);
    printf("name after calling functions = %s\n", s2.name);
    return 0;
}
