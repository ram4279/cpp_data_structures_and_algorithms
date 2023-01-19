#include <stdio.h>

int main(int argc, char const *argv[])
{
    static struct static_struct
    {
        int i_num;
        float f_num;
        char *c_ptr;
    } g_static_struct_t;

    static union
    {
        int i;
        float f;
        char c;
    } data;

    printf("Integer value: %d\n", data.i);
    printf("Float value: %f\n", data.f);
    printf("Character value: %c\n", data.c);

    printf("g_static_struct_t.i_num = %d\n", g_static_struct_t.i_num);
    printf("g_static_struct_t.f_num = %f\n", g_static_struct_t.f_num);
    printf("g_static_struct_t.c_ptr = %s\n", g_static_struct_t.c_ptr);
    return 0;
}
