#include <stdio.h>
#include <stdlib.h>

enum status
{
    Q_OK,
    Q_FULL,
    Q_EMPTY,
    Q_FAIL,
    Q_UNKNOWN
};

typedef struct queue
{
    int* arr;
    int len;
    int __size;
    int start;
    int end;
} queue_t;

int q_size(queue_t *q)
{
    return q->len;
}

int q_empty(queue_t *q)
{
    return q->len == 0;
}

int init_que(queue_t *q, size_t size)
{
   q->arr = malloc(sizeof(int) * size);
   if (!q->arr)
   {
      return Q_FAIL; 
   }
   q->len = 0;
   q->start = q->end = -1;
   q->__size = size;
   return Q_OK;
}

void free_que(queue_t *q)
{
    free(q->arr);
}

int q_front(queue_t *q, int* val)
{
    if (!q_empty(q))
    {
        *val = q->arr[q->start];
        return Q_OK;
    }
    val = NULL;
    return Q_EMPTY;
}

int enque(queue_t *q, int val)
{
    if (q_size(q) >= q->__size)
    {
        printf("Queue is full");
        return Q_FULL;
    }
    if (q_size(q) == 0)
    {
       q->start = 0;
       q->end   = 0;
    }
    else
    {
        q->end = (q->end + 1) % q->__size;
    }
    q->arr[q->end] = val;
    q->len++;
    return Q_OK;
}

void print_q(queue_t *q)
{
    for (int i = q->start; i <= q->end; i++)
    {
        printf("%d - ", q->arr[i]);
    }
    printf("\n");
}

int deque(queue_t *q)
{
    if (q_empty(q))
    {
        return Q_EMPTY;
    }
    if (q_size(q) == 1)
    {
        q->start = q->end = -1;
        q->len   = 0;
    }
    else
    {
        q->start = (q->start + 1) % q->__size;
        q->len--;
    }
    return Q_OK;
}

int main()
{
    queue_t *q = malloc(sizeof(q));
    init_que(q, 10);
    for (int i = 0; i < 11; i++)
    {
       enque(q, i+1); 
    }
    print_q(q);
    free_que(q);
    return 0;
}
