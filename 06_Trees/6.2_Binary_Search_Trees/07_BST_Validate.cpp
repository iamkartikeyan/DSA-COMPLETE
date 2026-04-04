/*
 * File: 07_BST_Validate.cpp
 * Topic: Check if a tree is a valid BST
 * Description: Use min/max bounds to verify BST property
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

// Check BST using min/max range
// Every node must be within (minVal, maxVal)
bool isValidBST(TreeNode* root, long long minVal, long long maxVal) {
    // empty tree is valid BST
    if (root == NULL) {
        return true;
    }

    // current node violates BST property
    if (root->val <= minVal || root->val >= maxVal) {
        return false;
    }

    // check left subtree (must be < root->val)
    // check right subtree (must be > root->val)
    return isValidBST(root->left, minVal, root->val) &&
           isValidBST(root->right, root->val, maxVal);
}

// Wrapper function with default values
bool isValidBST(TreeNode* root) {
    return isValidBST(root, -9999999999, 9999999999);
}

// Free tree
void deleteTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    cout << "=== BST Validation ===" << endl;
    cout << endl;

    /*
     * Valid BST:
     *         50
     *       /    \
     *     30      70
     *    /  \    /  \
     *  20   40  60   80
     */
    TreeNode* valid = new TreeNode(50);
    valid->left = new TreeNode(30);
    valid->right = new TreeNode(70);
    valid->left->left = new TreeNode(20);
    valid->left->right = new TreeNode(40);
    valid->right->left = new TreeNode(60);
    valid->right->right = new TreeNode(80);

    cout << "--- Valid BST Test ---" << endl;
    cout << "Tree: 50, 30, 70, 20, 40, 60, 80" << endl;
    if (isValidBST(valid)) {
        cout << "Result: Valid BST" << endl;
    } else {
        cout << "Result: NOT a valid BST" << endl;
    }

    cout << endl;

    /*
     * Invalid BST:
     *         10
     *       /    \
     *      5      15
     *       \
     *        20    <- 20 is in left subtree but > 10!
     */
    TreeNode* invalid = new TreeNode(10);
    invalid->left = new TreeNode(5);
    invalid->right = new TreeNode(15);
    invalid->left->right = new TreeNode(20);

    cout << "--- Invalid BST Test ---" << endl;
    cout << "Tree: 10, 5, 15, 20 (20 in left subtree of 10)" << endl;
    if (isValidBST(invalid)) {
        cout << "Result: Valid BST" << endl;
    } else {
        cout << "Result: NOT a valid BST" << endl;
    }

    cout << endl;
    cout << "How it works:" << endl;
    cout << "  1. Every node has a valid range (min, max)" << endl;
    cout << "  2. Root can be any value (-infinity to +infinity)" << endl;
    cout << "  3. Left child must be < parent" << endl;
    cout << "  4. Right child must be > parent" << endl;
    cout << "  5. Range narrows as we go deeper" << endl;

    deleteTree(valid);
    deleteTree(invalid);

    return 0;
}
