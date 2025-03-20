#include <iostream>
#include <queue>
using namespace std;
template <class T>
class AbstractIterator
{
public:
	virtual ~AbstractIterator() {};
	virtual bool InRange() const = 0;		 
	virtual void Reset() = 0;			
	virtual T& operator *() const = 0;		
	virtual void operator ++() = 0;			
};

class AbstarctCointainer
{
    public:
    virtual ~AbstarctCointainer(){}
    virtual bool empty() const = 0;
    virtual bool full() const = 0;
};
template <class T>
class AbstractStack: public AbstarctCointainer
{
    public:
    virtual void push(const T& dat) = 0;
    virtual void pop() = 0;
    virtual T& top() = 0;
};
template <class T>
class AbstractQueue: public AbstarctCointainer<T>
{
    public:
    virtual void push(const T& dat) = 0;
    virtual void pop() = 0;
    queue<T> haha

};
template<class T> 
class ArrayStack: public AbstractStack<T>
{
    size_t arr_size;
    T* arr_pointer;
    size_t stack_size;
public:
    ArrayStack(size_t _arr_size = 100): arr_size (_arr_size), stack_size(0)
    {
        arr_pointer = new T[arr_size];
    }
    ~ArrayStack()
    {
        delete[] arr_pointer;
    }
    void push(const T& n)
    {
        if(stack_size <= arr_size)
        {
            arr_pointer[stack_size] = n;
        }
        else
        {
            
        }
    }
};