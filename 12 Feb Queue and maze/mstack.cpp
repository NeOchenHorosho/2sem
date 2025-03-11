#include <iostream>

using namespace std;
template <class T>
class MyStack
{
private:
    struct Node
    {
        T NodeData;
        Node* prev;
        Node()
        {
            prev = nullptr;
        }
        Node(T _NodeData, Node* _prev = nullptr)
        {
            NodeData = _NodeData;
            prev = _prev;
        }
    };
    Node* top_pointer;
    Node* bottom_pointer;

public:
    MyStack()
    {
        top_pointer = nullptr;
        bottom_pointer = nullptr;
    }
    void push(T Data)
    {
        if(bottom_pointer != nullptr)
        {
            top_pointer = new Node(Data, top_pointer);
        }
        else
        {
            bottom_pointer = top_pointer = new Node(Data, top_pointer);
        }
    }
    T& top()
    {
        return top_pointer->NodeData;
    }
    void pop()
    {
        Node* tmp = top_pointer;
        top_pointer = top_pointer->prev;
        delete top_pointer;
    }
};
int main()
{

}