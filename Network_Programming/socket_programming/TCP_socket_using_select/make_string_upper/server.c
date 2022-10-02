#include "mysock.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{

    SOCKET server_sock;
    struct addrinfo hints;
    struct addrinfo *serveraddr;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    getaddrinfo(0, "8080", &hints, &serveraddr);
    
    server_sock = socket(serveraddr->ai_family, serveraddr->ai_socktype, serveraddr->ai_protocol);

    bind(server_sock, serveraddr->ai_addr, serveraddr->ai_addrlen);
    freeaddrinfo(serveraddr);

    listen(server_sock, 10);

    fd_set master;
    FD_ZERO(&master);
    FD_SET(server_sock, &master);
    SOCKET max_socket = server_sock;
    while(1) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }
        SOCKET i;
        for(i = 1; i <= max_socket; ++i) {
            if (FD_ISSET(i, &reads)) {
                if (i == server_sock) {
                    struct sockaddr_storage client_address;
                    socklen_t client_len = sizeof(client_address);
                    SOCKET socket_client = accept(server_sock, (struct sockaddr*) &client_address, &client_len);
                    if (!ISVALIDSOCKET(socket_client)) {
                        fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
                        return 1;
                    }
                    FD_SET(socket_client, &master);
                    if (socket_client > max_socket) {
                        max_socket = socket_client;
                    }
                    char address_buffer[100];
                    getnameinfo((struct sockaddr*)&client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
                    printf("New connection from %s\n", address_buffer);
                } else {
                    char read[1024];
                    int bytes_received = recv(i, read, 1024, 0);
                    if (bytes_received < 1) {
                        FD_CLR(i, &master);
                        CLOSESOCKET(i);
                        continue;
                    }
                    int j;
                    for (j = 0; j < bytes_received; ++j) {
                        read[j] = toupper(read[j]);
                    }
                    send(i, read, bytes_received, 0);
                }
            }
        }

    }
    return 0;
}
