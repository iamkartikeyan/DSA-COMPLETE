#include <iostream>
#include <algorithm>

using namespace std;

// ============================================================
// Tree Node Structure (Basic Binary Tree)
// ============================================================
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

// Helper function to create a new node
TreeNode* createNode(int value) {
    TreeNode* node = new TreeNode;
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ============================================================
// 1. Tree Diameter
// Longest path between any two nodes (measured in edges)
// Uses post-order DFS: compute height, update diameter
// ============================================================

// Global variable to track diameter
int globalDiameter;

int heightAndDiameter(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    // Post-order: process children first
    int leftHeight = heightAndDiameter(root->left);
    int rightHeight = heightAndDiameter(root->right);

    // Update diameter through this node
    int diameterThroughNode = leftHeight + rightHeight;
    if (diameterThroughNode > globalDiameter) {
        globalDiameter = diameterThroughNode;
    }

    // Return height of this subtree
    int h = leftHeight;
    if (rightHeight > h) {
        h = rightHeight;
    }
    return h + 1;
}

int treeDiameter(TreeNode* root) {
    globalDiameter = 0;
    heightAndDiameter(root);
    return globalDiameter;
}

// ============================================================
// 2. Maximum Path Sum in Binary Tree
// Path can start and end at any node
// Uses similar post-order DFS approach
// ============================================================

int globalMaxPathSum;

int maxPathSumHelper(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    // Post-order: process children first
    // Only take positive contributions (ignore negative paths)
    int leftSum = maxPathSumHelper(root->left);
    int rightSum = maxPathSumHelper(root->right);

    if (leftSum < 0) leftSum = 0;
    if (rightSum < 0) rightSum = 0;

    // Path through this node (can use both children)
    int pathThroughRoot = leftSum + rightSum + root->val;

    // Update global maximum
    if (pathThroughRoot > globalMaxPathSum) {
        globalMaxPathSum = pathThroughRoot;
    }

    // Return max single path (can only use one child for parent)
    int singlePath = leftSum;
    if (rightSum > singlePath) {
        singlePath = rightSum;
    }
    return singlePath + root->val;
}

int maxPathSum(TreeNode* root) {
    globalMaxPathSum = -999999;  // Very small number
    maxPathSumHelper(root);
    return globalMaxPathSum;
}

// ============================================================
// Helper: Free tree memory
// ============================================================
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// ============================================================
// Main - Test all functions
// ============================================================

int main() {
    cout << "=== DP on Trees ===" << endl;
    cout << endl;

    // Test 1: Tree Diameter
    cout << "--- 1. Tree Diameter ---" << endl;

    // Build tree 1:
    //         1
    //        / \
    //       2   3
    //      / \
    //     4   5
    TreeNode* root1 = createNode(1);
    root1->left = createNode(2);
    root1->right = createNode(3);
    root1->left->left = createNode(4);
    root1->left->right = createNode(5);

    cout << "Tree 1:" << endl;
    cout << "        1" << endl;
    cout << "       / \\" << endl;
    cout << "      2   3" << endl;
    cout << "     / \\" << endl;
    cout << "    4   5" << endl;
    int diam1 = treeDiameter(root1);
    cout << "Diameter: " << diam1 << endl;
    cout << "Expected: 3 (path 4->2->5 or 5->2->1->3)" << endl;
    cout << endl;

    // Build tree 2 (skewed):
    //     1
    //      \
    //       2
    //        \
    //         3
    //          \
    //           4
    TreeNode* root2 = createNode(1);
    root2->right = createNode(2);
    root2->right->right = createNode(3);
    root2->right->right->right = createNode(4);

    cout << "Tree 2 (skewed):" << endl;
    cout << "  1" << endl;
    cout << "   \\" << endl;
    cout << "    2" << endl;
    cout << "     \\" << endl;
    cout << "      3" << endl;
    cout << "       \\" << endl;
    cout << "        4" << endl;
    int diam2 = treeDiameter(root2);
    cout << "Diameter: " << diam2 << endl;
    cout << "Expected: 3" << endl;
    cout << endl;

    // Test 2: Maximum Path Sum
    cout << "--- 2. Maximum Path Sum ---" << endl;

    // Build tree 3:
    //        -10
    //        / \
    //       9  20
    //          / \
    //         15  7
    TreeNode* root3 = createNode(-10);
    root3->left = createNode(9);
    root3->right = createNode(20);
    root3->right->left = createNode(15);
    root3->right->right = createNode(7);

    cout << "Tree 3:" << endl;
    cout << "       -10" << endl;
    cout << "       / \\" << endl;
    cout << "      9  20" << endl;
    cout << "         / \\" << endl;
    cout << "       15   7" << endl;
    int maxSum = maxPathSum(root3);
    cout << "Max Path Sum: " << maxSum << endl;
    cout << "Expected: 42 (15->20->7)" << endl;
    cout << endl;

    // Build tree 4 (all negative):
    //       -5
    //      / \
    //    -3  -8
    TreeNode* root4 = createNode(-5);
    root4->left = createNode(-3);
    root4->right = createNode(-8);

    cout << "Tree 4 (all negative):" << endl;
    cout << "     -5" << endl;
    cout << "    /  \\" << endl;
    cout << "  -3   -8" << endl;
    int maxSum2 = maxPathSum(root4);
    cout << "Max Path Sum: " << maxSum2 << endl;
    cout << "Expected: -3 (single node)" << endl;
    cout << endl;

    // Clean up memory
    freeTree(root1);
    freeTree(root2);
    freeTree(root3);
    freeTree(root4);

    return 0;
}
