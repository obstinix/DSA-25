#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAX = 100;
float e[MAX][MAX], w[MAX][MAX];
int root[MAX][MAX];

void optimalBST(vector<float>& p, int n) {
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = 0;
        w[i][i - 1] = 0;
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j - 1] + p[j];

            for (int r = i; r <= j; r++) {
                float t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << fixed << setprecision(3);
    cout << "\nMinimum cost of Optimal BST: " << e[1][n] << "\n";
}

void printTree(int i, int j, int parent, string relation) {
    if (i > j) return;
    int r = root[i][j];
    if (parent == -1)
        cout << "Root: k" << r << "\n";
    else
        cout << "k" << r << " is " << relation << " child of k" << parent << "\n";

    printTree(i, r - 1, r, "left");
    printTree(r + 1, j, r, "right");
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    vector<float> p(n + 1); // 1-based indexing

    cout << "Enter access probabilities for keys (p1 to pn):\n";
    for (int i = 1; i <= n; i++) {
        cout << "p[" << i << "] = ";
        cin >> p[i];
    }

    optimalBST(p, n);
    cout << "\nStructure of Optimal BST:\n";
    printTree(1, n, -1, "");

    return 0;
}
