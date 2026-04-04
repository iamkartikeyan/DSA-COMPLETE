// Coin Change Problem
// Two variations:
// Variation 1: Minimum number of coins to make a given amount
//   dp[i] = minimum coins needed to make amount i
//   Transition: dp[i] = min(dp[i], dp[i - coin] + 1) for each coin
//
// Variation 2: Count total number of ways to make a given amount
//   dp[i] = number of ways to make amount i
//   Transition: dp[i] += dp[i - coin] for each coin

#include <iostream>

using namespace std;

// A large value to represent infinity
const int INF = 999999;

// Variation 1: Find minimum number of coins to make amount
int minCoins(int coins[], int n, int amount) {
    int dp[10001];

    // Base case: 0 coins needed to make amount 0
    dp[0] = 0;

    // Initialize all other values to infinity (impossible)
    for (int i = 1; i <= amount; i++) {
        dp[i] = INF;
    }

    // Fill the DP table
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            // If this coin can be used (coin value <= current amount)
            if (coins[j] <= i) {
                int remaining = i - coins[j];
                // If remaining amount is reachable and using this coin gives fewer coins
                if (dp[remaining] != INF) {
                    int newCount = dp[remaining] + 1;
                    if (newCount < dp[i]) {
                        dp[i] = newCount;
                    }
                }
            }
        }
    }

    // If dp[amount] is still INF, amount cannot be made
    if (dp[amount] == INF) {
        return -1;
    }
    return dp[amount];
}

// Variation 2: Count number of ways to make amount
long long countWays(int coins[], int n, int amount) {
    long long dp[10001];

    // Base case: 1 way to make amount 0 (use no coins)
    dp[0] = 1;

    // Initialize all other values to 0
    for (int i = 1; i <= amount; i++) {
        dp[i] = 0;
    }

    // Fill the DP table
    // Process coins one by one to avoid counting permutations
    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    return dp[amount];
}

int main() {
    cout << "=== Coin Change: Minimum Coins ===" << endl;

    // Example 1
    int coins1[] = {1, 2, 5};
    int n1 = 3;
    int amount1 = 11;

    cout << "\nCoins: ";
    for (int i = 0; i < n1; i++) {
        cout << coins1[i] << " ";
    }
    cout << "\nAmount: " << amount1 << endl;
    int result1 = minCoins(coins1, n1, amount1);
    cout << "Minimum coins needed: " << result1 << endl;
    cout << "Explanation: 5 + 5 + 1 = 11 (3 coins)" << endl;

    // Example 2
    int coins2[] = {2};
    int n2 = 1;
    int amount2 = 3;

    cout << "\nCoins: ";
    for (int i = 0; i < n2; i++) {
        cout << coins2[i] << " ";
    }
    cout << "\nAmount: " << amount2 << endl;
    int result2 = minCoins(coins2, n2, amount2);
    cout << "Minimum coins needed: " << result2 << endl;
    cout << "Explanation: Cannot make 3 with only coin value 2, returns -1" << endl;

    // Example 3
    int coins3[] = {1, 3, 4};
    int n3 = 3;
    int amount3 = 6;

    cout << "\nCoins: ";
    for (int i = 0; i < n3; i++) {
        cout << coins3[i] << " ";
    }
    cout << "\nAmount: " << amount3 << endl;
    int result3 = minCoins(coins3, n3, amount3);
    cout << "Minimum coins needed: " << result3 << endl;
    cout << "Explanation: 3 + 3 = 6 (2 coins)" << endl;

    cout << "\n=== Coin Change: Count Ways ===" << endl;

    // Example 4
    cout << "\nCoins: ";
    for (int i = 0; i < n1; i++) {
        cout << coins1[i] << " ";
    }
    cout << "\nAmount: " << amount1 << endl;
    long long ways1 = countWays(coins1, n1, amount1);
    cout << "Number of ways: " << ways1 << endl;
    cout << "Explanation: Multiple combinations of {1,2,5} can make 11" << endl;

    // Example 5
    int coins4[] = {1, 2, 3};
    int n4 = 3;
    int amount4 = 4;

    cout << "\nCoins: ";
    for (int i = 0; i < n4; i++) {
        cout << coins4[i] << " ";
    }
    cout << "\nAmount: " << amount4 << endl;
    long long ways2 = countWays(coins4, n4, amount4);
    cout << "Number of ways: " << ways2 << endl;
    cout << "Explanation: Ways are: {1,1,1,1}, {1,1,2}, {2,2}, {1,3} = 4 ways" << endl;

    // Example 6
    cout << "\nCoins: ";
    for (int i = 0; i < n1; i++) {
        cout << coins1[i] << " ";
    }
    cout << "\nAmount: 0" << endl;
    long long ways3 = countWays(coins1, n1, 0);
    cout << "Number of ways: " << ways3 << endl;
    cout << "Explanation: 1 way (use no coins)" << endl;

    return 0;
}
