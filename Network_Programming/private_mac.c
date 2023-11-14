#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_ARG_COUNT 2
#define MAX_MAC_SIZE  6
/*
 * String representation 02:00:0f:aa:ab:ac
 * MAC_ADDRESS representation 
 * lo  = 0x2000
 * mid = 0x0faa
 * hi  = 0xabac
 */

typedef struct {
    uint16_t lo;
    uint16_t mi;
    uint16_t hi;
} MAC_ADDRESS;

int main(int argc, char *argv[])
{
    if (argc != MAX_ARG_COUNT)
    {
        printf("%s\n", "Invalid Arguments");
        return -1;
    }

    uint8_t mac_len = strlen(argv[1]);
    if (mac_len != 17)
    {
        printf("%s\n", "Invalid MAC_ADDRESS");
        printf("%s %d\n", "MAC_ADDRESS length is", mac_len);
        return -1;
    }

    char mac_buf[18] = {0};
    uint8_t mac_addr[MAX_MAC_SIZE];
    strncpy(mac_buf, argv[1], mac_len);
    
    char *token = strtok(mac_buf, ":");
    int index = 0;
    while (token) {
        if (index == MAX_MAC_SIZE)
        {
            printf("%s\n", "Invalid MAC ADDRESS FORMAT");
            return -1;  
        }
        mac_addr[index] = (uint8_t)strtol(token, NULL, 16); 
        printf("%02x\n", mac_addr[index]);
        index++;
        token = strtok(NULL, ":");
    }

    if (index != MAX_MAC_SIZE)
    {
        printf("%s\n", "Invalid MAC ADDRESS FORMAT");
        return -1;
    }

    MAC_ADDRESS src_addr = {
        .lo = mac_addr[0] << 8 | mac_addr[1],
        .mi = mac_addr[2] << 8 | mac_addr[3],
        .hi = mac_addr[4] << 8 | mac_addr[5]
    };

    printf("%x", src_addr.lo);
    printf("%x", src_addr.mi);
    printf("%x\n", src_addr.hi);
    return 0;
}
