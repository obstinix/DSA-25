#include <iostream>
#include <cstring>
using namespace std;

class Node {
public:
    int data;
    int weight;
    Node* next;
};

class Graph {
public:
    Node* head[50];
    int visited[50], span_V[50], no;
    char officeNames[50][20]; // array of office names
    int officeCount;

    Graph() {
        officeCount = 0;
        for (int i = 0; i < 50; i++) {
            head[i] = nullptr;
            visited[i] = 0;
            span_V[i] = -1;
        }
    }

    void insertOffice(char name[]) {
        strcpy(officeNames[officeCount], name);
        officeCount++;
    }

    int getOfficeIndex(char name[]) {
        for (int i = 0; i < officeCount; i++) {
            if (strcmp(officeNames[i], name) == 0)
                return i;
        }
        return -1; // not found
    }

    void insertEdge(char name1[], char name2[], int weight) {
        int v1 = getOfficeIndex(name1);
        int v2 = getOfficeIndex(name2);
        addEdge(v1, v2, weight);
        addEdge(v2, v1, weight); // undirected graph
    }

    void addEdge(int from, int to, int weight) {
        Node* temp = new Node;
        temp->data = to;
        temp->weight = weight;
        temp->next = head[from];
        head[from] = temp;
    }

    int get_min_edge(int& from, int& to) {
        int min_wt = 100000;
        from = to = -1;
        for (int i = 0; span_V[i] != -1; i++) {
            int u = span_V[i];
            Node* p = head[u];
            while (p != NULL) {
                if (!visited[p->data] && p->weight < min_wt) {
                    min_wt = p->weight;
                    from = u;
                    to = p->data;
                }
                p = p->next;
            }
        }
        return min_wt;
    }

    void primsAlgo(char startName[]) {
        int start = getOfficeIndex(startName);
        int j = 0, cost = 0;
        span_V[j++] = start;
        visited[start] = 1;

        cout << "\nMinimum Spanning Tree:\n";

        for (int i = 0; i < no - 1; i++) {
            int from, to;
            int wt = get_min_edge(from, to);
            if (to == -1) break;

            span_V[j++] = to;
            visited[to] = 1;
            cost += wt;

            cout << officeNames[from] << " -> " << officeNames[to] << " [Cost: " << wt << "]\n";
        }

        cout << "\nTotal Minimum Cost to Connect All Offices: " << cost << "\n";
    }
};

int main() {
    Graph g;
    char name1[20], name2[20], ch;
    int edgeCost;

    cout << "Enter number of offices: ";
    cin >> g.no;

    cout << "Enter names of the offices:\n";
    for (int i = 0; i < g.no; i++) {
        cin >> name1;
        g.insertOffice(name1);
    }

    do {
        cout << "\nEnter connection (Office1 Office2 Cost): ";
        cin >> name1 >> name2 >> edgeCost;
        g.insertEdge(name1, name2, edgeCost);

        cout << "Do you want to enter more connections? (y/n): ";
        cin >> ch;
    } while (ch == 'y');

    cout << "\nEnter starting office: ";
    cin >> name1;
    g.primsAlgo(name1);

    return 0;
}
