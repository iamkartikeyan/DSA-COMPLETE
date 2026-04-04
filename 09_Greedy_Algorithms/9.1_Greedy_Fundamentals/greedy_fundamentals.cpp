/*
 * Greedy Fundamentals - Greedy Choice Property, Optimal Substructure
 *
 * Greedy algorithms make locally optimal choices at each step,
 * hoping to reach a globally optimal solution.
 *
 * Two Key Properties:
 *   1. Greedy Choice Property:
 *      A globally optimal solution can be reached by making locally
 *      optimal (greedy) choices. No need to reconsider choices.
 *
 *   2. Optimal Substructure:
 *      An optimal solution contains optimal solutions to subproblems.
 *      After the greedy choice, the remaining subproblem is also optimal.
 *
 * When Greedy Works:
 *   - Activity Selection: sort by finish time
 *   - Fractional Knapsack: sort by value/weight ratio
 *   - Huffman Coding: always merge two smallest frequencies
 *   - Minimum Spanning Tree (Prim's, Kruskal's)
 *   - Dijkstra's shortest path
 *
 * When Greedy FAILS:
 *   - 0/1 Knapsack: greedy by ratio is NOT optimal
 *   - Coin Change (arbitrary denominations): greedy may fail
 *   - Traveling Salesperson: nearest neighbor is NOT optimal
 *   - These require DP or other approaches
 *
 * Greedy vs DP:
 *   Greedy: One pass, no backtracking, O(n log n) typically
 *   DP: Explore all options, O(n^2) or more, guarantees optimal
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;

// ============================================================
// 1. GREEDY WORKS: Activity Selection
//    Sort by finish time, pick earliest finishing first
//    This leaves maximum room for remaining activities
// ============================================================
struct Activity {
    int id, start, finish;
};

vector<int> activitySelection(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(),
         [](const Activity& a, const Activity& b) {
             return a.finish < b.finish;  // sort by finish time
         });

    vector<int> selected;
    int lastFinish = -1;
    for (auto& a : activities) {
        if (a.start >= lastFinish) {  // compatible
            selected.push_back(a.id);
            lastFinish = a.finish;
        }
    }
    return selected;
}

// ============================================================
// 2. GREEDY WORKS: Fractional Knapsack
//    Can take fractions of items, so sort by value/weight ratio
// ============================================================
struct Item {
    int id, weight, value;
    double ratio() const { return (double)value / weight; }
};

double fractionalKnapsack(vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(),
         [](const Item& a, const Item& b) { return a.ratio() > b.ratio(); });

    double totalValue = 0;
    for (auto& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            totalValue += item.ratio() * capacity;  // take fraction
            capacity = 0;
            break;
        }
    }
    return totalValue;
}

// ============================================================
// 3. GREEDY FAILS: 0/1 Knapsack with greedy ratio
//    Demonstrates why greedy doesn't work for 0/1 knapsack
// ============================================================
int greedyKnapsack01(vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(),
         [](const Item& a, const Item& b) { return a.ratio() > b.ratio(); });

    int totalValue = 0;
    for (auto& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value;
            capacity -= item.weight;
        }
        // Can't take fraction, skip entirely
    }
    return totalValue;
}

// DP solution (correct answer)
int optimalKnapsack01(int W, const vector<int>& wt, const vector<int>& val) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int w = 0; w <= W; ++w) {
            dp[i][w] = dp[i - 1][w];
            if (wt[i - 1] <= w)
                dp[i][w] = max(dp[i][w], dp[i - 1][w - wt[i - 1]] + val[i - 1]);
        }
    return dp[n][W];
}

// ============================================================
// 4. GREEDY FAILS: Coin Change with non-standard denominations
//    Greedy works for {1, 5, 10, 25} (US coins)
//    Greedy FAILS for {1, 3, 4} making 6: greedy gives 4+1+1=3 coins, optimal is 3+3=2
// ============================================================
int greedyCoinChange(vector<int>& coins, int amount) {
    sort(coins.rbegin(), coins.rend());  // largest first
    int count = 0;
    for (int c : coins) {
        count += amount / c;
        amount %= c;
    }
    return count;
}

// DP solution (correct answer)
int optimalCoinChange(const vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 1e9);
    dp[0] = 0;
    for (int c : coins)
        for (int i = c; i <= amount; ++i)
            dp[i] = min(dp[i], dp[i - c] + 1);
    return dp[amount];
}

// ============================================================
// 5. GREEDY WORKS: Minimum Platforms (Interval overlap)
//    Sort events, use greedy to track max concurrent
// ============================================================
int minPlatforms(const vector<int>& arrivals, const vector<int>& departures) {
    vector<int> arr = arrivals, dep = departures;
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());

    int platforms = 0, maxPlatforms = 0;
    int i = 0, j = 0, n = arr.size();
    while (i < n) {
        if (arr[i] <= dep[j]) {
            platforms++; i++;
            maxPlatforms = max(maxPlatforms, platforms);
        } else {
            platforms--; j++;
        }
    }
    return maxPlatforms;
}

// ============================================================
// 6. GREEDY WORKS: Assign Cookies
//    Sort children and cookies, greedily satisfy least greedy first
// ============================================================
int assignCookies(vector<int>& greed, vector<int>& cookies) {
    sort(greed.begin(), greed.end());
    sort(cookies.begin(), cookies.end());
    int i = 0, j = 0, count = 0;
    while (i < greed.size() && j < cookies.size()) {
        if (cookies[j] >= greed[i]) {
            count++; i++;  // satisfied
        }
        j++;  // try next cookie
    }
    return count;
}

// ============================================================
// MAIN: Demonstrate when greedy works and fails
// ============================================================
int main() {
    cout << "=== GREEDY FUNDAMENTALS ===\n\n";

    // --- Activity Selection (Greedy Works) ---
    cout << "--- Activity Selection (Greedy Works) ---\n";
    vector<Activity> acts = {
        {1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7},
        {5, 3, 9}, {6, 5, 9}, {7, 6, 10}, {8, 8, 11}
    };
    auto selected = activitySelection(acts);
    cout << "Selected activities: ";
    for (int id : selected) cout << id << " ";
    cout << "(" << selected.size() << " activities)\n\n";

    // --- Fractional Knapsack (Greedy Works) ---
    cout << "--- Fractional Knapsack (Greedy Works) ---\n";
    vector<Item> items = {
        {1, 10, 60}, {2, 20, 100}, {3, 30, 120}
    };
    cout << "Fractional knapsack (capacity=50): "
         << fractionalKnapsack(items, 50) << "\n";  // 240\n\n";

    // --- 0/1 Knapsack: Greedy vs DP ---
    cout << "--- 0/1 Knapsack: Greedy FAILS ---\n";
    // Counterexample: items with (weight, value) = (3,4), (2,3), (2,3)
    // Capacity = 4. Greedy by ratio picks (3,4) first => value 4.
    // Optimal: pick (2,3) + (2,3) => value 6.
    vector<Item> items2 = {{1, 3, 4}, {2, 2, 3}, {3, 2, 3}};
    int greedyVal = greedyKnapsack01(items2, 4);
    // Reset items2 order for DP
    vector<int> wt = {3, 2, 2}, val = {4, 3, 3};
    int dpVal = optimalKnapsack01(4, wt, val);
    cout << "Greedy 0/1 Knapsack: " << greedyVal << "\n";  // 4
    cout << "Optimal (DP):        " << dpVal << "\n";       // 6
    cout << "Greedy is NOT optimal!\n\n";

    // --- Coin Change: Greedy vs DP ---
    cout << "--- Coin Change: Greedy FAILS for {1,3,4}, amount=6 ---\n";
    vector<int> coins = {1, 3, 4};
    cout << "Greedy: " << greedyCoinChange(coins, 6) << " coins\n";   // 3: 4+1+1
    cout << "Optimal: " << optimalCoinChange(coins, 6) << " coins\n";  // 2: 3+3
    cout << "Greedy is NOT optimal!\n\n";

    // --- Minimum Platforms (Greedy Works) ---
    cout << "--- Minimum Platforms (Greedy Works) ---\n";
    vector<int> arr = {900, 940, 950, 1100, 1500, 1800};
    vector<int> dep = {910, 1200, 1120, 1130, 1900, 2000};
    cout << "Min platforms needed: " << minPlatforms(arr, dep) << "\n";  // 3\n\n";

    // --- Assign Cookies (Greedy Works) ---
    cout << "--- Assign Cookies (Greedy Works) ---\n";
    vector<int> greed = {1, 2, 3};
    vector<int> cookieSizes = {1, 1};
    cout << "Satisfied children: " << assignCookies(greed, cookieSizes) << "\n";  // 1\n\n";

    // --- Summary ---
    cout << "--- When Greedy Works ---\n";
    cout << "Activity Selection:   Sort by finish time\n";
    cout << "Fractional Knapsack:  Sort by value/weight ratio\n";
    cout << "Huffman Coding:       Merge two smallest frequencies\n";
    cout << "MST (Prim/Kruskal):   Pick minimum weight edges\n";
    cout << "Dijkstra:             Pick closest unvisited vertex\n";

    cout << "\n--- When Greedy Fails (Use DP) ---\n";
    cout << "0/1 Knapsack:         Need to consider all combinations\n";
    cout << "Coin Change:          Non-standard denominations\n";
    cout << "TSP:                  Nearest neighbor not optimal\n";
    cout << "Longest Path:         Greedy doesn't work\n";

    cout << "\n--- Key Insight ---\n";
    cout << "Greedy: Make the best local choice, never look back.\n";
    cout << "If greedy works, it's fast O(n log n). If it fails, use DP.\n";
    cout << "Proving greedy correctness requires mathematical proof!\n";

    return 0;
}
