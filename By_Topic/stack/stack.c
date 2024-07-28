#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


enum stack_status
{
    STK_OK,
    STK_FAIL,
    STK_FULL,
    STK_EMPTY,
};

typedef struct stack
{
    int *arr;
    int __size;
    int len;
    int top;
} stck_t;


int init_stack(stck_t *stk, size_t size)
{
    stk->arr = malloc(sizeof(int) * size);
    if (!stk->arr)
    {
        return STK_FAIL;
    }
    stk->__size = size;
    stk->len = 0;
    stk->top = -1;
    return STK_OK;
}

int free_stack(stck_t *stk)
{
    free(stk->arr);
    return STK_OK;
}

bool stack_empty(stck_t *stk)
{
    return stk->len == 0;
}

int push(stck_t *stk, int val)
{
    if (stk->len >= stk->__size)
    {
        return STK_FULL;
    }
    else
    {
        stk->top += 1;
        stk->arr[stk->top] = val;
        stk->len += 1;
        return STK_OK;
    }
}

int pop(stck_t *stk)
{
    if (stack_empty(stk))
    {
        return STK_EMPTY;
    }
    else
    {
        stk->top--;
        stk->len--;
        return STK_OK;
    }
}

int top(stck_t *stk, int *val)
{
    if (stack_empty(stk))
    {
        return STK_EMPTY;
    }
    else
    {
        *val = stk->arr[stk->top];
        return STK_OK;
    }
}

int main()
{
    stck_t *stk = malloc(sizeof(stck_t));
    init_stack(stk, 5);
    for (int i = 0; i < 10; i++)
    {
        push(stk, i);        
    }
    free_stack(stk);
    return 0;
}
