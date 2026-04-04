#include <iostream>

using namespace std;

// ============================================================
// Advanced DP Patterns - Summary
// ============================================================

void printSection(char* title) {
    cout << "========================================" << endl;
    cout << title << endl;
    cout << "========================================" << endl;
    cout << endl;
}

// ============================================================
// Main - Print complete summary
// ============================================================

int main() {
    cout << endl;
    printSection("ADVANCED DYNAMIC PROGRAMMING PATTERNS - SUMMARY");

    // ============================================================
    // 1. Pattern Overview
    // ============================================================
    printSection("1. ALL DP TOPICS IN THIS FOLDER");

    cout << "File 01: Palindrome_DP.cpp" << endl;
    cout << "  - Longest Palindromic Subsequence (LPS)" << endl;
    cout << "  - Count Palindromic Substrings" << endl;
    cout << "  - Min Cuts for Palindrome Partitioning" << endl;
    cout << endl;

    cout << "File 02: Matrix_Chain_Multiplication.cpp" << endl;
    cout << "  - Optimal Matrix Chain Multiplication" << endl;
    cout << "  - Print Optimal Parenthesization" << endl;
    cout << endl;

    cout << "File 03: DP_on_Trees.cpp" << endl;
    cout << "  - Tree Diameter (longest path between any two nodes)" << endl;
    cout << "  - Max Path Sum in Binary Tree" << endl;
    cout << endl;

    cout << "File 04: Bitmask_DP.cpp" << endl;
    cout << "  - Traveling Salesperson Problem (TSP)" << endl;
    cout << "  - Recursive (top-down) with memoization" << endl;
    cout << "  - Iterative (bottom-up) approach" << endl;
    cout << endl;

    // ============================================================
    // 2. When to Use Each Pattern
    // ============================================================
    printSection("2. WHEN TO USE EACH PATTERN");

    cout << "Palindrome DP:" << endl;
    cout << "  Use when: problem involves palindromes in strings/arrays" << endl;
    cout << "  Clues: 'longest palindrome', 'palindrome partitioning'," << endl;
    cout << "         'count palindromes', 'minimum palindrome cuts'" << endl;
    cout << "  Key idea: dp[i][j] represents answer for substring s[i..j]" << endl;
    cout << "  Match case: s[i]==s[j] leads to inner problem dp[i+1][j-1]" << endl;
    cout << endl;

    cout << "Matrix Chain Multiplication (MCM):" << endl;
    cout << "  Use when: need optimal way to combine/merge/group items" << endl;
    cout << "  Clues: 'optimal grouping', 'minimum cost to merge'," << endl;
    cout << "         'best way to parenthesize', 'burst balloons'" << endl;
    cout << "  Key idea: try all split points k, take minimum" << endl;
    cout << "  Similar problems: Optimal BST, Burst Balloons," << endl;
    cout << "                    Minimum cost to cut a stick" << endl;
    cout << endl;

    cout << "DP on Trees:" << endl;
    cout << "  Use when: problem is on a tree structure" << endl;
    cout << "  Clues: 'tree diameter', 'max path sum', 'tree coloring'," << endl;
    cout << "         'maximum independent set on tree'" << endl;
    cout << "  Key idea: post-order DFS, compute from children to parent" << endl;
    cout << "  Return height/value from subtrees, combine at parent" << endl;
    cout << endl;

    cout << "Bitmask DP:" << endl;
    cout << "  Use when: n is small (<=20) and need to track subsets" << endl;
    cout << "  Clues: 'visit all', 'permutation', 'assignment problem'," << endl;
    cout << "         'TSP', 'matching', 'subset selection'" << endl;
    cout << "  Key idea: mask represents visited/set of items" << endl;
    cout << "  Each bit in mask = one item selected/visited" << endl;
    cout << "  Transition: try adding one item at a time" << endl;
    cout << endl;

    // ============================================================
    // 3. State Definitions
    // ============================================================
    printSection("3. STATE DEFINITIONS");

    cout << "Palindrome DP (LPS):" << endl;
    cout << "  dp[i][j] = LPS length in substring s[i..j]" << endl;
    cout << "  Answer: dp[0][n-1]" << endl;
    cout << endl;

    cout << "Palindrome Partitioning:" << endl;
    cout << "  dp[i] = min cuts for prefix s[0..i]" << endl;
    cout << "  isPal[i][j] = is s[i..j] a palindrome" << endl;
    cout << "  Answer: dp[n-1]" << endl;
    cout << endl;

    cout << "Matrix Chain Multiplication:" << endl;
    cout << "  dp[i][j] = min multiplications for matrices i..j" << endl;
    cout << "  Answer: dp[1][n]" << endl;
    cout << endl;

    cout << "Tree Diameter:" << endl;
    cout << "  Global diameter variable, update during DFS" << endl;
    cout << "  Return: height of subtree from each node" << endl;
    cout << "  Answer: global diameter" << endl;
    cout << endl;

    cout << "Bitmask DP (TSP):" << endl;
    cout << "  dp[mask][i] = min cost visiting cities in mask, ending at i" << endl;
    cout << "  Answer: min over all last cities of dp[full_mask][last] + dist[last][0]" << endl;
    cout << endl;

    // ============================================================
    // 4. Transitions
    // ============================================================
    printSection("4. TRANSITION RECURRENCES");

    cout << "LPS:" << endl;
    cout << "  if s[i] == s[j]:" << endl;
    cout << "    dp[i][j] = 2 + dp[i+1][j-1]" << endl;
    cout << "  else:" << endl;
    cout << "    dp[i][j] = max(dp[i+1][j], dp[i][j-1])" << endl;
    cout << endl;

    cout << "MCM:" << endl;
    cout << "  dp[i][j] = min over k from i to j-1:" << endl;
    cout << "    dp[i][k] + dp[k+1][j] + dims[i-1]*dims[k]*dims[j]" << endl;
    cout << endl;

    cout << "Tree Diameter (at node):" << endl;
    cout << "  diameter = max(diameter, leftHeight + rightHeight)" << endl;
    cout << "  return height = max(leftHeight, rightHeight) + 1" << endl;
    cout << endl;

    cout << "Bitmask DP (TSP):" << endl;
    cout << "  dp[mask][i] = min over all unvisited j:" << endl;
    cout << "    dist[i][j] + dp[mask | (1<<j)][j]" << endl;
    cout << "  Base case: dp[all_visited][last] = dist[last][0]" << endl;
    cout << endl;

    // ============================================================
    // 5. Complexity Comparison
    // ============================================================
    printSection("5. COMPLEXITY COMPARISON");

    cout << "Pattern                    | Time            | Space" << endl;
    cout << "---------------------------|-----------------|----------------" << endl;
    cout << "LPS (Palindrome)           | O(n^2)          | O(n^2)" << endl;
    cout << "Count Palindromes          | O(n^2)          | O(1)" << endl;
    cout << "Palindrome Partitioning    | O(n^2)          | O(n^2)" << endl;
    cout << "MCM                        | O(n^3)          | O(n^2)" << endl;
    cout << "Tree Diameter              | O(n)            | O(h) stack" << endl;
    cout << "Max Path Sum (Tree)        | O(n)            | O(h) stack" << endl;
    cout << "Bitmask DP (TSP)           | O(n^2 * 2^n)    | O(n * 2^n)" << endl;
    cout << endl;
    cout << "Note: h = tree height, n = input size" << endl;
    cout << endl;

    // ============================================================
    // 6. Tips and Patterns
    // ============================================================
    printSection("6. TIPS AND COMMON PATTERNS");

    cout << "General DP Tips:" << endl;
    cout << "  1. Identify the state (what defines a subproblem?)" << endl;
    cout << "  2. Define what dp[state] means clearly" << endl;
    cout << "  3. Find the base cases" << endl;
    cout << "  4. Write the recurrence relation" << endl;
    cout << "  5. Determine fill order (smaller states first)" << endl;
    cout << "  6. Identify the answer in the dp table" << endl;
    cout << endl;

    cout << "2D DP Patterns:" << endl;
    cout << "  - Palindrome, LCS, Edit Distance, MCM" << endl;
    cout << "  - Usually dp[i][j] for range s[i..j] or two sequences" << endl;
    cout << "  - Fill diagonally or by length" << endl;
    cout << endl;

    cout << "Bitmask Tips:" << endl;
    cout << "  - (mask >> i) & 1 checks if bit i is set" << endl;
    cout << "  - mask | (1 << i) sets bit i" << endl;
    cout << "  - Full mask = (1 << n) - 1 (all bits set)" << endl;
    cout << "  - Max n is usually 20 (2^20 = 1,048,576 states)" << endl;
    cout << endl;

    cout << "Tree DP Tips:" << endl;
    cout << "  - Always post-order (children before parent)" << endl;
    cout << "  - Use global variable for diameter/max answers" << endl;
    cout << "  - Return height or partial result from recursion" << endl;
    cout << endl;

    // ============================================================
    // 7. Related DP Topics (in other files)
    // ============================================================
    printSection("7. RELATED DP TOPICS (OTHER FILES)");

    cout << "In 8.1_Basic_DP:" << endl;
    cout << "  - Fibonacci, Factorial" << endl;
    cout << "  - Memoization vs Tabulation" << endl;
    cout << "  - 1D DP patterns" << endl;
    cout << endl;

    cout << "In 8.2_Intermediate_DP:" << endl;
    cout << "  - 0/1 Knapsack, Unbounded Knapsack" << endl;
    cout << "  - Longest Common Subsequence (LCS)" << endl;
    cout << "  - Longest Increasing Subsequence (LIS)" << endl;
    cout << "  - Coin Change, Edit Distance" << endl;
    cout << endl;

    cout << "Other common advanced patterns:" << endl;
    cout << "  - Digit DP (count numbers with property in range)" << endl;
    cout << "  - DP with Bitsets (optimization)" << endl;
    cout << "  - Profile DP / Broken Profile (tiling problems)" << endl;
    cout << "  - SOS DP (Sum Over Subsets)" << endl;
    cout << "  - DP on DAGs (Directed Acyclic Graphs)" << endl;
    cout << "  - Convex Hull Optimization" << endl;
    cout << "  - Divide and Conquer Optimization" << endl;
    cout << endl;

    cout << "=== End of Advanced DP Summary ===" << endl;

    return 0;
}
