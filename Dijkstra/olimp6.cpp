#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

class Graph {

    struct Point {
        Point() : num(0), value(1e9), from(-1) {}
        Point(int n, int s, int r) : num(n), value(s), from(r) {}
        int num;
        int value;
        int from;
        bool operator<(const Point& other) const {
            return value > other.value;
        }
    };

    int N, start, end;
    bool* visited;
    int** A;
    vector<Point> points;

public:
    Graph() : N(0), end(0), start(0) {}

    void show_matrix() {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
    }

    void dijkstra() {
        priority_queue<Point> Q;
        points[start].value = 0;
        points[start].num = start;
        Q.push(points[start]);

        while(!Q.empty()) {
            Point top = Q.top();
            Q.pop();

            if(visited[top.num]) continue;
            visited[top.num] = true;

            for(int i = 0; i < N; ++i) {
                if (i == top.num || A[top.num][i] == -1) continue;
                if(top.value + A[top.num][i] < points[i].value) {
                    points[i].value = top.value + A[top.num][i];
                    points[i].num = i;
                    points[i].from = top.num;
                    Q.push(points[i]);
                }
            }
        }
    }

    void way_value(ostream& out) {
        if (start == end) {
            out << 0 << endl;
            return;
        }
        if (points[end].from == -1) {
            out << -1 << endl;
            return;
        }
        out << points[end].value << endl;
    }

    void way(ostream& out) {
        if (start == end) {
            out << (start + 1) << endl;
            return;
        }
        if (points[end].from == -1) {
            out << -1 << endl;
            return;
        }
        int curr = end;
        stack<int> v;
        while (curr != start) {
            v.push(curr);
            curr = points[curr].from;
        }
        out << (start + 1) << " ";
        while(!v.empty()) {
            out << (v.top() + 1) << " ";
            v.pop();
        }
        out << endl;
    }

    void show_p() {
        for(int i = 0; i < N; ++i) {
            cout << (i + 1) << "\t"
                 << points[i].value << "\t"
                 << (points[i].from != -1 ? points[i].from + 1 : -1) << endl;
        }
    }

    ~Graph() {
        for(int i = 0; i < N; ++i) {
            delete[] A[i];
        }
        delete[] A;
        delete[] visited;
    }

    friend istream& operator>> (istream& in, Graph& obj);
};

istream& operator>> (istream& in, Graph& obj) {
    in >> obj.N >> obj.start >> obj.end;
    obj.start--;
    obj.end--;
    obj.points.resize(obj.N);
    obj.visited = new bool[obj.N]{false};
    obj.A = new int*[obj.N];
    for(int i = 0; i < obj.N; ++i) {
        obj.A[i] = new int[obj.N];
    }
    int num;
    for(int i = 0; i < obj.N; ++i) {
        for (int j = 0; j < obj.N; ++j) {
            in >> num;
            obj.A[i][j] = num;
        }
    }
    return in;
}

int main() {
    ifstream fin("input.txt");
    if(!fin.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    Graph W;
    fin >> W;
    W.dijkstra();
    //W.way_value(cout);
    W.way(cout);
    return 0;
}
