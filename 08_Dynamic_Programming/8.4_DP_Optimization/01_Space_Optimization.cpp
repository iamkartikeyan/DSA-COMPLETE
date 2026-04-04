#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// =============================================
// SPACE OPTIMIZATION IN DYNAMIC PROGRAMMING
// =============================================
// Many DP solutions store full tables (e.g., dp[n] or dp[n][W]),
// but often we only need the LAST few values to compute the next state.
// This lets us reduce space dramatically.
//
// Key idea: If dp[i] only depends on dp[i-1] and dp[i-2],
//           we don't need to store dp[0..i-3].
//
// =============================================


// =============================================
// EXAMPLE 1: FIBONACCI - O(n) space -> O(1) space
// =============================================
// Standard DP uses an array of size n+1.
// But fib(i) only needs fib(i-1) and fib(i-2).
// So we just keep two variables!

int fibonacci_O_space(int n) {
    if (n <= 1) {
        return n;
    }

    // Only store the last two values
    int prev2 = 0;  // fib(0)
    int prev1 = 1;  // fib(1)
    int current = 0;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

void fibonacci_example() {
    cout << "=== Fibonacci: Space Optimization ===" << endl;

    // Compare with standard O(n) space approach
    int n = 10;

    // Standard DP: O(n) space
    int dp[11];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout << "fib(" << n << ") with O(n) space = " << dp[n] << endl;

    // Optimized: O(1) space
    cout << "fib(" << n << ") with O(1) space = " << fibonacci_O_space(n) << endl;

    cout << endl;
}


// =============================================
// EXAMPLE 2: 0/1 KNAPSACK - O(n*W) -> O(W) space
// =============================================
// Standard DP uses dp[n+1][W+1] table.
// But dp[i][w] only depends on row i-1.
//
// KEY RULE: When using 1D array for 0/1 Knapsack,
//           iterate BACKWARDS (from W down to weight[i]).
//           This ensures we don't use the same item twice.
//           If we iterate forward, we'd use the UPDATED value
//           from the current iteration (which means reusing the item).

int knapsack_01_O_W_space(int n, int W, int weights[], int values[]) {
    // dp[w] = maximum value with capacity w
    int dp[1001];

    // Initialize all to 0
    for (int w = 0; w <= W; w++) {
        dp[w] = 0;
    }

    for (int i = 0; i < n; i++) {
        // IMPORTANT: Iterate BACKWARDS to avoid using item i more than once
        for (int w = W; w >= weights[i]; w--) {
            dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
        }
    }

    return dp[W];
}

void knapsack_01_example() {
    cout << "=== 0/1 Knapsack: Space Optimization ===" << endl;

    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int n = 3;
    int W = 50;

    cout << "Items (value, weight): (60,10), (100,20), (120,30)" << endl;
    cout << "Capacity: " << W << endl;
    cout << "Max value (O(W) space) = " << knapsack_01_O_W_space(n, W, weights, values) << endl;

    // Show why BACKWARDS matters:
    // If we iterate forwards, when processing item with weight 10 and value 60:
    //   dp[10] = max(dp[10], 60 + dp[0]) = 60
    //   dp[20] = max(dp[20], 60 + dp[10]) = 60 + 60 = 120  <-- WRONG! Used item twice!
    // By iterating backwards:
    //   dp[50] uses dp[40] (old value, item not yet used)
    //   dp[40] uses dp[30] (old value, item not yet used)
    //   ... so each item is only considered once per iteration

    cout << "Note: Must iterate BACKWARDS to avoid using same item twice" << endl;
    cout << endl;
}


// =============================================
// EXAMPLE 3: UNBOUNDED KNAPSACK - O(W) space
// =============================================
// Same as 0/1 Knapsack but items can be used INFINITE times.
// KEY RULE: Iterate FORWARDS this time!
//           Because we WANT to allow reusing the same item.

int unbounded_knapsack_O_W_space(int n, int W, int weights[], int values[]) {
    int dp[1001];

    // Initialize all to 0
    for (int w = 0; w <= W; w++) {
        dp[w] = 0;
    }

    for (int i = 0; i < n; i++) {
        // IMPORTANT: Iterate FORWARDS to allow reusing the same item
        // When we reach dp[w], dp[w - weights[i]] might already include item i
        // That's exactly what we want for unbounded knapsack!
        for (int w = weights[i]; w <= W; w++) {
            dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
        }
    }

    return dp[W];
}

void unbounded_knapsack_example() {
    cout << "=== Unbounded Knapsack: Space Optimization ===" << endl;

    int values[] = {10, 30, 20};
    int weights[] = {5, 10, 15};
    int n = 3;
    int W = 100;

    cout << "Items (value, weight): (10,5), (30,10), (20,15)" << endl;
    cout << "Capacity: " << W << endl;
    cout << "Max value (O(W) space, items can be reused) = "
         << unbounded_knapsack_O_W_space(n, W, weights, values) << endl;

    // With W=100 and item (30, 10), we can take it 10 times = 300
    // The forward iteration allows this: dp[10] = 30, dp[20] = 30 + 30 = 60, ...

    cout << "Note: Must iterate FORWARDS to allow reusing items" << endl;
    cout << endl;
}


// =============================================
// EXAMPLE 4: LCS - O(m*n) -> O(n) space
// =============================================
// Standard DP uses dp[m+1][n+1] table.
// But to compute row i, we only need row i-1.
// So we keep just two rows: previous and current.

int lcs_O_n_space(string& X, string& Y, int m, int n) {
    // Only need two rows instead of (m+1) rows
    int prev[1001];
    int curr[1001];

    // Initialize base case (empty string = length 0 LCS)
    for (int j = 0; j <= n; j++) {
        prev[j] = 0;
    }

    for (int i = 1; i <= m; i++) {
        curr[0] = 0;  // Empty string Y has LCS of 0

        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }

        // Current row becomes previous row for next iteration
        for (int j = 0; j <= n; j++) {
            prev[j] = curr[j];
        }
    }

    return prev[n];
}

void lcs_example() {
    cout << "=== LCS: Space Optimization ===" << endl;

    string X = "AGGTAB";
    string Y = "GXTXAYB";
    int m = X.length();
    int n = Y.length();

    cout << "String 1: " << X << endl;
    cout << "String 2: " << Y << endl;

    // Standard DP would use dp[7][8] table
    // Optimized uses just 2 rows of size 8
    cout << "LCS length (O(n) space) = " << lcs_O_n_space(X, Y, m, n) << endl;
    cout << "Expected: 4 (GTAB)" << endl;

    cout << endl;
}


int main() {
    cout << "========================================" << endl;
    cout << "  SPACE OPTIMIZATION IN DP" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // Example 1: Fibonacci
    fibonacci_example();

    // Example 2: 0/1 Knapsack
    knapsack_01_example();

    // Example 3: Unbounded Knapsack
    unbounded_knapsack_example();

    // Example 4: LCS
    lcs_example();

    // Summary comparison
    cout << "========================================" << endl;
    cout << "  SUMMARY: Space Optimization" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Problem               | Original Space | Optimized Space" << endl;
    cout << "----------------------|----------------|----------------" << endl;
    cout << "Fibonacci             | O(n)           | O(1)" << endl;
    cout << "0/1 Knapsack          | O(n*W)         | O(W)" << endl;
    cout << "Unbounded Knapsack    | O(n*W)         | O(W)" << endl;
    cout << "LCS                   | O(m*n)         | O(n)" << endl;
    cout << endl;
    cout << "Key Patterns:" << endl;
    cout << "- If current state depends on only 1-2 previous states -> O(1) space" << endl;
    cout << "- If current row depends only on previous row -> O(n) instead of O(m*n)" << endl;
    cout << "- 0/1 Knapsack: iterate BACKWARDS in 1D array" << endl;
    cout << "- Unbounded Knapsack: iterate FORWARDS in 1D array" << endl;
    cout << endl;

    return 0;
}
