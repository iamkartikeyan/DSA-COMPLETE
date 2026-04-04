/*
 * File: 06_BST_Delete.cpp
 * Topic: Delete a node from BST (3 cases)
 * Description: Leaf deletion, one child, two children
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

// Find minimum (leftmost)
TreeNode* findMin(TreeNode* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Inorder successor
TreeNode* inorderSuccessor(TreeNode* node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->right != NULL) {
        return findMin(node->right);
    }
    return NULL;
}

// Delete node from BST
TreeNode* deleteBST(TreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    // Find the node to delete
    if (key < root->val) {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->val) {
        root->right = deleteBST(root->right, key);
    }
    else {
        // Found the node to delete

        // Case 1: Leaf node (no children)
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }

        // Case 2: Only one child (right)
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }

        // Case 2: Only one child (left)
        if (root->right == NULL) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Two children
        // Replace with inorder successor (smallest in right subtree)
        TreeNode* succ = inorderSuccessor(root);
        root->val = succ->val;
        // Delete the successor node from right subtree
        root->right = deleteBST(root->right, succ->val);
    }

    return root;
}

// Inorder traversal
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

    cout << "=== BST Delete ===" << endl;
    cout << endl;

    cout << "Before delete: ";
    inorder(root);
    cout << endl;

    // Case 1: Delete leaf node (20)
    cout << endl;
    cout << "--- Case 1: Delete leaf node 20 ---" << endl;
    root = deleteBST(root, 20);
    cout << "After delete 20:  ";
    inorder(root);
    cout << endl;

    // Case 2: Delete node with one child (70 has children 60, 80)
    cout << endl;
    cout << "--- Case 3: Delete node with 2 children (30) ---" << endl;
    root = deleteBST(root, 30);
    cout << "After delete 30:  ";
    inorder(root);
    cout << endl;

    cout << endl;
    cout << "3 Cases of BST Delete:" << endl;
    cout << "  Case 1 - Leaf node: Simply remove it" << endl;
    cout << "  Case 2 - One child: Replace with that child" << endl;
    cout << "  Case 3 - Two children: Replace with inorder successor," << endl;
    cout << "           then delete the successor node" << endl;
    cout << endl;
    cout << "Time: O(log n) balanced, O(n) skewed" << endl;

    deleteTree(root);

    return 0;
}
