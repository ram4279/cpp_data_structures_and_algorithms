#include <stdio.h>
#include <string.h>
#include "mysock.h"

int main(int argc, char** argv)
{
    if (argc < 3) {
        printf("Usage: app hostname port\n");
        return 1;
    }
    
    SOCKET fd;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_socktype = SOCK_STREAM;
    // hints.ai_family   = AF_INET; <- This is not need getaddrinfo will figure it out

    struct addrinfo *serveraddress;

    if (getaddrinfo(argv[1], argv[2], &hints, &serveraddress)) {
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    printf("Connect to:");
    char address[100];
    char service[32];
    getnameinfo(serveraddress->ai_addr, serveraddress->ai_addrlen, address, sizeof(address), service, sizeof(service), 
                serveraddress->ai_protocol);
    printf("%s %s\n", address, service);

    printf("Creating socket...\n");
    SOCKET socket_peer;
    socket_peer = socket(serveraddress->ai_family, serveraddress->ai_socktype, serveraddress->ai_protocol);
    if (!ISVALIDSOCKET(socket_peer)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    printf("Connecting...\n");
    if (connect(socket_peer, serveraddress->ai_addr, serveraddress->ai_addrlen)) {
        fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(serveraddress);
    printf("Connected.\n");
    printf("To send data, enter text followed by enter.\n");

    while (1) {
        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(socket_peer, &reads);
        FD_SET(0, &reads);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 500000;
        
        if (select(socket_peer + 1, &reads, 0, 0, &tv) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        if (FD_ISSET(socket_peer, &reads)) {
            char read[4096];
            int bytes_received = recv(socket_peer, read, 4096, 0);
            if (bytes_received < 1) {
                printf("Connection closed by peer.\n");
                break;
            }
            printf("Received (%d bytes): %.*s", bytes_received, bytes_received, read);
        }
        
        if (FD_ISSET(0, &reads)) {
            char read[4096];
            if (!fgets(read, 4096, stdin)) break;
            printf("Sending %s", read);
            int bytes_sent = send(socket_peer, read,  strlen(read), 0);
            printf("Sent %d bytes.\n", bytes_sent);
        }
    }

    printf("Closing socket...\n");
    CLOSESOCKET(socket_peer);

    return 0;
}
