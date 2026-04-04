/*
 * Classic DP Patterns - 1D, 2D, Knapsack, LCS, Edit Distance, Coin Change
 *
 * 1D DP: Single parameter state (e.g., dp[i])
 *   - Fibonacci, climbing stairs, house robber
 *
 * 2D DP: Two parameter state (e.g., dp[i][j])
 *   - Grid paths, LCS, edit distance
 *
 * Knapsack Pattern:
 *   - 0/1 Knapsack: each item used at most once
 *   - Unbounded: each item can be used infinitely
 *   - State: dp[i][w] = max value using items 0..i with capacity w
 *
 * LCS (Longest Common Subsequence):
 *   - State: dp[i][j] = LCS of text1[0..i-1] and text2[0..j-1]
 *   - Match: dp[i][j] = 1 + dp[i-1][j-1]
 *   - Mismatch: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *
 * Edit Distance:
 *   - State: dp[i][j] = min edits to convert word1[0..i-1] to word2[0..j-1]
 *   - Operations: insert, delete, replace (cost 1 each)
 *
 * Coin Change:
 *   - Count ways (unbounded): dp[i] += dp[i - coin]
 *   - Min coins: dp[i] = min(dp[i], dp[i - coin] + 1)
 *
 * Subset Sum:
 *   - dp[i][j] = can we make sum j using first i items?
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================
// 1D DP: House Robber (already in foundations, quick recap)
// ============================================================
int houseRobber(const vector<int>& nums) {
    if (nums.empty()) return 0;
    int prev2 = 0, prev1 = 0;
    for (int x : nums) {
        int cur = max(prev1, prev2 + x);
        prev2 = prev1; prev1 = cur;
    }
    return prev1;
}

// ============================================================
// 2D DP: Unique Paths in Grid
//    Robot at (0,0), move right or down, reach (m-1, n-1)
//    State: dp[i][j] = paths to reach cell (i,j)
//    dp[i][j] = dp[i-1][j] + dp[i][j-1]
// ============================================================
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));
    for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    return dp[m - 1][n - 1];
}

// Unique Paths with Obstacles (1 = blocked)
int uniquePathsWithObstacles(const vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = (grid[0][0] == 0);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) continue;
            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (j > 0) dp[i][j] += dp[i][j - 1];
        }
    return dp[m - 1][n - 1];
}

// ============================================================
// Longest Common Subsequence (LCS)
// ============================================================
int lcs(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    return dp[m][n];
}

// ============================================================
// Edit Distance (Levenshtein Distance)
// ============================================================
int editDistance(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Base: convert to/from empty string
    for (int i = 0; i <= m; ++i) dp[i][0] = i;  // delete all
    for (int j = 0; j <= n; ++j) dp[0][j] = j;  // insert all

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];  // no op needed
            else
                dp[i][j] = 1 + min({dp[i - 1][j],      // delete
                                     dp[i][j - 1],      // insert
                                     dp[i - 1][j - 1]}); // replace
    return dp[m][n];
}

// ============================================================
// 0/1 Knapsack: Each item can be taken at most once
// State: dp[i][w] = max value using items 0..i-1 with capacity w
// Choice: take item (wt[i] + val[i]) or skip
// ============================================================
int knapsack01(int W, const vector<int>& wt, const vector<int>& val) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i)
        for (int w = 0; w <= W; ++w) {
            dp[i][w] = dp[i - 1][w];  // skip item
            if (wt[i - 1] <= w)
                dp[i][w] = max(dp[i][w], dp[i - 1][w - wt[i - 1]] + val[i - 1]);
        }
    return dp[n][W];
}

// Unbounded Knapsack: each item can be taken infinitely
int unboundedKnapsack(int W, const vector<int>& wt, const vector<int>& val) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);
    for (int w = 0; w <= W; ++w)
        for (int i = 0; i < n; ++i)
            if (wt[i] <= w) dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

// ============================================================
// Coin Change: Min coins and Count ways
// ============================================================
int coinChangeMin(const vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int c : coins)
        for (int i = c; i <= amount; ++i)
            if (dp[i - c] != INT_MAX)
                dp[i] = min(dp[i], dp[i - c] + 1);
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int coinChangeWays(const vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (int c : coins)
        for (int i = c; i <= amount; ++i)
            dp[i] += dp[i - c];
    return dp[amount];
}

// ============================================================
// Subset Sum: Can we pick a subset with sum = target?
// State: dp[i][j] = can we make sum j using first i items?
// ============================================================
bool subsetSum(const vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    for (int i = 0; i <= n; ++i) dp[i][0] = true;  // sum 0 always possible

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= target; ++j) {
            dp[i][j] = dp[i - 1][j];  // skip
            if (j >= nums[i - 1])
                dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
        }
    return dp[n][target];
}

// Partition Equal Subset Sum: can array be split into two equal-sum subsets?
bool canPartition(const vector<int>& nums) {
    int sum = 0;
    for (int x : nums) sum += x;
    if (sum % 2 != 0) return false;
    return subsetSum(nums, sum / 2);
}

// ============================================================
// MAIN: Demonstrate all patterns
// ============================================================
int main() {
    cout << "=== CLASSIC DP PATTERNS ===\n\n";

    // --- 2D Grid Paths ---
    cout << "--- Grid Paths ---\n";
    cout << "Unique paths 3x7: " << uniquePaths(3, 7) << "\n";
    vector<vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    cout << "Paths with obstacle: " << uniquePathsWithObstacles(grid) << "\n\n";

    // --- LCS ---
    cout << "--- Longest Common Subsequence ---\n";
    cout << "LCS('abcde', 'ace'): " << lcs("abcde", "ace") << "\n";  // 3: ace
    cout << "LCS('abc', 'def'): " << lcs("abc", "def") << "\n";      // 0
    cout << "LCS('abcdef', 'ace'): " << lcs("abcdef", "ace") << "\n"; // 3\n\n";

    // --- Edit Distance ---
    cout << "--- Edit Distance ---\n";
    cout << "Edit('horse', 'ros'): " << editDistance("horse", "ros") << "\n";  // 3
    cout << "Edit('intention', 'execution'): "
         << editDistance("intention", "execution") << "\n";  // 5\n\n";

    // --- 0/1 Knapsack ---
    cout << "--- 0/1 Knapsack ---\n";
    vector<int> wt = {1, 3, 4, 5}, val = {1, 4, 5, 7};
    cout << "Max value (capacity=7): " << knapsack01(7, wt, val) << "\n";  // 9
    cout << "Unbounded (capacity=7): " << unboundedKnapsack(7, wt, val) << "\n"; // 14\n\n";

    // --- Coin Change ---
    cout << "--- Coin Change ---\n";
    vector<int> coins = {1, 2, 5};
    cout << "Min coins for 11: " << coinChangeMin(coins, 11) << "\n";  // 3: 5+5+1
    cout << "Ways to make 5: " << coinChangeWays(coins, 5) << "\n";    // 4\n\n";

    // --- Subset Sum ---
    cout << "--- Subset Sum ---\n";
    vector<int> nums = {3, 34, 4, 12, 5, 2};
    cout << "Subset sum 9 exists: " << subsetSum(nums, 9) << "\n";   // true: 4+5
    cout << "Subset sum 30 exists: " << subsetSum(nums, 30) << "\n"; // false
    cout << "Can partition {1,5,11,5}: " << canPartition({1, 5, 11, 5}) << "\n"; // true

    cout << "\n--- Pattern Summary ---\n";
    cout << "1D DP:       dp[i], single index/state\n";
    cout << "2D DP:       dp[i][j], grid/string comparison\n";
    cout << "Knapsack:    take or skip, capacity constraint\n";
    cout << "LCS:         match => diagonal+1, else max(up, left)\n";
    cout << "Edit Dist:   match => copy, else 1+min(del, ins, repl)\n";
    cout << "Coin Change: unbounded knapsack variant\n";
    cout << "Subset Sum:  boolean knapsack\n";

    return 0;
}
