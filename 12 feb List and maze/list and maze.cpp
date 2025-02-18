#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
using namespace std;
template <class T>
class mqueue
{
    struct node
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
        node* tmp;
        while (head != nullptr)
        {
            tmp = head->next_node;
            delete head;
            head = tmp;
        }
    }
    mqueue(mqueue& _mqueue)
    {
        head = nullptr;
        tail = nullptr;
        node* tmp = _mqueue.head;
        while (tmp != nullptr)
        {
            this->push(tmp->data);
            tmp = tmp->next_node;
        }
    }
    void zabava()
    {
        node* tmp = head;
        while (tmp != nullptr)
        {
            cout <<'\t' << tmp->data;
            tmp = tmp->next_node;
        }
        cout << endl;
    }
    T& top()
    {
        if (head != nullptr)
            return head->data;
    }
    void push(T _data)
    {
        if (tail == nullptr)
            tail = new node(_data);
        else
        {
            node* tmp = tail;
               
            tail->next_node = new node(_data);
            tail = tmp->next_node;
        }
        if (head == nullptr)
        {
            head = tail;
        }
    }
    void pop()
    {
        if (head != nullptr)
        {
            if (head == tail)
                tail = head;
            node* tmp = head->next_node;
            delete head;
            head = tmp;
        }
    }
    bool is_empty()
    {
        if (head == nullptr)
            return 1;
        return 0;
    }
};
struct ppoint
{
    int x, y;
    ppoint* prev_point;
    ppoint()
    {
        x = y = -1;
        prev_point = nullptr;
    }
    ppoint(ppoint* _ppoint, const int& _x,const int& _y)
    {
        prev_point = _ppoint;
        x = _x;
        y = _y;
    }    
};
struct just_point
{
    int x;
    int y;
    just_point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    friend bool operator< (const just_point first, const just_point sec)
    {
        if (first.x < sec.x) return true;
        if (first.x > sec.x) return false;
        if (first.y < sec.y) return true;
        return false;
    }
};
bool is_in_bound(int x, int y, int x_size, int y_size)
{
    if(x >= 0 && y >= 0 && x < x_size && y <= y_size)
        return true;
    return false;
}
bool is_free(char symb)
{
    if(symb == ' ' || symb == 'T')
        return true;
    return false;
}
bool alredy_used(set<just_point>& bili, int x, int y)
{
    if(bili.count(just_point(x,y)) >=1)
        return true;
    return false;
}
int main()
{
    string file_name = "maze.txt";
    fstream inp(file_name);
    const char person= 'P';
    const char treasure = 'T';
    int x_size, y_size;
    inp >> x_size;
    inp >> y_size;
    char** maze = new char* [x_size];
    for (int i = 0; i < x_size; i++)
    {
        maze[i] = new char[y_size];
    }
    inp.ignore();
    char* temp = new char[y_size+1];
    for(int i = 0; i < x_size; i++)
    {
        inp.getline(temp, y_size+1);
        strncpy(maze[i], temp, y_size);
    }
    mqueue<ppoint*> steps;
    ppoint* pperson_position = new ppoint;
    int treasurex;
    int treasurey;
    for(int i = 0; i< x_size; i++)
    {
        for(int j = 0; j < y_size; j++)
        {
            if(maze[i][j]==person)
            {
                pperson_position->x = i;
                pperson_position->y = j;
            }
            if(maze[i][j]==treasure)
            {
                treasurex = i;
                treasurey = j;
            }
        }
    }
    steps.push(pperson_position);
    int tempx, tempy, neibx, neiby;
    set<just_point> bili;
    bili.insert(just_point(pperson_position->x, pperson_position->y));
    while(true)
    {
        tempx = steps.top()->x;
        tempy = steps.top()->y;
        if(tempx ==treasurex && tempy == treasurey)
        {
            break;
        }
        neibx = tempx -1;
        neiby = tempy;
        if(is_in_bound(neibx, neiby, x_size, y_size))
        {
            if(is_free(maze[neibx][neiby]) && !alredy_used(bili, neibx, neiby))
            {
                steps.push(new ppoint(steps.top(), neibx, neiby));
                bili.insert(just_point(neibx, neiby));
            }
        }
        neibx = tempx;
        neiby = tempy - 1;
                if(is_in_bound(neibx, neiby, x_size, y_size))
        {
            if(is_free(maze[neibx][neiby]) && !alredy_used(bili, neibx, neiby))
            {
                steps.push(new ppoint(steps.top(), neibx, neiby));
                bili.insert(just_point(neibx, neiby));
            }
        }
        neibx = tempx +1;
        neiby = tempy;
                if(is_in_bound(neibx, neiby, x_size, y_size))
        {
            if(is_free(maze[neibx][neiby]) && !alredy_used(bili, neibx, neiby))
            {
                steps.push(new ppoint(steps.top(), neibx, neiby));
                bili.insert(just_point(neibx, neiby));
            }
        }
        neibx = tempx;
        neiby = tempy +1;
    if(is_in_bound(neibx, neiby, x_size, y_size))
        {
            if(is_free(maze[neibx][neiby]) && !alredy_used(bili, neibx, neiby))
            {
                steps.push(new ppoint(steps.top(), neibx, neiby));
                bili.insert(just_point(neibx, neiby));
            }
        }
        steps.pop();
    }

    cout << "\nThe shortest pass:\n\n";
    ppoint* temppoint = steps.top();
    while(temppoint != nullptr)
    {
        cout << "\nx: " << temppoint->x << "\ty: " << temppoint->y;
        temppoint = temppoint->prev_point;
    }
    return 0;
}