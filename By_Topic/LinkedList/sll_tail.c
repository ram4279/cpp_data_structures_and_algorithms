#include <stdio.h>
#include <stdlib.h>
#include "sll.h"


/* Create Node */
Node* create_node(int data)
{
    Node* newnode = malloc(sizeof(Node));
    if (!newnode) {
        perror("Memory allocation failed\n");
        exit(1);
    }
    newnode->next = NULL;
    newnode->data = data;
    return newnode;
}

void print_list(sll* list)
{
    Node* trav = list->head;
    for (; trav; trav = trav->next) {
        printf("%d->", trav->data);
    }
    printf("NULL\n");
    return;
}


#ifdef __LL_TAIL__
void init_list(sll** list)
{
    *list = malloc(sizeof(sll));
    if (!(*list)) {
        fprintf(stderr, "Memory allocation failed %s\n", __FUNCTION__);
        exit(1);
    }
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->count = 0;
}

void delete_list(sll** list)
{
    Node* tptr = (*list)->head;
    Node* del_ptr = tptr;
    for (; tptr; tptr=tptr->next) {
        del_ptr = tptr;
        free(del_ptr);
    }
    free(tptr);
    free((*list));
}
/* Function to insert at index */
void insert(sll* list, int data, int pos)
{
    if (!list) {
        perror("list is NULL");
        return;
    }
    Node* newnode = create_node(data);

    if (pos == 0) {
        if (list->head == NULL) {
            list->tail = newnode;
            list->head = newnode;
            list->count++;
            return;
        }
        newnode->next = list->head;
        list->head = newnode;
    } else if (pos >= list->count) {
        if (list->tail == NULL) {
            list->head = newnode;
            list->tail = newnode;
            list->count++;
            return;
        }
        list->tail->next = newnode;
        list->tail = newnode;
    } else {
        Node* tptr = list->head;
        /* stop before the index */
        while (pos > 1) {
            tptr = tptr->next;
            pos--;
        }
        newnode->next = tptr->next;
        tptr->next = newnode;
    }
    
    list->count++;
    return;
}

/* Function to delete at index */
int delete(sll* list, int pos)
{
    if (pos >= list->count || list->count <= 0) {
        return -1;
    }

    int ret_val;
    Node* temp = NULL;

    if (pos == 0) {
        temp = list->head;
        ret_val = temp->data;
        list->head = list->head->next;
        free(temp);
        if (list->head == NULL) {
            list->tail = NULL;
        }
    } else if (pos == list->count-1) {
        temp = list->head;
        while (temp->next != list->tail) {
            temp = temp->next;
        }
        Node* newtail = temp;
        Node* oldtail = temp->next;
        ret_val = oldtail->data;
        newtail->next = NULL;
        list->tail = newtail;
        free(oldtail);
    } else {
        Node* prev_ptr = list->head;
        /* stop before the index */
        while (pos > 1) {
            prev_ptr = prev_ptr->next;
            pos--;
        }
        Node* deleted_node = prev_ptr->next;
        prev_ptr->next = prev_ptr->next->next;
        ret_val = deleted_node->data;
        free(deleted_node);
    }

    list->count--;
    return ret_val;
}
#else

void init_list(sll** list)
{
    (*list) = malloc(sizeof(list));
    (*list)->head = NULL;
    (*list)->count = 0;
}

void insert(sll *list, int data, int position)
{
    Node* newnode = create_node(data);
    if (position == 0) {
        newnode->next = list->head;
        list->head = newnode;
    } else if (position >= list->count) {
        if (!list->head) {
            newnode->next = list->head;
            list->head = newnode;
        } else {
            Node* last_node = list->head;
            while(last_node->next) {
                last_node = last_node->next;
            }
            last_node->next = newnode;
        }
    } else {
        Node* prv = list->head;
        while (position-- > 1) {
            prv = prv->next;
        }
        newnode->next = prv->next;
        prv->next = newnode;
    }
    list->count++;
    return;
}


void sorted_insert(sll *list, int val)
{
    Node* newnode = create_node(val);
    Node* curr = list->head;
    Node* prev = NULL;
    while (curr && val > curr->data) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL) {
        newnode->next = list->head;
        list->head = newnode;
        return;
    } else {
        newnode->next = prev->next;
        prev->next = newnode;
    }
}

void delete(sll *list, int position)
{
    if (list->count <= 0) {
        printf("List is empty\n");
        return;
    }

    if (position > list->count) {
        printf("position out of index\n");
        return;
    }

    if (position == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    } else if (position > list->count) {
        Node* temp = list->head;
        while (temp->next->next) {
            temp = temp->next;
        }
        Node* last_element = temp->next;
        temp->next = NULL;
        free(last_element);
    } else {
        Node* prev = list->head;
        while (position-- > 1) {
            prev = prev->next;
        }
        Node* element_to_free = prev->next;
        prev->next = prev->next->next;
        free(element_to_free);
    }
    list->count--;
}

void reverse_list(sll* list)
{
    Node* prev = NULL;
    Node* next = NULL;
    Node* curr = list->head;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;
}

Node* reverse_list_rec_helper(Node* head)
{
    if (!head->next) {
        return head;
    }
    Node* newhead = reverse_list_rec_helper(head->next);
    head->next->next = head;
    head->next = NULL;
    return newhead;
}

void reverse_list_rec(sll* list)
{
    if (!list->head) {
        return;
    } else {
        list->head = reverse_list_rec_helper(list->head);
    }
    return;
}

void delete_list(sll* list)
{
    Node* curr = list->head;
    Node* next = NULL;
    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
}

void swap_nodes(sll* list, Node* n1, Node* n2)
{
    if (list->count == 1) {
        printf("Only 1 element so not swapping");
        return;
    }
    Node* n1_prev;
    Node* n2_prev;
    Node* temp = list->head;
    Node* prev = NULL;
    while (temp) {
        if (temp->data == n1->data) {
            n1_prev = prev;
        } else if (temp->data == n2->data) {
            n2_prev = prev;
        }
        prev = temp;
        temp = temp->next;
    }

    temp = NULL;
    if (n1_prev != NULL) {
        n1_prev->next = n2;
    } else {
        list->head = n2;
    }

    if (n2_prev != NULL) {
        n2_prev->next = n1;
    } else {
        list->head = n1;
    }

    temp = n2->next;
    n2->next = n1->next;
    n1->next = temp;

}

void swapPairs(sll* list) {
    if (!list->head || !list->head->next) {
        return;
    }

    Node* dummy = create_node(0);
    Node* prev = dummy;
    Node* cur  = list->head;
    while (cur && cur->next) {
        prev->next = cur->next;
        cur->next = cur->next->next;
        prev->next->next = cur;

        prev = cur;
        cur  = cur->next;
    }
    list->head = dummy->next;
}

#endif /* __LL_TAIL__ */

int main(int argc, char const *argv[])
{
    sll* num_list;
    init_list(&num_list);

    while (1)
    {
        int number, position;
        int option = 0;
        scanf("%d", &option);
        if (option == 1) {
            scanf("%d", &number);
            scanf("%d", &position);
            insert(num_list, number, position);
        } else if (option == 0) {
            scanf("%d", &position);
            delete(num_list, position);
        } else if (option == 2){
            reverse_list(num_list);
        } else if (option == 3) {
            swapPairs(num_list);
        } else if (option == 4) {
            scanf("%d", &number);
            sorted_insert(num_list, number);
        } else if (option == 5) {
            reverse_list_rec(num_list);
        }
        print_list(num_list);
    }

    // for (int i = 1; i <= 3; i++) {
    //     insert(num_list, i, 0);
    // }
    // print_list(num_list);
    // swap_nodes(num_list, num_list->head->next, num_list->head->next->next);
    // print_list(num_list);

    return 0;
}
