/*
 * Greedy Algorithms - Complete Summary
 *
 * This file provides a comprehensive reference for:
 *   1. Summary table of greedy algorithms
 *   2. When greedy works (conditions)
 *   3. When greedy fails
 *   4. Checklist for identifying greedy problems
 *   5. List of all greedy problems in this folder
 */

#include <iostream>

/*
 * ============================================================
 * SUMMARY TABLE: Greedy Algorithms Covered
 * ============================================================
 *
 * Problem                  | Greedy Choice               | Time     | Works?
 * -------------------------|-----------------------------|----------|-------
 * Activity Selection       | Earliest finish time        | O(nlogn) | YES
 * Fractional Knapsack      | Highest value/weight ratio  | O(nlogn) | YES
 * Huffman Coding           | Merge two smallest freq     | O(nlogn) | YES
 * Job Sequencing w/ Deadl. | Highest profit first        | O(n^2)   | YES
 * Minimum Platforms        | Sort arrivals & departures  | O(nlogn) | YES
 * Interval Merging         | Sort by start time          | O(nlogn) | YES
 * Assign Cookies           | Satisfy least greedy first  | O(nlogn) | YES
 * MST (Kruskal's)          | Smallest edge w/o cycle     | O(ElogE) | YES
 * MST (Prim's)             | Nearest vertex not in MST   | O(ElogV) | YES
 * Dijkstra's Shortest Path | Nearest unvisited vertex    | O(E+VlogV)| YES
 * Coin Change (US coins)   | Largest coin first          | O(n)     | YES*
 * 0/1 Knapsack             | Highest ratio               | O(nlogn) | NO*
 * Coin Change {1,3,4}      | Largest coin first          | O(n)     | NO*
 *
 * * = depends on coin denominations
 */

/*
 * ============================================================
 * WHEN GREEDY WORKS - Two Conditions
 * ============================================================
 *
 * Condition 1: Greedy Choice Property
 *   A globally optimal solution can be reached by making
 *   locally optimal choices at each step.
 *   "The best local choice is part of SOME global optimum."
 *
 * Condition 2: Optimal Substructure
 *   An optimal solution to the problem contains optimal
 *   solutions to sub-problems within it.
 *   "After the greedy choice, the remaining problem is
 *    the same problem on a smaller input."
 *
 * If BOTH conditions hold -> greedy likely works.
 * If either fails -> need DP or another approach.
 */

/*
 * ============================================================
 * WHEN GREEDY FAILS
 * ============================================================
 *
 * Greedy fails when the locally optimal choice prevents
 * achieving the globally optimal solution.
 *
 * Common failure patterns:
 *
 * 1. DISCRETE CHOICES (0/1 decisions):
 *    Taking the "best" item might block a better combination.
 *    Example: 0/1 Knapsack - greedy ratio fails.
 *
 * 2. INTERDEPENDENT CHOICES:
 *    The current choice affects future options in ways that
 *    cannot be captured by a simple greedy criterion.
 *    Example: Coin change {1,3,4} for amount 6.
 *
 * 3. FUTURE CONSTRAINTS MATTER:
 *    The greedy choice doesn't account for future constraints.
 *    Example: Some scheduling problems with dependencies.
 */

/*
 * ============================================================
 * CHECKLIST: How to identify a greedy problem
 * ============================================================
 *
 * Ask these questions:
 *
 * Q1: Can I make a locally optimal choice that seems best right now?
 *     If NO -> probably not greedy.
 *
 * Q2: After making this choice, does the remaining problem look
 *     like the original problem but smaller?
 *     If NO -> probably need DP.
 *
 * Q3: Can I prove (or at least believe) that making this choice
 *     never prevents reaching the optimal solution?
 *     If NO -> test with examples, likely need DP.
 *
 * Q4: Does the problem involve making a sequence of choices where
 *     each choice is FINAL (no backtracking needed)?
 *     If NO -> might need backtracking or DP.
 */

int main() {
    std::cout << "================================================" << std::endl;
    std::cout << "   GREEDY ALGORITHMS - COMPLETE SUMMARY" << std::endl;
    std::cout << "================================================" << std::endl;

    std::cout << std::endl;
    std::cout << "=== SUMMARY TABLE ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Problem                  | Greedy Choice              | Time     | Works?" << std::endl;
    std::cout << "-------------------------|----------------------------|----------|-------" << std::endl;
    std::cout << "Activity Selection       | Earliest finish time       | O(nlogn) | YES" << std::endl;
    std::cout << "Fractional Knapsack      | Highest value/weight ratio | O(nlogn) | YES" << std::endl;
    std::cout << "Huffman Coding           | Merge two smallest freq    | O(nlogn) | YES" << std::endl;
    std::cout << "Job Sequencing w/Deadl.  | Highest profit first       | O(n^2)   | YES" << std::endl;
    std::cout << "Minimum Platforms        | Sort arrivals & departures | O(nlogn) | YES" << std::endl;
    std::cout << "Interval Merging         | Sort by start time         | O(nlogn) | YES" << std::endl;
    std::cout << "Assign Cookies           | Satisfy least greedy first | O(nlogn) | YES" << std::endl;
    std::cout << "MST (Kruskal)            | Smallest edge w/o cycle    | O(ElogE) | YES" << std::endl;
    std::cout << "MST (Prim)               | Nearest vertex not in MST  | O(ElogV) | YES" << std::endl;
    std::cout << "Dijkstra Shortest Path   | Nearest unvisited vertex   | O(E+VlogV)| YES" << std::endl;
    std::cout << "Coin Change (US coins)   | Largest coin first         | O(n)     | YES*" << std::endl;
    std::cout << "0/1 Knapsack             | Highest ratio              | O(nlogn) | NO" << std::endl;
    std::cout << "Coin Change {1,3,4} amt6 | Largest coin first         | O(n)     | NO" << std::endl;

    std::cout << std::endl;
    std::cout << "* depends on coin denominations" << std::endl;

    std::cout << std::endl;
    std::cout << "=== GREEDY WORKS WHEN ===" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Greedy Choice Property holds" << std::endl;
    std::cout << "2. Optimal Substructure holds" << std::endl;
    std::cout << "3. Choices are independent or have matroid structure" << std::endl;
    std::cout << "4. Local optimum = global optimum" << std::endl;

    std::cout << std::endl;
    std::cout << "=== GREEDY FAILS WHEN ===" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Choices are discrete (0/1) with complex trade-offs" << std::endl;
    std::cout << "2. Current choice affects future options non-trivially" << std::endl;
    std::cout << "3. Need to explore ALL combinations for optimum" << std::endl;
    std::cout << "4. Problem has overlapping subproblems with choices" << std::endl;

    std::cout << std::endl;
    std::cout << "=== GREEDY PROBLEMS IN THIS FOLDER ===" << std::endl;
    std::cout << std::endl;
    std::cout << "9.1_Greedy_Fundamentals:" << std::endl;
    std::cout << "  01_What_Is_Greedy.cpp" << std::endl;
    std::cout << "  02_Activity_Selection.cpp" << std::endl;
    std::cout << "  03_Fractional_Knapsack.cpp" << std::endl;
    std::cout << "  04_Greedy_vs_DP.cpp" << std::endl;
    std::cout << "  05_Greedy_Summary.cpp (this file)" << std::endl;
    std::cout << std::endl;
    std::cout << "9.2_Classic_Greedy:" << std::endl;
    std::cout << "  01_Huffman_Coding.cpp" << std::endl;
    std::cout << "  02_Job_Sequencing_Deadlines.cpp" << std::endl;
    std::cout << "  03_Minimum_Platforms.cpp" << std::endl;
    std::cout << "  04_Interval_Merging.cpp" << std::endl;
    std::cout << "  05_Assign_Cookies.cpp" << std::endl;
    std::cout << "  06_Classic_Greedy_Summary.cpp" << std::endl;

    return 0;
}
