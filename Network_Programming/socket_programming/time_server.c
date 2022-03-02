#include <stdio.h>
#include <time.h>
#include <string.h>
#include "mysock.h"

int main()
{
    SOCKET listen_socket;
    struct addrinfo hints;

    printf("Configuring local address...");
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET; /*For IPv6 change this to AF_INET6*/
    hints.ai_flags    = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    
    struct addrinfo *serv_addr;
    getaddrinfo(0, "8080", &hints, &serv_addr);

    printf("Creating socket...\n");
    listen_socket = socket(serv_addr->ai_family, serv_addr->ai_socktype, serv_addr->ai_protocol);
    
    if (!ISVALIDSOCKET(listen_socket)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    printf("Binding socket to local address...\n");
    if (bind(listen_socket, serv_addr->ai_addr, serv_addr->ai_addrlen)) {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    freeaddrinfo(serv_addr);

    printf("Listening...\n");
    if (listen(listen_socket, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    printf("Waiting for connection...\n");
	struct sockaddr_storage client_address;
 	socklen_t client_len = sizeof(client_address);
 	SOCKET socket_client = accept(listen_socket, (struct sockaddr*) &client_address, &client_len);
	if (!ISVALIDSOCKET(socket_client)) {
		fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
		return 1;
	}

	printf("Client is connected... ");
	char address_buffer[100];
	getnameinfo((struct sockaddr*)&client_address,
	client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
	printf("%s\n", address_buffer);

	printf("Reading request...\n");
	char request[1024];
	int bytes_received = recv(socket_client, request, 1024, 0);
    printf("%.*s", bytes_received, request);
	printf("Received %d bytes.\n", bytes_received);

	printf("Sending response...\n");
	const char *response =
 		"HTTP/1.1 200 OK\r\n"
		 "Connection: close\r\n"
		 "Content-Type: text/plain\r\n\r\n"
		 "Local time is: ";
	int bytes_sent = send(socket_client, response, strlen(response), 0);
	printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));

	time_t timer;
	time(&timer);
	char *time_msg = ctime(&timer);
	bytes_sent = send(socket_client, time_msg, strlen(time_msg), 0);
	printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(time_msg));


	printf("Closing connection...\n");
	CLOSESOCKET(socket_client);

	return 0;
}
