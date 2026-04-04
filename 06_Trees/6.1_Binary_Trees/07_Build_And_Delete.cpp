/*
 * File: 07_Build_And_Delete.cpp
 * Topic: Build a sample tree, delete it safely
 * Description: How to create and free tree memory
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

// Delete tree using postorder (children first, then parent)
void deleteTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Build this tree:
//         1
//       /   \
//      2     3
//     / \   / \
//    4   5 6   7
TreeNode* buildSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    return root;
}

int main() {
    cout << "=== Build and Delete Tree ===" << endl;
    cout << endl;

    TreeNode* root = buildSampleTree();

    cout << "Tree created:" << endl;
    cout << "        1" << endl;
    cout << "      /   \\" << endl;
    cout << "     2     3" << endl;
    cout << "    / \\   / \\" << endl;
    cout << "   4   5 6   7" << endl;
    cout << endl;

    cout << "Root value: " << root->val << endl;
    cout << "Deleting tree safely using postorder..." << endl;

    deleteTree(root);

    cout << "Tree deleted. No memory leak." << endl;

    return 0;
}
