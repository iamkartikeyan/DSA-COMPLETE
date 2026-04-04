// Subset Sum / Partition Problem
// Given an array of positive integers and a target sum
// Question: Is there a subset that adds up to exactly the target sum?
//
// State: dp[i][j] = true if sum j can be achieved using first i items
// Transition:
//   - Don't include item i: dp[i][j] = dp[i-1][j]
//   - Include item i (if item value <= j): dp[i][j] = dp[i-1][j - item] OR dp[i-1][j]
//
// Also covers: Partition Equal Subset Sum
//   - Check if array can be split into two subsets with equal sum
//   - If total sum is odd, impossible
//   - If total sum is even, check if sum/2 is achievable

#include <iostream>

using namespace std;

// Function to check if a subset with given sum exists
bool subsetSum(int arr[], int n, int target) {
    bool dp[101][10001];

    // Base case: sum 0 is always possible (empty subset)
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    // Base case: with 0 items, no positive sum is possible
    for (int j = 1; j <= target; j++) {
        dp[0][j] = false;
    }

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            // Option 1: Don't include item i
            dp[i][j] = dp[i - 1][j];

            // Option 2: Include item i (if it fits)
            if (j >= arr[i - 1]) {
                if (dp[i - 1][j - arr[i - 1]]) {
                    dp[i][j] = true;
                }
            }
        }
    }

    return dp[n][target];
}

// Function to check if array can be partitioned into two equal sum subsets
bool canPartitionEqualSum(int arr[], int n) {
    // Calculate total sum
    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum = totalSum + arr[i];
    }

    // If total sum is odd, cannot split into two equal parts
    if (totalSum % 2 != 0) {
        return false;
    }

    // Check if subset with sum = totalSum/2 exists
    return subsetSum(arr, n, totalSum / 2);
}

// Helper to print which elements form the subset (backtracking)
void printSubset(int arr[], int n, int target) {
    bool dp[101][10001];

    // Build DP table
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }
    for (int j = 1; j <= target; j++) {
        dp[0][j] = false;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= arr[i - 1]) {
                if (dp[i - 1][j - arr[i - 1]]) {
                    dp[i][j] = true;
                }
            }
        }
    }

    if (!dp[n][target]) {
        cout << "  No subset found!" << endl;
        return;
    }

    // Backtrack to find the subset
    cout << "  Subset: ";
    int i = n, j = target;
    bool first = true;
    while (j > 0 && i > 0) {
        if (dp[i - 1][j]) {
            // Element i was not included
            i--;
        } else {
            // Element i was included
            if (!first) {
                cout << " + ";
            }
            cout << arr[i - 1];
            j = j - arr[i - 1];
            i--;
            first = false;
        }
    }
    cout << " = " << target << endl;
}

int main() {
    cout << "=== Subset Sum ===" << endl;

    // Example 1
    int arr1[] = {3, 34, 4, 12, 5, 2};
    int n1 = 6;
    int target1 = 9;

    cout << "\nArray: ";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
    }
    cout << "\nTarget sum: " << target1 << endl;
    cout << "Subset exists: " << (subsetSum(arr1, n1, target1) ? "Yes" : "No") << endl;
    printSubset(arr1, n1, target1);

    // Example 2
    int target2 = 30;
    cout << "\nArray: ";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
    }
    cout << "\nTarget sum: " << target2 << endl;
    cout << "Subset exists: " << (subsetSum(arr1, n1, target2) ? "Yes" : "No") << endl;

    // Example 3
    int arr2[] = {1, 2, 3, 5};
    int n2 = 4;
    int target3 = 6;

    cout << "\nArray: ";
    for (int i = 0; i < n2; i++) {
        cout << arr2[i] << " ";
    }
    cout << "\nTarget sum: " << target3 << endl;
    cout << "Subset exists: " << (subsetSum(arr2, n2, target3) ? "Yes" : "No") << endl;
    printSubset(arr2, n2, target3);

    cout << "\n=== Partition Equal Subset Sum ===" << endl;

    // Example 4: Can be partitioned
    int arr3[] = {1, 5, 11, 5};
    int n3 = 4;

    cout << "\nArray: ";
    for (int i = 0; i < n3; i++) {
        cout << arr3[i] << " ";
    }
    cout << "\nTotal sum: " << (1 + 5 + 11 + 5) << endl;
    cout << "Can partition into equal subsets: " << (canPartitionEqualSum(arr3, n3) ? "Yes" : "No") << endl;
    cout << "Explanation: {1, 5, 5} and {11} both sum to 11" << endl;

    // Example 5: Cannot be partitioned
    int arr4[] = {1, 2, 3, 5};
    int n4 = 4;

    cout << "\nArray: ";
    for (int i = 0; i < n4; i++) {
        cout << arr4[i] << " ";
    }
    cout << "\nTotal sum: " << (1 + 2 + 3 + 5) << endl;
    cout << "Can partition into equal subsets: " << (canPartitionEqualSum(arr4, n4) ? "Yes" : "No") << endl;
    cout << "Explanation: Sum = 11 (odd), cannot split equally" << endl;

    // Example 6: Can be partitioned
    int arr5[] = {2, 2, 3, 5};
    int n5 = 4;

    cout << "\nArray: ";
    for (int i = 0; i < n5; i++) {
        cout << arr5[i] << " ";
    }
    cout << "\nTotal sum: " << (2 + 2 + 3 + 5) << endl;
    cout << "Can partition into equal subsets: " << (canPartitionEqualSum(arr5, n5) ? "Yes" : "No") << endl;
    cout << "Explanation: Sum = 12, each subset should sum to 6" << endl;

    return 0;
}
