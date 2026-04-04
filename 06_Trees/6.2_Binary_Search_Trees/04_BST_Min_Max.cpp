/*
 * File: 04_BST_Min_Max.cpp
 * Topic: Find minimum and maximum value in BST
 * Description: Min = leftmost node, Max = rightmost node
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

// Find minimum (leftmost node)
TreeNode* findMin(TreeNode* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Find maximum (rightmost node)
TreeNode* findMax(TreeNode* root) {
    while (root != NULL && root->right != NULL) {
        root = root->right;
    }
    return root;
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

    cout << "=== BST Min/Max ===" << endl;
    cout << endl;

    TreeNode* minNode = findMin(root);
    cout << "Minimum value: " << minNode->val << endl;

    TreeNode* maxNode = findMax(root);
    cout << "Maximum value: " << maxNode->val << endl;

    cout << endl;
    cout << "How it works:" << endl;
    cout << "  Minimum: Keep going LEFT until you cannot" << endl;
    cout << "  Maximum: Keep going RIGHT until you cannot" << endl;
    cout << endl;
    cout << "In this tree:" << endl;
    cout << "  Min = 20 (leftmost node)" << endl;
    cout << "  Max = 80 (rightmost node)" << endl;
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
