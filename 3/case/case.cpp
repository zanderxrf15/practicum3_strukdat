#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key, height;
    Node *left, *right;
    Node(int k) : key(k), height(1), left(NULL), right(NULL) {}
};

int height(Node* n) {
    if (n == NULL) return 0;
    return n->height;
}

int getBalance(Node* n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* root, int key) {
    if (root == NULL) return new Node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key) return rightRotate(root);
    if (balance < -1 && key > root->right->key) return leftRotate(root);
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(Node* root, int col, map<int, int>& m) {
    if (root == NULL) return;

    inorder(root->left, col - 1, m);
    m[col] += root->key;
    inorder(root->right, col + 1, m);
}

int main() {
    int N;
    cin >> N;

    Node* root = NULL;
    for (int i = 0; i < N; i++) {
        string command;
        cin >> command;
        if (command == "insert") {
            int X;
            cin >> X;
            root = insert(root, X);
        }
        else if (command == "solve") {
            map<int, int> m;
            inorder(root, 0, m);
            for (auto it = m.begin(); it != m.end(); it++) {
                cout << it->second << " ";
            }
            cout << endl;
        }
    }
}
