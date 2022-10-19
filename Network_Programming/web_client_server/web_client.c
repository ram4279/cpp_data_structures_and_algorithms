#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <unistd.h>

#define TIMEOUT 5

void send_request(int sfd, char* hostname, char* port, char* path)
{
	char buffer[2048] = {0};
	sprintf(buffer, "GET /%s HTTP/1.1\r\n", path);
	sprintf(buffer + strlen(buffer), "Host: %s:%s\r\n", hostname, port);
	sprintf(buffer + strlen(buffer), "Connection: close\r\n");
	sprintf(buffer + strlen(buffer), "User-Agent: honpwc web_get 1.0\r\n");
	sprintf(buffer + strlen(buffer), "\r\n");

	send(sfd, buffer, strlen(buffer), 0);
}

/* https://example.com:443/resource_1 */
int parse_url(char* url, char** host, char **port, char **path)
{
    char *p = strstr(url, "://");

	char *protocol = NULL;
	if (p) {
		protocol = url;
		*p = 0;
		p += 3; /*p wil point to starting of str :// so skip it */
	} else {
		p = url;
	}


    if (strcmp(protocol, "http")) {
        printf("Only http is supported for now exiting..\n");
        exit(1); 
    }

	*host = p;
	while (*p && *p != ':' && *p != '/' && *p != '#') {
		++p;
	}

	/* If port is give use it else set 80 as default */
	if (*p == ':') {
		*p++ = 0;
		*port = p;
	} else {	
		*port = "80";
	}


	while (*p && *p != '/' && *p != '#') {
		++p;
	}
	*path = p;
	if (*p == '/') {
		*path = p + 1;
	}
	*p = 0;

	while (*p && *p != '#') {
		++p;
	}
	if (*p == '#') {
		*p = 0;
	}

    return 0;
}

int main(int argc, char** argv)
{
    if (argc < 1) {
        printf("Missing arguments\n");
        printf("example:\n webclient http://example.com/page\n");
        exit(1);
    }

    char *protocol = NULL;
    char *host = NULL;
    char *port = NULL;
    char *path = NULL;

    if (parse_url(argv[1], &host, &port, &path)) {
        printf("Parsing url failed\n");
        exit(1);
    }
    
    printf("host: %s\n", host);
    printf("port: %s\n", port);
    printf("path: %s\n", path);

	
	struct addrinfo hints = {0};
	hints.ai_socktype = SOCK_STREAM;
	
	struct addrinfo *server_info = NULL;
	if (getaddrinfo(host, port, &hints, &server_info)) {
		perror("getaddrinfo failed\n");
		exit(1);
	}
	
	int skt = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if (skt < 0) {
		perror("socket creation failed\n");
		exit(1);
	}

	if (connect(skt, server_info->ai_addr, server_info->ai_addrlen)) {
		perror("connect failed\n");
		exit(1);
	}

	freeaddrinfo(server_info);

	send_request(skt, host, port, path);

	const clock_t start_time = clock();

	#define RESPONSE_SIZE 8192
	char response[8192] = {0};
	char* p = response, *q;
	char *end = response + RESPONSE_SIZE;
	char *body = NULL;

	enum {length, chunked, connection};
	int encoding = 0;
	int remaining = 0;

	while(1) {
		if ((clock() - start_time) / CLOCKS_PER_SEC > TIMEOUT) {
			perror("Timeout for receving data\n");
			exit(1);
		}

		if (p == end) {
			printf("out of buffer\n");
			exit(1);
		}

		fd_set reads;
		FD_ZERO(&reads);
		FD_SET(skt, &reads);

		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 200000;
		
		if (select(skt + 1, &reads, 0, 0, &timeout) < 0) {
			perror("Select failed\n");
			return 1;
		}

		if (FD_ISSET(skt, &reads)) {
			int bytes_recvd = recv(skt, p, end - p, 0);
			if (bytes_recvd < 1) {
				perror("recv failed\n");
				exit(1);
			}

			printf("Received (%d bytes)\n '%.*s'", bytes_recvd, bytes_recvd, p);
			p += bytes_recvd;
			*p = 0;
		}

	}

	close(skt);
    return 0;
}
