/*
 * File: 03_BST_Insert.cpp
 * Topic: Insert a new key into BST
 * Description: New key is always added as a leaf
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

// Insert key into BST
TreeNode* insertBST(TreeNode* root, int key) {
    // found empty spot - create new node
    if (root == NULL) {
        return new TreeNode(key);
    }

    // key is smaller, go left
    if (key < root->val) {
        root->left = insertBST(root->left, key);
    }
    // key is larger, go right
    else if (key > root->val) {
        root->right = insertBST(root->right, key);
    }
    // duplicate key - ignore (BST has unique values)

    return root;
}

// Inorder traversal to show sorted order
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
    cout << "=== BST Insert ===" << endl;
    cout << endl;

    // Start with empty tree
    TreeNode* root = NULL;

    // Insert values
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = 7;

    cout << "Inserting values: ";
    for (int i = 0; i < n; i++) {
        cout << values[i] << " ";
        root = insertBST(root, values[i]);
    }
    cout << endl;
    cout << endl;

    /*
     * Resulting BST:
     *         50
     *       /    \
     *     30      70
     *    /  \    /  \
     *  20   40  60   80
     */
    cout << "Resulting BST:" << endl;
    cout << "          50" << endl;
    cout << "        /    \\" << endl;
    cout << "      30      70" << endl;
    cout << "     /  \\    /  \\" << endl;
    cout << "   20   40  60   80" << endl;
    cout << endl;

    // Insert duplicate (will be ignored)
    cout << "Inserting duplicate 30... (ignored)" << endl;
    root = insertBST(root, 30);

    cout << "Inorder (sorted): ";
    inorder(root);
    cout << endl;

    cout << endl;
    cout << "How it works:" << endl;
    cout << "  1. Start at root" << endl;
    cout << "  2. Compare key with current node" << endl;
    cout << "  3. If smaller -> go left" << endl;
    cout << "  4. If larger -> go right" << endl;
    cout << "  5. When you reach NULL -> insert new node there" << endl;
    cout << "  6. Duplicate values are ignored" << endl;
    cout << endl;
    cout << "Time: O(log n) balanced, O(n) skewed" << endl;

    deleteTree(root);

    return 0;
}
