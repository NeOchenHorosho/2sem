#include <iostream>

using namespace std;

class AbstractIterator
{
public:
	virtual ~AbstractIterator() {};
	virtual bool in_range() const = 0;	
	virtual void reset() = 0;			
	virtual int &operator*() const = 0; 
	virtual void operator++() = 0;		
};

class AbstractContainer
{
public:
	virtual ~AbstractContainer() {};
	virtual bool is_empty() const = 0;	 
	virtual void push(const int &n) = 0; 
	virtual void pop() = 0;				 
	virtual int get_size() const = 0;		 
	virtual void show() const = 0;
};

class AbstractStack : public AbstractContainer
{
public:
	virtual ~AbstractStack() {};
	virtual int get_top() const = 0; 
};

class AbstractQueue : public AbstractContainer
{
public:
	virtual ~AbstractQueue() {};
	virtual int get_front() const = 0; 
	virtual int get_back() const = 0;  
};

class ArrayStackIterator; 
class ArrayQueueIterator;
class ListStackIterator;
class ListQueueIterator;

struct node
{
	int info;
	node *next;
};

class ArrayStack : public AbstractStack
{
protected:
	int size; 
	int *M;	  
	int top;  
public:
	ArrayStack(int _size = 16)
	{
		size = _size;
		M = new int[size];
		top = -1;
	}
	ArrayStack(const ArrayStack &s)
	{
		size = s.size;
		M = new int[size];
		top = s.top;
		for (int i = 0; i <= top; ++i)
		{
			M[i] = s.M[i];
		}
	}
	ArrayStack(ArrayStack &&s)
	{
		M = s.M;
		size = s.size;
		top = s.top;

		s.M = nullptr;
		s.size = 0;
		s.top = 0;
	}
	~ArrayStack()
	{
		delete[] M;
	}

	void push(const int &n)
	{
		if (is_full())
		{
			cout << "Stack is full\n";
            return;
		}
		M[top + 1] = n;
		top = top + 1;
	}
	void pop()
	{
		if (is_empty())
		{
			cout << "Stack is empty\n";
            return;
		}
		top = top - 1;
	}

	bool is_empty() const
	{
		return top == -1;
	}
	bool is_full() const
	{
		return top == size - 1;
	}

	int get_top() const
	{
		if (is_empty())
		{
			cout << "Stack is empty\n";
            throw "Stack is empty";
		}
		return M[top];
	}

	int get_size() const
	{
		return top + 1;
	}

	ArrayStack operator=(const ArrayStack &s)
	{
		if (this != &s)
		{
			delete[] M;
			size = s.size;
			top = s.top;

			M = new int[size];
			for (int i = 0; i < size; i++)
            {
                M[i] = s.M[i];
            }
		}
		return *this;
	}
	ArrayStack operator=(ArrayStack &&s)
	{
		if (this != &s)
		{
			delete[] M;
			M = s.M;
			size = s.size;
			top = s.top;

			s.M = nullptr;
			s.size = 0;
			s.top = 0;
		}
		return *this;
	}

	void show() const
	{
		if (is_empty())
		{
			cout << "Stack is empty\n";
            return;
		}
		int i = top;
		while (i != -1)
		{
			cout << M[i] << " ";
			i--;
		}
		cout << endl;
	}
	friend class ArrayStackIterator;
};

class ArrayQueue : public AbstractQueue
{
protected:
	int size;  
	int *p;	   
	int head;  
	int tail;  
	int count; 
public:
	ArrayQueue(int _size = 16)
	{
		size = _size;
		count = 0;
		p = new int[size];
		head = -1;
		tail = 0;
	}
	ArrayQueue(const ArrayQueue &q)
	{
		size = q.size;
		p = new int[size];
		count = q.count;
		head = q.head;
		tail = q.tail;
		for (int i = 0; i < size; ++i)
		{
			p[i] = q.p[i];
		}
	}
	ArrayQueue(ArrayQueue &&q)
	{
		p = q.p;
		size = q.size;
		head = q.head;
		tail = q.tail;
		count = q.count;

		q.p = nullptr;
		q.size = 0;
		q.head = 0;
		q.tail = 0;
		q.count = 0;
	}
	~ArrayQueue()
	{
		delete[] p;
	}

	void push(const int &n)
	{
		if (is_full())
		{
			cout << "Queue is full\n";
            return;
		}
		p[tail] = n;
		tail = (tail + 1) % size;
		if (head == -1)
		{
			head = 0;
		}
		count++;
	}
	void pop()
	{
		if (is_empty())
		{
			cout << "Queue is empty\n";
            return;
		}
		head = (head + 1) % size;
		count--;
	}

	bool is_empty() const
	{
		return count == 0;
	}
	bool is_full() const
	{
		return count == size;
	}

	int get_size() const
	{
		return count;
	}

	int get_front() const
	{
		if (is_empty())
		{
			cout << "Queue is empty\n";
            throw "Stack is empty";
		}
		return p[head];
	}
	int get_back() const
	{
		if (is_empty())
		{
			cout << "Queue is empty\n";
            throw "Stack is empty";
		}
		return p[(tail - 1 + size) % size];
	}

	ArrayQueue operator=(const ArrayQueue &q)
	{
		if (this != &q)
		{
			delete[] p;
			size = q.size;
			head = q.head;
			tail = q.tail;
			count = q.count;

			p = new int[size];
			for (int i = 0; i < size; i++)
            {
                p[i] = q.p[i];
            }
		}
		return *this;
	}
	ArrayQueue operator=(ArrayQueue &&q)
	{
		if (this != &q)
		{
			delete[] p;
			p = q.p;
			size = q.size;
			head = q.head;
			tail = q.tail;
			count = q.count;

			q.p = nullptr;
			q.size = 0;
			q.head = 0;
			q.tail = 0;
			q.count = 0;
		}
		return *this;
	}

	void show() const
	{
		if (is_empty())
		{
			cout << "Queue is empty" << endl;
			return;
		}

		int current = head;
		for (int i = 0; i < count; ++i)
		{
			cout << p[current] << " ";
			current = (current + 1) % size;
		}
		cout << endl;
	}
	friend class ArrayQueueIterator;
};

class ListQueue : public AbstractQueue
{
protected:
	node *head;
	node *tail;

public:
	ListQueue() : head(nullptr), tail(nullptr)
	{
	}

	ListQueue(const ListQueue &el)
	{
		head = nullptr;
		tail = nullptr;
		for (auto i = el.head; i != nullptr; i = i->next)
		{
			push(i->info);
		}
	}

	ListQueue(ListQueue &&x)
	{
		head = x.head;
		tail = x.tail;
		x.head = nullptr;
		x.tail = nullptr;
	}

	~ListQueue()
	{
		while (head != nullptr)
		{
			node *temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
	}

	void push(const int &info)
	{
		node *temp = new node;
		temp->info = info;
		temp->next = nullptr;
		if (tail == nullptr)
			head = temp;
		else
			tail->next = temp;
		tail = temp;
	}

	void pop()
	{
		if (head == nullptr)
		{
			cout << "Queue is empty\n";
            return;
		}
		node *temp = head;
		head = head->next;
		delete temp;

		if (head == nullptr)
			tail = nullptr;
	}

	int get_size() const
	{
		node *temp = head;
		int i = 0;
		while (temp != nullptr)
		{
			i++;
			temp = temp->next;
		}
		return i;
	}

	int get_front() const
	{
		if (head == nullptr)
		{
			cout << "Queue is empty\n";
            throw "Stack is empty";
		}
		return head->info;
	}

	int get_back() const
	{
		if (tail == nullptr)
		{
			cout << "Queue is empty\n";
            throw "Stack is empty";
		}
		return tail->info;
	}

	bool is_empty() const
	{
		return head == nullptr;
	}

	ListQueue &operator=(const ListQueue &x)
	{
		if (this != &x)
		{
			node *temp;
			while (head != nullptr)
			{
				pop();
			}
			tail = nullptr;

			temp = x.head;
			while (temp != nullptr)
			{
				push(temp->info);
				temp = temp->next;
			}
		}
		return *this;
	}

	ListQueue &operator=(ListQueue &&x)
	{
		if (this != &x)
		{
			head = x.head;
			tail = x.tail;
			x.head = nullptr;
			x.tail = nullptr;
		}
		return *this;
	}

	void show() const
	{
		if (head == nullptr)
		{
			cout << "Queue is empty\n";
            return;
		}

		node *current = head;
		while (current != nullptr)
		{
			cout << current->info << " ";
			current = current->next;
		}
		cout << endl;
	}

	friend class ListQueueIterator;
};

class ListStack : public AbstractStack
{
protected:
	node *head;

public:
	ListStack() : head(nullptr) {}

	ListStack(ListStack &&x)
	{
		head = x.head;
		x.head = nullptr;
	}

	ListStack(const ListStack &x)
	{
		head = nullptr;
		node *temp;
		ListStack y;
		temp = x.head;
		while (temp != nullptr)
		{
			y.push(temp->info);
			temp = temp->next;
		}
		temp = y.head;
		while (temp != nullptr)
		{
			push(temp->info);
			temp = temp->next;
		}
	}

	~ListStack()
	{
		node *temp;
		while (head != nullptr)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}

	void push(const int &x)
	{
		node *temp = new node;
		temp->info = x;
		temp->next = head;
		head = temp;
	}

	void pop()
	{
		if (head == nullptr)
		{
			cout << "Queue is empty\n";
            return;
		}
		node *temp = head;
		head = head->next;
		delete temp;
	}

	int get_size() const
	{
		node *temp = head;
		int i = 0;
		while (temp != nullptr)
		{
			i++;
			temp = temp->next;
		}
		return i;
	}

	int get_top() const
	{
		if (head == nullptr)
		{
			cout << "Queue is empty\n";
            throw "Stack is empty";
		}
		return head->info;
	}

	bool is_empty() const
	{
		return head == nullptr;
	}

	ListStack &operator=(const ListStack &x)
	{
		if (this != &x)
		{
			node *temp;
			while (head != nullptr)
			{
				pop();
			}

			ListStack y;
			temp = x.head;
			while (temp != nullptr)
			{
				y.push(temp->info);
				temp = temp->next;
			}

			temp = y.head;
			while (temp != nullptr)
			{
				push(temp->info);
				temp = temp->next;
			}
		}
		return *this;
	}

	ListStack &operator=(ListStack &x)
	{
		if (this != &x)
		{
			head = x.head;
			x.head = nullptr;
		}
		return *this;
	}

	void show() const
	{
		if (head == nullptr)
		{
			cout << "Stack is empty\n";
            return;
		}
		node *temp = head;
		while (temp != nullptr)
		{
			cout << temp->info << endl;
			temp = temp->next;
		}
	}

	friend class ListStackIterator;
};

class ArrayStackIterator : public AbstractIterator
{
	ArrayStack &a; 
	int pos;	   
	ArrayStackIterator();

public:
	ArrayStackIterator(ArrayStack &_a) : a(_a), pos(_a.top) {}
	bool in_range() const
	{
		return pos > -1;
	}
	void reset()
	{
		pos = a.top;
	}
	int &operator*() const
	{
		if (!in_range())
		{
			cout << "Iterator out of range\n";
            throw "Stack is empty";
		}
		return a.M[pos];
	}
	void operator++()
	{
		if (!in_range())
		{
			cout << "Iterator out of range\n";
            return;
		}
		--pos;
	}
};

class ArrayQueueIterator : public AbstractIterator
{
	ArrayQueue &a;	 
	int pos, passed; 
	ArrayQueueIterator();

public:
	ArrayQueueIterator(ArrayQueue &_a) : a(_a)
	{
		pos = a.head;
		passed = a.count;
	}
	bool in_range() const
	{
		return passed != 0;
	}
	void reset()
	{
		pos = a.head;
		passed = a.count;
	}
	int &operator*() const
	{
		if (!in_range())
		{
			cout << "Iterator out of range\n";
            throw "Stack is empty";
		}
		return a.p[pos];
	}
	void operator++()
	{
		pos = (pos + 1) % a.size;
		passed--;
	}
};

class ListStackIterator : public AbstractIterator
{
	ListStack &a;  
	node *current; 
	ListStackIterator();

public:
	ListStackIterator(ListStack &_a) : a(_a)
	{
		current = a.head;
	}
	bool in_range() const
	{
		return current != nullptr;
	}
	void reset()
	{
		current = a.head;
	}
	int &operator*() const
	{
		if (!in_range())
		{
			cout << "Iterator out of range\n";
            throw "Stack is empty";
		}
		return current->info;
	}
	void operator++()
	{
		if (!in_range())
		{
			cout << "Iterator out of range\n";
            return;
		}
		current = current->next;
	}
};

class ListQueueIterator : public AbstractIterator
{
	ListQueue &a;  
	node *current; 
	ListQueueIterator();

public:
	ListQueueIterator(ListQueue &_a) : a(_a)
	{
		current = a.head;
	}
	bool in_range() const
	{
		return current != nullptr;
	}
	void reset()
	{
		current = a.head;
	}
	int &operator*() const
	{
		if (!in_range())
		{
			cout << "Iterator out of range\n";
            throw "Stack is empty";
		}
		return current->info;
	}
	void operator++()
	{
		if (!in_range())
		{
			cout << "Iterator out of range\n";
            return;
		}
		current = current->next;
	}
};

int main()
{
	ArrayQueue haha;
	AbstractQueue &haha_ref = haha;
	for (int i = 0; i < 10; i++)
	{
		haha_ref.push(i);
	}
	ArrayQueueIterator iter(haha);
	AbstractIterator &iter_ref = iter;
	while (iter_ref.in_range())
	{
		cout << *iter_ref << " ";
		++iter_ref;
	}
	return 0;
}