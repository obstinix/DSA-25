#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;

    Node(string key, string mean) {
        keyword = key;
        meaning = mean;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    Node* insert(Node* node, string key, string mean) {
        if (!node) return new Node(key, mean);
        if (key < node->keyword)
            node->left = insert(node->left, key, mean);
        else if (key > node->keyword)
            node->right = insert(node->right, key, mean);
        else {
            cout << "Keyword already exists. Use update instead.\n";
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Balancing cases
        if (balance > 1 && key < node->left->keyword)
            return rotateRight(node);
        if (balance < -1 && key > node->right->keyword)
            return rotateLeft(node);
        if (balance > 1 && key > node->left->keyword) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->keyword) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left) current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, string key) {
        if (!root) return root;

        if (key < root->keyword)
            root->left = deleteNode(root->left, key);
        else if (key > root->keyword)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        if (!root) return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);

        // Rebalance
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->keyword << " : " << root->meaning << endl;
            inorder(root->right);
        }
    }

    void reverseInorder(Node* root) {
        if (root) {
            reverseInorder(root->right);
            cout << root->keyword << " : " << root->meaning << endl;
            reverseInorder(root->left);
        }
    }

    Node* update(Node* root, string key, string newMean) {
        if (!root) return nullptr;
        if (key == root->keyword) {
            root->meaning = newMean;
            cout << "Meaning updated.\n";
        } else if (key < root->keyword)
            update(root->left, key, newMean);
        else
            update(root->right, key, newMean);
        return root;
    }

    void search(Node* root, string key, int& comparisons) {
        if (!root) {
            cout << "Keyword not found.\n";
            return;
        }
        comparisons++;
        if (key == root->keyword)
            cout << "Found: " << root->keyword << " = " << root->meaning << endl;
        else if (key < root->keyword)
            search(root->left, key, comparisons);
        else
            search(root->right, key, comparisons);
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(string key, string mean) {
        root = insert(root, key, mean);
    }

    void remove(string key) {
        root = deleteNode(root, key);
    }

    void update(string key, string newMean) {
        root = update(root, key, newMean);
    }

    void displayAscending() {
        cout << "\nDictionary in Ascending Order:\n";
        inorder(root);
    }

    void find(string key) {
        int comparisons = 0;
        search(root, key, comparisons);
        cout << "Comparisons made: " << comparisons << endl;
    }

    void maxComparisons() {
        cout << "Maximum comparisons (height): " << getHeight(root) << endl;
    }
};

int main() {
    AVLTree dict;
    int ch;
    string key, mean;

    do {
        cout << "\n----- Dictionary Menu -----\n";
        cout << "1. Insert\n2. Delete\n3. Update\n4. Display Ascending\n5. Display Descending\n6. Search\n7. Max Comparisons\n8. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;
        cin.ignore();

        switch (ch) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, mean);
                dict.insert(key, mean);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                dict.remove(key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, mean);
                dict.update(key, mean);
                break;
            case 4:
                dict.displayAscending();
                break;
            case 5:
                dict.displayDescending();
                break;
            case 6:
                cout << "Enter keyword to search: ";
                getline(cin, key);
                dict.find(key);
                break;
            case 7:
                dict.maxComparisons();
                break;
            case 8:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (ch != 8);

    return 0;
}
