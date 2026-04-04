/*
 * 01_What_Is_DP.cpp
 * Topic: What is Dynamic Programming?
 *
 * Dynamic Programming (DP) is an optimization technique over plain recursion.
 * It works when a problem has TWO properties:
 *
 * 1. Overlapping Subproblems:
 *    - The same subproblem is solved multiple times
 *    - Example: fib(5) calls fib(3) twice, fib(2) three times, etc.
 *    - DP stores results of subproblems so we don't recompute them
 *
 * 2. Optimal Substructure:
 *    - The optimal solution can be built from optimal solutions of subproblems
 *    - Example: fib(n) = fib(n-1) + fib(n-2)
 *
 * Two Approaches:
 *
 * MEMOIZATION (Top-Down):
 *   - Start with the recursive solution
 *   - Add a lookup table (array) to store results
 *   - Before computing, check if result already exists
 *   - If yes, return it. If no, compute and store it.
 *   - Still recursive, but each subproblem solved only once
 *
 * TABULATION (Bottom-Up):
 *   - Remove recursion entirely
 *   - Fill a table iteratively from smallest subproblem to largest
 *   - No function call overhead
 *   - Usually more efficient
 *
 * Fibonacci Example:
 *   fib(0) = 0, fib(1) = 1
 *   fib(n) = fib(n-1) + fib(n-2) for n >= 2
 *
 *   Naive recursion:     O(2^n) time - exponential, terrible
 *   Memoization:         O(n) time, O(n) space for array + call stack
 *   Tabulation:          O(n) time, O(n) space for array
 *   Space optimized:     O(n) time, O(1) space - only store last 2 values
 */

#include <iostream>

using namespace std;

/* ============================================================
 * APPROACH 1: NAIVE RECURSION (NO DP) - O(2^n)
 * ============================================================
 * Simple recursive solution. Recomputes the same values many times.
 *
 * Call tree for fib(5):
 *
 *                    fib(5)
 *                  /        \
 *              fib(4)       fib(3)
 *             /      \      /      \
 *         fib(3)    fib(2) fib(2)  fib(1)
 *        /     \     /    \   /   \
 *     fib(2) fib(1) fib(1)fib(0) ...
 *    /     \
 *  fib(1) fib(0)
 *
 * Notice fib(3) computed twice, fib(2) computed THREE times!
 * This is "Overlapping Subproblems".
 */

int fibNaive(int n) {
    // Base cases
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    // Recursive case: sum of two previous
    return fibNaive(n - 1) + fibNaive(n - 2);
}

/* ============================================================
 * APPROACH 2: MEMOIZATION (TOP-DOWN DP) - O(n)
 * ============================================================
 * Same recursive logic, but we store results in a memo array.
 *
 * memo[i] = -1 means not yet computed
 * memo[i] >= 0  means already computed, just return it
 *
 * This turns O(2^n) into O(n) because each fib(i) is computed ONCE.
 */

int fibMemoHelper(int n, int memo[]) {
    // If already computed, return stored value
    if (memo[n] != -1) {
        return memo[n];
    }
    // Compute and store result
    memo[n] = fibMemoHelper(n - 1, memo) + fibMemoHelper(n - 2, memo);
    return memo[n];
}

int fibMemo(int n) {
    // Create memo array and initialize with -1
    int memo[50];
    int i;
    for (i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    // Base cases
    memo[0] = 0;
    memo[1] = 1;

    return fibMemoHelper(n, memo);
}

/* ============================================================
 * APPROACH 3: TABULATION (BOTTOM-UP DP) - O(n)
 * ============================================================
 * No recursion. Build the table from bottom to top.
 *
 * We fill dp[0], dp[1], dp[2], ..., dp[n] in order.
 * Each dp[i] depends on dp[i-1] and dp[i-2] which are already computed.
 *
 *   dp[0] = 0
 *   dp[1] = 1
 *   dp[2] = dp[1] + dp[0] = 1
 *   dp[3] = dp[2] + dp[1] = 2
 *   dp[4] = dp[3] + dp[2] = 3
 *   dp[5] = dp[4] + dp[3] = 5
 *   ... and so on
 */

int fibTab(int n) {
    int dp[50];

    // Base cases
    dp[0] = 0;
    dp[1] = 1;

    // Fill table bottom-up
    int i;
    for (i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

/* ============================================================
 * APPROACH 4: SPACE OPTIMIZED TABULATION - O(n) time, O(1) space
 * ============================================================
 * Notice: to compute fib(i), we only need fib(i-1) and fib(i-2).
 * We don't need the entire dp array, just the last two values.
 *
 * Use two variables instead of full array.
 * This is the BEST approach for Fibonacci.
 */

int fibSpaceOpt(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    int prev2 = 0; // fib(0)
    int prev1 = 1; // fib(1)
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
 * HELPER: Print first n Fibonacci numbers using a method
 * ============================================================
 */

void printFibSequence(int n) {
    int i;
    cout << "First " << n << " Fibonacci numbers: ";
    for (i = 0; i < n; i++) {
        cout << fibSpaceOpt(i);
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

/* ============================================================
 * MAIN - Demonstrate all 4 approaches
 * ============================================================
 */

int main() {
    int n = 10;

    cout << "=== DYNAMIC PROGRAMMING: FIBONACCI ===" << endl;
    cout << endl;

    cout << "Fibonacci sequence:" << endl;
    printFibSequence(n);
    cout << endl;

    // Test all 4 approaches for fib(10)
    cout << "--- Computing fib(" << n << ") ---" << endl;
    cout << endl;

    cout << "Approach 1: Naive Recursion" << endl;
    cout << "  Result: " << fibNaive(n) << endl;
    cout << "  Time:   O(2^n) - exponential (very slow for large n)" << endl;
    cout << "  Space:  O(n) - call stack" << endl;
    cout << endl;

    cout << "Approach 2: Memoization (Top-Down)" << endl;
    cout << "  Result: " << fibMemo(n) << endl;
    cout << "  Time:   O(n) - each subproblem solved once" << endl;
    cout << "  Space:  O(n) - memo array + call stack" << endl;
    cout << endl;

    cout << "Approach 3: Tabulation (Bottom-Up)" << endl;
    cout << "  Result: " << fibTab(n) << endl;
    cout << "  Time:   O(n) - single loop" << endl;
    cout << "  Space:  O(n) - dp array" << endl;
    cout << endl;

    cout << "Approach 4: Space Optimized" << endl;
    cout << "  Result: " << fibSpaceOpt(n) << endl;
    cout << "  Time:   O(n) - single loop" << endl;
    cout << "  Space:  O(1) - only 3 variables" << endl;
    cout << endl;

    // Show why naive recursion is bad
    cout << "--- Why Naive Recursion is Bad ---" << endl;
    cout << "  fib(40) with naive recursion would make ~2 BILLION calls" << endl;
    cout << "  fib(40) with DP takes only 40 steps" << endl;
    cout << endl;

    // Demonstrate with a smaller value
    int test = 7;
    cout << "All 4 approaches for fib(" << test << "):" << endl;
    cout << "  Naive:       " << fibNaive(test) << endl;
    cout << "  Memo:        " << fibMemo(test) << endl;
    cout << "  Tabulation:  " << fibTab(test) << endl;
    cout << "  Space Optim: " << fibSpaceOpt(test) << endl;
    cout << endl;

    // Key comparison table
    cout << "=== MEMOIZATION vs TABULATION ===" << endl;
    cout << endl;
    cout << "| Aspect          | Memoization      | Tabulation       |" << endl;
    cout << "|-----------------|------------------|------------------|" << endl;
    cout << "| Direction       | Top-down         | Bottom-up        |" << endl;
    cout << "| Style           | Recursive        | Iterative        |" << endl;
    cout << "| Computes        | Only needed      | All subproblems  |" << endl;
    cout << "| Function calls  | Yes (overhead)   | No               |" << endl;
    cout << "| Space           | O(n) + stack     | O(n)             |" << endl;
    cout << "| Easier to write | Yes (just add memo)| Requires thought|" << endl;
    cout << endl;

    cout << "=== WHEN TO USE WHICH? ===" << endl;
    cout << endl;
    cout << "Use Memoization when:" << endl;
    cout << "  - You only need some subproblems (not all)" << endl;
    cout << "  - You want quick conversion from recursive solution" << endl;
    cout << "  - The state space is sparse" << endl;
    cout << endl;
    cout << "Use Tabulation when:" << endl;
    cout << "  - You need ALL subproblems anyway" << endl;
    cout << "  - You want to avoid recursion overhead" << endl;
    cout << "  - You need to optimize space (can often reduce to O(1))" << endl;
    cout << "  - Stack overflow is a concern for large inputs" << endl;

    return 0;
}
