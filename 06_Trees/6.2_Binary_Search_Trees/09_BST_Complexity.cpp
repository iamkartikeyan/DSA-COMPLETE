/*
 * File: 09_BST_Complexity_Summary.cpp
 * Topic: BST Complexity, Properties, Summary
 * Description: Time complexity table and key BST facts
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

// Inorder traversal (BST -> sorted output)
void inorder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
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

    cout << "=== BST - Complexity & Summary ===" << endl;
    cout << endl;

    // Show sorted output
    cout << "Inorder traversal (always sorted in BST): ";
    inorder(root);
    cout << endl;

    cout << endl;
    cout << "--- Time Complexity ---" << endl;
    cout << endl;
    cout << "Operation  | Balanced Tree | Skewed Tree" << endl;
    cout << "-----------|---------------|------------" << endl;
    cout << "Search     |  O(log n)     |  O(n)" << endl;
    cout << "Insert     |  O(log n)     |  O(n)" << endl;
    cout << "Delete     |  O(log n)     |  O(n)" << endl;
    cout << "Min/Max    |  O(log n)     |  O(n)" << endl;
    cout << "LCA        |  O(log n)     |  O(n)" << endl;
    cout << "Inorder    |  O(n)         |  O(n)" << endl;

    cout << endl;
    cout << "--- Space Complexity ---" << endl;
    cout << "Recursive: O(h) call stack where h = tree height" << endl;
    cout << "Iterative: O(1) for search, O(n) for traversals" << endl;

    cout << endl;
    cout << "--- Key BST Facts ---" << endl;
    cout << "1. Left subtree < Root < Right subtree (for ALL nodes)" << endl;
    cout << "2. Inorder traversal ALWAYS gives sorted output" << endl;
    cout << "3. This is the defining property of BST" << endl;
    cout << "4. Balanced BST = O(log n) operations" << endl;
    cout << "5. Skewed BST degrades to O(n) (like a linked list)" << endl;
    cout << "6. AVL Trees and Red-Black Trees are self-balancing BSTs" << endl;

    cout << endl;
    cout << "--- BST Operations Covered ---" << endl;
    cout << "01. BST Basics          - Node structure + BST property" << endl;
    cout << "02. Search              - Recursive + Iterative" << endl;
    cout << "03. Insert              - Always as a leaf" << endl;
    cout << "04. Min/Max             - Leftmost / Rightmost node" << endl;
    cout << "05. Successor/Pred      - Next greater / Next smaller" << endl;
    cout << "06. Delete              - 3 cases (leaf, 1 child, 2 children)" << endl;
    cout << "07. Validate BST        - Min/max range check" << endl;
    cout << "08. LCA                 - Split point of two nodes" << endl;
    cout << "09. Complexity Summary  - This file" << endl;

    deleteTree(root);

    return 0;
}
