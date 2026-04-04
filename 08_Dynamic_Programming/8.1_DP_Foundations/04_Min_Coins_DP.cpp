/*
 * 04_Min_Coins_DP.cpp
 * Topic: Minimum Coins to Make Amount (Unbounded Knapsack / Coin Change)
 *
 * PROBLEM:
 * You are given coins of different denominations (unlimited supply of each).
 * Find the MINIMUM number of coins needed to make a given amount.
 * If it is impossible, return -1.
 *
 * EXAMPLE:
 *   coins = [1, 3, 4], amount = 6
 *
 *   Possible ways:
 *     6 = 1+1+1+1+1+1  -> 6 coins
 *     6 = 3+3          -> 2 coins  <-- BEST
 *     6 = 4+1+1        -> 3 coins
 *     6 = 3+1+1+1      -> 4 coins
 *     6 = 4+?          -> 4+1+1 = 3 coins
 *   Answer: 2 coins (3+3)
 *
 *   Notice: greedy fails!
 *     Greedy would pick 4 first (largest coin <= 6)
 *     Then 6-4=2, pick 1, then 1
 *     Greedy gives: 4+1+1 = 3 coins (NOT optimal!)
 *
 * WHY IS THIS DP?
 *
 * STATE:
 *   dp[i] = minimum coins needed to make amount i
 *
 * TRANSITION:
 *   For each coin c, if i - c >= 0:
 *     dp[i] = min(dp[i], dp[i - c] + 1)
 *
 *   We try every coin and pick the one that gives minimum total.
 *
 * BASE CASE:
 *   dp[0] = 0  (zero coins needed for amount 0)
 *   dp[i] = infinity for i > 0  (initially, meaning "not yet achievable")
 *
 * ANSWER:
 *   dp[amount]  (or -1 if it is still infinity)
 *
 * WALKTHROUGH: coins = [1, 3, 4], amount = 6
 *
 *   dp[0] = 0
 *   dp[1] = dp[0] + 1 = 1                    (use coin 1)
 *   dp[2] = dp[1] + 1 = 2                    (use coin 1 twice)
 *   dp[3] = min(dp[2]+1, dp[0]+1) = min(3,1) = 1  (use coin 3 directly!)
 *   dp[4] = min(dp[3]+1, dp[1]+1, dp[0]+1) = min(2,2,1) = 1  (use coin 4 directly!)
 *   dp[5] = min(dp[4]+1, dp[2]+1, dp[1]+1) = min(2,3,2) = 2  (4+1 or 3+1+1, best is 4+1)
 *   dp[6] = min(dp[5]+1, dp[3]+1, dp[2]+1) = min(3,2,3) = 2  (3+3 is best!)
 *
 *   Answer: dp[6] = 2
 */

#include <iostream>

using namespace std;

/* Helper: return minimum of two integers */
int minInt(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

/* A large value to represent infinity */
const int INF = 999999;

/* ============================================================
 * APPROACH 1: NAIVE RECURSION - Exponential
 * ============================================================
 * Try every coin at every step. Explore all possibilities.
 */

int minCoinsNaive(int coins[], int n, int amount) {
    // Base case: amount is 0, no more coins needed
    if (amount == 0) {
        return 0;
    }
    // Base case: amount is negative, invalid path
    if (amount < 0) {
        return INF;
    }

    int result = INF;
    int i;
    for (i = 0; i < n; i++) {
        int subResult = minCoinsNaive(coins, n, amount - coins[i]);
        if (subResult != INF) {
            result = minInt(result, subResult + 1);
        }
    }
    return result;
}

/* ============================================================
 * APPROACH 2: MEMOIZATION - O(n * amount)
 * ============================================================
 * dp[amount] = min coins for this amount, memoized
 */

int minCoinsMemoHelper(int coins[], int n, int amount, int memo[]) {
    if (amount == 0) {
        return 0;
    }
    if (amount < 0) {
        return INF;
    }
    if (memo[amount] != -1) {
        return memo[amount];
    }

    int result = INF;
    int i;
    for (i = 0; i < n; i++) {
        int subResult = minCoinsMemoHelper(coins, n, amount - coins[i], memo);
        if (subResult != INF) {
            result = minInt(result, subResult + 1);
        }
    }
    memo[amount] = result;
    return result;
}

int minCoinsMemo(int coins[], int n, int amount) {
    int memo[200];
    int i;
    for (i = 0; i <= amount; i++) {
        memo[i] = -1;
    }
    return minCoinsMemoHelper(coins, n, amount, memo);
}

/* ============================================================
 * APPROACH 3: TABULATION - O(n * amount)
 * ============================================================
 * Build dp table from 0 to amount.
 *
 * dp[0] = 0
 * dp[i] = min over all coins c: dp[i - c] + 1
 */

int minCoinsTab(int coins[], int n, int amount) {
    int dp[200];
    int i, j;

    // Initialize: dp[0] = 0, everything else = infinity
    dp[0] = 0;
    for (i = 1; i <= amount; i++) {
        dp[i] = INF;
    }

    // Fill table
    for (i = 1; i <= amount; i++) {
        for (j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int subResult = dp[i - coins[j]];
                if (subResult != INF) {
                    dp[i] = minInt(dp[i], subResult + 1);
                }
            }
        }
    }

    // Check if amount is achievable
    if (dp[amount] == INF) {
        return -1;
    }
    return dp[amount];
}

/* ============================================================
 * HELPER: Print which coins were used (reconstruct solution)
 * ============================================================
 */

void printCoinBreakdown(int coins[], int n, int amount) {
    int dp[200];
    int i, j;

    dp[0] = 0;
    for (i = 1; i <= amount; i++) {
        dp[i] = INF;
    }

    for (i = 1; i <= amount; i++) {
        for (j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int subResult = dp[i - coins[j]];
                if (subResult != INF) {
                    dp[i] = minInt(dp[i], subResult + 1);
                }
            }
        }
    }

    if (dp[amount] == INF) {
        cout << "  Amount " << amount << " is NOT achievable with given coins" << endl;
        return;
    }

    // Reconstruct which coins were used
    int remaining = amount;
    int count[10];  // count how many of each coin
    for (i = 0; i < n; i++) {
        count[i] = 0;
    }

    while (remaining > 0) {
        for (i = 0; i < n; i++) {
            if (coins[i] <= remaining && dp[remaining - coins[i]] == dp[remaining] - 1) {
                count[i]++;
                remaining = remaining - coins[i];
                break;
            }
        }
    }

    cout << "  Coins used:" << endl;
    for (i = 0; i < n; i++) {
        if (count[i] > 0) {
            cout << "    Coin " << coins[i] << " x " << count[i] << endl;
        }
    }
    cout << "  Total coins: " << dp[amount] << endl;
}

/* ============================================================
 * MAIN
 * ============================================================
 */

int main() {
    cout << "=== MINIMUM COINS DP (COIN CHANGE) ===" << endl;
    cout << endl;

    // Example 1
    int coins1[] = {1, 3, 4};
    int n1 = 3;
    int amount1 = 6;

    cout << "Example 1:" << endl;
    cout << "  Coins: [1, 3, 4]" << endl;
    cout << "  Amount: 6" << endl;
    cout << endl;

    cout << "  DP Table:" << endl;
    cout << "  dp[0] = 0" << endl;
    cout << "  dp[1] = 1  (coin 1)" << endl;
    cout << "  dp[2] = 2  (1+1)" << endl;
    cout << "  dp[3] = 1  (coin 3 directly!)" << endl;
    cout << "  dp[4] = 1  (coin 4 directly!)" << endl;
    cout << "  dp[5] = 2  (4+1)" << endl;
    cout << "  dp[6] = 2  (3+3)" << endl;
    cout << endl;

    cout << "  Results:" << endl;
    cout << "  Naive:    " << minCoinsNaive(coins1, n1, amount1) << endl;
    cout << "  Memo:     " << minCoinsMemo(coins1, n1, amount1) << endl;
    cout << "  Tab:      " << minCoinsTab(coins1, n1, amount1) << endl;
    cout << endl;

    printCoinBreakdown(coins1, n1, amount1);
    cout << endl;

    // Example 2: Impossible case
    int coins2[] = {2, 5};
    int n2 = 2;
    int amount2 = 3;

    cout << "Example 2 (impossible):" << endl;
    cout << "  Coins: [2, 5]" << endl;
    cout << "  Amount: 3" << endl;
    cout << "  Result: " << minCoinsTab(coins2, n2, amount2) << " (not achievable)" << endl;
    cout << endl;

    // Example 3: US-like coins
    int coins3[] = {1, 5, 10, 25};
    int n3 = 4;
    int amount3 = 63;

    cout << "Example 3 (US-like coins):" << endl;
    cout << "  Coins: [1, 5, 10, 25]" << endl;
    cout << "  Amount: 63" << endl;
    cout << "  Result: " << minCoinsTab(coins3, n3, amount3) << " coins" << endl;
    printCoinBreakdown(coins3, n3, amount3);
    cout << endl;

    // Example 4: Show greedy fails
    int coins4[] = {1, 3, 4};
    int n4 = 3;
    int amount4 = 6;

    cout << "=== WHY GREEDY FAILS ===" << endl;
    cout << endl;
    cout << "Coins: [1, 3, 4], Amount: 6" << endl;
    cout << endl;
    cout << "Greedy (always pick largest coin first):" << endl;
    cout << "  Step 1: pick 4, remaining = 2" << endl;
    cout << "  Step 2: pick 1, remaining = 1" << endl;
    cout << "  Step 3: pick 1, remaining = 0" << endl;
    cout << "  Greedy answer: 3 coins (4+1+1)" << endl;
    cout << endl;
    cout << "DP (optimal):" << endl;
    cout << "  DP answer: 2 coins (3+3)" << endl;
    cout << endl;
    cout << "Greedy gives 3 coins, DP gives 2 coins." << endl;
    cout << "Greedy does NOT work for general coin systems!" << endl;
    cout << endl;

    // Summary
    cout << "=== RECURRENCE ===" << endl;
    cout << endl;
    cout << "  dp[0] = 0" << endl;
    cout << "  dp[i] = min(dp[i - coin] + 1) for all coins where i - coin >= 0" << endl;
    cout << "  If dp[i] stays at infinity, amount i is not achievable." << endl;
    cout << endl;
    cout << "  Time:  O(n * amount) where n = number of coin types" << endl;
    cout << "  Space: O(amount)" << endl;
    cout << endl;
    cout << "  This is an UNBOUNDED KNAPSACK variant." << endl;
    cout << "  Each coin can be used unlimited times." << endl;

    return 0;
}
