#include <iostream>

using namespace std;

template <typename T>
class Vector
{
private:
    T *arr;
    size_t size;
    size_t capacity;

public:
    Vector()
    {
        capacity = 2;
        size     = 0; 
        arr = new T[capacity];
    }

    Vector(int capacity)
    {
        this->capacity = capacity;
        this->size     = 0;
        this->arr = new int[capacity];
    }

    void push_back(T data)
    {
        if (size == capacity) {
            T *old_arr = arr;
            capacity = 2 * capacity;
            arr = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                arr[i] = old_arr[i];
            }
            delete[] old_arr;
        }
        arr[size] = data;
        size++;
    }

    void pop_back()
    {
        if (size >= 0) {
            size--;
        }
    }

    bool empty()
    {
        return size==0;
    }

    size_t get_size()
    {
        return size;
    }

    size_t capactiy()
    {
        return capacity;
    }

    T at(size_t index)
    {
        return arr[index];
    }

    T operator [] (size_t index)
    {
        return arr[index];
    }
};

int main(int argc, char const *argv[])
{
    Vector<string> vec;
    vec.push_back("bob");
    vec.push_back("marley");
    vec.push_back("jason");
    vec.push_back("stathom");
    vec.push_back("quentin");

    for (int i = 0; i < vec.get_size(); i++) {
        cout << vec.at(i) << endl;
        cout << vec[i] << endl;
    }

    cout << "Capacity = " <<  vec.capactiy() << endl;
    cout << vec.get_size() << endl;

    return 0;
}
