/*
 * File: 01_BST_Basics.cpp
 * Topic: BST Node + BST Property
 * Description: What is BST, left < root < right rule
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
    /*
     * BST Property:
     *   - Left subtree values < root value
     *   - Right subtree values > root value
     *   - This applies to EVERY node, not just root
     *
     * Example Valid BST:
     *         50
     *       /    \
     *     30      70
     *    /  \    /  \
     *  20   40  60   80
     *
     * All values in left subtree of 50 are < 50
     * All values in right subtree of 50 are > 50
     */

    cout << "=== Binary Search Tree (BST) ===" << endl;
    cout << endl;
    cout << "BST Property:" << endl;
    cout << "  - Left child value < Parent value" << endl;
    cout << "  - Right child value > Parent value" << endl;
    cout << "  - Applies to EVERY node in tree" << endl;
    cout << endl;
    cout << "Example BST:" << endl;
    cout << "          50" << endl;
    cout << "        /    \\" << endl;
    cout << "      30      70" << endl;
    cout << "     /  \\    /  \\" << endl;
    cout << "   20   40  60   80" << endl;
    cout << endl;
    cout << "Benefits:" << endl;
    cout << "  - Search in O(log n) on balanced tree" << endl;
    cout << "  - Insert in O(log n) on balanced tree" << endl;
    cout << "  - Delete in O(log n) on balanced tree" << endl;
    cout << "  - Inorder traversal gives SORTED order" << endl;

    // Creating a simple BST
    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(30);
    root->right = new TreeNode(70);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(40);
    root->right->left = new TreeNode(60);
    root->right->right = new TreeNode(80);

    cout << endl;
    cout << "BST created successfully." << endl;
    cout << "Root value: " << root->val << endl;
    cout << "Left child of root: " << root->left->val << endl;
    cout << "Right child of root: " << root->right->val << endl;

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
