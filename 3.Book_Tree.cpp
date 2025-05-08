#include<iostream>
using namespace std;

class node {
public:
    int data;
    node* link[10];
};

class Tree {
public:
    void insertChap(node*);
    void insertSec(node*);
    void insertSubSec(node*);
    void display(node*);
};

void Tree::insertChap(node* root) {
    int chap;
    cout << "\nEnter number of chapters in the book: ";
    cin >> chap;

    for (int i = 0; i < chap; i++) {
        node* n = new node;
        n->data = i + 1;
        for (int j = 0; j < 10; j++)
            n->link[j] = NULL;

        root->link[i] = n;
        insertSec(n);
    }
}

void Tree::insertSec(node* root) {
    int sec;
    cout << "\nEnter number of sections in chapter " << root->data << ": ";
    cin >> sec;

    for (int i = 0; i < sec; i++) {
        node* n = new node;
        n->data = i + 1;
        for (int j = 0; j < 10; j++)
            n->link[j] = NULL;

        root->link[i] = n;
        insertSubSec(n);
    }
}

void Tree::insertSubSec(node* root) {
    int subsec;
    cout << "\nEnter number of subsections in section " << root->data << ": ";
    cin >> subsec;

    for (int i = 0; i < subsec; i++) {
        node* n = new node;
        n->data = i + 1;
        for (int j = 0; j < 10; j++)
            n->link[j] = NULL;

        root->link[i] = n;
    }
}

void Tree::display(node* root) {
    if (root) {
        cout << "\nBook Index:\n";
        for (int i = 0; root->link[i] != NULL; i++) {
            node* ch = root->link[i];
            cout << "\nChapter " << ch->data;

            for (int j = 0; ch->link[j] != NULL; j++) {
                node* s = ch->link[j];
                cout << "\n  Section " << ch->data << "." << s->data;

                for (int k = 0; s->link[k] != NULL; k++) {
                    node* p = s->link[k];
                    cout << "\n    Subsection " << ch->data << "." << s->data << "." << p->data;
                }
            }
        }
    }
}

int main() {
    node* root = new node;
    root->data = 0;
    for (int i = 0; i < 10; i++)
        root->link[i] = NULL;

    Tree t;
    t.insertChap(root);
    t.display(root);

    return 0;
}
