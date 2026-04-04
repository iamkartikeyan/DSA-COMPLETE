/*
 * File: 02_BST_Search.cpp
 * Topic: Search in BST (Recursive + Iterative)
 * Description: Find a key in BST using BST property
 */
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

// Recursive search
TreeNode* searchBST(TreeNode* root, int key) {
    // base case: not found
    if (root == NULL) {
        return NULL;
    }
    // key found
    if (root->val == key) {
        return root;
    }
    // key is smaller, go left
    if (key < root->val) {
        return searchBST(root->left, key);
    }
    // key is larger, go right
    return searchBST(root->right, key);
}

// Iterative search (no recursion, uses less memory)
TreeNode* searchBSTIter(TreeNode* root, int key) {
    while (root != NULL) {
        if (root->val == key) {
            return root; // found
        }
        if (key < root->val) {
            root = root->left; // go left
        } else {
            root = root->right; // go right
        }
    }
    return NULL; // not found
}

int main() {
    /*
     * BST:
     *         50
     *       /    \
     *     30      70
     *    /  \    /  \
     *  20   40  60   80
     */
    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(30);
    root->right = new TreeNode(70);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(40);
    root->right->left = new TreeNode(60);
    root->right->right = new TreeNode(80);

    cout << "=== BST Search ===" << endl;
    cout << endl;

    // Search using recursion
    cout << "--- Recursive Search ---" << endl;
    int key1 = 40;
    TreeNode* found = searchBST(root, key1);
    if (found != NULL) {
        cout << "Search " << key1 << ": Found (value = " << found->val << ")" << endl;
    } else {
        cout << "Search " << key1 << ": Not found" << endl;
    }

    int key2 = 99;
    found = searchBST(root, key2);
    if (found != NULL) {
        cout << "Search " << key2 << ": Found" << endl;
    } else {
        cout << "Search " << key2 << ": Not found" << endl;
    }

    cout << endl;

    // Search using iteration
    cout << "--- Iterative Search ---" << endl;
    int key3 = 60;
    found = searchBSTIter(root, key3);
    if (found != NULL) {
        cout << "Search " << key3 << ": Found (value = " << found->val << ")" << endl;
    } else {
        cout << "Search " << key3 << ": Not found" << endl;
    }

    cout << endl;
    cout << "How it works:" << endl;
    cout << "  1. Compare key with current node" << endl;
    cout << "  2. If equal -> found" << endl;
    cout << "  3. If smaller -> go left" << endl;
    cout << "  4. If larger -> go right" << endl;
    cout << "  5. Repeat until found or reach NULL" << endl;
    cout << endl;
    cout << "Time: O(log n) balanced, O(n) skewed" << endl;

    // Free memory
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right->left;
    delete root->right->right;
    delete root->right;
    delete root;

    return 0;
}
