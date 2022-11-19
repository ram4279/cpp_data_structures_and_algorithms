#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char** argv)
{
	if (argc < 2) {
		printf("eg: %s 10.10.10.0/16\n", argv[0]);
		return 1;
	}

	char* endptr;
	char ip_addr[18] = {0};
	char mask_str[2] = {0};

	char* ptr = argv[1];
	char* ip_ptr = ip_addr;
	char* mask_ptr = mask_str;

	while(*ptr && *ptr != '/') {
		*ip_ptr++ = *ptr++;
	}
	*ip_ptr = 0;

	ptr++;
	while(*ptr) {
		*mask_ptr++ = *ptr++;
	}
	*mask_ptr = 0;
	
	printf("ipaddres = %s\n", ip_addr);
	printf("number of bits set = %s\n", mask_str);

	/* Convert the mask to integer */
	uint32_t bits_set = (uint32_t)strtol(mask_str, &endptr, 10);
	uint32_t bits_not_set = 32 - bits_set; /* bits not set are aka host part bits */

	/*by shifting 0xffffffff with bits that are not set ie 00000000 part we can get the mask */
	uint32_t mask = 0xffffffff << bits_not_set;


	char dotted_mask[18] = {0};
	sprintf(dotted_mask, "%d.%d.%d.%d", (mask>>24) & 0xff, (mask >> 16) & 0xff, (mask >> 8) & 0xff, mask & 0xff);
	/*
	 * Why 0xff is used, 0xf is only 1111(4 bits) in binary, whereas 0xff is 11111111(8bits set)
	 */
	printf("Subnet mask dotted mask = %s\n", dotted_mask);

	short unsigned int  a, b, c, d, bits;
    if (sscanf(argv[1], "%hu.%hu.%hu.%hu/%hu", &a, &b, &c, &d, &bits) < 5) {
        return -1; /* didn't convert enough of CIDR */
    }	

	uint32_t ip_addr_in_int = (a << 24UL) | (b << 16UL) | (c << 8UL) | d;

	char ip_buffer[18] = {0};
	snprintf(ip_buffer, sizeof(ip_buffer), "%d.%d.%d.%d", 
											(ip_addr_in_int >> 24UL) & 0xff,
											(ip_addr_in_int >> 16UL) & 0xff,
											(ip_addr_in_int >> 8UL) & 0xff,
											(ip_addr_in_int & 0xff));

	printf("first ip address in integer format = %d\n", ip_addr_in_int);
	printf("first ip address in string  format = %s\n", ip_buffer);

	uint32_t last_ip_addr_int  = ip_addr_in_int + (1 << bits_not_set) - 1;
	snprintf(ip_buffer, sizeof(ip_buffer), "%d.%d.%d.%d", (last_ip_addr_int >> 24UL) & 0xff,
													(last_ip_addr_int >> 16UL) & 0xff,
													(last_ip_addr_int >> 8UL) & 0xff,
													(last_ip_addr_int & 0xff));


	printf("last ip address in integer format = %d\n", last_ip_addr_int);
	printf("last ip address in string format = %s\n", ip_buffer);

	printf("ip address in range %d\n", last_ip_addr_int - ip_addr_in_int + 1);

	return 0;
}
