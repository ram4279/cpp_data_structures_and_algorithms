#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <cerrno>

#define PORT_NO "5555"

using namespace std;

int main()
{
    struct addrinfo hints = {0};

    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *server = NULL;

    if (getaddrinfo("127.0.0.1", PORT_NO, &hints, &server) < 0) {
        cerr << "getaddrinfo failed" << endl;
    }

    int serv_fd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    if (serv_fd < 0) {
        cerr << "socket failed" << endl;
    }
    
    while (true) {
        char buffer[128] = {0};
        cin >> buffer;
        ssize_t bytes_send = sendto(serv_fd, buffer, strlen(buffer), 0, server->ai_addr, server->ai_addrlen);
        if (bytes_send < 0) {
            cerr << "Send failed" << strerror(errno) << endl;
        }
        char recv_buffer[128] ={0};
        ssize_t bytes_recv = recvfrom(serv_fd, recv_buffer, sizeof(recv_buffer), 0, server->ai_addr, &server->ai_addrlen);
        cout << recv_buffer << endl;
    }

    return 0;

}
