#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

typedef enum ops
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NOP
} ops_t;

typedef int(*arith_t) (int, int);

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divi(int a, int b) { assert(b != 0); return a / b; }
int mod(int a, int b) { return a % b; }

int calculate(ops_t operation, int a, int b)
{
    static const arith_t arith_t_array[] = { add, sub, mul, divi, mod};

    if (operation >= NOP || operation < 0) {
        errno = EINVAL;
        return 0;
    }
    return arith_t_array[operation] (a,b);
}

int main()
{
    int res = 0;
    res = calculate(ADD, 1, 1);
    printf("ADD = %d\n", res);
    res = calculate(SUB, 1, 1);
    printf("SUB = %d\n", res);
    res = calculate(MUL, 2, 3);
    printf("MUL = %d\n", res);
    res = calculate(DIV, 1, 1);
    printf("DIV = %d\n", res);
    res = calculate(MOD, 5, 3);
    printf("MOD = %d\n", res);
   
    return 0;
}
