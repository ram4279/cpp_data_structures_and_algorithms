#include <stdio.h>


/* 
Compile with the flag to do packing
gcc .\bit_fields_eg.c -o .\bit_fields_eg.exe -mno-ms-bitfields
*/
#pragma pack(1)
typedef struct date_t
{
    unsigned int m: 4;
    unsigned int d: 5;
    unsigned int y;
}date_t;

int main(int argc, char const *argv[])
{
    printf("%d\n", sizeof(date_t));
    return 0;
}

