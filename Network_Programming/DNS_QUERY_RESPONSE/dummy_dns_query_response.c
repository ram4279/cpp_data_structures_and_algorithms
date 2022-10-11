#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

int main()
{
    // DNS HEADER FORMAT 
    // https://www.oreilly.com/api/v2/epubs/9781789349863/files/assets/346de5c8-e0a1-4694-bee3-2ffd68761f09.png

    // DNS QUESTION FORMAT
    // https://images.slideplayer.com/35/10291817/slides/slide_17.jpg
    
    char dns_query[] = {  /* HEADER PART FIRST*/
                          0xAB, 0xAB, /* 16 bit Random ID, you can set whatever you want the same will be in response */ 
                          0x01, /* FIRST 8BITS are QR = 0, OPCODE = 0000, AA=0, TC=0, RD=1| */
                          0x00, /* SECOND 8BITS are RA = 0, z = 000, RCODE = 0000 */
                          0x00, 0x01, /* QDCOUNT = 00000000 00000000*/
                          0x00, 0x00, /* ANCOUNT = 00000000 00000000*/
                          0x00, 0x00, /* NSCOUNT = 00000000 00000000*/
                          0x00, 0x00, /* ARCOUNT = 00000000 00000000*/
                          6, 'g', 'o', 'o', 'g', 'l', 'e', /* 6 google*/
                          3, 'c', 'o', 'm', /*3 com*/
                          0, /*End of name*/
                          0x00, 0x01, /* QTYPE = A which means IP address */
                          0x00, 0x01  /* QCLASS = 1 which means internet */
                       };

    char *dns_server = "8.8.8.8";

    struct addrinfo hints = {0};
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *server_info = NULL;
    if (getaddrinfo(dns_server, "53", &hints, &server_info)) {
        perror("getaddrinfo failed\n");
        return -1;
    }
    
    int sfd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
    if (sfd < 0) {
        perror("Socket creation failed\n");
        return -1;
    }

    ssize_t bytes_sent = sendto(sfd, dns_query, sizeof(dns_query), 0, server_info->ai_addr, server_info->ai_addrlen);
    if (bytes_sent < 0) {
        perror("sendto failed\n");
        return -1;
    }
    return 0;
}
