#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#define BUFLEN 2048

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <interface>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sock_fd;
    struct ifreq ifr;
    char mac_addr[6] = {0};
	memset(&ifr, 0, sizeof(struct ifreq));

    // Create a socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }

    // Set the interface name
    strncpy(ifr.ifr_name, argv[1], IFNAMSIZ);

    // Get the MAC address of the interface
    if (ioctl(sock_fd, SIOCGIFHWADDR, &ifr) < 0) {
        perror("ioctl() failed");
        exit(EXIT_FAILURE);
    }
    memcpy(mac_addr, ifr.ifr_hwaddr.sa_data, sizeof(mac_addr));

    // Print the MAC address
    printf("MAC address of interface %s: %02x:%02x:%02x:%02x:%02x:%02x\n", argv[1],
        mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

    // Close the socket
    close(sock_fd);

    return 0;
}
