#include <iostream>

using namespace std;
template <class T>
class mqueue
{
    class node
    {
        T data;
        node* next_node;
        node(T _data)
        {
            data = _data;
            next_node = nullptr;
        }
    };
    node* head;
    node* tail;
public:
    mqueue()
    {
        head = nullptr;
        tail = nullptr;
    }
    ~mqueue()
    {
        
    }
    T& top()
    {
        if(head != nullptr)
            return head->data;
    }
    void push(T _data)
    {
        if (tail == nullptr)
            tail == new node(_data);
        else
        tail->next_node = new node(_data);
        if(head == nullptr)
        {
            head = tail;
        }
    }
    void pop()
    {
        if(head != nullptr)
        {
            if(head == tail)
                tail = head;
            node* tmp = head->next_node;
            delete head;
            head = tmp;
        }
    }
};
int main()
{
    return 0;
}