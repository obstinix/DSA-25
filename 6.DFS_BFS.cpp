#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 6;
string landmark[MAX] = {
    "College Main Gate", "Library", "Cafeteria", 
    "Auditorium", "Hostel", "Sports Complex"
};

int adjMatrix[MAX][MAX] = {0};

vector<int> adjList[MAX];

bool visitedDFS[MAX];
bool visitedBFS[MAX];

void createGraph() {

    int edges[][2] = {
        {0, 1}, {0, 2}, {1, 3},
        {2, 4}, {4, 5}, {3, 5}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    for (int i = 0; i < numEdges; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adjMatrix[u][v] = adjMatrix[v][u] = 1;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

void DFS(int node) {
    visitedDFS[node] = true;
    cout << landmark[node] << " -> ";

    for (int i = 0; i < MAX; i++) {
        if (adjMatrix[node][i] && !visitedDFS[i]) {
            DFS(i);
        }
    }
}

void BFS(int start) {
    queue<int> q;
    visitedBFS[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front(); q.pop();
        cout << landmark[node] << " -> ";

        for (int neighbor : adjList[node]) {
            if (!visitedBFS[neighbor]) {
                visitedBFS[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    createGraph();

    cout << "DFS Traversal (using Adjacency Matrix) starting from College Main Gate:\n";
    for (int i = 0; i < MAX; i++) visitedDFS[i] = false;
    DFS(0);
    cout << "END\n\n";

    cout << "BFS Traversal (using Adjacency List) starting from College Main Gate:\n";
    for (int i = 0; i < MAX; i++) visitedBFS[i] = false;
    BFS(0);
    cout << "END\n";

    return 0;
}
