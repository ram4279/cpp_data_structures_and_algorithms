#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

typedef struct cqueue {
    int* arr;
    int size;
    int front;
    int rear;
} MyCircularQueue;

bool init_cqueue(MyCircularQueue *q, size_t size) {
    q->arr = (int *)malloc(sizeof(int) * size);
    if (!q->arr) {
        perror("Memory allocation failed\n");
        return false;
    }
    q->size = size;
    q->front = -1;
    q->rear = -1;
    return true;
}

void free_cqueue(MyCircularQueue *q) {
    if (q->arr) {
        free(q->arr);
    }
    q->size = 0;
    q->front = -1;
    q->rear = -1;
}

bool is_q_empty(MyCircularQueue *q) {
    return q->front == -1 && q->rear == -1;
}

bool is_q_full(MyCircularQueue *q) {
    int next_rear = (q->rear + 1) % q->size;
    return next_rear == q->front;
}

int get_front(MyCircularQueue *q) {
    if (!is_q_empty(q)) {
        return q->arr[q->front];
    }
    return -1;
}

int get_rear(MyCircularQueue *q) {
    if (!is_q_empty(q)) {
        return q->arr[q->rear];
    }
    return -1;
}

bool enqueue(MyCircularQueue *q, int data) {
    if (is_q_full(q)) {
        q->front = (q->front + 1) % q->size; // Move front if queue is full
    }
    q->rear = (q->rear + 1) % q->size;
    q->arr[q->rear] = data;
    if (q->front == -1) {
        q->front = q->rear;
    }
    return true;
}

bool dequeue(MyCircularQueue *q) {
    if (is_q_empty(q)) {
        return false; // Queue is empty
    }
    if (q->front == q->rear) {
        // Reset front and rear when the last element is dequeued
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->size;
    }
    return true;
}

int main(int argc, char const *argv[])
{
	MyCircularQueue *q = (MyCircularQueue *)malloc(sizeof(MyCircularQueue));
	init_cqueue(q, 5);
	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);
	enqueue(q, 3);
	enqueue(q, 3);
	if (is_q_empty(q))
	{
		cout << "empty q" << endl;
	}
	if (is_q_full(q))
	{
		cout << "q full" << endl;
	}
	free_cqueue(q);
	return 0;
}