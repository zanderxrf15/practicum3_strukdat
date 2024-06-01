#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

struct Node {
    int key, height;
    long long cnt;
    Node *left, *right;

    Node(int key) {
        this->key = key;
        height = 1;
        cnt = 1;
        left = right = nullptr;
    }

    int get_height() {
        return height;
    }

    long long get_cnt() {
        return cnt;
    }

    int get_balance_factor() {
        int left_height = (left != nullptr) ? left->height : 0;
        int right_height = (right != nullptr) ? right->height : 0;
        return right_height - left_height;
    }

    void update() {
        int left_height = (left != nullptr) ? left->height : 0;
        int right_height = (right != nullptr) ? right->height : 0;
        height = max(left_height, right_height) + 1;
        long long left_cnt = (left != nullptr) ? left->cnt : 0;
        long long right_cnt = (right != nullptr) ? right->cnt : 0;
        cnt = (left_cnt + right_cnt + 1) % mod;
    }

    Node* rotate_left() {
        Node* new_root = right;
        right = new_root->left;
        new_root->left = this;
        update();
        new_root->update();
        return new_root;
    }

    Node* rotate_right() {
        Node* new_root = left;
        left = new_root->right;
        new_root->right = this;
        update();
        new_root->update();
        return new_root;
    }

    Node* balance() {
        update();
        int balance_factor = get_balance_factor();
        if (balance_factor == 2) {
            if (right->get_balance_factor() < 0) {
                right = right->rotate_right();
            }
            return rotate_left();
        } else if (balance_factor == -2) {
            if (left->get_balance_factor() > 0) {
                left = left->rotate_left();
            }
            return rotate_right();
        }
        return this;
    }
};

Node* insert(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else {
        node->right = insert(node->right, key);
    }
    return node->balance();
}

long long counts_less_or_equal(Node* node, int key) {
    if (node == nullptr) {
        return 0;
    }
    if (key < node->key) {
        return counts_less_or_equal(node->left, key);
    }
    long long left_count = (node->left != nullptr) ? node->left->cnt : 0;
    long long right_count = counts_less_or_equal(node->right, key);
    return (left_count + right_count + 1) % mod;
}

int main() {
int N;
cin >> N;
vector<int> a(N);
for (int i = 0; i < N; i++) {
cin >> a[i];
}
Node* root = nullptr;
long long answer = 0;
for (int i = N - 1; i >= 0; i--) {
    answer = (answer + counts_less_or_equal(root, a[i])) % mod;
    root = insert(root, a[i]);
}
cout << (answer + 1) % mod << endl;
}
