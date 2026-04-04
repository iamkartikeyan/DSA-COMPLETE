/*
 * 05_Longest_Increasing_Subsequence.cpp
 * Topic: LIS - O(n^2) DP Solution
 *
 * PROBLEM:
 * Given an array of integers, find the length of the LONGEST
 * STRICTLY INCREASING subsequence.
 *
 * A subsequence: you can skip elements but cannot reorder.
 * Strictly increasing: each element must be greater than the previous.
 *
 * EXAMPLE:
 *   arr = [10, 22, 9, 33, 21, 50, 41, 60]
 *
 *   Some increasing subsequences:
 *     [10, 22, 33, 50, 60]  -> length 5
 *     [10, 22, 33, 41, 60]  -> length 5
 *     [10, 22, 33, 50]      -> length 4
 *     [9, 21, 41, 60]       -> length 4
 *     [10, 22, 33]          -> length 3
 *
 *   LIS = [10, 22, 33, 50, 60] or [10, 22, 33, 41, 60]
 *   Length = 5
 *
 * WHY IS THIS DP?
 *
 * STATE:
 *   dp[i] = length of the Longest Increasing Subsequence that ENDS at index i
 *
 * TRANSITION:
 *   For each j < i:
 *     If arr[j] < arr[i], then we can extend the subsequence ending at j
 *     dp[i] = max(dp[i], dp[j] + 1)
 *
 *   If no j < i has arr[j] < arr[i], then dp[i] = 1 (just the element itself)
 *
 * BASE CASE:
 *   Every element is an increasing subsequence of length 1 by itself.
 *   Initialize all dp[i] = 1.
 *
 * ANSWER:
 *   max(dp[0], dp[1], ..., dp[n-1])
 *
 * WALKTHROUGH: arr = [10, 22, 9, 33, 21, 50, 41, 60]
 *
 *   Initialize: dp = [1, 1, 1, 1, 1, 1, 1, 1]
 *
 *   i = 0: arr[0] = 10
 *          no j < 0, dp[0] stays 1
 *
 *   i = 1: arr[1] = 22
 *          j = 0: arr[0]=10 < 22, dp[1] = max(1, dp[0]+1) = max(1, 2) = 2
 *          dp[1] = 2  -> subsequence: [10, 22]
 *
 *   i = 2: arr[2] = 9
 *          j = 0: arr[0]=10 > 9, skip
 *          j = 1: arr[1]=22 > 9, skip
 *          dp[2] = 1  -> subsequence: [9]
 *
 *   i = 3: arr[3] = 33
 *          j = 0: arr[0]=10 < 33, dp[3] = max(1, dp[0]+1) = 2
 *          j = 1: arr[1]=22 < 33, dp[3] = max(2, dp[1]+1) = 3
 *          j = 2: arr[2]=9 < 33,  dp[3] = max(3, dp[2]+1) = 3 (no change)
 *          dp[3] = 3  -> subsequence: [10, 22, 33]
 *
 *   i = 4: arr[4] = 21
 *          j = 0: arr[0]=10 < 21, dp[4] = max(1, dp[0]+1) = 2
 *          j = 1: arr[1]=22 > 21, skip
 *          j = 2: arr[2]=9 < 21,  dp[4] = max(2, dp[2]+1) = 2 (no change)
 *          j = 3: arr[3]=33 > 21, skip
 *          dp[4] = 2  -> subsequence: [10, 21]
 *
 *   i = 5: arr[5] = 50
 *          j = 0: 10 < 50, dp[5] = max(1, 2) = 2
 *          j = 1: 22 < 50, dp[5] = max(2, 3) = 3
 *          j = 2: 9 < 50,  dp[5] = max(3, 2) = 3 (no change)
 *          j = 3: 33 < 50, dp[5] = max(3, 4) = 4
 *          j = 4: 21 < 50, dp[5] = max(4, 3) = 4 (no change)
 *          dp[5] = 4  -> subsequence: [10, 22, 33, 50]
 *
 *   i = 6: arr[6] = 41
 *          j = 0: 10 < 41, dp[6] = 2
 *          j = 1: 22 < 41, dp[6] = 3
 *          j = 2: 9 < 41,  dp[6] = 3 (no change)
 *          j = 3: 33 < 41, dp[6] = 4
 *          j = 4: 21 < 41, dp[6] = max(4, 3) = 4 (no change)
 *          j = 5: 50 > 41, skip
 *          dp[6] = 4  -> subsequence: [10, 22, 33, 41]
 *
 *   i = 7: arr[7] = 60
 *          j = 0: 10 < 60, dp[7] = 2
 *          j = 1: 22 < 60, dp[7] = 3
 *          j = 2: 9 < 60,  dp[7] = 3 (no change)
 *          j = 3: 33 < 60, dp[7] = 4
 *          j = 4: 21 < 60, dp[7] = max(4, 3) = 4 (no change)
 *          j = 5: 50 < 60, dp[7] = max(4, 5) = 5
 *          j = 6: 41 < 60, dp[7] = max(5, 5) = 5 (no change)
 *          dp[7] = 5  -> subsequence: [10, 22, 33, 50, 60]
 *
 *   Final dp = [1, 2, 1, 3, 2, 4, 4, 5]
 *   Max = 5
 *   Answer: 5
 */

#include <iostream>

using namespace std;

/* Helper: return maximum of two integers */
int maxInt(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

/* Helper: return maximum value in array */
int maxInArray(int arr[], int n) {
    int maxVal = arr[0];
    int i;
    for (i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

/* ============================================================
 * LIS: O(n^2) DP Solution
 * ============================================================
 * dp[i] = length of LIS ending at index i
 */

int lis(int arr[], int n) {
    if (n == 0) {
        return 0;
    }

    int dp[100];
    int i, j;

    // Initialize: every element is an LIS of length 1 by itself
    for (i = 0; i < n; i++) {
        dp[i] = 1;
    }

    // Fill dp table
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = maxInt(dp[i], dp[j] + 1);
            }
        }
    }

    // Answer is the maximum in dp array
    return maxInArray(dp, n);
}

/* ============================================================
 * LIS: Print the actual subsequence (not just length)
 * ============================================================
 */

void printLIS(int arr[], int n) {
    if (n == 0) {
        return;
    }

    int dp[100];
    int parent[100];  // to reconstruct the path
    int i, j;

    // Initialize
    for (i = 0; i < n; i++) {
        dp[i] = 1;
        parent[i] = -1;  // no parent
    }

    // Fill dp and parent
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }

    // Find the index with maximum dp value
    int maxIdx = 0;
    for (i = 1; i < n; i++) {
        if (dp[i] > dp[maxIdx]) {
            maxIdx = i;
        }
    }

    // Reconstruct the LIS by following parent pointers
    int lis[100];
    int lisLen = 0;
    int curr = maxIdx;
    while (curr != -1) {
        lis[lisLen] = arr[curr];
        lisLen++;
        curr = parent[curr];
    }

    // Print in correct order (we built it backwards)
    cout << "  One LIS: [";
    for (i = lisLen - 1; i >= 0; i--) {
        cout << lis[i];
        if (i > 0) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    cout << "  Length: " << lisLen << endl;

    // Print dp array
    cout << "  DP array: [";
    for (i = 0; i < n; i++) {
        cout << dp[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

/* ============================================================
 * MAIN
 * ============================================================
 */

int main() {
    cout << "=== LONGEST INCREASING SUBSEQUENCE (LIS) ===" << endl;
    cout << endl;

    // Example 1
    int arr1[] = {10, 22, 9, 33, 21, 50, 41, 60};
    int n1 = 8;

    cout << "Example 1:" << endl;
    cout << "  Array: [10, 22, 9, 33, 21, 50, 41, 60]" << endl;
    cout << "  LIS length: " << lis(arr1, n1) << endl;
    cout << endl;
    printLIS(arr1, n1);
    cout << endl;

    // Example 2: Already sorted
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = 5;

    cout << "Example 2 (already sorted):" << endl;
    cout << "  Array: [1, 2, 3, 4, 5]" << endl;
    cout << "  LIS length: " << lis(arr2, n2) << endl;
    printLIS(arr2, n2);
    cout << endl;

    // Example 3: Reverse sorted (LIS is 1)
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = 5;

    cout << "Example 3 (reverse sorted):" << endl;
    cout << "  Array: [5, 4, 3, 2, 1]" << endl;
    cout << "  LIS length: " << lis(arr3, n3) << endl;
    printLIS(arr3, n3);
    cout << endl;

    // Example 4: All same (LIS is 1, not strictly increasing)
    int arr4[] = {3, 3, 3, 3};
    int n4 = 4;

    cout << "Example 4 (all same):" << endl;
    cout << "  Array: [3, 3, 3, 3]" << endl;
    cout << "  LIS length: " << lis(arr4, n4) << endl;
    cout << "  (Strictly increasing, so no duplicates allowed)" << endl;
    printLIS(arr4, n4);
    cout << endl;

    // Example 5: Classic example
    int arr5[] = {3, 10, 2, 1, 20};
    int n5 = 5;

    cout << "Example 5:" << endl;
    cout << "  Array: [3, 10, 2, 1, 20]" << endl;
    cout << "  LIS length: " << lis(arr5, n5) << endl;
    printLIS(arr5, n5);
    cout << endl;

    // Summary
    cout << "=== RECURRENCE ===" << endl;
    cout << endl;
    cout << "  dp[i] = 1  (initialized, element alone)" << endl;
    cout << "  dp[i] = max(dp[i], dp[j] + 1)  for all j < i where arr[j] < arr[i]" << endl;
    cout << "  Answer = max(dp[0], dp[1], ..., dp[n-1])" << endl;
    cout << endl;
    cout << "  Time:  O(n^2) - nested loops" << endl;
    cout << "  Space: O(n)    - dp array" << endl;
    cout << endl;
    cout << "  Note: There exists an O(n log n) solution using" << endl;
    cout << "  binary search and a 'tails' array. That is an" << endl;
    cout << "  advanced technique covered separately." << endl;

    return 0;
}
