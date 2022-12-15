#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_DATA_SIZE 100

typedef struct tlv {
    int type;
    int length;
    char value[MAX_DATA_SIZE];
} tlv_t;

void encode_tlv(tlv_t tlv, char* buffer)
{
    memcpy(buffer, &tlv.type, sizeof(tlv.type));
    memcpy(buffer+sizeof(tlv.type), &tlv.length, sizeof(tlv.length));
    memcpy(buffer+sizeof(tlv.type)+sizeof(tlv.length), tlv.value, tlv.length);
}

void decode_tlv(char* buffer, tlv_t* tlv)
{
    memcpy(&tlv->type, buffer, sizeof(tlv->type));
    memcpy(&tlv->length, buffer + sizeof(tlv->type), sizeof(tlv->length));
    memcpy(tlv->value, buffer + sizeof(tlv->length) + sizeof(tlv->type), 
            tlv->length);
}
int main()
{
    tlv_t m_tlv = {4, 10, "0987654321"};
    char* buffer = malloc(sizeof(tlv_t));
    encode_tlv(m_tlv, buffer);

    printf("Encoded TLV: ");
    for (int i = 0; i < (8 + m_tlv.length); i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");

    tlv_t decoded_tlv;
    decode_tlv(buffer, &decoded_tlv);
    printf("Decoded TLV: TYPE = %d LEN = %d VALUE = %s\n", 
            decoded_tlv.type, decoded_tlv.length, decoded_tlv.value);

    printf("\n");
}