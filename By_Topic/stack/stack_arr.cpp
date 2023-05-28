#include <iostream>

#define STACK_SIZE 100

class stack
{
    public:
        stack();
        int count;
        int data[STACK_SIZE];
        
    private:
        void push(int item);
        int pop();
};

stack::stack()
{
    count = 0;
}

//Copy constructor
stack::stack(const stack& old_stack)
{
    int i;
    for (i = 0; i < old_stack.count; i++) {
        data[i] = old_stack.data[i];
    }
    count = old_stack.count;
}

inline void stack::push(int item)
{
    assert(count >= 0 && count < sizeof(data)/sizeof(data[0]));
    data[count] = item;
    count++;
}

inline int stack::pop()
{
    count--;
    return data[count];
}