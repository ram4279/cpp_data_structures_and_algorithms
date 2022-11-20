/* This code mostly wont work because our ISP block port 25
 * Instead use secured way mentioned in
 * https://curl.se/libcurl/c/smtp-tls.html
 */

#if 0
Client server interaction in SMTP

S: 220 mail.example.com SMTP server ready
C: HELO mail.example.net
S: 250 Hello mail.example.net [192.0.2.67]
C: MAIL FROM:<alice@example.net>
S: 250 OK
C: RCPT TO:<bob@example.com>
S: 250 Accepted
C: DATA
S: 354 Enter message, ending with "." on a line by itself
C: Subject: Re: The Cake
C: Date: Fri, 03 May 2019 02:31:20 +0000
C:
C: Do NOT forget to bring the cake!
C: .
S: 250 OK
C: QUIT
S: 221 closing connection
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAXINPUT 512
#define MAXRESPONSE 1024

void get_input(const char* prompt, char* buffer)
{
	printf("%s", prompt);
	buffer[0] = 0;
	fgets(buffer, MAXINPUT, stdin);
	const int read = strlen(buffer);
	if (read > 0) {
		/* Remove newline */
		buffer[read-1] = 0;
	}
}

void send_format(int socket, const char* text, ...)
{
	char buffer[1024] = {0};
	va_list args;
	va_start(args, text);
	vsprintf(buffer, text, args);
	va_end(args);
	
	send(socket, buffer, strlen(buffer), 0);

}

int parse_response(const char* response)
{
	const char* k_ptr = response;
	/* There is no response */
	if (!k_ptr[0] || !k_ptr[1] || !k_ptr[2]) {
		return 0;
	}
	
	for (; k_ptr[3]; ++k_ptr) {
		if (k_ptr == response || k_ptr[-1] == '\n') {
			/* k_ptr == response is for single line resonse */
			if (isdigit(k_ptr[0]) && isdigit(k_ptr[1]) && isdigit(k_ptr[2])) {
				if (k_ptr[3] != '-') {
					if (strstr(k_ptr, "\r\n")) {
						return strtol(k_ptr, 0, 10);
					}
				}
			}
		}
	}

	return 0;
}


void wait_on_response(int socket, int expecting)
{
	char response[MAXRESPONSE + 1];
	char *p = response;
	char *end = response + MAXRESPONSE;
	int resp_code = 0;

	do {
		int bytes_received = recv(socket, p, end-p, 0);
		if (bytes_received < 1) {
			perror("Connection dropped\n");
			exit(1);
		}

		p += bytes_received;
		*p = 0;
		if (p == end) {
			perror("response too large\n");
			printf("response: %s\n", response);
			exit(1);
		}

		resp_code = parse_response(response);

	} while (resp_code == 0);
}

int connect_to_host(const char* mail_server, const char* port)
{
	struct addrinfo hints = {0};
	struct addrinfo *server_addr = NULL;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(mail_server, port, &hints, &server_addr)) {
		perror("getaddrinfo failed\n");
		exit(1);
	}

	printf("Remote address is: ");
	char address_buffer[128] = {0};
	char serive_buffer[12] = {0};
	
	getnameinfo(server_addr->ai_addr, server_addr->ai_addrlen,
				address_buffer, sizeof(address_buffer), serive_buffer, sizeof(serive_buffer),
				NI_NUMERICHOST);
	
	printf("%s %s\n", address_buffer, serive_buffer);

	int serv_sock = socket(server_addr->ai_family, server_addr->ai_socktype, server_addr->ai_protocol);
	if (serv_sock < 1) {
		printf("Socket creation failed\n");
		exit(1);
	}
		printf("Socket creation success\n");

	if (connect(serv_sock, server_addr->ai_addr, server_addr->ai_addrlen)) {
		perror("Connect failed\n");
		exit(1);
	}
		perror("Connect success\n");
	freeaddrinfo(server_addr);
	printf("Connected \n");
	return serv_sock;

}

int main()
{
	char hostname[MAXINPUT];
	get_input("mail server: ", hostname);
	int serv_sock = connect_to_host(hostname, "25");
	
	wait_on_response(serv_sock, 220);

	send_format(serv_sock, "HELO BY_SAIRAM\r\n");
	wait_on_response(serv_sock, 250);

	char sender[MAXINPUT];
	get_input("from: ", sender);
	send_format(serv_sock, "MAIL FROM:<%s>\r\n", sender);
	wait_on_response(serv_sock, 250);

	char recipient[MAXINPUT];
	get_input("to: ", recipient);
	send_format(serv_sock, "RCPT TO:<%s>\r\n", recipient);
	wait_on_response(serv_sock, 250);


	send_format(serv_sock, "DATA\r\n");
	wait_on_response(serv_sock, 250);

	char subject[MAXINPUT];
	get_input("subject: ", subject);
	send_format(serv_sock, "From:<%s>\r\n", sender);
	send_format(serv_sock, "To:<%s>\r\n", recipient);
	send_format(serv_sock, "Subject:%s\r\n", subject);
	time_t timer;
	time(&timer);
	struct tm *timeinfo;
	timeinfo = gmtime(&timer);

	char date[128] = {0};
	strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S +0000", timeinfo);
	send_format(serv_sock, "Date:%s\r\n", date);

	send_format(serv_sock, "/r/n");
	/* Upto this we have sent email headers, Now send body */
	
	printf("Enter your email text, end with \".\" on a line by itself.\n");
	while (1) {
		char body[MAXINPUT];
		get_input("> ", body);
		send_format(serv_sock, "%s\r\n", body);
		if (strcmp(body, ".") == 0) {
			break;
		}
	}

	wait_on_response(serv_sock, 250);

	send_format(serv_sock, "QUIT\r\n");
	wait_on_response(serv_sock, 221);
	close(serv_sock);
	return 0;
}


