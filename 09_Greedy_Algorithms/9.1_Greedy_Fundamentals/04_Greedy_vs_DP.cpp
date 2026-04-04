/*
 * Greedy vs Dynamic Programming - Direct Comparison
 *
 * This file demonstrates side-by-side how greedy and DP
 * approaches differ, with concrete examples where:
 *   1. Greedy fails (0/1 Knapsack)
 *   2. Greedy fails (Coin Change with {1, 3, 4})
 */

#include <iostream>

/*
 * ============================================================
 * EXAMPLE 1: 0/1 Knapsack
 * ============================================================
 *
 * Items: 3 items with (weight, value) pairs:
 *   Item 1: (10, 60)  ratio = 6.0
 *   Item 2: (20, 100) ratio = 5.0
 *   Item 3: (30, 120) ratio = 4.0
 *
 * Capacity: 50
 *
 * GREEDY (by value/weight ratio):
 *   Pick item 1 (w=10, v=60), remaining = 40
 *   Pick item 2 (w=20, v=100), remaining = 20
 *   Item 3 needs w=30, cannot fit fully, skip
 *   Total = 60 + 100 = 160
 *
 * DP OPTIMAL:
 *   Pick item 2 (w=20, v=100) + item 3 (w=30, v=120) = 220
 *   Total = 220
 *
 * GREEDY FAILS! 160 < 220
 */

/*
 * ============================================================
 * EXAMPLE 2: Coin Change with coins {1, 3, 4}
 * ============================================================
 *
 * Make amount 6.
 *
 * GREEDY (always pick largest coin that fits):
 *   Pick 4, remaining = 2
 *   Pick 1, remaining = 1
 *   Pick 1, remaining = 0
 *   Total coins: 3  (4 + 1 + 1)
 *
 * OPTIMAL:
 *   Pick 3, remaining = 3
 *   Pick 3, remaining = 0
 *   Total coins: 2  (3 + 3)
 *
 * GREEDY FAILS! 3 coins > 2 coins
 */

/* ---- 0/1 Knapsack: Greedy Approach ---- */
struct Item {
    int weight;
    int value;
    double ratio;
};

int knapsackGreedy01(Item items[], int n, int capacity) {
    /* Greedy: pick by highest ratio (can't take fractions) */

    int totalValue = 0;
    int remaining = capacity;
    int taken[10] = {0};  /* track taken items */

    int iteration = 0;
    while (iteration < n) {
        /* Find highest ratio item not yet taken */
        int bestIdx = -1;
        double bestRatio = -1;
        int k = 0;
        while (k < n) {
            if (taken[k] == 0 && items[k].ratio > bestRatio) {
                bestRatio = items[k].ratio;
                bestIdx = k;
            }
            k = k + 1;
        }

        if (bestIdx == -1) break;
        taken[bestIdx] = 1;

        if (items[bestIdx].weight <= remaining) {
            totalValue = totalValue + items[bestIdx].value;
            remaining = remaining - items[bestIdx].weight;
        }
        iteration = iteration + 1;
    }

    return totalValue;
}

/* ---- 0/1 Knapsack: DP Approach ---- */
int knapsackDP(int weights[], int values[], int n, int capacity) {
    int dp[100][100];

    /* Base case: 0 items or 0 capacity -> 0 value */
    int i = 0;
    while (i <= n) {
        dp[i][0] = 0;
        i = i + 1;
    }
    int j = 0;
    while (j <= capacity) {
        dp[0][j] = 0;
        j = j + 1;
    }

    /* Fill DP table */
    i = 1;
    while (i <= n) {
        j = 1;
        while (j <= capacity) {
            if (weights[i - 1] <= j) {
                int include = values[i - 1] + dp[i - 1][j - weights[i - 1]];
                int exclude = dp[i - 1][j];
                if (include > exclude) {
                    dp[i][j] = include;
                } else {
                    dp[i][j] = exclude;
                }
            } else {
                dp[i][j] = dp[i - 1][j];
            }
            j = j + 1;
        }
        i = i + 1;
    }

    return dp[n][capacity];
}

/* ---- Coin Change: Greedy Approach ---- */
int coinChangeGreedy(int coins[], int n, int amount) {
    int count = 0;
    int remaining = amount;
    int i = 0;

    while (i < n) {
        while (remaining >= coins[i]) {
            remaining = remaining - coins[i];
            count = count + 1;
        }
        i = i + 1;
    }

    return count;
}

/* ---- Coin Change: DP Approach ---- */
int coinChangeDP(int coins[], int n, int amount) {
    int dp[100];
    int MAX_VAL = amount + 1;  /* infinity substitute */

    dp[0] = 0;
    int i = 1;
    while (i <= amount) {
        dp[i] = MAX_VAL;
        i = i + 1;
    }

    i = 1;
    while (i <= amount) {
        int j = 0;
        while (j < n) {
            if (coins[j] <= i) {
                int result = dp[i - coins[j]];
                if (result != MAX_VAL && result + 1 < dp[i]) {
                    dp[i] = result + 1;
                }
            }
            j = j + 1;
        }
        i = i + 1;
    }

    if (dp[amount] == MAX_VAL) {
        return -1;  /* cannot make change */
    }
    return dp[amount];
}

int main() {
    /*
     * ========================================================
     * DEMO 1: 0/1 Knapsack
     * ========================================================
     */
    std::cout << "=== 0/1 Knapsack: Greedy vs DP ===" << std::endl;
    std::cout << std::endl;

    int n1 = 3;
    int weights[3] = {10, 20, 30};
    int values[3]  = {60, 100, 120};
    int capacity = 50;

    /* Greedy approach */
    Item items[3];
    items[0].weight = 10; items[0].value = 60;  items[0].ratio = 6.0;
    items[1].weight = 20; items[1].value = 100; items[1].ratio = 5.0;
    items[2].weight = 30; items[2].value = 120; items[2].ratio = 4.0;

    int greedyVal = knapsackGreedy01(items, n1, capacity);
    int dpVal = knapsackDP(weights, values, n1, capacity);

    std::cout << "Items: (w=10,v=60), (w=20,v=100), (w=30,v=120)" << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Greedy (by ratio): " << greedyVal << std::endl;
    std::cout << "DP (optimal):      " << dpVal << std::endl;

    if (greedyVal < dpVal) {
        std::cout << "RESULT: Greedy FAILS! (" << greedyVal
                  << " < " << dpVal << ")" << std::endl;
    } else {
        std::cout << "RESULT: Greedy matches DP" << std::endl;
    }

    /*
     * ========================================================
     * DEMO 2: Coin Change {1, 3, 4}, Amount = 6
     * ========================================================
     */
    std::cout << std::endl;
    std::cout << "=== Coin Change: Greedy vs DP ===" << std::endl;
    std::cout << std::endl;

    int coins[3] = {4, 3, 1};  /* sorted descending for greedy */
    int amount = 6;

    int greedyCoins = coinChangeGreedy(coins, 3, amount);
    int dpCoins = coinChangeDP(coins, 3, amount);

    std::cout << "Coins: {1, 3, 4}" << std::endl;
    std::cout << "Amount: " << amount << std::endl;
    std::cout << "Greedy: " << greedyCoins << " coins (4+1+1)" << std::endl;
    std::cout << "DP:     " << dpCoins << " coins (3+3)" << std::endl;

    if (greedyCoins > dpCoins) {
        std::cout << "RESULT: Greedy FAILS! (" << greedyCoins
                  << " > " << dpCoins << ")" << std::endl;
    } else {
        std::cout << "RESULT: Greedy matches DP" << std::endl;
    }

    /*
     * ========================================================
     * SUMMARY
     * ========================================================
     */
    std::cout << std::endl;
    std::cout << "=== Key Takeaways ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Greedy is faster but NOT always correct." << std::endl;
    std::cout << "DP is slower but ALWAYS correct." << std::endl;
    std::cout << std::endl;
    std::cout << "Use greedy when you can PROVE it works." << std::endl;
    std::cout << "Use DP when greedy fails or is unprovable." << std::endl;

    return 0;
}
