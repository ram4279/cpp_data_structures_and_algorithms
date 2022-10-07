#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/in.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("lookup hostname\n");
        printf("eg: lookup google.com\n");
        return -1;
    }

    struct addrinfo hints = {0};
    hints.ai_flags = AI_ALL; // Get both IPv4 and IPv6 addresses

    struct addrinfo *addresses = NULL;
    struct addrinfo *address = NULL;
    int res = getaddrinfo(argv[1], 0, &hints, &addresses);

    if (res != 0) {
        printf("Lookup failed\n");
        return 0;
    }

    printf("Resolving hostnames...");
    for (address = addresses; address; address = address->ai_next) {
        char ip_addr[64] = {0};
        char service[8]  = {0};
        if (!getnameinfo(address->ai_addr, address->ai_addrlen, ip_addr, sizeof(ip_addr), service, sizeof(service),
             NI_NUMERICHOST|NI_NUMERICSERV)) {
            printf("%s %s\n", ip_addr, service);
        }
    }
    freeaddrinfo(addresses);

}
