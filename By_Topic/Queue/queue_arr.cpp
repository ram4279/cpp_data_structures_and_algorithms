#include <iostream>
#include <cassert>

using namespace std;

#define QUEUE_SIZE 100

class queue
{
    private:
        int count;
        int data[QUEUE_SIZE];
    
    public:
        void enque(int item);
        int deque();
        void print_que();
        queue(const queue& old_que);
        queue();


};

void queue::print_que()
{
    for (int i = 0; i < count; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

queue::queue()
{
    count = 0;
}

void queue::enque(int item)
{
    data[count] = item;
    count++;
}

int queue::deque()
{
    assert(count > 0);
    int item = data[0];
    for (int i = 0; i < count - 1; i++) {
        data[i] = data[i+1];
    }
    count--;
    return item;
}

queue::queue(const queue& old_que)
{
    for (int i = 0; i < old_que.count; i++) {
        data[i] = old_que.data[i];
    }
    count = old_que.count;
}

int main()
{
    queue mq;
    mq.enque(1);
    mq.enque(2);
    mq.enque(3);
    mq.print_que();
    mq.deque();
    mq.print_que();
    mq.deque();
    mq.print_que();
    return 0;
}