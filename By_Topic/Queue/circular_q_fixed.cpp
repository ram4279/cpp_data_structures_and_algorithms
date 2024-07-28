#include <algorithm>
#include <cstddef>
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


typedef struct {
    int *arr;
    int front;
    int rear;
    int size;
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k) {
	MyCircularQueue *q = (MyCircularQueue *)malloc(sizeof(MyCircularQueue));
	if (!q)
	{
		return NULL;
	}
	q->arr = (int *)malloc(sizeof(int) * k);
	if (!q->arr)
	{
		free(q);
		return NULL;
	}

	q->front = -1;
	q->rear = -1;
	q->size = k;
	return q;
}

bool myCircularQueueIsEmpty(MyCircularQueue* q) {
    return (q->front == -1 && q->rear == -1);
}

bool myCircularQueueIsFull(MyCircularQueue* q) {
    return (((q->rear + 1) % q->size) == q->front);
}

bool myCircularQueueEnQueue(MyCircularQueue* q, int value) {
    if (myCircularQueueIsFull(q))
    {
    	return false;
    }
    if (q->front == -1)
    {
    	// first element is being inserted 
    	// if this is not done the front will stay in -1 forever and when
    	// new elements are inserted overwrite happens aka myCircularQueueIsFull will always returns false
    	q->front += 1;
    }
    q->rear = (q->rear + 1) % q->size;
    q->arr[q->rear] = value;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* q) {
    if (myCircularQueueIsEmpty(q))
    {
    	return false;
    }
    if(q->front == q->rear)
    {
    	//all the items had been read reset now
    	q->front = -1;
    	q->rear = -1;
    }
    else
    {
		q->front = (q->front + 1) % q->size;
    }
    
    return true;
}

int myCircularQueueFront(MyCircularQueue* q) {
	if (!myCircularQueueIsEmpty(q))
    	return q->arr[q->front];
    return -1;
}

int myCircularQueueRear(MyCircularQueue* q) {
	if (!myCircularQueueIsEmpty(q))
    	return q->arr[q->rear];
    return -1;
}

void myCircularQueueFree(MyCircularQueue* q) {
    free(q->arr);
    free(q);
}


void print_q(MyCircularQueue* q)
{
	for (int i = 0; i < q->size; i++)
	{
		cout << q->arr[i] << " ";
	}
	cout << endl;
}

int main(int argc, char const *argv[])
{
	MyCircularQueue *q = myCircularQueueCreate(6);
	cout << myCircularQueueEnQueue(q, 6) << endl;
	cout << myCircularQueueRear(q) << endl;
	cout << myCircularQueueRear(q) << endl;
	cout << myCircularQueueDeQueue(q) << endl;
	cout << myCircularQueueEnQueue(q, 5) << endl;
	return 0;
}