// 0/1 Knapsack Problem
// Given n items with weights and values, and a knapsack of capacity W
// Each item can be chosen AT MOST ONCE
// Goal: maximize total value without exceeding capacity
// dp[i][w] = max value using items 0..i-1 with capacity w
// Choice: take item i (if weight fits) OR skip item i
// Transition: dp[i][w] = max(dp[i-1][w], value[i-1] + dp[i-1][w-weight[i-1]])

// Also covers: Unbounded Knapsack (item can be used infinitely)

#include <iostream>

using namespace std;

// 0/1 Knapsack: each item can be used at most once
int knapsack01(int weights[], int values[], int n, int W) {
    int dp[101][1001];

    // Base case: 0 items or 0 capacity = 0 value
    for (int w = 0; w <= W; w++) {
        dp[0][w] = 0;
    }
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            // Option 1: Skip item i
            dp[i][w] = dp[i - 1][w];

            // Option 2: Take item i (if it fits)
            if (weights[i - 1] <= w) {
                int takeValue = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                if (takeValue > dp[i][w]) {
                    dp[i][w] = takeValue;
                }
            }
        }
    }

    return dp[n][W];
}

// Unbounded Knapsack: each item can be used infinite times
// dp[w] = max value with capacity w
// Transition: dp[w] = max(dp[w], value[i] + dp[w - weight[i]])
int unboundedKnapsack(int weights[], int values[], int n, int W) {
    int dp[1001];

    // Base case: 0 capacity = 0 value
    for (int w = 0; w <= W; w++) {
        dp[w] = 0;
    }

    // For each item, try to fit it at each capacity
    for (int i = 0; i < n; i++) {
        for (int w = weights[i]; w <= W; w++) {
            int takeValue = values[i] + dp[w - weights[i]];
            if (takeValue > dp[w]) {
                dp[w] = takeValue;
            }
        }
    }

    return dp[W];
}

int main() {
    cout << "=== 0/1 Knapsack ===" << endl;
    cout << "Each item can be used at most once" << endl;

    // Example 1
    int weights1[] = {1, 3, 4, 5};
    int values1[] = {1, 4, 5, 7};
    int n1 = 4;
    int W1 = 7;

    cout << "\nItems (weight, value):" << endl;
    for (int i = 0; i < n1; i++) {
        cout << "  Item " << i + 1 << ": (" << weights1[i] << ", " << values1[i] << ")" << endl;
    }
    cout << "Knapsack capacity: " << W1 << endl;
    cout << "Max value (0/1 Knapsack): " << knapsack01(weights1, values1, n1, W1) << endl;
    cout << "Explanation: Take items 2 and 3 (weight=3+4=7, value=4+5=9)" << endl;

    // Example 2
    int weights2[] = {2, 1, 3};
    int values2[] = {4, 2, 3};
    int n2 = 3;
    int W2 = 4;

    cout << "\nItems (weight, value):" << endl;
    for (int i = 0; i < n2; i++) {
        cout << "  Item " << i + 1 << ": (" << weights2[i] << ", " << values2[i] << ")" << endl;
    }
    cout << "Knapsack capacity: " << W2 << endl;
    cout << "Max value (0/1 Knapsack): " << knapsack01(weights2, values2, n2, W2) << endl;
    cout << "Explanation: Take items 1 and 2 (weight=2+1=3, value=4+2=6)" << endl;

    cout << "\n=== Unbounded Knapsack ===" << endl;
    cout << "Each item can be used infinite times" << endl;

    // Example 3: Same items, but unbounded
    cout << "\nItems (weight, value):" << endl;
    for (int i = 0; i < n1; i++) {
        cout << "  Item " << i + 1 << ": (" << weights1[i] << ", " << values1[i] << ")" << endl;
    }
    cout << "Knapsack capacity: " << W1 << endl;
    cout << "Max value (Unbounded): " << unboundedKnapsack(weights1, values1, n1, W1) << endl;
    cout << "Explanation: Take item 4 once (weight=5, value=7) + item 1 twice (weight=2, value=2) = 9" << endl;

    // Example 4: Coin-like items (good for unbounded)
    int weights3[] = {1, 2, 3};
    int values3[] = {10, 15, 40};
    int n3 = 3;
    int W3 = 6;

    cout << "\nItems (weight, value):" << endl;
    for (int i = 0; i < n3; i++) {
        cout << "  Item " << i + 1 << ": (" << weights3[i] << ", " << values3[i] << ")" << endl;
    }
    cout << "Knapsack capacity: " << W3 << endl;
    cout << "Max value (0/1 Knapsack): " << knapsack01(weights3, values3, n3, W3) << endl;
    cout << "Max value (Unbounded): " << unboundedKnapsack(weights3, values3, n3, W3) << endl;
    cout << "Explanation: Item 3 twice (weight=3+3=6, value=40+40=80)" << endl;

    return 0;
}
