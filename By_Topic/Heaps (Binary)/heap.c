#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#define GET_PARENT_IDX(i) ((i - 1) / 2)
#define GET_LEFT_CHILD_IDX(i) (2*i + 1)
#define GET_RIGHT_CHILD_IDX(i) (2*i + 2)

int swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int* heap_arr = NULL;
int heap_size = 0;
int heap_capacity = 0;

void print_heap()
{
    for (size_t i = 0; i < heap_size; i++)
    {
        printf("%d ", heap_arr[i]);
    }
    printf("\n");
}

void insert(int ele)
{
    if (heap_size == heap_capacity) {
        printf("Heap is FULL\n");
        return;
    }
    heap_arr[heap_size] = ele;
    heap_size++;
    int curr_index = heap_size - 1;
    while (curr_index != 0 &&
            heap_arr[curr_index] < heap_arr[GET_PARENT_IDX(curr_index)])
    {
        swap(&heap_arr[curr_index], &heap_arr[GET_PARENT_IDX(curr_index)]);
        curr_index = GET_PARENT_IDX(curr_index);
    }
}

void heapify(int idx)
{
    int li = GET_LEFT_CHILD_IDX(idx);
    int ri = GET_RIGHT_CHILD_IDX(idx);
    int smallest = idx;
    if (li < heap_size && heap_arr[li] < heap_arr[smallest]) {
        smallest = li;
    } else if (ri < heap_size && heap_arr[ri] < heap_arr[smallest]) {
        smallest = ri;
    }
    if (smallest != idx) {
        swap(&heap_arr[idx], &heap_arr[smallest]);
        heapify(smallest);
    }
}

int extract_min()
{
    if (heap_size == 0) {
        printf("Heap is empty\n");
        return INT_MIN;
    }
    int ele = heap_arr[0];
    swap(&heap_arr[0], &heap_arr[heap_size - 1]);
    heap_size--;
    heapify(0);
    return ele;
}

int replace_element(int idx, int ele)
{
    if (idx >= heap_size) {
        printf("Heap is full\n");
        return -1;
    }
    heap_arr[idx] = ele;
    while (idx != 0 && heap_arr[idx] < heap_arr[GET_PARENT_IDX(idx)]) {
        swap(&heap_arr[idx], &heap_arr[GET_PARENT_IDX(idx)]);
        idx = GET_PARENT_IDX(idx);
    }
    return 0;
}

int delete_idx(int idx)
{
    replace_element(idx, INT_MIN);
    extract_min();
}

int main(int argc, char const *argv[])
{
    int choice;
    int element;
    printf("Enter Heap capacity:\n");
    scanf("%d", &heap_capacity);
    heap_arr = malloc(sizeof(int) * heap_capacity);
    printf("Heap capacity = %d\n", heap_capacity);
    while (1) {
        printf("MIN HEAP OPERATIONS MENU\n");
        printf("1. Insert element into heap\n");
        printf("2. Remove minimum element from heap\n");
        printf("3. Display minimum element of heap\n");
        printf("4. Display all elements of heap\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter a element to insert into heap\n");
            scanf("%d", &element);
            insert(element);
            break;
        case 2:
            printf("Removed element = %d\n", extract_min());
            break;
        case 4:
            print_heap();
            break;
        case 5:
            free(heap_arr);
            exit(0);
        default:
            break;
        }
    }
    
    return 0;
}
