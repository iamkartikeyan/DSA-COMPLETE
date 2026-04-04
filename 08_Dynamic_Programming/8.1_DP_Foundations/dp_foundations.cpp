/*
 * DP Foundations - Memoization, Tabulation, State Definition
 *
 * Dynamic Programming solves problems by breaking them into overlapping
 * subproblems and combining their solutions.
 *
 * Two Key Properties:
 *   1. Overlapping Subproblems: same subproblem solved multiple times
 *   2. Optimal Substructure: optimal solution contains optimal sub-solutions
 *
 * Two Approaches:
 *   Memoization (Top-Down): Recursive + cache results
 *     - Natural to write, only computes needed states
 *     - Risk of stack overflow for deep recursion
 *
 *   Tabulation (Bottom-Up): Iterative, fill table from base cases
 *     - No recursion overhead, can optimize space
 *     - Must determine correct fill order
 *
 * State Definition:
 *   The "state" is what uniquely identifies a subproblem.
 *   dp[i] = answer for subproblem of size i
 *   Good state: minimal parameters that capture the subproblem
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================
// 1. FIBONACCI: Classic example of overlapping subproblems
//    fib(n) = fib(n-1) + fib(n-2), fib(0)=0, fib(1)=1
// ============================================================

// NAIVE: Exponential O(2^n) - recalculates same values
long long fibNaive(int n) {
    if (n <= 1) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);
}

// MEMOIZATION: Top-down, O(n) time, O(n) space
long long fibMemo(int n, vector<long long>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];  // already computed
    return memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
}

// TABULATION: Bottom-up, O(n) time, O(n) space
long long fibTab(int n) {
    if (n <= 1) return n;
    vector<long long> dp(n + 1);
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

// SPACE OPTIMIZED: O(1) space (see dp_optimization.cpp for more)
long long fibOptimized(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        long long c = a + b;
        a = b; b = c;
    }
    return b;
}

// ============================================================
// 2. CLIMBING STAIRS: How many ways to reach step n?
//    Can climb 1 or 2 steps at a time.
//    Same recurrence as fibonacci!
// ============================================================

// State: dp[i] = ways to reach step i
// Transition: dp[i] = dp[i-1] + dp[i-2]
// Base: dp[0] = 1 (one way: stay), dp[1] = 1
int climbStairsMemo(int n, vector<int>& memo) {
    if (n <= 1) return 1;
    if (memo[n] != -1) return memo[n];
    return memo[n] = climbStairsMemo(n - 1, memo) + climbStairsMemo(n - 2, memo);
}

int climbStairsTab(int n) {
    if (n <= 1) return 1;
    vector<int> dp(n + 1);
    dp[0] = 1; dp[1] = 1;
    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

// ============================================================
// 3. COUNT WAYS WITH VARIABLE STEPS
//    Can climb 1, 2, or m steps at a time
// ============================================================
int climbWithSteps(int n, int m) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int step = 1; step <= m && step <= i; ++step)
            dp[i] += dp[i - step];
    return dp[n];
}

// ============================================================
// 4. MINIMUM COINS TO REACH AMOUNT (unbounded)
//    State: dp[i] = min coins to make amount i
//    Transition: dp[i] = min(dp[i - coin] + 1) for each coin
//    Base: dp[0] = 0
// ============================================================
int minCoins(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i)
        for (int c : coins)
            if (i >= c && dp[i - c] != INT_MAX)
                dp[i] = min(dp[i], dp[i - c] + 1);
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// ============================================================
// 5. LONGEST INCREASING SUBSEQUENCE (LIS)
//    State: dp[i] = length of LIS ending at index i
//    Transition: dp[i] = max(dp[j] + 1) for all j < i with arr[j] < arr[i]
//    Base: dp[i] = 1 (each element alone)
// ============================================================
int lis(const vector<int>& arr) {
    if (arr.empty()) return 0;
    int n = arr.size();
    vector<int> dp(n, 1);
    for (int i = 1; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (arr[j] < arr[i]) dp[i] = max(dp[i], dp[j] + 1);
    return *max_element(dp.begin(), dp.end());
}

// ============================================================
// 6. STATE DEFINITION PATTERN
//    How to think about DP state:
//    - What parameters uniquely identify a subproblem?
//    - What is the answer for that subproblem?
//    Example: dp[index][remaining_capacity] for knapsack
// ============================================================

// Example: Maximum sum of non-adjacent elements (House Robber)
// State: dp[i] = max sum considering houses 0..i
// Choice at i: rob house i (arr[i] + dp[i-2]) or skip (dp[i-1])
int houseRobber(const vector<int>& houses) {
    if (houses.empty()) return 0;
    int n = houses.size();
    if (n == 1) return houses[0];
    vector<int> dp(n);
    dp[0] = houses[0];
    dp[1] = max(houses[0], houses[1]);
    for (int i = 2; i < n; ++i)
        dp[i] = max(dp[i - 1], houses[i] + dp[i - 2]);
    return dp[n - 1];
}

// ============================================================
// MAIN: Demonstrate all DP concepts
// ============================================================
int main() {
    cout << "=== DP FOUNDATIONS ===\n\n";

    // --- Fibonacci Comparison ---
    cout << "--- Fibonacci ---\n";
    int n = 10;
    cout << "fib(" << n << ") naive: " << fibNaive(n) << "\n";

    vector<long long> memo(n + 1, -1);
    cout << "fib(" << n << ") memo: " << fibMemo(n, memo) << "\n";
    cout << "fib(" << n << ") tab:  " << fibTab(n) << "\n";
    cout << "fib(" << n << ") opt:  " << fibOptimized(n) << "\n\n";

    // --- Climbing Stairs ---
    cout << "--- Climbing Stairs ---\n";
    vector<int> stairMemo(11, -1);
    cout << "Ways to climb 10 stairs: " << climbStairsMemo(10, stairMemo) << "\n";
    cout << "Ways to climb 10 stairs (tab): " << climbStairsTab(10) << "\n";
    cout << "With steps {1,2,3}, ways to climb 5: " << climbWithSteps(5, 3) << "\n\n";

    // --- Min Coins ---
    cout << "--- Min Coins ---\n";
    vector<int> coins = {1, 3, 4};
    cout << "Min coins for amount 6: " << minCoins(coins, 6) << "\n";  // 2 coins: 3+3
    cout << "Min coins for amount 7: " << minCoins(coins, 7) << "\n";  // 2 coins: 3+4\n\n";

    // --- LIS ---
    cout << "--- Longest Increasing Subsequence ---\n";
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS of {10,9,2,5,3,7,101,18}: " << lis(arr) << "\n";  // 4: {2,5,7,101}\n\n";

    // --- House Robber ---
    cout << "--- House Robber (Non-Adjacent Max Sum) ---\n";
    vector<int> houses = {2, 7, 9, 3, 1};
    cout << "Max from {2,7,9,3,1}: " << houseRobber(houses) << "\n";  // 12: 2+9+1

    // --- DP Approach Summary ---
    cout << "\n--- Memoization vs Tabulation ---\n";
    cout << "Memoization:  Recursive + cache, computes only needed states\n";
    cout << "Tabulation:   Iterative table-fill, no recursion overhead\n";
    cout << "Both have same time complexity O(states * transitions)\n";

    cout << "\n--- Steps to Solve DP Problems ---\n";
    cout << "1. Identify the state (what defines a subproblem?)\n";
    cout << "2. Write the recurrence relation\n";
    cout << "3. Identify base cases\n";
    cout << "4. Choose memoization or tabulation\n";
    cout << "5. (Optional) Optimize space\n";

    return 0;
}
