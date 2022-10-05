#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define PORT_NO "5555"

using namespace std;

int main()
{
    struct addrinfo hints = {0};

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *server = NULL;

    if (getaddrinfo("localhost", PORT_NO, &hints, &server) < 0) {
        cerr << "getaddrinfo failed" << endl;
    }

    int serv_fd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    if (serv_fd < 0) {
        cerr << "socket failed" << endl;
    }

    if (bind(serv_fd, server->ai_addr, server->ai_addrlen) < 0) {
        cerr << "bind failed" << endl;
    }
    
    while (true) {
        struct sockaddr_storage client_addr;
        socklen_t client_len = sizeof(client_addr);
        char buffer[4096] = {0};
        ssize_t bytes_read = recvfrom(serv_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_len);
        char client_ip[128] = {0};
        if (!getnameinfo((struct sockaddr*)&client_addr, client_len, client_ip, sizeof(client_ip), NULL, 0, NI_NUMERICHOST)) {
            cout << "Data received from " << client_ip << endl;
        }
        
        const char *msg = "Thanks for the data";
        ssize_t bytes_send = sendto(serv_fd, msg, strlen(msg), 0, (struct sockaddr*)&client_addr, client_len);
        cout << buffer << endl; 
    }
    return 0;
}
