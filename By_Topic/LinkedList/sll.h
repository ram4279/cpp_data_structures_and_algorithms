#ifndef __DLL_H__
#define __DLL_H__

typedef struct Node
{
    struct Node* next;
    int data;
}Node;

#ifdef __LL_TAIL__
typedef struct sll 
{
    Node* head;
    Node* tail;
    int count;

}sll;
#else
typedef struct sll 
{
    Node* head;
    int count;

}sll;
#endif /* __LL_TAIL__ */

#endif /* __DLL_H__ */