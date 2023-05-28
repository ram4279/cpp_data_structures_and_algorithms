#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct node
{
    struct node *next;
    int data;
};

typedef struct node node_t;

node_t* head;
pthread_mutex_t mutex;
pthread_cond_t cond;

node_t* create_node(int data)
{
    node_t* newnode = malloc(sizeof(node_t));
    if (!newnode) {
        perror("Malloc failed!!!");
        exit(1);
    }
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void push(int data)
{
    node_t* new_node = create_node(data);
    new_node->next = head;
    head = new_node;
}

int is_list_empty()
{
    return (!head) ? 1 : 0;
}

int pop()
{
    node_t* temp = head;
    if (is_list_empty()) {
        return 0xDEADBEEF;
    } else {
        head = head->next;
        int data = temp->data;
        free(temp);
        return data;
    }
}

void* consumer(void *arg)
{
    pthread_mutex_lock(&mutex);
    while (is_list_empty()) {
        printf("List is empty waiting\n");
        pthread_cond_wait(&cond, &mutex); // Unlocks mutex and consumer goes to sleep
    }
    int data = pop();
    printf("Consumed element %d\n", data);
    pthread_mutex_unlock(&mutex);
}

void* producer(void* arg)
{
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        push(i);
        printf("Produced Element %d\n", i);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        sleep(1);
    }
    
}

void printList()
{
    node_t* temp = head;
    while(temp) {
        printf("%d->", temp->data);
        temp = temp->next;
    }
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, consumer, NULL);
    pthread_create(&t2, NULL, producer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
