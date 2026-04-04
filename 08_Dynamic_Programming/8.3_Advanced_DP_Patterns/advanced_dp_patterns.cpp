/*
 * Advanced DP Patterns - Palindrome DP, Tree DP, Bitmask DP
 *
 * DP on Strings:
 *   Palindrome Partitioning: min cuts to make all substrings palindromes
 *   Longest Palindromic Substring: dp[i][j] = s[i..j] is palindrome?
 *   Palindromic Subsequences: count palindromic subsequences
 *
 * DP on Trees:
 *   Tree Diameter: longest path between any two nodes
 *   Max Path Sum: max sum path in binary tree
 *   State depends on subtree results (post-order traversal)
 *
 * Bitmask DP:
 *   State includes a bitmask representing a subset
 *   Used when n <= 20 (2^20 ~ 1 million states)
 *   dp[mask] = answer for subset represented by mask
 *   Transitions: iterate over which element to add/remove
 *   Applications: TSP, assignment problem, traveling salesman
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================
// 1. PALINDROME PARTITIONING - Min Cuts
//    dp[i] = min cuts for s[0..i-1]
//    isPal[i][j] = true if s[i..j] is palindrome
//    dp[i] = min(dp[j] + 1) for all j < i where s[j..i-1] is palindrome
// ============================================================
int minCutPalindrome(const string& s) {
    int n = s.size();
    if (n <= 1) return 0;

    // Precompute palindromes
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    for (int i = n - 1; i >= 0; --i)
        for (int j = i; j < n; ++j)
            if (s[i] == s[j] && (j - i < 2 || isPal[i + 1][j - 1]))
                isPal[i][j] = true;

    // DP for min cuts
    vector<int> dp(n + 1, 0);
    for (int i = 0; i <= n; ++i) dp[i] = i - 1;  // worst case: each char separate

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < i; ++j)
            if (isPal[j][i - 1])
                dp[i] = min(dp[i], dp[j] + 1);

    return dp[n];
}

// ============================================================
// 2. LONGEST PALINDROMIC SUBSEQUENCE
//    State: dp[i][j] = LPS length in s[i..j]
//    Match: dp[i][j] = 2 + dp[i+1][j-1]
//    Mismatch: dp[i][j] = max(dp[i+1][j], dp[i][j-1])
// ============================================================
int longestPalindromicSubseq(const string& s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) dp[i][i] = 1;  // single char

    for (int len = 2; len <= n; ++len)
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j])
                dp[i][j] = 2 + dp[i + 1][j - 1];
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    return dp[0][n - 1];
}

// ============================================================
// 3. PALINDROMIC SUBSTRINGS (Count)
//    Expand around center, or DP
// ============================================================
int countPalindromicSubstrings(const string& s) {
    int n = s.size(), count = 0;
    for (int center = 0; center < 2 * n - 1; ++center) {
        int l = center / 2, r = l + center % 2;
        while (l >= 0 && r < n && s[l] == s[r]) {
            count++; l--; r++;
        }
    }
    return count;
}

// ============================================================
// 4. DP ON TREES - Binary Tree Node
// ============================================================
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// --- Tree Diameter: Longest path between any two nodes ---
// For each node: diameter = leftHeight + rightHeight
int treeDiameter(TreeNode* root, int& diameter) {
    if (!root) return 0;
    int lh = treeDiameter(root->left, diameter);
    int rh = treeDiameter(root->right, diameter);
    diameter = max(diameter, lh + rh);  // path through this node
    return max(lh, rh) + 1;  // return height
}

// --- Max Path Sum in Binary Tree ---
// Path can start/end at any node, goes through parent at most once
int maxPathSumHelper(TreeNode* root, int& maxSum) {
    if (!root) return 0;
    // Max from subtrees (ignore negative contributions)
    int left = max(0, maxPathSumHelper(root->left, maxSum));
    int right = max(0, maxPathSumHelper(root->right, maxSum));
    // Path through this node
    maxSum = max(maxSum, left + right + root->val);
    // Return max path going up (can only go one direction)
    return max(left, right) + root->val;
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumHelper(root, maxSum);
    return maxSum;
}

// --- Maximum Independent Set on Tree ---
// Pick max number of nodes, no two adjacent
// dp[node][0] = max set not including node
// dp[node][1] = max set including node
pair<int, int> treeMaxIndependentSet(TreeNode* root) {
    if (!root) return {0, 0};
    auto left = treeMaxIndependentSet(root->left);
    auto right = treeMaxIndependentSet(root->right);
    // Include root: cannot include children
    int take = 1 + left.first + right.first;
    // Exclude root: can include or exclude children
    int skip = max(left.first, left.second) + max(right.first, right.second);
    return {skip, take};  // {exclude, include}
}

// ============================================================
// 5. BITMASK DP - Traveling Salesperson Problem (TSP)
//    State: dp[mask][i] = min cost visiting all cities in mask, ending at i
//    mask: bitmask of visited cities
//    Transition: dp[mask | (1<<j)][j] = min(dp[mask][i] + dist[i][j])
// ============================================================
int tsp(const vector<vector<int>>& dist) {
    int n = dist.size();
    int FULL = (1 << n) - 1;
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));

    dp[1][0] = 0;  // start at city 0, only city 0 visited

    for (int mask = 1; mask <= FULL; ++mask)
        for (int i = 0; i < n; ++i) {
            if (dp[mask][i] == INT_MAX) continue;  // unreachable state
            // Try going to next city j
            for (int j = 0; j < n; ++j)
                if (!(mask & (1 << j)))  // j not yet visited
                    dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j],
                                                  dp[mask][i] + dist[i][j]);
        }

    // Answer: min cost to visit all cities, end anywhere, return to 0
    int ans = INT_MAX;
    for (int i = 0; i < n; ++i)
        if (dp[FULL][i] != INT_MAX)
            ans = min(ans, dp[FULL][i] + dist[i][0]);
    return ans;
}

// ============================================================
// HELPER: Build a simple tree for demo
// ============================================================
TreeNode* buildDemoTree() {
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
}

// ============================================================
// MAIN: Demonstrate all advanced DP patterns
// ============================================================
int main() {
    cout << "=== ADVANCED DP PATTERNS ===\n\n";

    // --- Palindrome Partitioning ---
    cout << "--- Palindrome Partitioning ---\n";
    cout << "Min cuts for 'aab': " << minCutPalindrome("aab") << "\n";     // 1: aa|b
    cout << "Min cuts for 'ababbbabbababa': "
         << minCutPalindrome("ababbbabbababa") << "\n";  // 3\n\n";

    // --- Longest Palindromic Subsequence ---
    cout << "--- Longest Palindromic Subsequence ---\n";
    cout << "LPS of 'bbbab': " << longestPalindromicSubseq("bbbab") << "\n";  // 4: bbbb
    cout << "LPS of 'cbbd': " << longestPalindromicSubseq("cbbd") << "\n";    // 2: bb
    cout << "\n";

    // --- Palindromic Substrings ---
    cout << "--- Palindromic Substrings ---\n";
    cout << "Count in 'abc': " << countPalindromicSubstrings("abc") << "\n";     // 3
    cout << "Count in 'aaa': " << countPalindromicSubstrings("aaa") << "\n";     // 6\n\n";

    // --- Tree DP ---
    cout << "--- Tree DP ---\n";
    TreeNode* root = buildDemoTree();
    int diameter = 0;
    treeDiameter(root, diameter);
    cout << "Tree diameter: " << diameter << "\n";  // 3: 4-2-1-3 or 5-2-1-3

    cout << "Max path sum: " << maxPathSum(root) << "\n";  // 12: 4-2-1-3 (wait, 4+2+1+3=10?)
    // Actually: max path is 4-2-5 = 11 or 4-2-1-3 = 10. Let me recalculate.
    // The max path sum helper allows paths that go through a node.
    // Path 4-2-5: 4+2+5 = 11. Path through 1: max(0,left)+max(0,right)+1
    // left from 2: max(4,5) = 5, right from 3: 3
    // So path through 1: 5+3+1 = 9. Path through 2: 4+5+2 = 11. Max = 11.

    auto mis = treeMaxIndependentSet(root);
    cout << "Max independent set: " << max(mis.first, mis.second) << "\n"; // 3: {2,3} or {4,5,3}

    // Cleanup
    delete root->left->left; delete root->left->right;
    delete root->left; delete root->right; delete root;

    cout << "\n";

    // --- Bitmask DP: TSP ---
    cout << "--- Bitmask DP: TSP ---\n";
    // 4 cities with distances
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    cout << "TSP min cost: " << tsp(dist) << "\n";  // 80: 0-1-3-2-0 = 10+25+30+15

    // --- Summary ---
    cout << "\n--- Advanced Pattern Summary ---\n";
    cout << "Palindrome DP:    isPal[i][j] table, min cuts, LPS\n";
    cout << "Tree DP:          Post-order, subtree results combine at parent\n";
    cout << "Bitmask DP:       State = (mask, position), n <= 20\n";
    cout << "TSP:              O(n^2 * 2^n), exponential but better than O(n!)\n";

    return 0;
}
