#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <netdb.h>

#define PORT_NUMBER 1224

int main(int argc, char** argv)
{
    //Create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("socket creation failed\n");
        return -1;
    }

    //bind
    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(PORT_NUMBER);
    serv_addr.sin_family      = AF_INET;

    if (bind(sfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("bind failed\n");
        return -1;
    }

    //listen
    if (listen(sfd, 0) < 0) {
        perror("listen failed");
        return -1;
    }

    //accept
    while (true) {
        struct sockaddr_in client_addr = {0};
        socklen_t client_addr_size = sizeof(struct sockaddr);
        char ip[128] = {0};
        int client_fd = accept(sfd, (struct sockaddr *)&client_addr, &client_addr_size);

        if (client_fd < 0) {
            perror("accpet failed");
            return -1;
        }
        getnameinfo((struct sockaddr *)&client_addr, sizeof(struct sockaddr_in), ip, sizeof(ip),
                    NULL, 0, 0);

        printf("Getting  request from %s\n", ip);
        char msg[128] = {0};
message:
        printf("Server:");
        fgets(msg, sizeof(msg), stdin);
        ssize_t bytes_sent = send(client_fd, msg, strlen(msg), 0);
        if (bytes_sent < 0) {
            perror("Sending message failed\n");
            return -1;
        }
        goto message;
    }

    close(sfd);
    return 0;
}
