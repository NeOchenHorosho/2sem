#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class Graph
{
private:
    int number_of_vertices;
    int number_of_edges;
    list<int>* vertices;

    bool* is_visited;
public:
    Graph()
    {
        number_of_vertices = 0;
        number_of_edges = 0;
        vertices = nullptr;
        is_visited = nullptr;
    }
    Graph(istream& inp)
    {
        inp >> number_of_vertices;
        inp >> number_of_edges;
        vertices = new list<int>[number_of_vertices];
        is_visited = new bool[number_of_vertices]{};
        int tmp1, tmp2;
        for(int i = 0; i < number_of_edges; i++)
        {
            inp >> tmp1;
            inp >> tmp2;
            vertices[tmp1-1].push_back(tmp2-1);
            vertices[tmp2-1].push_back(tmp1-1);
        }
    }
    unordered_set<int> WFS(int cvert)
    {
        unordered_set<int> result;
        queue<int> WFS_queue;
        result.insert(cvert+1);
        WFS_queue.push(cvert);
        is_visited[cvert] = true;
        while(!WFS_queue.empty())
        {
            int curr_vert = WFS_queue.front();
            WFS_queue.pop();
            for(auto i = vertices[curr_vert].begin(); i!=vertices[curr_vert].end(); i++)
            {
                if(is_visited[*i] == true)
                    continue;
                WFS_queue.push(*i);
                result.insert(*i+1);
                is_visited[*i]=true;
            } 
        }
        return result;
    }
    unordered_set<int> DFS(int cvert) {
    unordered_set<int> result;
    stack<int> DFS_stack;
    DFS_stack.push(cvert);
    is_visited[cvert] = true;

    while (!DFS_stack.empty()) {
        int curr = DFS_stack.top();
        DFS_stack.pop();  // Снимаем вершину со стека (а не внутри цикла по соседям!)

        // Добавляем вершину в результат (если нужно — можно было добавить при push)
        result.insert(curr+1);

        // Перебираем всех соседей curr
        for (int neighbor : vertices[curr]) {
            // Если сосед ещё не посещён
            if (!is_visited[neighbor]) {
                is_visited[neighbor] = true;
                DFS_stack.push(neighbor);
            }
        }
    }
    return result;
}
    vector<unordered_set<int>> find_all_companents_WFS()
    {
        vector<unordered_set<int>> result;
        for(int cvert = 0; cvert < number_of_vertices; cvert++)
        {
            if(!is_visited[cvert])
            {
                result.push_back(WFS(cvert));
            }
        }
        return result;
    }
    vector<unordered_set<int>> find_all_companents_DFS()
    {
        vector<unordered_set<int>> result;
        for(int cvert = 0; cvert < number_of_vertices; cvert++)
        {
            if(!is_visited[cvert])
            {
                result.push_back(DFS(cvert));
            }
        }
        return result;
    }
    int get_number_of_vertices()
    {
        return number_of_vertices;
    }
    int get_number_of_edges()
    {
        return number_of_edges;
    }
};


int main()
{
    Graph haha(cin);
    vector<unordered_set<int>> result = haha.find_all_companents_DFS();
    cout << result.size() << '\n';
    for(auto i = 0; i < result.size(); i++)
    {
        cout << result[i].size() << '\n';
        for(auto j = result[i].begin(); j!= result[i].end(); j++)
        {
            cout << *j << ' ';
        }
        cout << '\n';
    }
    return 0;
}