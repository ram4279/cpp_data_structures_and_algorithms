#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int err = -1;
    struct ifaddrs *addresses = NULL;
    struct ifaddrs *address = NULL;
    char ip[100] = {0};
    size_t family_size = 0;

    // Call getifaddrs function to get the interfaces in a linked list 
    // This function allocated the memory as well
    if ((err = getifaddrs(&addresses))) {
        printf("Getting interfaces failed\n");
        return err;
    }

    // Make address point to first result
    address = addresses;

    // Traverse and print
    while(address) {
        int family = address->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) {
           printf("%s\t", address->ifa_name); 
           printf("%s\t", (family == AF_INET) ? "IPv4": "IPv6");
           family_size = (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
           getnameinfo(address->ifa_addr, family_size, ip, sizeof(ip), 0, 0, NI_NUMERICHOST);
           printf("\t%s\n", ip);
        }
        address = address->ifa_next;
    }

    freeifaddrs(addresses);
    return 0;
}
