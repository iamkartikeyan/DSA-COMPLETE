#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

// ============================================================
// Traveling Salesperson Problem (TSP) with Bitmask DP
//
// State: dp[mask][i] = min cost visiting all cities in mask, ending at city i
// Transition: try going to unvisited city j
// Start at city 0, visit all, return to 0
//
// Time Complexity: O(n^2 * 2^n)
// Space Complexity: O(n * 2^n)
// ============================================================

int n;  // number of cities
int dist[20][20];  // distance matrix (max 20 cities)
int dp[1048576][20];  // dp table (2^20 * 20)

// Initialize the distance matrix and dp table
void initialize(int numCities) {
    n = numCities;

    // Reset dp table
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i] = -1;  // -1 means not computed
        }
    }
}

// Recursive TSP with memoization
int solveTSP(int mask, int currentCity) {
    // Base case: all cities visited
    // Check if mask has all bits set
    if (mask == (1 << n) - 1) {
        // Return distance to go back to starting city (city 0)
        if (dist[currentCity][0] == -1) {
            return INT_MAX / 2;  // No path exists
        }
        return dist[currentCity][0];
    }

    // Check if already computed
    if (dp[mask][currentCity] != -1) {
        return dp[mask][currentCity];
    }

    // Try visiting each unvisited city
    int result = INT_MAX / 2;  // Use INT_MAX/2 to avoid overflow

    for (int nextCity = 0; nextCity < n; nextCity++) {
        // Check if nextCity is not in mask (not visited yet)
        if ((mask & (1 << nextCity)) == 0) {
            // Check if path exists
            if (dist[currentCity][nextCity] != -1) {
                int newMask = mask | (1 << nextCity);
                int cost = dist[currentCity][nextCity] + solveTSP(newMask, nextCity);
                if (cost < result) {
                    result = cost;
                }
            }
        }
    }

    dp[mask][currentCity] = result;
    return result;
}

// Iterative TSP (bottom-up)
int solveTSP_Iterative(int numCities) {
    int totalMasks = 1 << numCities;

    // Reset dp table
    for (int mask = 0; mask < totalMasks; mask++) {
        for (int i = 0; i < numCities; i++) {
            dp[mask][i] = INT_MAX / 2;
        }
    }

    // Base case: only city 0 visited, at city 0
    dp[1][0] = 0;  // mask=1 means only city 0 is visited

    // Iterate over all masks
    for (int mask = 1; mask < totalMasks; mask++) {
        for (int currentCity = 0; currentCity < numCities; currentCity++) {
            // If current city not in mask, skip
            if ((mask & (1 << currentCity)) == 0) continue;

            // If this state is unreachable, skip
            if (dp[mask][currentCity] == INT_MAX / 2) continue;

            // Try going to each unvisited city
            for (int nextCity = 0; nextCity < numCities; nextCity++) {
                // If nextCity already in mask, skip
                if ((mask & (1 << nextCity)) != 0) continue;

                // If no path exists, skip
                if (dist[currentCity][nextCity] == -1) continue;

                int newMask = mask | (1 << nextCity);
                int newCost = dp[mask][currentCity] + dist[currentCity][nextCity];

                if (newCost < dp[newMask][nextCity]) {
                    dp[newMask][nextCity] = newCost;
                }
            }
        }
    }

    // Find minimum cost to complete the tour (return to city 0)
    int result = INT_MAX / 2;
    int fullMask = totalMasks - 1;

    for (int lastCity = 0; lastCity < numCities; lastCity++) {
        if (lastCity == 0) continue;
        if (dist[lastCity][0] != -1) {
            int totalCost = dp[fullMask][lastCity] + dist[lastCity][0];
            if (totalCost < result) {
                result = totalCost;
            }
        }
    }

    return result;
}

// ============================================================
// Main - Test all functions
// ============================================================

int main() {
    cout << "=== Bitmask DP: Traveling Salesperson Problem ===" << endl;
    cout << endl;

    // Test 1: Simple 4-city TSP
    // Cities: 0, 1, 2, 3
    // Distance matrix (symmetric)
    cout << "--- Test 1: 4 Cities ---" << endl;
    cout << "Distance matrix:" << endl;
    cout << "  0  1  2  3" << endl;
    cout << "0  0 10 15 20" << endl;
    cout << "1 10  0 35 25" << endl;
    cout << "2 15 35  0 30" << endl;
    cout << "3 20 25 30  0" << endl;
    cout << endl;

    n = 4;
    dist[0][1] = 10; dist[0][2] = 15; dist[0][3] = 20;
    dist[1][0] = 10; dist[1][2] = 35; dist[1][3] = 25;
    dist[2][0] = 15; dist[2][1] = 35; dist[2][3] = 30;
    dist[3][0] = 20; dist[3][1] = 25; dist[3][2] = 30;

    // Diagonal: distance from city to itself is 0
    dist[0][0] = 0;
    dist[1][1] = 0;
    dist[2][2] = 0;
    dist[3][3] = 0;

    initialize(n);
    int result1 = solveTSP(1, 0);  // Start: only city 0 visited, at city 0
    cout << "Min tour cost (recursive): " << result1 << endl;
    cout << "Expected: 80 (0->1->3->2->0 = 10+25+30+15)" << endl;
    cout << endl;

    int result2 = solveTSP_Iterative(n);
    cout << "Min tour cost (iterative): " << result2 << endl;
    cout << endl;

    // Test 2: 3-city TSP
    cout << "--- Test 2: 3 Cities ---" << endl;
    cout << "Distance matrix:" << endl;
    cout << "  0  1  2" << endl;
    cout << "0  0  5 10" << endl;
    cout << "1  5  0  8" << endl;
    cout << "2 10  8  0" << endl;
    cout << endl;

    n = 3;
    dist[0][1] = 5;  dist[0][2] = 10;
    dist[1][0] = 5;  dist[1][2] = 8;
    dist[2][0] = 10; dist[2][1] = 8;
    dist[0][0] = 0;  dist[1][1] = 0; dist[2][2] = 0;

    initialize(n);
    int result3 = solveTSP(1, 0);
    cout << "Min tour cost (recursive): " << result3 << endl;
    cout << "Expected: 23 (0->1->2->0 = 5+8+10)" << endl;
    cout << endl;

    return 0;
}
