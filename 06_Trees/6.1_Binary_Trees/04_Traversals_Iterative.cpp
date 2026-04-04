/*
 * File: 04_Traversals_Iterative.cpp
 * Topic: Inorder using Stack (no recursion)
 * Description: Iterative inorder traversal
 */
#include <iostream>
#include <stack>
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

// Inorder without recursion using stack
void inorderIterative(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;

    while (curr != NULL || st.empty() == false) {
        // Go to leftmost node
        while (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        }

        // Process node
        curr = st.top();
        st.pop();
        cout << curr->val << " ";

        // Go to right
        curr = curr->right;
    }
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

    cout << "Inorder (Iterative): ";
    inorderIterative(root);
    cout << endl;

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
