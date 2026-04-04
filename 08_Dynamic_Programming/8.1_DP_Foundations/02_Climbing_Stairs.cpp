/*
 * 02_Climbing_Stairs.cpp
 * Topic: Climbing Stairs - Classic DP Problem
 *
 * PROBLEM:
 * You are climbing a staircase with n steps.
 * Each time you can climb 1 or 2 steps.
 * In how many distinct ways can you climb to the top?
 *
 * EXAMPLE:
 * n = 3
 * Ways:  1+1+1, 1+2, 2+1
 * Answer: 3 ways
 *
 * WHY IS THIS DP?
 * Think about it: to reach step n, you could have come from:
 *   - Step n-1 (then took 1 step), OR
 *   - Step n-2 (then took 2 steps)
 *
 * So: ways(n) = ways(n-1) + ways(n-2)
 *
 * This is the SAME recurrence as Fibonacci!
 *   ways(0) = 1  (one way: do nothing)
 *   ways(1) = 1  (only 1 step)
 *   ways(2) = 2  (1+1 or 2)
 *   ways(3) = 3  (1+1+1, 1+2, 2+1)
 *   ways(4) = 5
 *   ways(5) = 8
 *
 * This problem has both DP properties:
 *   - Overlapping subproblems: same subproblems computed many times
 *   - Optimal substructure: answer built from sub-answers
 */

#include <iostream>

using namespace std;

/* ============================================================
 * APPROACH 1: NAIVE RECURSION - O(2^n)
 * ============================================================
 * Direct translation of the recurrence.
 * Recomputes same values many times. Very slow.
 */

int climbStairsNaive(int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 1;
    }
    return climbStairsNaive(n - 1) + climbStairsNaive(n - 2);
}

/* ============================================================
 * APPROACH 2: MEMOIZATION - O(n)
 * ============================================================
 * Add memo array to avoid recomputation.
 */

int climbStairsMemoHelper(int n, int memo[]) {
    if (memo[n] != -1) {
        return memo[n];
    }
    memo[n] = climbStairsMemoHelper(n - 1, memo) + climbStairsMemoHelper(n - 2, memo);
    return memo[n];
}

int climbStairsMemo(int n) {
    int memo[50];
    int i;
    for (i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    memo[0] = 1;
    memo[1] = 1;
    return climbStairsMemoHelper(n, memo);
}

/* ============================================================
 * APPROACH 3: TABULATION - O(n)
 * ============================================================
 * Build table bottom-up.
 *
 * dp[i] = number of ways to reach step i
 * dp[i] = dp[i-1] + dp[i-2]
 */

int climbStairsTab(int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 1;
    }

    int dp[50];
    dp[0] = 1;
    dp[1] = 1;

    int i;
    for (i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

/* ============================================================
 * APPROACH 4: SPACE OPTIMIZED - O(n) time, O(1) space
 * ============================================================
 * Only need last two values.
 */

int climbStairsSpaceOpt(int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 1;
    }

    int prev2 = 1; // ways(0)
    int prev1 = 1; // ways(1)
    int curr = 0;
    int i;

    for (i = 2; i <= n; i++) {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return curr;
}

/* ============================================================
 * APPROACH 5: VARIABLE STEPS (can take 1, 2, or m steps)
 * ============================================================
 * Generalized version: you can take 1, 2, 3, ..., up to m steps at once.
 *
 * Recurrence: ways(n) = ways(n-1) + ways(n-2) + ... + ways(n-m)
 * (for all valid n-k >= 0)
 *
 * For m = 2, this reduces to the original problem.
 * For m = 3: ways(n) = ways(n-1) + ways(n-2) + ways(n-3)
 */

int climbStairsVariableSteps(int n, int m) {
    int dp[50];

    // Base case: 1 way to stay at ground (do nothing)
    dp[0] = 1;

    int i, j;
    for (i = 1; i <= n; i++) {
        dp[i] = 0;
        // Try all step sizes from 1 to m
        for (j = 1; j <= m; j++) {
            if (i - j >= 0) {
                dp[i] = dp[i] + dp[i - j];
            }
        }
    }

    return dp[n];
}

/* ============================================================
 * HELPER: Print all ways to climb n stairs (for small n)
 * Uses backtracking to show actual paths
 * ============================================================
 */

void printWaysHelper(int remaining, int path[], int pathLen) {
    if (remaining == 0) {
        int i;
        cout << "  [";
        for (i = 0; i < pathLen; i++) {
            cout << path[i];
            if (i < pathLen - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
        return;
    }

    if (remaining >= 1) {
        path[pathLen] = 1;
        printWaysHelper(remaining - 1, path, pathLen + 1);
    }
    if (remaining >= 2) {
        path[pathLen] = 2;
        printWaysHelper(remaining - 2, path, pathLen + 1);
    }
}

void printAllWays(int n) {
    int path[20];
    cout << "All ways to climb " << n << " stairs:" << endl;
    printWaysHelper(n, path, 0);
}

/* ============================================================
 * MAIN
 * ============================================================
 */

int main() {
    int n = 6;

    cout << "=== CLIMBING STAIRS DP ===" << endl;
    cout << endl;

    // Show all actual ways for small n
    cout << "--- All Ways (n = 4) ---" << endl;
    printAllWays(4);
    cout << endl;

    // Show sequence
    cout << "--- Number of ways for n = 0 to " << n << " ---" << endl;
    int i;
    for (i = 0; i <= n; i++) {
        cout << "  n = " << i << " : " << climbStairsSpaceOpt(i) << " ways" << endl;
    }
    cout << endl;

    // Compare approaches
    cout << "--- Computing ways(" << n << ") with all approaches ---" << endl;
    cout << "  Naive Recursion:  " << climbStairsNaive(n) << endl;
    cout << "  Memoization:      " << climbStairsMemo(n) << endl;
    cout << "  Tabulation:       " << climbStairsTab(n) << endl;
    cout << "  Space Optimized:  " << climbStairsSpaceOpt(n) << endl;
    cout << endl;

    // Key insight
    cout << "=== KEY INSIGHT ===" << endl;
    cout << endl;
    cout << "Climbing Stairs IS Fibonacci!" << endl;
    cout << "  fib: 0, 1, 1, 2, 3, 5, 8, 13, 21, ..." << endl;
    cout << "  stairs: 1, 1, 2, 3, 5, 8, 13, 21, 34, ..." << endl;
    cout << "  ways(n) = fib(n+1)" << endl;
    cout << endl;

    // Variable steps example
    cout << "=== VARIABLE STEPS VERSION ===" << endl;
    cout << endl;
    cout << "If you can take 1, 2, or 3 steps at a time (m=3):" << endl;
    for (i = 0; i <= n; i++) {
        cout << "  n = " << i << " : " << climbStairsVariableSteps(i, 3) << " ways" << endl;
    }
    cout << endl;

    cout << "If you can take 1 or 2 steps at a time (m=2):" << endl;
    for (i = 0; i <= n; i++) {
        cout << "  n = " << i << " : " << climbStairsVariableSteps(i, 2) << " ways" << endl;
    }
    cout << endl;

    // Recurrence summary
    cout << "=== RECURRENCE SUMMARY ===" << endl;
    cout << endl;
    cout << "Original (1 or 2 steps):" << endl;
    cout << "  dp[i] = dp[i-1] + dp[i-2]" << endl;
    cout << endl;
    cout << "Variable (1 to m steps):" << endl;
    cout << "  dp[i] = dp[i-1] + dp[i-2] + ... + dp[i-m]" << endl;
    cout << "  (for all terms where i-k >= 0)" << endl;

    return 0;
}
