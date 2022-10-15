#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DNS_SERVER_IP "8.8.8.8"
#define DNS_PORT_NO   "53"
const unsigned char *print_name(const unsigned char *msg,const unsigned char *p, const unsigned char *end)
{
	if (p + 2 > end) {
		fprintf(stderr, "End of message.\n"); 
		exit(1);
	}
	if ((*p & 0xC0) == 0xC0) {
		const int k = ((*p & 0x3F) << 8) + p[1];
		p += 2;
		printf(" (pointer %d) ", k);
		print_name(msg, msg+k, end);
		return p;
	} else {
		const int len = *p++;
		if (p + len + 1 > end) {
			fprintf(stderr, "End of message.\n"); 
			exit(1);
		}
		printf("%.*s", len, p);
		p += len;
		if (*p) {
			printf(".");
			return print_name(msg, p, end);
		} else {
			return p+1;
		}
	}
}

void print_dns_message(const char* message, int msg_length)
{
   if (msg_length < 12) {
        perror("Message is invalid\n");
        exit(1);
   }
   const unsigned char *msg = (const unsigned char *)message;

#if RAW_PRINT 
   int i;
   for (i = 0; i < msg_length; ++i) {
       unsigned char r = msg[i];
       printf("%02d: %02X %03d '%c'\n", i, r, r, r);
   }
   printf("\n");
#endif

    printf("ID = %0X %0X\n", msg[0], msg[1]);

    /*QR TYPE*/
    int qr = (msg[2]  & 0x80) >> 7; /*First bit 10000000*/
    printf("QR = %d %s\n", qr, qr ? "response" : "query");

    /*OP Code*/
    int opcode = (msg[2] & 0x78) >> 3; /*next 4 bits 0111 1000 but only 3 are used */
    printf("OPCODE = %d ", opcode);
    switch (opcode) {
        case 0: printf("standard\n"); break;
        case 1: printf("reverse\n"); break;
        case 2: printf("status\n"); break;
        default: printf("Unknown opcode"); break;
    }
    
    /*Authorative answer AA */
    int aa = (msg[2] & 0x04) >> 2;
    printf("AA = %d %s\n", aa, aa ? "authortative": "");
    
    /* Truncated*/
    int tc = (msg[2] & 0x02) >> 1;
    printf("TC = %d %s\n", tc, tc ? "truncated": "");

    /* Recursion desired */
    int rd = (msg[2] & 0x01);
    printf("RG = %d %s\n", rd, rd ? "recursion desired": "");

    if (qr) {
        /*reason code*/
        int rcode = (msg[3] & 0x8);
        printf("RCODE = %d ",rcode);
        switch (rcode) {
            case 0: printf("success\n"); break;
            case 1: printf("format error\n"); break;
            case 2: printf("server failure\n"); break;
            case 3: printf("name error\n"); break;
            case 4: printf("not implemented\n"); break;
            case 5: printf("refused\n"); break;
            default: printf("Unknown rcode\n"); break;
        }
        if (rcode != 0) return;
    }

	int qdcount = (msg[4] << 8) + msg[5];
	int ancount = (msg[6] << 8) + msg[7];
	int nscount = (msg[8] << 8) + msg[9];
	int arcount = (msg[10] << 8) + msg[11];
	printf("QDCOUNT = %d\n", qdcount);
	printf("ANCOUNT = %d\n", ancount);
	printf("NSCOUNT = %d\n", nscount);
	printf("ARCOUNT = %d\n", arcount);

	const unsigned char *p = msg + 12; /* SKIP HEADER AS IT IS printed by now */
	const unsigned char *end = msg + msg_length; /* To identify end of message */

	if (qdcount) {
		int i;
		for (i = 0; i < qdcount; i++) {
			if (p >= end) {
				fprintf(stdin, "End of message\n");
				exit(1);
			}
			printf("Query %2d\n", i + 1); /* Query: 1, 2, 3,...*/
			printf("	name: ");
			p = print_name(msg, p, end);
			printf("\n");

			if (p + 4 > end) {
				/*if no type and qclasss */
				fprintf(stderr, "End of message.\n"); 
				exit(1);
			}

			const int type = (p[0] << 8) + p[1]; /*When two bytes are to be added use this logic */
			printf("	type: %d\n", type);
			p+=2; /* JUMP 2 bytes p is char pointer so it will jump two bytes */


			const int qclass = (p[0] << 8) + p[1]; /*When two bytes are to be added use this logic */
			printf("	qclass: %d\n", qclass);
			p+=2;
		}
	}

	if (ancount || nscount || arcount) {
		int i;
		for (i = 0; i < ancount + nscount + arcount; i++) {
			if (p >= end) {
				printf("End of message\n");
				exit(1);
			}

			printf("Answer: %2d\n", i+1);
			printf("	name: ");
			p = print_name(msg, p, end);
			printf("\n");
			
			if (p+10 > end) {
				printf(" End of message\n");
				exit(1);
			}

			const int type = (p[0] << 8) + p[1];
			printf(" type: %d\n", type);
			p += 2;
			const int qclass = (p[0] << 8) + p[1];
			printf(" class: %d\n", qclass);
			p += 2;
			
			/* Time to live */
			unsigned int ttl = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
			printf(" ttl: %u\n", ttl);
			p += 4;

			const int rdlen = (p[0] << 8) + p[1];
			printf(" data length: %d\n", rdlen);
			p += 2;

			if (p + rdlen > end) {
				fprintf(stderr, "End of message.\n"); 
				exit(1);
			}
			
			/* Printing the actual ip address or result */
			if (rdlen == 4 && type == 1) {
				/*IPV4 record aka A record*/
				printf("Address ");
				printf("%d.%d.%d.%d\n", p[0], p[1], p[2], p[3]);
			} else if (rdlen > 3 && type == 15) {
				/* MX record aka mail service record */
				const int preference = (p[0] << 8) + p[1];
				printf(" pref: %d\n", preference);
				printf("MX: ");
				print_name(msg, p+2, end); 
				printf("\n");
			} else if (rdlen == 16 /*ipv6 is 128 bits*/ && type == 28) {
				printf("Address ");
				int j;
				for (j = 0; j < rdlen; j+=2) {
					printf("%02x%02x", p[j], p[j+1]);
					if (j + 2 < rdlen)
						printf(":");
				}
				printf("\n");
			} else if (type == 16) { /* TXT Record */
				printf("TXT: '%.*s'\n", rdlen-1, p+1);
			} else if (type == 5) { /* CNAME Record */
				printf("CNAME: ");
				print_name(msg, p, end);
				printf("\n");
			}
			p += rdlen;
		}
	}
	printf("\n");
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Usage: %s <url> <type of record>\n", argv[0]);
        printf("Example: %s google.com a\n", argv[0]);
        exit(1);
    }

    unsigned char query_type = 0;

    if (!strcmp(argv[2], "a")) {
        query_type = 1;
    } else if (!strcmp(argv[2], "mx")) {
        query_type = 15;
    } else if (!strcmp(argv[2], "txt")) {
        query_type = 16;
    } else if (!strcmp(argv[2], "aaaa")) {
        query_type = 28;
    } else if (!strcmp(argv[2], "any")) {
        query_type = 255;
    } else {
        perror("Invalid record\n");
        perror("Valid record types are a, aaaa, txt, mx, any\n");
        exit(1);
    }
    
    struct addrinfo hints = {0};
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *serv_details = NULL;
    if (getaddrinfo(DNS_SERVER_IP, DNS_PORT_NO, &hints, &serv_details)) {
        perror("getaddrinfo failed\n");
        exit(1);
    }

    int serv_sock = socket(serv_details->ai_family, serv_details->ai_socktype, serv_details->ai_protocol);
    if (serv_sock < 0) {
        perror("socket creation failed");
        exit(1);
    }

    char dns_query[1024] = { 0xAB, 0xCD, /* ID */
                             0x01, 0x00, /* Set recursion */
                             0x00, 0x01, /* QDCOUNT */
                             0x00, 0x00, /* ANCOUNT */
                             0x00, 0x00, /* NSCOUNT */
                             0x00, 0x00  /* ARCOUNT */
                           };

    /* Now encode user entered ip address*/
    char *ptr = dns_query + 12; /* 12 bytes are for header */
    char *h_ptr = argv[1];

    while(*h_ptr) {
        char* len = ptr;
        ptr++;
        
        if (h_ptr != argv[1]) 
            ++h_ptr;

        while (*h_ptr && *h_ptr != '.') {
            /*Copy each character of host name to dns_query array */
            *ptr++ = *h_ptr++;
        }

        /*Calculate length of current part of hostname "google" -> 6 and put it in location len*/
        *len = ptr - len - 1;
    }

    *ptr++ = 0; /*Finish name section */

    *ptr++ = 0x00; *ptr++ = query_type; /* QTYPE = a, aaaa, txt */
    *ptr++ = 0x00; *ptr++ = 0x01; /* QCLASS = Internet 1 */
    
    const int final_length_of_query = ptr - dns_query;
    ssize_t bytes_sent = sendto(serv_sock, dns_query, final_length_of_query, 0,
                                serv_details->ai_addr, serv_details->ai_addrlen);
    printf("Sent %ld bytes\n", bytes_sent);

    char read[1024] = {0};
    ssize_t bytes_recv = recvfrom(serv_sock, read, sizeof(read), 0, 0, 0);
    printf("Bytes received = %ld\n", bytes_recv);

	print_dns_message(read, bytes_recv);

    freeaddrinfo(serv_details);
    close(serv_sock);
    return 0;
}
