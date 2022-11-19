#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, const char** argv)
{
	if (argc != 2) {
		printf("How to run %s <number>\n", argv[0]);
		printf("eg %s 10\n", argv[0]);
		exit(1);
	}

	int some_number = atoi(argv[1]);
	char ip_buffer[32] = {0};
	inet_ntop(AF_INET, &some_number, ip_buffer, sizeof(ip_buffer));
	printf("%s\n", ip_buffer);
	return 0;
}
