// 01_What_Is_Backtracking.cpp
// Backtracking: A systematic way to search through all possible solutions
// by building candidates incrementally and abandoning partial candidates
// that cannot lead to a valid solution.
//
// Core Idea: CHOICE -> CONSTRAINT -> GOAL -> PRUNE -> BACKTRACK
//
// State Space Tree:
//   - Root = empty/initial state
//   - Each node = a partial solution
//   - Each branch = a choice made from available candidates
//   - Leaves = complete solutions (valid) or dead ends (invalid/pruned)
//   - Traversal = Depth-First Search (DFS) with undo on return

#include <iostream>
using namespace std;

/*
 * ============================================================
 * THE BACKTRACKING PATTERN (5 Steps)
 * ============================================================
 *
 * 1. CHOICE:      What options do I have right now?
 *                 Example: include or exclude element? Place queen here?
 *
 * 2. CONSTRAINT:  Is this choice valid? Does it break any rules?
 *                 Example: does this queen attack another? Is sum <= target?
 *
 * 3. GOAL:        Have I reached a complete solution?
 *                 Example: processed all elements? Filled all positions?
 *
 * 4. PRUNING:     Can I skip this branch early? (Optimization)
 *                 Example: current sum already exceeds target?
 *
 * 5. BACKTRACK:   Undo my last choice and try the next option.
 *                 Example: remove element from current subset, try exclude.
 *
 * ============================================================
 * STATE SPACE TREE (visual example for subsets of {1, 2, 3})
 * ============================================================
 *
 *                          []              <-- root (empty subset)
 *                      /        \
 *                 [1]            []        <-- include/exclude 1
 *               /     \        /    \
 *          [1,2]     [1]      [2]     []   <-- include/exclude 2
 *          /   \     /  \     /  \    /  \
 *       [1,2,3][1,2][1,3][1][2,3][2][3][]  <-- include/exclude 3
 *
 * Total leaves = 2^3 = 8 subsets
 * Each root-to-leaf path = one subset
 *
 * Backtracking traverses this tree in DFS order.
 * At each node: make a choice, recurse, undo the choice.
 */

// Simple example: generate and print all subsets of {1, 2, 3}
// Demonstrates the choice-constraint-goal-prune-backtrack flow.

void generateSubsets(int arr[], int n, int idx, int current[], int currentSize) {
    // GOAL: processed all elements, print current subset
    if (idx == n) {
        cout << "  {";
        for (int i = 0; i < currentSize; i++) {
            cout << current[i];
            if (i + 1 < currentSize) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }

    // CHOICE 1: Include arr[idx] in current subset
    current[currentSize] = arr[idx];
    generateSubsets(arr, n, idx + 1, current, currentSize + 1);
    // BACKTRACK: undo include (just reduce size on next call, no explicit pop needed)

    // CHOICE 2: Exclude arr[idx] from current subset
    generateSubsets(arr, n, idx + 1, current, currentSize);
    // No undo needed (nothing was added)
}

int main() {
    cout << "=== What Is Backtracking? ===" << endl;
    cout << endl;

    cout << "Backtracking = DFS on the State Space Tree + Undo choices" << endl;
    cout << endl;

    cout << "The 5 pillars:" << endl;
    cout << "  1. CHOICE      - pick from available options" << endl;
    cout << "  2. CONSTRAINT  - is this choice valid?" << endl;
    cout << "  3. GOAL        - is the solution complete?" << endl;
    cout << "  4. PRUNING     - skip branches that cannot succeed" << endl;
    cout << "  5. BACKTRACK   - undo and try next option" << endl;
    cout << endl;

    int arr[] = {1, 2, 3};
    int n = 3;
    int current[3];  // buffer for current subset

    cout << "All subsets of {1, 2, 3} (2^3 = 8):" << endl;
    generateSubsets(arr, n, 0, current, 0);
    cout << endl;

    cout << "How backtracking works here:" << endl;
    cout << "  At each element, we make a BINARY choice:" << endl;
    cout << "    - Include it  -> recurse -> backtrack (undo)" << endl;
    cout << "    - Exclude it  -> recurse (no undo needed)" << endl;
    cout << "  This forms a binary tree of depth n." << endl;
    cout << "  DFS visits every leaf = every subset." << endl;
    cout << endl;

    cout << "Why not brute force?" << endl;
    cout << "  Brute force generates all 2^n subsets but cannot prune." << endl;
    cout << "  Backtracking can PRUNE branches early when constraints fail," << endl;
    cout << "  saving time on impossible paths." << endl;

    return 0;
}
