/*
 * 03_House_Robber.cpp
 * Topic: Maximum Sum of Non-Adjacent Elements
 *
 * PROBLEM:
 * You are a robber planning to rob houses along a street.
 * Each house has a certain amount of money.
 * CONSTRAINT: You cannot rob two adjacent houses
 *              (security system will trigger an alarm).
 *
 * Given an array of house values, find the MAXIMUM money
 * you can rob without triggering the alarm.
 *
 * EXAMPLE:
 *   houses = [2, 7, 9, 3, 1]
 *
 *   Bad choice: rob all = 2+7+9+3+1 = 22 (ALARM! adjacent houses robbed)
 *   Good choice:  rob houses 0, 2, 4 = 2+9+1 = 12
 *   Better:       rob houses 1, 3 = 7+3 = 10  (worse)
 *   Best:         rob houses 0, 2, 4 = 2+9+1 = 12... wait
 *                 rob houses 1, 3 = 7+3 = 10
 *                 rob houses 1, 4 = 7+1 = 8
 *                 rob houses 0, 3 = 2+3 = 5
 *                 rob houses 0, 4 = 2+1 = 3
 *
 *   Let me redo: [2, 7, 9, 3, 1]
 *   - Rob index 1 (val 7) + index 3 (val 3) = 10
 *   - Rob index 0 (val 2) + index 2 (val 9) + index 4 (val 1) = 12
 *   - Rob index 0 (val 2) + index 3 (val 3) = 5
 *   - Rob index 1 (val 7) + index 4 (val 1) = 8
 *   - Rob index 2 (val 9) + index 4 (val 1) = 10
 *   Answer: 12 (rob houses 0, 2, 4)
 *
 * WHY IS THIS DP?
 * At each house i, you have TWO choices:
 *
 *   Choice 1: ROB this house
 *     - You get money[i]
 *     - You CANNOT rob house i-1
 *     - Best from remaining = money[i] + rob(i-2)
 *
 *   Choice 2: SKIP this house
 *     - You get 0 from this house
 *     - You CAN rob house i-1
 *     - Best from remaining = rob(i-1)
 *
 * RECURRENCE:
 *   rob(i) = max(money[i] + rob(i-2), rob(i-1))
 *
 * BASE CASES:
 *   rob(-1) = 0  (no houses, no money)
 *   rob(0) = money[0]  (only one house, rob it)
 */

#include <iostream>

using namespace std;

/* Helper function: return maximum of two integers */
int maxInt(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

/* ============================================================
 * APPROACH 1: NAIVE RECURSION - O(2^n)
 * ============================================================
 * Direct translation of recurrence. Very slow.
 */

int robberNaive(int money[], int n) {
    // No houses left
    if (n < 0) {
        return 0;
    }
    // Only one house
    if (n == 0) {
        return money[0];
    }
    // Choice 1: rob this house + best from n-2
    int robThis = money[n] + robberNaive(money, n - 2);
    // Choice 2: skip this house, best from n-1
    int skipThis = robberNaive(money, n - 1);
    // Take the better choice
    return maxInt(robThis, skipThis);
}

/* ============================================================
 * APPROACH 2: MEMOIZATION - O(n)
 * ============================================================
 */

int robberMemoHelper(int money[], int n, int memo[]) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return money[0];
    }
    if (memo[n] != -1) {
        return memo[n];
    }
    int robThis = money[n] + robberMemoHelper(money, n - 2, memo);
    int skipThis = robberMemoHelper(money, n - 1, memo);
    memo[n] = maxInt(robThis, skipThis);
    return memo[n];
}

int robberMemo(int money[], int n) {
    int memo[50];
    int i;
    for (i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    return robberMemoHelper(money, n, memo);
}

/* ============================================================
 * APPROACH 3: TABULATION - O(n)
 * ============================================================
 * dp[i] = maximum money you can rob from houses 0 to i
 *
 * dp[i] = max(money[i] + dp[i-2], dp[i-1])
 *
 * Walkthrough for [2, 7, 9, 3, 1]:
 *   dp[0] = 2                          (only house 0)
 *   dp[1] = max(7, 2) = 7              (rob house 1, or house 0)
 *   dp[2] = max(9+2, 7) = 11           (rob house 2+0, or just house 1)
 *   dp[3] = max(3+7, 11) = 11          (rob house 3+1, or dp[2])
 *   dp[4] = max(1+11, 11) = 12         (rob house 4+2, or dp[3])
 *   Answer: 12
 */

int robberTab(int money[], int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return money[0];
    }

    int dp[50];
    dp[0] = money[0];
    dp[1] = maxInt(money[0], money[1]);

    int i;
    for (i = 2; i <= n; i++) {
        dp[i] = maxInt(money[i] + dp[i - 2], dp[i - 1]);
    }

    return dp[n];
}

/* ============================================================
 * APPROACH 4: SPACE OPTIMIZED - O(n) time, O(1) space
 * ============================================================
 * Notice: dp[i] only depends on dp[i-1] and dp[i-2].
 * So we only need two variables.
 *
 *   prev2 = dp[i-2] (best without current and previous)
 *   prev1 = dp[i-1] (best including previous)
 *   curr  = max(money[i] + prev2, prev1)
 */

int robberSpaceOpt(int money[], int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return money[0];
    }

    int prev2 = 0;          // dp[-1] = 0 (no houses)
    int prev1 = money[0];   // dp[0] = money[0]
    int curr = prev1;
    int i;

    for (i = 1; i <= n; i++) {
        curr = maxInt(money[i] + prev2, prev1);
        prev2 = prev1;
        prev1 = curr;
    }

    return curr;
}

/* Helper: print array */
void printArray(int arr[], int n) {
    int i;
    cout << "[";
    for (i = 0; i <= n; i++) {
        cout << arr[i];
        if (i < n) {
            cout << ", ";
        }
    }
    cout << "]";
}

/* ============================================================
 * MAIN
 * ============================================================
 */

int main() {
    // Example 1
    int money1[] = {2, 7, 9, 3, 1};
    int n1 = 4;  // 5 elements, last index is 4

    cout << "=== HOUSE ROBBER DP ===" << endl;
    cout << endl;

    cout << "Example 1:" << endl;
    cout << "  Houses: ";
    printArray(money1, n1);
    cout << endl;
    cout << "  Max money (naive):        " << robberNaive(money1, n1) << endl;
    cout << "  Max money (memo):         " << robberMemo(money1, n1) << endl;
    cout << "  Max money (tabulation):   " << robberTab(money1, n1) << endl;
    cout << "  Max money (space opt):    " << robberSpaceOpt(money1, n1) << endl;
    cout << endl;

    // Show DP table
    cout << "  DP Table (tabulation):" << endl;
    cout << "  dp[0] = " << money1[0] << "  (only house 0)" << endl;
    cout << "  dp[1] = max(" << money1[0] << ", " << money1[1] << ") = 7" << endl;
    cout << "  dp[2] = max(" << money1[2] << "+2, 7) = 11" << endl;
    cout << "  dp[3] = max(" << money1[3] << "+7, 11) = 11" << endl;
    cout << "  dp[4] = max(" << money1[4] << "+11, 11) = 12" << endl;
    cout << "  Answer: 12 (rob houses at index 0, 2, 4: values 2+9+1)" << endl;
    cout << endl;

    // Example 2: All same values
    int money2[] = {5, 5, 5, 5, 5, 5};
    int n2 = 5;
    cout << "Example 2:" << endl;
    cout << "  Houses: ";
    printArray(money2, n2);
    cout << endl;
    cout << "  Max money: " << robberSpaceOpt(money2, n2) << endl;
    cout << "  (rob every other house: 5+5+5 = 15)" << endl;
    cout << endl;

    // Example 3: Alternating high-low
    int money3[] = {1, 100, 1, 1, 100, 1};
    int n3 = 5;
    cout << "Example 3:" << endl;
    cout << "  Houses: ";
    printArray(money3, n3);
    cout << endl;
    cout << "  Max money: " << robberSpaceOpt(money3, n3) << endl;
    cout << "  (rob houses at index 1 and 4: 100+100 = 200)" << endl;
    cout << endl;

    // Example 4: Single house
    int money4[] = {42};
    cout << "Example 4:" << endl;
    cout << "  Houses: [42]" << endl;
    cout << "  Max money: " << robberSpaceOpt(money4, 0) << endl;
    cout << endl;

    // Summary
    cout << "=== RECURRENCE ===" << endl;
    cout << endl;
    cout << "  dp[i] = max(money[i] + dp[i-2], dp[i-1])" << endl;
    cout << endl;
    cout << "  At each house, you either:" << endl;
    cout << "    1. Rob it:  get money[i] + best from houses 0..i-2" << endl;
    cout << "    2. Skip it: get best from houses 0..i-1" << endl;
    cout << "  Take whichever gives more money." << endl;
    cout << endl;
    cout << "  Time:  O(n)" << endl;
    cout << "  Space: O(1) with space optimization" << endl;

    return 0;
}
