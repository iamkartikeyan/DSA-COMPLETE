/*
 * 06_DP_Steps_Framework.cpp
 * Topic: General Framework for Solving ANY DP Problem
 *
 * This file summarizes the systematic approach to solving
 * Dynamic Programming problems and when to use which technique.
 *
 * ============================================================
 * 5 STEPS TO SOLVE ANY DP PROBLEM
 * ============================================================
 *
 * STEP 1: IDENTIFY THE STATE
 *   - What is the minimum information needed to describe a subproblem?
 *   - Examples:
 *       fib(n)         -> state is just: n
 *       dp[i]          -> state is just: index i
 *       dp[i][w]       -> state is: index i, remaining capacity w
 *       dp[idx][amount]-> state is: current index, remaining amount
 *   - The state determines the dimensions of your DP table.
 *
 * STEP 2: WRITE THE RECURRENCE RELATION
 *   - How does the answer for state S depend on answers for smaller states?
 *   - Think: "What choices do I have at this state?"
 *   - Examples:
 *       fib(n)     = fib(n-1) + fib(n-2)
 *       climb(n)   = climb(n-1) + climb(n-2)
 *       rob(i)     = max(money[i] + rob(i-2), rob(i-1))
 *       dp[i]      = min(dp[i-coin] + 1)  for all coins
 *       dp[i]      = max(dp[j] + 1)       for all j < i where arr[j] < arr[i]
 *
 * STEP 3: IDENTIFY BASE CASES
 *   - What are the smallest subproblems with obvious answers?
 *   - Examples:
 *       fib(0) = 0, fib(1) = 1
 *       dp[0] = 0  (zero amount needs zero coins)
 *       dp[i] = 1  (every element is an LIS of length 1 by itself)
 *
 * STEP 4: CHOOSE APPROACH (Memoization or Tabulation)
 *   - Memoization: Start recursive, add memo array. Easy to write.
 *   - Tabulation: Remove recursion, fill table iteratively.
 *
 * STEP 5: OPTIMIZE SPACE (if possible)
 *   - Can you reduce the DP table size?
 *   - If dp[i] only depends on dp[i-1] and dp[i-2], use 2 variables.
 *   - If dp[i] depends on dp[0..i-1], you need the full array.
 *
 * ============================================================
 * WHEN TO USE MEMOIZATION vs TABULATION
 * ============================================================
 *
 * USE MEMOIZATION WHEN:
 *   1. You only need SOME subproblems (not all)
 *      Example: if transitions are conditional, many states may be unreachable
 *   2. You want a quick solution from a recursive approach
 *      (just add memo array to existing recursive code)
 *   3. The state space is sparse or complex
 *   4. Base cases are tricky to order in bottom-up
 *
 * USE TABULATION WHEN:
 *   1. You need ALL subproblems anyway
 *   2. You want maximum efficiency (no recursion overhead)
 *   3. You need to optimize space
 *   4. Stack overflow is a concern (deep recursion)
 *   5. You need to reconstruct the solution path
 *
 * ============================================================
 * COMMON DP PATTERNS SUMMARY
 * ============================================================
 *
 * 1. LINEAR DP (1D array)
 *    State: dp[i] = answer for subproblem ending at / up to index i
 *    Examples: Fibonacci, Climbing Stairs, House Robber, LIS
 *    Transition: dp[i] = f(dp[0], dp[1], ..., dp[i-1])
 *
 * 2. KNAPSACK-STYLE DP (2D array)
 *    State: dp[i][w] = answer using items 0..i with capacity w
 *    Examples: 0/1 Knapsack, Coin Change, Subset Sum
 *    Transition: dp[i][w] = max/min(take item i, skip item i)
 *
 * 3. STRING DP (2D array)
 *    State: dp[i][j] = answer for first i chars of string1, first j of string2
 *    Examples: LCS, Edit Distance, Longest Palindromic Subsequence
 *    Transition: depends on whether chars match or not
 *
 * 4. GRID / MATRIX DP (2D array)
 *    State: dp[i][j] = answer for reaching cell (i, j)
 *    Examples: Minimum path sum, Unique paths, Max square of 1s
 *    Transition: dp[i][j] = f(dp[i-1][j], dp[i][j-1], ...)
 *
 * 5. INTERVAL DP (2D array)
 *    State: dp[i][j] = answer for subarray from index i to j
 *    Examples: Matrix Chain Multiplication, Burst Balloons
 *    Transition: dp[i][j] = f(dp[i][k], dp[k+1][j]) for all k in [i, j)
 *
 * ============================================================
 * DECISION TREE: IS THIS A DP PROBLEM?
 * ============================================================
 *
 * Ask yourself:
 *
 * 1. Can I break this problem into smaller subproblems?
 *       -> If NO: probably not DP
 *       -> If YES: go to 2
 *
 * 2. Are subproblems OVERLAPPING? (same subproblem solved multiple times)
 *       -> If NO: use Divide and Conquer instead
 *       -> If YES: go to 3
 *
 * 3. Does the optimal solution depend on optimal solutions of subproblems?
 *       -> If NO: probably Greedy
 *       -> If YES: this is DP!
 *
 * ============================================================
 * QUICK REFERENCE: ALL PATTERNS FROM THIS FOLDER
 * ============================================================
 *
 * Problem              | State      | Recurrence                              | Pattern
 * ---------------------|------------|-----------------------------------------|----------
 * Fibonacci            | dp[i]      | dp[i] = dp[i-1] + dp[i-2]              | Linear
 * Climbing Stairs      | dp[i]      | dp[i] = dp[i-1] + dp[i-2]              | Linear
 * House Robber         | dp[i]      | dp[i] = max(arr[i]+dp[i-2], dp[i-1])   | Linear
 * Min Coins            | dp[i]      | dp[i] = min(dp[i-c]+1) for all c       | Knapsack
 * LIS                  | dp[i]      | dp[i] = max(dp[j]+1) for j<i, arr[j]<arr[i] | Linear
 */

#include <iostream>

using namespace std;

/* ============================================================
 * DEMONSTRATION: Same problem solved with the 5-step framework
 * Let's solve House Robber step by step.
 * ============================================================
 */

/* Helper: max of two */
int maxInt(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

/*
 * STEP 1: State -> dp[i] = max money from houses 0 to i
 * STEP 2: Recurrence -> dp[i] = max(money[i] + dp[i-2], dp[i-1])
 * STEP 3: Base cases -> dp[0] = money[0], dp[1] = max(money[0], money[1])
 * STEP 4: Approach -> Tabulation (we need all subproblems)
 * STEP 5: Space opt -> Only need prev2 and prev1
 */

int houseRobber(int money[], int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return money[0];
    }

    /* Step 4: Tabulation with Step 5: Space optimization */
    int prev2 = 0;          /* dp[-1] = 0 */
    int prev1 = money[0];   /* dp[0] */
    int curr = prev1;
    int i;

    for (i = 1; i <= n; i++) {
        /* Step 2: Apply recurrence */
        curr = maxInt(money[i] + prev2, prev1);
        prev2 = prev1;
        prev1 = curr;
    }

    return curr;
}

/* ============================================================
 * DEMONSTRATION: Walk through the 5 steps for Min Coins
 * ============================================================
 */

/* Helper: min of two */
int minInt(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

const int INF = 999999;

/*
 * STEP 1: State -> dp[i] = min coins to make amount i
 * STEP 2: Recurrence -> dp[i] = min(dp[i-c] + 1) for all coins c
 * STEP 3: Base cases -> dp[0] = 0, dp[i] = INF for i > 0
 * STEP 4: Approach -> Tabulation (we need all amounts from 0 to target)
 * STEP 5: Space opt -> Need full array (dp[i] can depend on any dp[i-c])
 */

int minCoins(int coins[], int n, int amount) {
    int dp[200];
    int i, j;

    /* Step 3: Base cases */
    dp[0] = 0;
    for (i = 1; i <= amount; i++) {
        dp[i] = INF;
    }

    /* Step 4: Tabulation, Step 2: Recurrence */
    for (i = 1; i <= amount; i++) {
        for (j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INF) {
                dp[i] = minInt(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }

    if (dp[amount] == INF) {
        return -1;
    }
    return dp[amount];
}

/* ============================================================
 * MAIN: Summary and demonstrations
 * ============================================================
 */

int main() {
    cout << "=== DP PROBLEM-SOLVING FRAMEWORK ===" << endl;
    cout << endl;

    /* --- The 5 Steps --- */
    cout << "=== THE 5 STEPS ===" << endl;
    cout << endl;
    cout << "Step 1: Identify the State" << endl;
    cout << "        What defines a subproblem? (usually index, amount, etc.)" << endl;
    cout << "        This determines your DP table dimensions." << endl;
    cout << endl;
    cout << "Step 2: Write the Recurrence Relation" << endl;
    cout << "        How does the answer depend on smaller subproblems?" << endl;
    cout << "        Think about the CHOICES at each state." << endl;
    cout << endl;
    cout << "Step 3: Identify Base Cases" << endl;
    cout << "        What are the smallest subproblems with obvious answers?" << endl;
    cout << "        These are your starting points." << endl;
    cout << endl;
    cout << "Step 4: Choose Approach (Memoization or Tabulation)" << endl;
    cout << "        Memoization: recursive + cache (easier)" << endl;
    cout << "        Tabulation: iterative table fill (faster)" << endl;
    cout << endl;
    cout << "Step 5: Optimize Space" << endl;
    cout << "        Can you reduce the DP table size?" << endl;
    cout << "        If dp[i] only needs last 2 values -> O(1) space" << endl;
    cout << "        If dp[i] needs any previous value -> keep full array" << endl;
    cout << endl;

    /* --- When to use which --- */
    cout << "=== MEMOIZATION vs TABULATION ===" << endl;
    cout << endl;
    cout << "Use Memoization when:" << endl;
    cout << "  - Not all subproblems are needed" << endl;
    cout << "  - Quick conversion from recursive solution" << endl;
    cout << "  - Complex or sparse state space" << endl;
    cout << endl;
    cout << "Use Tabulation when:" << endl;
    cout << "  - All subproblems are needed" << endl;
    cout << "  - Maximum efficiency required" << endl;
    cout << "  - Space optimization is important" << endl;
    cout << "  - Deep recursion causes stack overflow" << endl;
    cout << endl;

    /* --- Common patterns --- */
    cout << "=== COMMON DP PATTERNS ===" << endl;
    cout << endl;
    cout << "1. LINEAR DP (1D)" << endl;
    cout << "   dp[i] = answer for subproblem at index i" << endl;
    cout << "   Examples: Fibonacci, Climbing Stairs, House Robber, LIS" << endl;
    cout << endl;
    cout << "2. KNAPSACK-STYLE (2D)" << endl;
    cout << "   dp[i][w] = answer using items 0..i with capacity w" << endl;
    cout << "   Examples: 0/1 Knapsack, Coin Change, Subset Sum" << endl;
    cout << endl;
    cout << "3. STRING DP (2D)" << endl;
    cout << "   dp[i][j] = answer for prefixes of two strings" << endl;
    cout << "   Examples: LCS, Edit Distance" << endl;
    cout << endl;
    cout << "4. GRID / MATRIX DP (2D)" << endl;
    cout << "   dp[i][j] = answer for reaching cell (i,j)" << endl;
    cout << "   Examples: Min path sum, Unique paths" << endl;
    cout << endl;
    cout << "5. INTERVAL DP (2D)" << endl;
    cout << "   dp[i][j] = answer for subarray from i to j" << endl;
    cout << "   Examples: Matrix Chain Multiplication" << endl;
    cout << endl;

    /* --- Is it DP? --- */
    cout << "=== IS THIS A DP PROBLEM? ===" << endl;
    cout << endl;
    cout << "Ask these questions:" << endl;
    cout << "  1. Can I break it into smaller subproblems?" << endl;
    cout << "  2. Are subproblems OVERLAPPING? (recomputed?)" << endl;
    cout << "  3. Does optimal answer build from optimal sub-answers?" << endl;
    cout << "  If YES to all -> It is DP!" << endl;
    cout << endl;

    /* --- Quick demo --- */
    cout << "=== DEMO: 5-Step Framework Applied ===" << endl;
    cout << endl;

    int money[] = {2, 7, 9, 3, 1};
    int n = 4;
    cout << "House Robber: [2, 7, 9, 3, 1]" << endl;
    cout << "  Step 1: State = dp[i] = max money from houses 0..i" << endl;
    cout << "  Step 2: dp[i] = max(money[i] + dp[i-2], dp[i-1])" << endl;
    cout << "  Step 3: dp[0] = 2, dp[1] = 7" << endl;
    cout << "  Step 4: Tabulation with space optimization" << endl;
    cout << "  Step 5: Use 2 variables instead of array" << endl;
    cout << "  Answer: " << houseRobber(money, n) << endl;
    cout << endl;

    int coins[] = {1, 3, 4};
    int amount = 6;
    cout << "Min Coins: coins=[1,3,4], amount=6" << endl;
    cout << "  Step 1: State = dp[i] = min coins for amount i" << endl;
    cout << "  Step 2: dp[i] = min(dp[i-c] + 1) for all coins c" << endl;
    cout << "  Step 3: dp[0] = 0, dp[i>0] = INF" << endl;
    cout << "  Step 4: Tabulation (need all amounts)" << endl;
    cout << "  Step 5: Cannot optimize (dp[i] depends on any dp[i-c])" << endl;
    cout << "  Answer: " << minCoins(coins, 3, amount) << endl;
    cout << endl;

    /* --- Summary table --- */
    cout << "=== PROBLEMS IN THIS FOLDER ===" << endl;
    cout << endl;
    cout << "| Problem       | State | Recurrence                    | Space  |" << endl;
    cout << "|---------------|-------|-------------------------------|--------|" << endl;
    cout << "| Fibonacci     | dp[i] | dp[i-1]+dp[i-2]               | O(1)   |" << endl;
    cout << "| Climbing Stairs| dp[i]| dp[i-1]+dp[i-2]               | O(1)   |" << endl;
    cout << "| House Robber  | dp[i] | max(arr[i]+dp[i-2],dp[i-1])  | O(1)   |" << endl;
    cout << "| Min Coins     | dp[i] | min(dp[i-c]+1)                | O(m)   |" << endl;
    cout << "| LIS           | dp[i] | max(dp[j]+1) j<i, arr[j]<arr[i]| O(n) |" << endl;
    cout << endl;

    cout << "Time to master DP: Practice! Start with these basics," << endl;
    cout << "then move to 2D DP, then advanced patterns." << endl;

    return 0;
}
