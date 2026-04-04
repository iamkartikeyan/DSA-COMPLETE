/*
 * File: 01_AVL_Node_and_Height.cpp
 * Topic: AVL Tree Node + Height + Balance Factor
 * Description: Basic AVL structure and helper functions
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

// Get height of a node (0 if NULL)
int getHeight(AVLNode* n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

// Update height using children heights
void updateHeight(AVLNode* n) {
    if (n == NULL) {
        return;
    }
    int lh = getHeight(n->left);
    int rh = getHeight(n->right);
    n->height = 1 + max(lh, rh);
}

// Balance factor = left height - right height
int getBalance(AVLNode* n) {
    if (n == NULL) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

int main() {
    /*
     * AVL Tree:
     *   - Self-balancing BST
     *   - Balance factor must be -1, 0, or 1 at every node
     *   - If balance factor goes outside this range, rotate to fix
     *
     * Balance Factor = height(left) - height(right)
     *
     * Positive = left-heavy
     * Negative = right-heavy
     */

    cout << "=== AVL Tree - Node Structure ===" << endl;
    cout << endl;

    // Create a simple tree
    AVLNode* root = new AVLNode(10);
    root->left = new AVLNode(5);
    root->right = new AVLNode(20);
    root->left->left = new AVLNode(3);

    // Update heights bottom-up
    updateHeight(root->left);
    updateHeight(root);

    cout << "Root (10): height = " << getHeight(root)
         << ", balance = " << getBalance(root) << endl;
    cout << "Left child (5): height = " << getHeight(root->left)
         << ", balance = " << getBalance(root->left) << endl;
    cout << "Right child (20): height = " << getHeight(root->right)
         << ", balance = " << getBalance(root->right) << endl;

    cout << endl;
    cout << "AVL Rule: balance factor must be -1, 0, or 1" << endl;
    cout << "If balance > 1 or < -1 -> tree is unbalanced -> need rotation" << endl;

    // Free memory
    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
