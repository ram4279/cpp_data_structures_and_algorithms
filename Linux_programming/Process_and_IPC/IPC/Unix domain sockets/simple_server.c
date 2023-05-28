//What is wrong with the below program


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdbool.h>

#define BACK_LOG 20
#define BUFFER_SIZE 1024
#define SOCKET_PATH "/tmp/server.sock"
#define MAX_CLIENTS 20

int comm_sockets[MAX_CLIENTS] = {0};
int client_results[MAX_CLIENTS] = {0};

static void init_comm_sockets()
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        comm_sockets[i] = -1;
    }
}

static void add_to_sockets(int sock_fd)
{
    int i;
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (comm_sockets[i] == -1) {
            comm_sockets[i] = sock_fd;
            break;
        }
    }
}

static void remove_from_sockets(int sock_fd)
{
    int i;
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (comm_sockets[i] == sock_fd) {
            comm_sockets[i] = -1;
            break;
        }
    }
}

static void refresh_fd_set(fd_set *fd_set_ptr)
{
    FD_ZERO(fd_set_ptr);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (comm_sockets[i] != -1) {
            FD_SET(comm_sockets[i], fd_set_ptr);
        }
    }
}

static int get_max_socket()
{
    int max = -1;
    int i;
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (comm_sockets[i] > max) {
            max = comm_sockets[i];
        }
    }
    return max;
}

int main(int argc, char const *argv[])
{
    int conn_fd, ret;
    int comm_fd, data_len;
    int data;
    fd_set set_fds;

    char buffer[BUFFER_SIZE]         = {0};
    struct sockaddr_un sockaddr_name = {0};

    unlink(SOCKET_PATH);
    init_comm_sockets();

    conn_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (conn_fd == -1) {
        perror("Socket creation failed!");
    } else {
        printf("Socket creation Success!\n");
    }

    sockaddr_name.sun_family = AF_UNIX;
    strncpy(sockaddr_name.sun_path, SOCKET_PATH, sizeof(sockaddr_name.sun_path) - 1);

    ret = bind(conn_fd, (const struct sockaddr *)&sockaddr_name, sizeof(sockaddr_name));
    if (ret == -1) {
        perror("bind failed!");
    } else {
        printf("bind Success!\n");
    }

    ret = listen(conn_fd, BACK_LOG);
    if (ret == -1) {
        perror("listen failed!");
    } else {
        printf("listen Success!\n");
    }

    FD_ZERO(&set_fds);
    add_to_sockets(conn_fd); 
    while (true) {
        refresh_fd_set(&set_fds);
        printf("FD SET Refreshed\n");
        ret = select(get_max_socket()+1, &set_fds, NULL, NULL, NULL);
        if (FD_ISSET(conn_fd, &set_fds)) {
            printf("New client connected\n");
            comm_fd = accept(conn_fd, NULL, NULL);
            if (comm_fd == -1) {
                printf("accept failed\n");
                return 1;
            }
            add_to_sockets(comm_fd);
        } else {
            int i = 0, comm_sock_fd = -1;
            for (; i < MAX_CLIENTS; i++) {
                if (FD_ISSET(comm_sockets[i], &set_fds)) {
                    comm_sock_fd = comm_sockets[i];
                    memset(buffer, 0, sizeof(buffer));
                    recv(comm_sock_fd, buffer, sizeof(buffer), 0);
                    data = atoi(buffer);
                    printf("Client sent %d\n", data);
                    if (data == 0) {
                        memset(buffer, 0, sizeof(buffer));
                        sprintf(buffer, "Result = %d", client_results[i]);
                        send(comm_sock_fd, buffer, sizeof(buffer), 0);
                        close(comm_fd);
                        remove_from_sockets(comm_sock_fd);
                        client_results[i] = 0;
                        break;
                    }
                    client_results[i] += data;
                }
            }
        }

    }
    close(conn_fd);
    return 0;
}
