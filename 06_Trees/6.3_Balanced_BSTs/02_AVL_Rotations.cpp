/*
 * File: 02_AVL_Rotations.cpp
 * Topic: Four Rotation Types (LL, RR, LR, RL)
 * Description: Right rotation, Left rotation, and combinations
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

// Right Rotation (fixes LL case - left-left heavy)
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights (y first, then x)
    updateHeight(y);
    updateHeight(x);

    return x; // new root
}

// Left Rotation (fixes RR case - right-right heavy)
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights (x first, then y)
    updateHeight(x);
    updateHeight(y);

    return y; // new root
}

void printTree(AVLNode* root, string indent, bool last) {
    if (root == NULL) return;
    cout << indent;
    if (last) {
        cout << "R----";
        indent += "     ";
    } else {
        cout << "L----";
        indent += "|    ";
    }
    cout << root->key << " (h=" << root->height << ")" << endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
}

void deleteTree(AVLNode* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    cout << "=== AVL Tree Rotations ===" << endl;
    cout << endl;

    // --- Right Rotation (LL Case) ---
    cout << "--- Right Rotation (LL Case) ---" << endl;
    cout << "Before (left-left heavy):" << endl;
    cout << "    30" << endl;
    cout << "   /" << endl;
    cout << "  20" << endl;
    cout << " /" << endl;
    cout << "10" << endl;
    cout << endl;

    AVLNode* ll = new AVLNode(30);
    ll->left = new AVLNode(20);
    ll->left->left = new AVLNode(10);
    updateHeight(ll->left->left);
    updateHeight(ll->left);
    updateHeight(ll);

    cout << "After right rotation at 30:" << endl;
    cout << "  20" << endl;
    cout << " /  \\" << endl;
    cout << "10   30" << endl;
    cout << endl;

    AVLNode* llNew = rotateRight(ll);
    cout << "New root: " << llNew->key << endl;
    cout << "Left child: " << llNew->left->key << endl;
    cout << "Right child: " << llNew->right->key << endl;

    deleteTree(llNew);

    cout << endl;

    // --- Left Rotation (RR Case) ---
    cout << "--- Left Rotation (RR Case) ---" << endl;
    cout << "Before (right-right heavy):" << endl;
    cout << "10" << endl;
    cout << " \\" << endl;
    cout << "  20" << endl;
    cout << "   \\" << endl;
    cout << "    30" << endl;
    cout << endl;

    AVLNode* rr = new AVLNode(10);
    rr->right = new AVLNode(20);
    rr->right->right = new AVLNode(30);
    updateHeight(rr->right->right);
    updateHeight(rr->right);
    updateHeight(rr);

    cout << "After left rotation at 10:" << endl;
    cout << "  20" << endl;
    cout << " /  \\" << endl;
    cout << "10   30" << endl;
    cout << endl;

    AVLNode* rrNew = rotateLeft(rr);
    cout << "New root: " << rrNew->key << endl;
    cout << "Left child: " << rrNew->left->key << endl;
    cout << "Right child: " << rrNew->right->key << endl;

    deleteTree(rrNew);

    cout << endl;
    cout << "--- Summary ---" << endl;
    cout << "LL Case (left-left heavy)  -> Right Rotation" << endl;
    cout << "RR Case (right-right heavy) -> Left Rotation" << endl;
    cout << "LR Case (left-right heavy)  -> Left then Right" << endl;
    cout << "RL Case (right-left heavy)  -> Right then Left" << endl;

    return 0;
}
