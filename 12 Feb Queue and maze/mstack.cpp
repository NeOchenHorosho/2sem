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
    MyStack(const MyStack& source)
    {
        top_pointer = nullptr;
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
    MyStack& operator=(const MyStack& right)
    {
        while (top_pointer != nullptr)
        {
            Node* temp = top_pointer;
            top_pointer = top_pointer->prev;
            delete temp;
        }
        MyStack tmp;
        Node* pointer = right.top_pointer;
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
        return *this;
    }
    MyStack& operator=(MyStack&& right)
    {
        Node* tmp = right.top_pointer;
        right.top_pointer = top_pointer;
        top_pointer = tmp;
        return *this;
    }
    MyStack(T ogo)
    {
        top_pointer = new Node(ogo);
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
        if(top_pointer== nullptr)
            return true;
        return false;
    }
    void show()
    {
    };
    ~MyStack()
    {
        while (top_pointer != nullptr)
        {
            Node* temp = top_pointer;
            top_pointer = top_pointer->prev;
            delete temp;
        }
    }
};
int main()
{
    MyStack<int> haha;
    haha.push(1);
    haha.push(2);
    haha.push(3);
    MyStack<int> zabava(haha);
    zabava = haha;
    haha.pop();
    haha.pop();
    cout << "\n\n\n";
    while(!zabava.empty())
    {
        
        cout << zabava.top() << '\t';
        zabava.pop();
    }
    return 0;
}