/*
 * File: 08_BST_LCA.cpp
 * Topic: Lowest Common Ancestor in BST
 * Description: Find the nearest common ancestor of two nodes
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

// Search in BST
TreeNode* searchBST(TreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->val == key) {
        return root;
    }
    if (key < root->val) {
        return searchBST(root->left, key);
    }
    return searchBST(root->right, key);
}

// Lowest Common Ancestor in BST
// LCA = first node where p and q split into different subtrees
TreeNode* LCA_BST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL) {
        return NULL;
    }

    // Both p and q are in left subtree
    if (p->val < root->val && q->val < root->val) {
        return LCA_BST(root->left, p, q);
    }

    // Both p and q are in right subtree
    if (p->val > root->val && q->val > root->val) {
        return LCA_BST(root->right, p, q);
    }

    // p and q are in different subtrees (or one equals root)
    // So root is the LCA
    return root;
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

    cout << "=== BST - Lowest Common Ancestor (LCA) ===" << endl;
    cout << endl;

    // LCA of 20 and 40
    TreeNode* p = searchBST(root, 20);
    TreeNode* q = searchBST(root, 40);
    TreeNode* lca = LCA_BST(root, p, q);
    cout << "LCA of 20 and 40 = " << lca->val << endl;
    cout << "  (both are in left subtree of 30)" << endl;

    cout << endl;

    // LCA of 20 and 80
    p = searchBST(root, 20);
    q = searchBST(root, 80);
    lca = LCA_BST(root, p, q);
    cout << "LCA of 20 and 80 = " << lca->val << endl;
    cout << "  (20 is in left subtree, 80 is in right subtree of 50)" << endl;

    cout << endl;

    // LCA of 60 and 80
    p = searchBST(root, 60);
    q = searchBST(root, 80);
    lca = LCA_BST(root, p, q);
    cout << "LCA of 60 and 80 = " << lca->val << endl;
    cout << "  (both are in right subtree of 70)" << endl;

    cout << endl;
    cout << "How it works:" << endl;
    cout << "  1. If both values < root -> LCA is in left subtree" << endl;
    cout << "  2. If both values > root -> LCA is in right subtree" << endl;
    cout << "  3. If values split (one left, one right) -> root IS the LCA" << endl;
    cout << endl;
    cout << "Time: O(log n) balanced, O(n) skewed" << endl;

    deleteTree(root);

    return 0;
}
