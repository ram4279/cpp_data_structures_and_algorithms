#include <stdio.h>

size_t my_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

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

int main() {
    const char *str = "abc123def456";
    
    // Example usage of my_strcspn
    size_t index_cspn = my_strcspn(str, "123");
    printf("strcspn: %zu\n", index_cspn);

    // Example usage of my_strspn
    size_t index_spn = my_strspn(str, "abc");
    printf("strspn: %zu\n", index_spn);

    return 0;
}
