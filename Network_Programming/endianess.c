#include <stdio.h>
#include <stdint.h>

void print_endianess()
{
    unsigned int val = 0xDEADBEEF;
    char *ptr = (char *)&val;
    if (*ptr == 0xDE) {
        printf("Big Endian\n");
    } else {
        printf("Little Endian\n");
    }
}

void convert_endianess(unsigned int val)
{
    unsigned int res = 0;
    printf("Before conversion ");
    printf("%x\n", val);
    res |= (val >> 24UL) & 0XFF;
    res |= (val << 8UL) & 0XFF0000;
    res |= (val >> 8UL) & 0XFF00;
    res |= (val << 24UL) & 0xff000000;
    printf("After conversion ");
    printf("%x\n", res);
}

#define SWAP_INT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))


void swap_endianess(unsigned int val)
{
    unsigned int res = 0;
    printf("Before conversion ");
    printf("%x\n", val);

    res |= (val /*& 0x000000FF*/) << 24;
    res |= (val & 0x0000FF00) << 8;
    res |= (val & 0x00FF0000) >> 8;
    res |= (val /*& 0xFF000000*/) >> 24;

    printf("After conversion ");
    printf("%x\n", res);
}

/**
 * 
    higher memory
       ----->
 +----+----+----+----+
 |0x01|0x00|0x00|0x00|
 +----+----+----+----+
 ^
 |
&data
*/
void print_endianess_union()
{
    union data
    {
        int var_x;
        char x;
    } data;

    data.var_x = 1;
    if (data.x == 1) {
        printf("Little indian\n");
    } else {
        printf("Big endian\n");
    }
    
}

void simple_convert_endianess(unsigned int val)
{
    printf("Before conversion ");
    printf("%x\n", val);
    uint32_t byte0, byte1, byte2, byte3;
    byte0 = val & 0xff;
    byte1 = (val >> 8) & 0xff;
    byte2 = (val >> 16) & 0xff;
    byte3 = (val >> 24) & 0xff;
    uint32_t res = (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3;
    printf("Before conversion ");
    printf("%x\n", res);
}

int main(int argc, char const *argv[])
{
    print_endianess();
    simple_convert_endianess(0xDEADBEEF);
    print_endianess_union();
    swap_endianess(0xDEADBEEF);
    return 0;
}
