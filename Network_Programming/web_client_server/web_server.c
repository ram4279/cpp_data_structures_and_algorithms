#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_REQUEST_SIZE 2047
#define BACKLOG			 10

struct client_info {
	socklen_t address_length;
	struct sockaddr_storage address;
	int socket;
	char request[MAX_REQUEST_SIZE];
	int received;
	struct client_info* next;
};

struct client_info *clients = NULL;

char* get_content_type(char* url)
{
	const char* dot = strchr(url, '.');
	if (dot) {
		if (strcmp(dot, "html") == 0) return "text/html";
		if (strcmp(dot, "htm") == 0) return "text/html";
		if (strcmp(dot, "css") == 0) return "text/css";
		if (strcmp(dot, "gif") == 0) return "text/gif";
		if (strcmp(dot, ".ico") == 0) return "image/x-icon";
		if (strcmp(dot, ".jpeg") == 0) return "image/jpeg";
		if (strcmp(dot, ".jpg") == 0) return "image/jpeg";
		if (strcmp(dot, ".js") == 0) return "application/javascript";
		if (strcmp(dot, ".json") == 0) return "application/json";
		if (strcmp(dot, ".png") == 0) return "image/png";
		if (strcmp(dot, ".pdf") == 0) return "application/pdf";
		if (strcmp(dot, ".svg") == 0) return "image/svg+xml";
		if (strcmp(dot, ".txt") == 0) return "text/plain";
	}
	return "application/octet-stream";
}

int create_socket(char* host, char* port)
{
	struct addrinfo hints = {0};
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;	
	hints.ai_flags  = AI_PASSIVE;
	struct addrinfo *serv_info = NULL;

	if (getaddrinfo(host, port, &hints, &serv_info)) {
		perror("getaddrinfo failed\n");
		return -1;
	}

	int sk_fd = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);
	if (sk_fd < -1) {
		perror("Socket creation failed\n");
		return -1;
	}

	const int enable = 1;
	setsockopt(sk_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	int ret = 0;
	ret = bind(sk_fd, serv_info->ai_addr, serv_info->ai_addrlen);
	if (ret < 0) {
		perror("bind failed\n");
		return ret;
	}

	ret = listen(sk_fd, BACKLOG);
	if (ret < 0) {
		perror("listen failed");
		return ret;
	}
	return sk_fd;
}

struct client_info* get_client(int socket)
{
	struct client_info *curr = clients;
	while (curr) {
		if (curr->socket == socket) {
			return curr;
		}
	}

	struct client_info* new_client_info = calloc(1, sizeof(struct client_info));

	if (!new_client_info) {
		perror("memory allocation for new_client_info failed");
		exit(1);
	}
	new_client_info->address_length = sizeof(new_client_info->address);
	new_client_info->next = clients; /* Add to head */
	clients = new_client_info;
	return new_client_info;
}

void drop_client(struct client_info* client)
{
	close(client->socket);
	struct client_info **ptr = &clients;
	while (*ptr) {
		if (*ptr == client) {
			*ptr = client->next; /* overwriting the ptr address with its next address */
			free(client);
			return;
		}
		ptr = &(*ptr)->next;
	}

	perror("Client not found\n");
	exit(1);
}


char* get_client_address(struct client_info *ci)
{
	static char ipaddr[100] = {0};
	getnameinfo((struct sockaddr*)&ci->address, ci->address_length, ipaddr, sizeof(ipaddr), 0, 0, NI_NUMERICHOST);
	return ipaddr;
}

fd_set wait_on_clients(int server)
{
	fd_set reads;
	FD_ZERO(&reads);

	FD_SET(server, &reads);
	int max_socket = server;

	struct client_info *ci_ptr = clients;
	while (ci_ptr) {
		FD_SET(ci_ptr->socket, &reads);
		if (ci_ptr->socket > max_socket) {
			max_socket = ci_ptr->socket;
		}
		ci_ptr = ci_ptr->next;
	}

	if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
		perror("select failed\n");
		exit(1);
	}

	return reads;
}

void send_400(struct client_info *ci)
{
	const char* msg_400 = "HTTP/1.1 400 Bad Reuest\r\n"
						  "Connection: close\r\n"
						  "Content-Length: 11\r\n\r\nBad Request";
	send(ci->socket, msg_400, strlen(msg_400), 0);
	drop_client(ci);
	return;
}

void send_404(struct client_info *client)
{
	const char *c404 = "HTTP/1.1 404 Not Found\r\n"
						"Connection: close\r\n"
						"Content-Length: 9\r\n\r\nNot Found";
	send(client->socket, c404, strlen(c404), 0);
	drop_client(client);
}

void serve_resource(struct client_info *client, const char *path)
{
	printf("serve_resource %s %s\n", get_client_address(client), path);
	if (strcmp(path, "/") == 0) {
		path = "/index.html";
	}

	if (strlen(path) > 100) {
		send_400(client);
		return;
	}

	if (strstr(path, "..")) {
		send_404(client);
		return;
	}

	char full_path[128] = {0};
	sprintf(full_path, "public%s", path);

	FILE *fp = fopen(full_path, "rb");
	if (!fp) {
		send_404(client);
		return;
	}

	/* Get the size of the file */
	fseek(fp, 0L, SEEK_END);
	size_t content_length = ftell(fp);
	rewind(fp);

	/* Get the content type of the file */
	const char* content_type = get_content_type(full_path);
	
	char buffer[1024] = {0};

	/* Send headers */
	sprintf(buffer, "HTTP/1.1 200 OK\r\n");
	send(client->socket, buffer, strlen(buffer), 0);

	sprintf(buffer, "Connection: close\r\n");
	send(client->socket, buffer, strlen(buffer), 0);

	sprintf(buffer, "Content-Length: %lu\r\n", content_length);
	send(client->socket, buffer, strlen(buffer), 0);

	sprintf(buffer, "Content-Type: %s\r\n", content_type);
	send(client->socket, buffer, strlen(buffer), 0);

	sprintf(buffer, "\r\n");
	send(client->socket, buffer, strlen(buffer), 0);

	/* Send actual data/file */
	int r = fread(buffer, 1, 1024, fp);
	while (r) {
		send(client->socket, buffer, r, 0);
		r = fread(buffer, 1, 1024, fp);
	}
	fclose(fp);
	drop_client(client);

}

int main()
{
	printf("Starting server....");
	int server_sfd = create_socket("localhost", "9999");
	while (1) {
		fd_set reads;
		reads = wait_on_clients(server_sfd);
		if (FD_ISSET(server_sfd, &reads)) {
			//New connection detected
			struct client_info* client = get_client(-1);
			client->socket = accept(server_sfd, (struct sockaddr*)&(client->address), &(client->address_length));
			if (client->socket < 0) {
				perror("Not a valid socket\n");
				return 1;
			}
			printf("New connection from %s.\n", get_client_address(client));
		}
		struct client_info* client = clients;
		while (client) {
			struct client_info* next = client->next;
			if (FD_ISSET(client->socket, &reads)) {
				if (MAX_REQUEST_SIZE == client->received) {
					send_400(client);
					client = next;
					continue;
				}
				int r = recv(client->socket, client->request + client->received, MAX_REQUEST_SIZE - client->received, 0);
				if (r < 1) {
					printf("Unexpected disconnect from %s.\n",
					get_client_address(client));
					drop_client(client);
				} else {
					client->received += r;
					client->request[client->received] = 0;
					char *q = strstr(client->request, "\r\n\r\n");
					if (q) {
						*q = 0;
						if (strncmp("GET /", client->request, 5)) {
							send_400(client);
						} else {
							char *path = client->request + 4;
							char *end_path = strstr(path, " ");
							if (!end_path) {
								send_400(client);
							} else {
								*end_path = 0;
								serve_resource(client, path);
							}
						}
					}
				}
			}
			client = next;
		}
	}
	close(server_sfd);
	return 0;
}
