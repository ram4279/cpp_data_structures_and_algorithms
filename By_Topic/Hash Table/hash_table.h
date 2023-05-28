#include <string>
using namespace std;

template <typename T>
class Node
{
public:
    string key;
    T val;
    Node *next;

    Node(string key, T val)
    {
        this->key = key;
        this->val = val;
        next = NULL;
    }

    ~Node()
    {
        if (next)
        {
            delete next;
        }
    }
};

template <typename T>
class Hashtable
{
    Node<T> **table;
    int curr_size;
    int table_size;

    int hashFn(string key)
    {
        int idx = 0;
        int power = 29;
        for (auto ch : key)
        {
            idx = (idx + ch * power) % table_size;
            power = (power * 29) % table_size;
        }
        return idx;
    }

    void rehash()
    {
        Node<T> **oldtable = table;

        // Increase table size
        int old_table_size = table_size;
        curr_size = 0;
        table_size = 2 * table_size + 1;
        table = new Node<T> *[table_size];

        // Make new table contents NULL
        for (int i = 0; i < table_size; i++)
        {
            table[i] = NULL;
        }

        // Copy elements from old table to new table
        for (int i = 0; i < old_table_size; i++)
        {
            Node<T> *temp = oldtable[i];
            while (temp)
            {
                insert(temp->key, temp->val);
                temp = temp->next;
            }
            // destroy ith linked list
            if (oldtable[i])
            {
                delete oldtable[i];
            }
        }
        delete[] oldtable;
    }

public:
    Hashtable(int default_size = 7)
    {
        curr_size = 0;
        table_size = default_size;

        table = new Node<T> *[table_size];

        for (int i = 0; i < table_size; i++)
        {
            table[i] = NULL;
        }
    }

    T *search(string key)
    {
        int idx = hashFn(key);
        Node<T> *temp = table[idx];
        while (temp)
        {
            if (temp->key == key)
            {
                return &temp->val;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void erase(string key)
    {
        int idx = hashFn(key);
        Node<T>* temp = table[idx];
        Node<T>* prev = NULL;
        while (temp) {
            if (temp->key == key) {
                //Delete at head
                if (prev == NULL) {
                    table[idx] = temp->next;
                } else {
                    prev->next = temp->next;    
                }
                // remove the reference to next node
                // otherwise that will also be deleted while deleting the current node
                temp->next = NULL;
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        return;
    }

    void insert(string key, T val)
    {
        int idx = hashFn(key);
        Node<T> *newnode = new Node<T>(key, val);

        // Just insert at head
        newnode->next = table[idx];
        table[idx] = newnode;
        curr_size++;

        float loadfactor = curr_size / (float)table_size;

        if (loadfactor > 0.7)
        {
            rehash();
        }
    }

    void print()
    {
        for (int i = 0; i < table_size; i++)
        {
            cout << "Bucket " << i << "->";
            Node<T> *temp = table[i];
            while (temp)
            {
                cout << temp->key << "->";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    T& operator[](string key)
    {
        T* value_found = search(key);
        if (value_found == NULL) {
            T object;
            insert(key, object);
            value_found = search(key);
        }
        return *value_found;
    }
};
