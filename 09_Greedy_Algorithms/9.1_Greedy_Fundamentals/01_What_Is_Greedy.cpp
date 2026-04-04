/*
 * What Is Greedy Algorithms?
 *
 * A greedy algorithm builds a solution piece by piece.
 * At each step it makes the locally best (locally optimal) choice
 * and never looks back. It hopes that local optima lead to a
 * global optimum.
 *
 * Two key properties:
 *   1. Greedy Choice Property
 *   2. Optimal Substructure
 */

#include <iostream>

/*
 * ============================================================
 * 1. GREEDY CHOICE PROPERTY
 * ============================================================
 * A globally optimal solution can be reached by choosing the
 * locally optimal (greedy) option at every step.
 *
 * Example: Activity Selection
 *   Always pick the activity that finishes first.
 *   This leaves maximum room for remaining activities.
 *
 * Important: Greedy commits to the choice IMMEDIATELY.
 * Dynamic Programming, by contrast, explores ALL choices
 * and picks the best among them.
 */

/*
 * ============================================================
 * 2. OPTIMAL SUBSTRUCTURE
 * ============================================================
 * An optimal solution to the problem contains optimal
 * solutions to its sub-problems.
 *
 * After making the greedy choice, the remaining problem is
 * a smaller instance of the same problem.
 *
 * Example: After picking the earliest-finishing activity,
 * we are left with the same "activity selection" problem
 * on a smaller set of compatible activities.
 */

/*
 * ============================================================
 * 3. WHEN GREEDY WORKS
 * ============================================================
 * Greedy works when you can PROVE that the greedy choice
 * at each step is part of SOME optimal solution.
 *
 * Problems where greedy WORKS:
 *   - Activity Selection       (sort by finish time)
 *   - Fractional Knapsack      (sort by value/weight ratio)
 *   - Huffman Coding           (always merge two smallest)
 *   - Minimum Spanning Tree    (Prim's, Kruskal's)
 *   - Dijkstra's Shortest Path (always pick nearest vertex)
 *
 * Problems where GREEDY FAILS:
 *   - 0/1 Knapsack             (need DP)
 *   - Coin Change {1,3,4}      (greedy gives 3 coins for 6,
 *                                but optimal is 2 coins: 3+3)
 *   - 0/1 items with weight    (cannot take fractions)
 */

/*
 * ============================================================
 * 4. GREEDY vs DYNAMIC PROGRAMMING
 * ============================================================
 *
 * | Aspect             | Greedy                  | DP                     |
 * |--------------------|-------------------------|------------------------|
 * | Decision           | Pick best now,          | Try all choices,       |
 * |                    | never reconsider        | pick best overall      |
 * |--------------------|-------------------------|------------------------|
 * | Future impact      | Ignored                 | Considered via table   |
 * |--------------------|-------------------------|------------------------|
 * | Time complexity    | Usually O(n log n)      | Usually O(n^2) or more |
 * |--------------------|-------------------------|------------------------|
 * | Space complexity   | O(1) or O(n)            | O(n^2) or O(n)         |
 * |--------------------|-------------------------|------------------------|
 * | Correctness        | Only if provable        | Always correct         |
 * |--------------------|-------------------------|------------------------|
 * | Approach           | Top-down, one pass      | Bottom-up or memoized  |
 *
 * Key insight:
 *   DP is more general but slower.
 *   Greedy is faster but only works for specific problems.
 *   If greedy works, use it. If not, fall back to DP.
 */

/*
 * ============================================================
 * 5. TEMPLATE: How to think about a greedy solution
 * ============================================================
 *
 * Step 1: Identify the greedy choice
 *         What is the "best" option at each step?
 *
 * Step 2: Prove the greedy choice property
 *         Show that making this choice can always lead to
 *         an optimal solution (exchange argument).
 *
 * Step 3: Prove optimal substructure
 *         After the greedy choice, remaining problem is
 *         the same type of problem on a smaller input.
 *
 * Step 4: Implement
 *         Sort if needed, then iterate and pick greedily.
 */

/*
 * ============================================================
 * DEMONSTRATION: A simple example where greedy works
 * ============================================================
 * Problem: Make change with denominations {1, 5, 10, 25}
 * (US coins). Greedy (always pick largest coin that fits)
 * is optimal for this specific set.
 */

int main() {
    int coins[4] = {25, 10, 5, 1};  // sorted descending
    int amount = 67;
    int original = amount;
    int count = 0;
    int used[4] = {0, 0, 0, 0};

    std::cout << "=== Greedy Coin Change ===" << std::endl;
    std::cout << "Amount: " << amount << std::endl;
    std::cout << "Coins: {25, 10, 5, 1}" << std::endl;
    std::cout << std::endl;

    int i = 0;
    while (i < 4) {
        while (amount >= coins[i]) {
            amount = amount - coins[i];
            used[i] = used[i] + 1;
            count = count + 1;
        }
        i = i + 1;
    }

    int j = 0;
    while (j < 4) {
        if (used[j] > 0) {
            std::cout << "  Coin " << coins[j] << " x " << used[j] << std::endl;
        }
        j = j + 1;
    }
    std::cout << "Total coins: " << count << std::endl;

    std::cout << std::endl;
    std::cout << "NOTE: Greedy works for {25,10,5,1} but NOT for all coin sets." << std::endl;
    std::cout << "For coins {1,3,4} and amount 6:" << std::endl;
    std::cout << "  Greedy gives: 4+1+1 = 3 coins" << std::endl;
    std::cout << "  Optimal is:   3+3   = 2 coins" << std::endl;

    return 0;
}
