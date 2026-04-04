/*
 * File: 03_AVL_Insert.cpp
 * Topic: Insert with AVL rebalancing (4 cases)
 * Description: BST insert + check balance + rotate if needed
 */
#include <iostream>
#include <cmath>
using namespace std;

struct AVLNode {
    int key;
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(int k) {
        key = k;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int getHeight(AVLNode* n) {
    if (n == NULL) return 0;
    return n->height;
}

void updateHeight(AVLNode* n) {
    if (n == NULL) return;
    int lh = getHeight(n->left);
    int rh = getHeight(n->right);
    n->height = 1 + max(lh, rh);
}

int getBalance(AVLNode* n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// Right Rotation
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// Left Rotation
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Insert with AVL rebalancing
AVLNode* insertAVL(AVLNode* node, int key) {
    // Step 1: Normal BST insert
    if (node == NULL) {
        return new AVLNode(key);
    }
    if (key < node->key) {
        node->left = insertAVL(node->left, key);
    }
    else if (key > node->key) {
        node->right = insertAVL(node->right, key);
    }
    else {
        return node; // duplicate keys not allowed
    }

    // Step 2: Update height
    updateHeight(node);

    // Step 3: Check balance
    int balance = getBalance(node);

    // Step 4: Rotate if unbalanced

    // LL Case: left heavy, key in left subtree of left child
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    // RR Case: right heavy, key in right subtree of right child
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    // LR Case: left heavy, key in right subtree of left child
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // RL Case: right heavy, key in left subtree of right child
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; // already balanced
}

// Inorder traversal
void inorderAVL(AVLNode* root) {
    if (root == NULL) return;
    inorderAVL(root->left);
    cout << root->key << " ";
    inorderAVL(root->right);
}

// Free tree
void deleteTree(AVLNode* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    cout << "=== AVL Tree Insert ===" << endl;
    cout << endl;

    AVLNode* root = NULL;
    int values[] = {10, 20, 30, 40, 50, 25};
    int n = 6;

    cout << "Inserting: 10 20 30 40 50 25" << endl;
    cout << endl;

    for (int i = 0; i < n; i++) {
        root = insertAVL(root, values[i]);
    }

    cout << "Inorder (sorted): ";
    inorderAVL(root);
    cout << endl;
    cout << endl;

    /*
     * Final AVL Tree after inserting [10, 20, 30, 40, 50, 25]:
     *
     *         30
     *       /    \
     *     20      40
     *    /  \       \
     *   10   25      50
     *
     * Tree stays balanced after every insert!
     */
    cout << "Resulting AVL Tree:" << endl;
    cout << "         30" << endl;
    cout << "       /    \\" << endl;
    cout << "     20      40" << endl;
    cout << "    /  \\       \\" << endl;
    cout << "   10   25      50" << endl;
    cout << endl;

    cout << "Rotations that happened:" << endl;
    cout << "  Insert 30 -> RR rotation at 10" << endl;
    cout << "  Insert 40 -> RR rotation at 20" << endl;
    cout << "  Insert 50 -> RR rotation at 30" << endl;
    cout << "  Insert 25 -> LR rotation at 40" << endl;
    cout << endl;
    cout << "Time: O(log n) for each insert" << endl;

    deleteTree(root);

    return 0;
}
