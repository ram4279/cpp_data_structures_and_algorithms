#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

int main()
{
    struct addrinfo hints = {0};
    hints.ai_family       = AF_INET;
    hints.ai_socktype     = SOCK_STREAM;

    struct addrinfo *server = NULL;
    if (getaddrinfo("localhost", "8888", &hints, &server) < 0) {
        perror("getaddrinfo failed\n");
        return -1;
    }

    int serv_fd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    if (serv_fd < 0) {
        perror("Socket creation failed\n");
        return -1;
    }

    if (bind(serv_fd, server->ai_addr, server->ai_addrlen) < 0) {
        perror("bind failed\n");
        return -1;
    }

    if (listen(serv_fd, 10) < 0) {
        perror("listed failed\n");
        return -1;
    }

    fd_set max_fds;
    FD_ZERO(&max_fds);
    FD_SET(serv_fd, &max_fds);
    int max_socket = serv_fd;
    
    while (1) {
        fd_set reads;
        reads = max_fds;
        int select_retval = select(max_socket+1, &reads, 0, 0, 0);
        if (select_retval < 0) {
            perror("Select failed");
            return -1;
        }
        int i = 1;
        for (i = 1; i <= max_socket; i++) {
            if (FD_ISSET(i, &reads)) {
                if (i == serv_fd) {
                    // New connection
                    struct sockaddr_storage client_addr = {0};
                    socklen_t client_addr_len = sizeof(struct sockaddr_storage);
                    int client_fd = accept(serv_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                    if (client_fd > 0) {
                        char client_ip[32] = {0};
                        if (!getnameinfo((struct sockaddr *)&client_addr, client_addr_len, client_ip, sizeof(client_ip), NULL, 0, NI_NUMERICHOST)) {
                            printf("New connection request recevied from %s \n", client_ip);
                        }
                        FD_SET(client_fd, &max_fds);
                        if (client_fd > max_socket) {
                            max_socket = client_fd; 
                        }
                    }
                } else {
                    // Message from exisiting client
                    char read[1024] = {0};
                    size_t bytes = recv(i, read, sizeof(read), 0);
                    if (bytes < 1) {
                        // Connection closed by the client do not listen on this socket from now on
                        FD_CLR(i, &max_fds);
                        close(i);
                        continue;
                    }

                    int j;
                    for (j = 1; j <= max_socket; j++) {
                        if (FD_ISSET(j, &max_fds)) {
                            // Do not send to server and to the message originator
                            if (j == serv_fd || j == i)
                                continue;
                            else
                                send(j, read, bytes, 0);
                        }
                    }
                }
            }
        }
    }

    close(serv_fd);
    return 0;

}
