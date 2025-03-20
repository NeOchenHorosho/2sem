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
public:
    MyStack() : top_pointer(nullptr){}
    MyStack(MyStack& source)
    {
        MyStack tmp;
        Node* pointer = source.top_pointer;
        while(pointer != nullptr)
        {
            tmp.push(pointer->NodeData);
            pointer = pointer->prev;
        }
        while(!tmp.empty())
        {
            this->push(tmp.top());
            tmp.pop();
        }
    }
    void push(T Data)
    {
        top_pointer = new Node(Data, top_pointer);
    }
    T& top()
    {
        return top_pointer->NodeData;
    }
    void pop()
    {
        if(top_pointer != nullptr)
        {
            Node* tmp = top_pointer;
            top_pointer = top_pointer->prev;
            delete tmp;
        }
    }
    bool empty()
    {
        if(top_pointer!= nullptr)
            return true;
        return false;
    }
};
int main()
{
    MyStack<int> haha;
    haha.push(1);
    haha.push(2);
    haha.push(3);

    MyStack<int> zabava(haha);
    cout << "\n\n\n";
    while(!zabava.empty())
    {
        
        cout << zabava.top() << '\t';
        zabava.pop();
    }
    return 0;
}