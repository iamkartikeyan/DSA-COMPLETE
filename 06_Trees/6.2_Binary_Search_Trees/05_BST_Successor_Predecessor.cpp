/*
 * File: 05_BST_Successor_Predecessor.cpp
 * Topic: Inorder Successor and Predecessor
 * Description: Next greater and next smaller value in BST
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

// Find minimum node (leftmost)
TreeNode* findMin(TreeNode* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Find maximum node (rightmost)
TreeNode* findMax(TreeNode* root) {
    while (root != NULL && root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Inorder successor: smallest value greater than current
// Go right once, then all the way left
TreeNode* inorderSuccessor(TreeNode* node) {
    if (node == NULL) {
        return NULL;
    }
    // if right subtree exists, min of right subtree is successor
    if (node->right != NULL) {
        return findMin(node->right);
    }
    return NULL; // no successor (node is the largest)
}

// Inorder predecessor: largest value smaller than current
// Go left once, then all the way right
TreeNode* inorderPredecessor(TreeNode* node) {
    if (node == NULL) {
        return NULL;
    }
    // if left subtree exists, max of left subtree is predecessor
    if (node->left != NULL) {
        return findMax(node->left);
    }
    return NULL; // no predecessor (node is the smallest)
}

// Helper: search for a value
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
     * BST (inorder: 20 30 40 50 60 70 80):
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

    cout << "=== BST Inorder Successor & Predecessor ===" << endl;
    cout << endl;
    cout << "Inorder: 20 30 40 50 60 70 80" << endl;
    cout << endl;

    // Test with node 50
    TreeNode* node = searchBST(root, 50);
    TreeNode* succ = inorderSuccessor(node);
    TreeNode* pred = inorderPredecessor(node);

    cout << "--- Node 50 ---" << endl;
    if (succ != NULL) {
        cout << "Successor: " << succ->val << endl;
    } else {
        cout << "Successor: none (50 is largest)" << endl;
    }
    if (pred != NULL) {
        cout << "Predecessor: " << pred->val << endl;
    } else {
        cout << "Predecessor: none (50 is smallest)" << endl;
    }

    cout << endl;

    // Test with node 20 (smallest)
    node = searchBST(root, 20);
    succ = inorderSuccessor(node);
    pred = inorderPredecessor(node);

    cout << "--- Node 20 (smallest) ---" << endl;
    if (succ != NULL) {
        cout << "Successor: " << succ->val << endl;
    } else {
        cout << "Successor: none" << endl;
    }
    if (pred != NULL) {
        cout << "Predecessor: " << pred->val << endl;
    } else {
        cout << "Predecessor: none" << endl;
    }

    cout << endl;
    cout << "How it works:" << endl;
    cout << "  Successor:   Go RIGHT once, then all the way LEFT" << endl;
    cout << "  Predecessor: Go LEFT once, then all the way RIGHT" << endl;
    cout << endl;
    cout << "Use: Needed in BST delete operation" << endl;

    deleteTree(root);

    return 0;
}
