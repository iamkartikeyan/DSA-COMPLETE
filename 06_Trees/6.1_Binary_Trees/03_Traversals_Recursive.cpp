/*
 * File: 03_Traversals_Recursive.cpp
 * Topic: Inorder, Preorder, Postorder (Recursive)
 * Description: Three depth-first traversal methods
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

// Inorder: Left -> Root -> Right
void inorder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// Preorder: Root -> Left -> Right
void preorder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder: Left -> Right -> Root
void postorder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

int main() {
    /*
     * Tree:
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

    cout << "Inorder:    ";
    inorder(root);
    cout << endl;

    cout << "Preorder:   ";
    preorder(root);
    cout << endl;

    cout << "Postorder:  ";
    postorder(root);
    cout << endl;

    cout << endl;
    cout << "--- Summary ---" << endl;
    cout << "Inorder:   Left -> Root -> Right   (BST gives sorted order)" << endl;
    cout << "Preorder:  Root -> Left -> Right   (useful to copy tree)" << endl;
    cout << "Postorder: Left -> Right -> Root   (useful to delete tree)" << endl;

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
