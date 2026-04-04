/*
 * File: 05_Level_Order.cpp
 * Topic: Level Order Traversal (BFS using Queue)
 * Description: Visit tree level by level
 */
#include <iostream>
#include <queue>
#include <vector>
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

// Simple Level Order
void levelOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    queue<TreeNode*> q;
    q.push(root);

    while (q.empty() == false) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";

        if (node->left != NULL) {
            q.push(node->left);
        }
        if (node->right != NULL) {
            q.push(node->right);
        }
    }
}

// Level Order - level by level grouping
void levelOrderGrouped(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    int levelNum = 0;

    while (q.empty() == false) {
        int sz = q.size();
        cout << "  Level " << levelNum << ": ";

        while (sz > 0) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->val << " ";

            if (node->left != NULL) {
                q.push(node->left);
            }
            if (node->right != NULL) {
                q.push(node->right);
            }
            sz = sz - 1;
        }
        cout << endl;
        levelNum = levelNum + 1;
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

    cout << "Level Order: ";
    levelOrder(root);
    cout << endl;
    cout << endl;

    cout << "Level Order Grouped:" << endl;
    levelOrderGrouped(root);

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
