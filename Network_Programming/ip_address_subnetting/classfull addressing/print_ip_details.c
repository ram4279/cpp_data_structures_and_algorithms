/*
 * Given an classful ipv4 address. Print the following
 * Network address
 * First host address
 * LAST host address
 * Broadcast address
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_IPV4_DOT_SEPARATOR 3
#define MAX_IPV4_OCTETS        4


#define CLASS_A_IP 127
#define CLASS_B_IP 192
#define CLASS_C_IP 224

enum {
    INVAL_DOT_FAILURE = 1,
    INVAL_NO_OF_OCTETS,
    INVAL_OCTET_NO,
    INVAL_CHARACTER,
    VAL_SUCCESS_IP
};

void print_ip(uint32_t ip)
{
    printf("%d.", (ip >> 24) & 0xFF);
    printf("%d.", (ip >> 16) & 0xFF);
    printf("%d.", (ip >> 8) & 0xFF);
    printf("%d", (ip) & 0xFF);
    return;
}

int validate_ip(char *ipaddress)
{
    // Check if 3 dots are there
    ipaddress = strdup(ipaddress);
    uint8_t no_of_dots = 0;
    uint8_t no_of_octets = 0;
    int ret = 0;
    long octet_number = 0;

    char* ptr = ipaddress;
    while (*ptr) {
        if (*ptr == '.')
            no_of_dots++;
        ptr++;
    }

    if (no_of_dots != MAX_IPV4_DOT_SEPARATOR) {
        return INVAL_DOT_FAILURE;
    }

    // Check any octets contain value greater than 255
    ptr = strtok(ipaddress, ".");
    while (ptr) {
        octet_number = strtol(ptr, NULL, 10);
        if (errno == ERANGE) {
            return INVAL_CHARACTER;
        }
        if (octet_number == 0 || octet_number > 255) {
            return INVAL_OCTET_NO;
        }
        ptr = strtok(NULL, ".");
        no_of_octets++;
    }

    // Check if only 4 octets are there in ip address
    if (no_of_octets != MAX_IPV4_OCTETS) {
        return INVAL_NO_OF_OCTETS;
    }

    free(ipaddress);
    return VAL_SUCCESS_IP;
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Invalid no of arguments\n");
        printf("Usage: %s <ipv4 address>\n", argv[0]);
        printf("Example: %s 192.168.1.2\n", argv[0]);
        exit(1);
    }

    int ret = 0;
    uint8_t ipv4_arr[MAX_IPV4_OCTETS];
    uint8_t subnet_arr[MAX_IPV4_OCTETS];
    uint8_t temp[MAX_IPV4_OCTETS];
    uint32_t ipv4_bits;
    uint32_t subnet_bits;
    uint32_t ip_pool_range_bits;

    char* subnet_str = "";
    char* ip_pool_range_str = "";

    ret = validate_ip((char *)argv[1]);
    if (ret != VAL_SUCCESS_IP) {
        printf("ip address is Invalid returned = %d\n", ret);
        return 0;
    }

    sscanf(argv[1], "%u.%u.%u.%u",
           &ipv4_arr[0], &ipv4_arr[1], &ipv4_arr[2], &ipv4_arr[3]);
    ipv4_bits = (ipv4_arr[0] << 24 | ipv4_arr[1] << 16 | 
                ipv4_arr[2] << 8 | ipv4_arr[3]);
    
    long first_octet = ipv4_arr[0];

    if (first_octet < CLASS_A_IP) {
        printf("Class A IP\n");
        subnet_str = "255.0.0.0";
        ip_pool_range_str = "0.255.255.255";
    } else if (first_octet < CLASS_B_IP) {
        printf("Class B IP\n");
        subnet_str = "255.255.0.0";
        ip_pool_range_str = "0.0.255.255";
    } else if (first_octet < CLASS_C_IP) {
        printf("Class C IP\n");
        subnet_str = "255.255.255.0";
        ip_pool_range_str = "0.0.0.255";
    } else {
        printf("Class D or E IP\n");
        return 0;
    }

    sscanf(subnet_str, "%u.%u.%u.%u", &subnet_arr[0], &subnet_arr[1], 
           &subnet_arr[2], &subnet_arr[3]);
    subnet_bits = (subnet_arr[0] << 24 | subnet_arr[1] << 16 | 
                   subnet_arr[2] << 8 | subnet_arr[3]);


    sscanf(ip_pool_range_str, "%u.%u.%u.%u", &temp[0], &temp[1], 
           &temp[2], &temp[3]);
    ip_pool_range_bits = (temp[0] << 24 | temp[1] << 16 | 
                   temp[2] << 8 | temp[3]);

    printf("Network id = ");
    print_ip(ipv4_bits & subnet_bits);
    printf("\n");

    printf("First host ip =  ");
    print_ip((ipv4_bits & subnet_bits) + 1);
    printf("\n");

    printf("Last host ip =  ");
    print_ip((ipv4_bits & subnet_bits) + (ip_pool_range_bits - 1));
    printf("\n");

    printf("Broadcast ip =  ");
    print_ip((ipv4_bits & subnet_bits) + (ip_pool_range_bits));
    printf("\n");

    return 0;
}
