#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

#define PORT_NAME 1224

int main(int argc, char** argv)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("socket creation failed\n");
        return -1;
    }

    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(PORT_NAME);
    serv_addr.sin_family      = AF_INET;

    if (connect(sfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("Connection with server failed\n");
        return -1;
    }

    while (true) {
        char buffer[128] = {0};
        ssize_t bytes_read = recv(sfd, buffer, sizeof(buffer), 0);
        if (bytes_read < 0) {
            perror("Bytes read failed");
            return -1;
        }
        printf("%s\n", buffer);
    }

    close(sfd);
    return 0;

}
