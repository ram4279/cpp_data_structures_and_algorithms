#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum length of the value field in the TLV triplet
#define MAX_VALUE_LENGTH 100

// Define a struct to represent a TLV triplet
typedef struct
{
    uint8_t type;
    uint8_t length;
    char value[MAX_VALUE_LENGTH];
} tlv_t;

// Encode a TLV triplet
void encode_tlv(tlv_t tlv, char* buffer)
{
    // Encode the type and length fields as a two-byte integer
    unsigned short type_length = (tlv.type << 8) | tlv.length;

    // Copy the encoded type and length fields to the buffer
    memcpy(buffer, &type_length, sizeof(type_length));

    // Copy the value field to the buffer
    memcpy(buffer + sizeof(type_length), tlv.value, tlv.length);
}

// Decode a TLV triplet
void decode_tlv(const char* buffer, tlv_t* tlv)
{
    // Read the encoded type and length fields from the buffer
    unsigned short type_length;
    memcpy(&type_length, buffer, sizeof(type_length));

    // Decode the type and length fields
    tlv->type = type_length >> 8;
    tlv->length = type_length & 0xFF;

    // Read the value field from the buffer
    memcpy(tlv->value, buffer + sizeof(type_length), tlv->length);
}

int main()
{
    // Create a TLV triplet
    tlv_t tlv = {4, 10, "0987654321"};

    // Allocate a buffer for the encoded TLV data
    char* buffer = (char*)malloc((2 + tlv.length) * sizeof(char));

    // Encode the TLV data
    encode_tlv(tlv, buffer);

    // Print the encoded TLV data
    printf("Encoded TLV data: ");
    for (int i = 0; i < 2 + tlv.length; i++)
        printf("%02X ", buffer[i]);
    printf("\n");

    // Decode the TLV data
    tlv_t decoded_tlv;
    decode_tlv(buffer, &decoded_tlv);

    // Print the decoded TLV data
    printf("Decoded TLV data: type=%d, length=%d, value=%s\n", decoded_tlv.type, decoded_tlv.length, decoded_tlv.value);

    // Free the allocated buffer
    free(buffer);

    return 0;
}
