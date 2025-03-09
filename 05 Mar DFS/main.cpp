#include <iostream>
#include <istream>
#include <fstream>
#include <stack>
#include <list>
#include <queue>

using namespace std;
class Graph
{
private:
    int size;
    list<int>* vertices;
    stack<int> DFS_stack;
    queue<int> WFS_queue;
    bool* is_visited;
public:
    Graph()
    {
        size = 0;
        vertices = nullptr;
        is_visited = nullptr;
    }
    Graph(istream& inp)
    {
        inp >> size;
        vertices = new list<int>[size];
        is_visited = new bool[size]{};
        int tmp, val;
        while(inp >> tmp)
        {
            inp >> val;
            vertices[tmp-1].push_back(val-1);
        }   
    }
    void WFS()
    {
        cout << 1 << ' ';
        for(auto i = vertices[0].begin(); i!=vertices[0].end(); i++)
        {
            WFS_queue.push(*i);
            cout << *i +1<< " ";
        }
        cout << '\n';
        is_visited[0] = true;
        while(!WFS_queue.empty())
        {
            int curr_vert = WFS_queue.back();
            WFS_queue.pop();
            for(auto i = vertices[curr_vert].begin(); i!=vertices[curr_vert].end(); i++)
            {
                if(is_visited[*i] == true)
                    continue;
                WFS_queue.push(*i);
                cout << *i +1<< " ";
            } 
            cout << '\n';
        }
        for(int i = 0; i < size; i++)
        {
            is_visited[i] = false;
        }
    }

    void DFS()
    {
        DFS_stack.push(0);
        cout << 1 << ' ';
        is_visited[0]=true;
        int curr_vert;
        while(!DFS_stack.empty())
        {
            curr_vert = DFS_stack.top();
            if(vertices[curr_vert].empty())
            {
                DFS_stack.pop();
                continue;
            }
            for(auto i = vertices[curr_vert].begin(); i!=vertices[curr_vert].end(); i++)
            {
                if(is_visited[*i] == false)
                {
                    DFS_stack.push(*i);
                    cout << *i+ 1 << ' ';
                    break;
                }
                DFS_stack.pop();
            } 
        }
    }
};
int main()
{
    cout << "\n\n\n";
    cout << "WFS: \n";
    fstream inp("graph.txt");
    Graph zabava(inp);
    zabava.WFS();
    cout << "\n\n\nDFS:\n";
    zabava.DFS();
    return 0;
}