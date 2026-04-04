#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

// =============================================
// DP OPTIMIZATION TECHNIQUES - SUMMARY
// =============================================
// This file covers all space optimization techniques
// learned in the DP Optimization section.
//
// Topics covered:
// 1. Fibonacci - O(1) space
// 2. 0/1 Knapsack - O(W) space (iterate backwards)
// 3. Unbounded Knapsack - O(W) space (iterate forwards)
// 4. LCS - O(n) space (two rows)
// 5. Edit Distance - O(min(m,n)) space (rolling arrays)
//
// =============================================


// =============================================
// TECHNIQUE 1: KEEP ONLY LAST K VALUES
// =============================================
// When dp[i] depends on only a fixed number of previous values
// (e.g., dp[i-1] and dp[i-2] for Fibonacci),
// we can use just those variables instead of an array.

void technique_last_k_values() {
    cout << "Technique 1: Keep Only Last K Values" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Use when: dp[i] depends on dp[i-1], dp[i-2], ... dp[i-k]" << endl;
    cout << "Space: O(n) -> O(k) or O(1)" << endl;
    cout << endl;
    cout << "Example - Fibonacci:" << endl;
    cout << "  Standard: dp[i] = dp[i-1] + dp[i-2], array of size n" << endl;
    cout << "  Optimized: keep only prev1 and prev2" << endl;
    cout << endl;

    int n = 15;
    int prev2 = 0, prev1 = 1, current = 0;

    cout << "Fibonacci sequence (first " << n << " terms):" << endl;
    cout << "0 1 ";

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        cout << current << " ";
        prev2 = prev1;
        prev1 = current;
    }
    cout << endl;
    cout << endl;
}


// =============================================
// TECHNIQUE 2: ROLLING ARRAYS (Two Rows)
// =============================================
// When dp[i][j] depends only on row i-1,
// we can use just two rows instead of the full table.

void technique_rolling_arrays() {
    cout << "Technique 2: Rolling Arrays (Two Rows)" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Use when: dp[i][j] depends only on values from row i-1" << endl;
    cout << "Space: O(m*n) -> O(n) or O(m)" << endl;
    cout << endl;
    cout << "How it works:" << endl;
    cout << "  - Maintain two arrays: prev[] and curr[]" << endl;
    cout << "  - Compute curr[] using values from prev[]" << endl;
    cout << "  - After each row, copy curr[] to prev[]" << endl;
    cout << "  - Repeat" << endl;
    cout << endl;
    cout << "Visual:" << endl;
    cout << "  Instead of this (O(m*n) space):" << endl;
    cout << "  dp[0][0] dp[0][1] dp[0][2] ..." << endl;
    cout << "  dp[1][0] dp[1][1] dp[1][2] ...  <- only need this row" << endl;
    cout << "  dp[2][0] dp[2][1] dp[2][2] ...  <- and this row" << endl;
    cout << "  ..." << endl;
    cout << endl;
    cout << "  Use this (O(n) space):" << endl;
    cout << "  prev[j] = values from row i-1" << endl;
    cout << "  curr[j] = values from row i (being computed)" << endl;
    cout << endl;
    cout << "Examples: LCS, Edit Distance, Matrix Chain Multiplication" << endl;
    cout << endl;
}


// =============================================
// TECHNIQUE 3: DIRECTION MATTERS (Knapsack)
// =============================================
// In 1D knapsack, the iteration direction determines
// whether items can be reused.

void technique_iteration_direction() {
    cout << "Technique 3: Iteration Direction Matters" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Use when: Converting 2D DP to 1D DP" << endl;
    cout << endl;
    cout << "0/1 Knapsack (each item used ONCE):" << endl;
    cout << "  Iterate BACKWARDS: for w = W down to weight[i]" << endl;
    cout << "  Why: dp[w - weight] should be from PREVIOUS iteration" << endl;
    cout << "  (item not yet used in current iteration)" << endl;
    cout << endl;
    cout << "Unbounded Knapsack (items can be reused):" << endl;
    cout << "  Iterate FORWARDS: for w = weight[i] to W" << endl;
    cout << "  Why: dp[w - weight] CAN include current item" << endl;
    cout << "  (allows reusing the same item)" << endl;
    cout << endl;
    cout << "This is the SAME code, just different loop direction!" << endl;
    cout << endl;
}


// =============================================
// TECHNIQUE 4: MODULO FOR ROLLING
// =============================================
// Instead of two separate arrays and copying,
// use dp[2][n] and access with i%2.

void technique_modulo_rolling() {
    cout << "Technique 4: Modulo Rolling Array" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Use when: You want cleaner code than manual copy" << endl;
    cout << "Space: O(m*n) -> O(n) with dp[2][n]" << endl;
    cout << endl;
    cout << "Pattern:" << endl;
    cout << "  int dp[2][MAX_N];" << endl;
    cout << "  int curr = i % 2;" << endl;
    cout << "  int prev = (i - 1) % 2;" << endl;
    cout << "  dp[curr][j] = ... dp[prev][j-1] ..." << endl;
    cout << endl;
    cout << "Advantage: No need to copy arrays" << endl;
    cout << "Disadvantage: Slightly harder to read for beginners" << endl;
    cout << endl;
}


// =============================================
// TECHNIQUE 5: BITSET OPTIMIZATION
// =============================================
// For boolean DP (yes/no answers), use bitset
// to process multiple states in parallel.

void technique_bitset_optimization() {
    cout << "Technique 5: Bitset Optimization (Brief)" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Use when: DP state is boolean (true/false)" << endl;
    cout << "Space: O(n) bits instead of O(n) ints" << endl;
    cout << "Time: Can process 64 states at once (on 64-bit machines)" << endl;
    cout << endl;
    cout << "Example: Subset Sum - can we make sum S?" << endl;
    cout << "  bitset<MAX_SUM> reachable;" << endl;
    cout << "  reachable[0] = 1;" << endl;
    cout << "  reachable = reachable | (reachable << weight[i]);" << endl;
    cout << endl;
    cout << "This is an advanced technique - learn the basics first!" << endl;
    cout << endl;
}


// =============================================
// WHEN CAN SPACE BE OPTIMIZED?
// =============================================
void when_to_optimize() {
    cout << "========================================" << endl;
    cout << "  WHEN CAN SPACE BE OPTIMIZED?" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Space CAN be optimized when:" << endl;
    cout << "  1. Current state depends on only a FEW previous states" << endl;
    cout << "     (e.g., Fibonacci needs only last 2 values)" << endl;
    cout << endl;
    cout << "  2. DP table is filled row by row, and each row" << endl;
    cout << "     only needs the previous row" << endl;
    cout << "     (e.g., LCS, Edit Distance)" << endl;
    cout << endl;
    cout << "  3. The DP state can be compressed using bitset" << endl;
    cout << "     (e.g., boolean DP problems)" << endl;
    cout << endl;
    cout << "Space CANNOT be easily optimized when:" << endl;
    cout << "  1. You need to RECONSTRUCT the solution path" << endl;
    cout << "     (e.g., print the actual LCS string)" << endl;
    cout << endl;
    cout << "  2. Current state depends on MANY previous states" << endl;
    cout << "     scattered throughout the table" << endl;
    cout << endl;
    cout << "  3. The problem requires the full DP table" << endl;
    cout << "     for some other computation" << endl;
    cout << endl;
}


// =============================================
// ALL DP TOPICS IN THIS FOLDER
// =============================================
void all_topics_summary() {
    cout << "========================================" << endl;
    cout << "  ALL DP TOPICS COVERED (8.4 DP Optimization)" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "File 1: 01_Space_Optimization.cpp" << endl;
    cout << "  - Fibonacci: O(n) -> O(1) space" << endl;
    cout << "  - 0/1 Knapsack: O(n*W) -> O(W) space (iterate backwards)" << endl;
    cout << "  - Unbounded Knapsack: O(n*W) -> O(W) space (iterate forwards)" << endl;
    cout << "  - LCS: O(m*n) -> O(n) space (two rows)" << endl;
    cout << endl;
    cout << "File 2: 02_Edit_Distance_Space_Optimized.cpp" << endl;
    cout << "  - Edit Distance: O(m*n) -> O(min(m,n)) space" << endl;
    cout << "  - Two approaches: two arrays vs modulo 2" << endl;
    cout << "  - Rolling array concept in detail" << endl;
    cout << endl;
    cout << "File 3: 03_DP_Optimization_Summary.cpp" << endl;
    cout << "  - All optimization techniques summarized" << endl;
    cout << "  - When space can/cannot be optimized" << endl;
    cout << "  - Complexity comparison table" << endl;
    cout << endl;
}


// =============================================
// COMPLEXITY TABLE
// =============================================
void complexity_table() {
    cout << "========================================" << endl;
    cout << "  COMPLEXITY TABLE" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Problem               | Time       | Space (Original) | Space (Optimized)" << endl;
    cout << "----------------------|------------|------------------|-------------------" << endl;
    cout << "Fibonacci             | O(n)       | O(n)             | O(1)" << endl;
    cout << "0/1 Knapsack          | O(n*W)     | O(n*W)           | O(W)" << endl;
    cout << "Unbounded Knapsack    | O(n*W)     | O(n*W)           | O(W)" << endl;
    cout << "LCS                   | O(m*n)     | O(m*n)           | O(n)" << endl;
    cout << "Edit Distance         | O(m*n)     | O(m*n)           | O(min(m,n))" << endl;
    cout << "Matrix Chain Mult.    | O(n^3)     | O(n^2)           | O(n^2) (hard to optimize)" << endl;
    cout << "Longest Inc. Subseq.  | O(n^2)     | O(n)             | O(n) (already optimal)" << endl;
    cout << "Coin Change           | O(n*amount)| O(amount)        | O(amount) (already optimal)" << endl;
    cout << endl;
    cout << "Key Observations:" << endl;
    cout << "  - Time complexity is USUALLY unchanged by space optimization" << endl;
    cout << "  - Space optimization saves MEMORY, not time" << endl;
    cout << "  - For small inputs, full table is fine (easier to debug)" << endl;
    cout << "  - For large inputs, space optimization prevents memory errors" << endl;
    cout << endl;
}


// =============================================
// QUICK REFERENCE: OPTIMIZATION PATTERNS
// =============================================
void quick_reference() {
    cout << "========================================" << endl;
    cout << "  QUICK REFERENCE: OPTIMIZATION PATTERNS" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Pattern 1: Fixed dependency (last k values)" << endl;
    cout << "  dp[i] = f(dp[i-1], dp[i-2], ...)" << endl;
    cout << "  -> Keep only k variables" << endl;
    cout << "  -> Space: O(n) -> O(k)" << endl;
    cout << endl;
    cout << "Pattern 2: Row-by-row dependency" << endl;
    cout << "  dp[i][j] = f(dp[i-1][...])" << endl;
    cout << "  -> Use two rows (prev and curr)" << endl;
    cout << "  -> Space: O(m*n) -> O(n)" << endl;
    cout << endl;
    cout << "Pattern 3: 1D array with direction" << endl;
    cout << "  dp[w] = max(dp[w], val + dp[w-weight])" << endl;
    cout << "  -> 0/1: iterate backwards" << endl;
    cout << "  -> Unbounded: iterate forwards" << endl;
    cout << "  -> Space: O(n*W) -> O(W)" << endl;
    cout << endl;
    cout << "Pattern 4: Modulo rolling" << endl;
    cout << "  dp[i%2][j] = f(dp[(i-1)%2][...])" << endl;
    cout << "  -> No array copy needed" << endl;
    cout << "  -> Space: O(m*n) -> O(n)" << endl;
    cout << endl;
}


int main() {
    cout << "========================================" << endl;
    cout << "  DP OPTIMIZATION TECHNIQUES SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // Explain each technique
    technique_last_k_values();
    technique_rolling_arrays();
    technique_iteration_direction();
    technique_modulo_rolling();
    technique_bitset_optimization();

    // When to optimize
    when_to_optimize();

    // All topics
    all_topics_summary();

    // Complexity table
    complexity_table();

    // Quick reference
    quick_reference();

    cout << "========================================" << endl;
    cout << "  END OF DP OPTIMIZATION SUMMARY" << endl;
    cout << "========================================" << endl;

    return 0;
}
