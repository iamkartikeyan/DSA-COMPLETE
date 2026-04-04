/*
 * File: 06_Tree_Types.cpp
 * Topic: Full Tree, Balanced Tree
 * Description: Check if a tree is Full or Balanced
 */
#include <iostream>
#include <cmath>
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

// Get height
int getHeight(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    return 1 + max(lh, rh);
}

// Check if Full Tree (every node has 0 or 2 children)
bool isFullTree(TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    // Leaf node
    if (root->left == NULL && root->right == NULL) {
        return true;
    }
    // Both children exist
    if (root->left != NULL && root->right != NULL) {
        return isFullTree(root->left) && isFullTree(root->right);
    }
    // Only one child - not full
    return false;
}

// Check if Balanced Tree (height diff <= 1 at every node)
bool isBalanced(TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    int diff = abs(lh - rh);

    if (diff > 1) {
        return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
}

int main() {
    /*
     * Tree (Full + Balanced):
     *       1
     *     /   \
     *    2     3
     *   / \   / \
     *  4   5 6   7
     */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    cout << "--- Tree Type Checks ---" << endl;

    if (isFullTree(root)) {
        cout << "Full Tree:     Yes" << endl;
    } else {
        cout << "Full Tree:     No" << endl;
    }

    if (isBalanced(root)) {
        cout << "Balanced Tree: Yes" << endl;
    } else {
        cout << "Balanced Tree: No" << endl;
    }

    cout << endl;
    cout << "--- Definitions ---" << endl;
    cout << "Full:     Every node has 0 or 2 children" << endl;
    cout << "Complete: All levels filled except last; last level is left-filled" << endl;
    cout << "Perfect:  All leaves at same depth; every internal node has 2 children" << endl;
    cout << "Balanced: Height difference of left and right subtree <= 1" << endl;

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
