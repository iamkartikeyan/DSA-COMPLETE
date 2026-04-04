/*
 * File: 01_Node_Structure.cpp
 * Topic: Binary Tree Node - Structure and Constructor
 * Description: Basic node structure for binary tree
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

int main() {
    // Creating a simple node
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);

    cout << "Root: " << root->val << endl;
    cout << "Left child: " << root->left->val << endl;
    cout << "Right child: " << root->right->val << endl;

    // Free memory
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
