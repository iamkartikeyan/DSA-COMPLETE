/*
 * DP Optimization - Space Optimization, Knuth, Divide & Conquer DP
 *
 * Space Optimization:
 *   Many DP problems only need the previous row/column
 *   O(n^2) space => O(n) or even O(1)
 *   Fibonacci: O(n) => O(1) by keeping only last 2 values
 *   Knapsack: O(n*W) => O(W) using 1D array (iterate backwards)
 *   LCS: O(m*n) => O(min(m,n)) using 2 rows
 *
 * Knuth Optimization:
 *   Applies when cost function satisfies quadrangle inequality
 *   Reduces O(n^3) to O(n^2) for optimal BST, matrix chain multiplication
 *   Key insight: opt[i][j-1] <= opt[i][j] <= opt[i+1][j]
 *   Narrow the search range for the optimal split point
 *
 * Divide & Conquer DP Optimization:
 *   Applies when opt[i][j] <= opt[i][j+1] (monotonicity)
 *   Reduces O(n^2 * m) to O(n * m * log n)
 *   Used in problems like "partition array into k subarrays"
 *
 * General Tricks:
 *   - Iterate in correct order (dependency resolution)
 *   - Use rolling arrays to save space
 *   - Prune unreachable states (INT_MAX checks)
 *   - Early exit when optimal found
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================
// 1. SPACE OPTIMIZATION: Fibonacci O(n) => O(1)
// ============================================================
long long fibO1(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        long long c = a + b;
        a = b; b = c;
    }
    return b;
}

// ============================================================
// 2. SPACE OPTIMIZATION: 0/1 Knapsack O(n*W) => O(W)
//    Key: iterate backwards to avoid using same item twice
// ============================================================
int knapsack1D(int W, const vector<int>& wt, const vector<int>& val) {
    vector<int> dp(W + 1, 0);
    int n = wt.size();
    for (int i = 0; i < n; ++i)
        for (int w = W; w >= wt[i]; --w)  // backwards!
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

// Unbounded: iterate forwards (can use same item multiple times)
int unboundedKnapsack1D(int W, const vector<int>& wt, const vector<int>& val) {
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < wt.size(); ++i)
        for (int w = wt[i]; w <= W; ++w)  // forwards
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

// ============================================================
// 3. SPACE OPTIMIZATION: LCS O(m*n) => O(min(m,n))
//    Only need current and previous row
// ============================================================
int lcsSpaceOptimized(string s1, string s2) {
    if (s1.size() < s2.size()) swap(s1, s2);  // s2 is shorter
    int m = s1.size(), n = s2.size();
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j)
            if (s1[i - 1] == s2[j - 1])
                curr[j] = 1 + prev[j - 1];
            else
                curr[j] = max(prev[j], curr[j - 1]);
        prev = curr;
    }
    return prev[n];
}

// ============================================================
// 4. SPACE OPTIMIZATION: Edit Distance O(m*n) => O(min(m,n))
// ============================================================
int editDistanceOptimized(string s1, string s2) {
    if (s1.size() < s2.size()) swap(s1, s2);
    int m = s1.size(), n = s2.size();
    vector<int> prev(n + 1), curr(n + 1);

    for (int j = 0; j <= n; ++j) prev[j] = j;

    for (int i = 1; i <= m; ++i) {
        curr[0] = i;
        for (int j = 1; j <= n; ++j)
            if (s1[i - 1] == s2[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = 1 + min({prev[j], curr[j - 1], prev[j - 1]});
        prev = curr;
    }
    return prev[n];
}

// ============================================================
// 5. KNUth OPTIMIZATION - Optimal BST Cost
//    dp[i][j] = min cost for keys i..j
//    Without optimization: O(n^3), with: O(n^2)
//    Constraint: opt[i][j-1] <= opt[i][j] <= opt[i+1][j]
// ============================================================
int optimalBST(const vector<int>& keys, const vector<int>& freq) {
    int n = keys.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));

    // Prefix sums for quick range sum
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + freq[i];
    auto rangeSum = [&](int i, int j) {
        return prefix[j + 1] - prefix[i];
    };

    for (int i = 0; i < n; ++i) {
        dp[i][i] = freq[i];
        opt[i][i] = i;
    }

    for (int len = 2; len <= n; ++len)
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            // Knuth: search range [opt[i][j-1], opt[i+1][j]]
            int start = opt[i][j - 1], end = (i + 1 <= j) ? opt[i + 1][j] : j;
            for (int r = start; r <= end; ++r) {
                int cost = (r > i ? dp[i][r - 1] : 0) +
                           (r < j ? dp[r + 1][j] : 0);
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    opt[i][j] = r;
                }
            }
            dp[i][j] += rangeSum(i, j);
        }
    return dp[0][n - 1];
}

// ============================================================
// 6. DIVIDE & CONQUER DP OPTIMIZATION
//    Problem: Partition array into k subarrays, minimize max sum
//    State: dp[i][j] = min max-sum partitioning arr[0..j-1] into i groups
//    Without optimization: O(k * n^2), with: O(k * n * log n)
// ============================================================
void computeDP(const vector<long long>& prefix, int k, int i, int optL, int optR,
               int l, int r, vector<vector<long long>>& dp) {
    if (l > r) return;
    int mid = (l + r) / 2;
    int bestK = -1;
    dp[i][mid] = LLONG_MAX;

    for (int K = optL; K <= min(mid - 1, optR); ++K) {
        long long val = max(dp[i - 1][K], prefix[mid] - prefix[K]);
        if (val < dp[i][mid]) {
            dp[i][mid] = val;
            bestK = K;
        }
    }
    computeDP(prefix, k, i, optL, bestK, l, mid - 1, dp);
    computeDP(prefix, k, i, bestK, optR, mid + 1, r, dp);
}

long long minimizeMaxSum(const vector<int>& arr, int k) {
    int n = arr.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + arr[i];

    vector<vector<long long>> dp(k + 1, vector<long long>(n + 1));
    for (int j = 0; j <= n; ++j) dp[1][j] = prefix[j];

    for (int i = 2; i <= k; ++i)
        computeDP(prefix, k, i, 0, n, 1, n, dp);

    return dp[k][n];
}

// ============================================================
// HELPER: Print array
// ============================================================
template<typename T>
void printArr(const vector<T>& arr, const string& label = "") {
    cout << label;
    for (const auto& x : arr) cout << x << " ";
    cout << "\n";
}

// ============================================================
// MAIN: Demonstrate all optimization techniques
// ============================================================
int main() {
    cout << "=== DP OPTIMIZATION ===\n\n";

    // --- Space Optimization: Fibonacci ---
    cout << "--- Space Optimization: Fibonacci ---\n";
    cout << "fib(20) = " << fibO1(20) << "\n\n";

    // --- Space Optimization: Knapsack ---
    cout << "--- Space Optimization: Knapsack ---\n";
    vector<int> wt = {1, 3, 4, 5}, val = {1, 4, 5, 7};
    cout << "0/1 Knapsack (W=7): " << knapsack1D(7, wt, val) << "\n";       // 9
    cout << "Unbounded (W=7): " << unboundedKnapsack1D(7, wt, val) << "\n";  // 14\n\n";

    // --- Space Optimization: LCS ---
    cout << "--- Space Optimization: LCS ---\n";
    cout << "LCS('abcde', 'ace'): " << lcsSpaceOptimized("abcde", "ace") << "\n";  // 3\n\n";

    // --- Space Optimization: Edit Distance ---
    cout << "--- Space Optimization: Edit Distance ---\n";
    cout << "Edit('horse', 'ros'): " << editDistanceOptimized("horse", "ros") << "\n";  // 3\n\n";

    // --- Knuth Optimization: Optimal BST ---
    cout << "--- Knuth Optimization: Optimal BST ---\n";
    vector<int> keys = {10, 20, 30}, freq = {34, 8, 50};
    cout << "Optimal BST cost for keys {10,20,30}: "
         << optimalBST(keys, freq) << "\n";  // 142\n\n";

    // --- Divide & Conquer DP ---
    cout << "--- Divide & Conquer DP ---\n";
    vector<int> arr = {7, 2, 5, 10, 8};
    cout << "Partition {7,2,5,10,8} into 2 groups, min max-sum: "
         << minimizeMaxSum(arr, 2) << "\n";  // 18: {7,2,5} | {10,8}
    cout << "Partition into 3 groups: " << minimizeMaxSum(arr, 3) << "\n";  // 14

    // --- Summary ---
    cout << "\n--- Optimization Summary ---\n";
    cout << "Space:         O(n^2) => O(n) using rolling arrays\n";
    cout << "Knuth:         O(n^3) => O(n^2) when opt satisfies monotonicity\n";
    cout << "Divide & Conv:  O(k*n^2) => O(k*n*log n) for partitioning problems\n";
    cout << "\nKey Insight: Understand which previous states are actually needed!\n";

    return 0;
}
