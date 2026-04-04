// 06_Backtracking_Framework_Summary.cpp
// Complete summary of all backtracking concepts covered in this folder.
// Acts as a quick reference and consolidation of the backtracking framework.

#include <iostream>
using namespace std;

/*
 * ============================================================
 * THE BACKTRACKING FRAMEWORK (Complete Reference)
 * ============================================================
 *
 * Backtracking = Depth-First Search on the State Space Tree
 *                + Undo choices when returning from recursion.
 *
 * +-----------------------------------------------------------+
 * |  Step          | Question                          | Action |
 * |-----------------------------------------------------------|
 * |  1. CHOICE     | What options do I have?           | Pick   |
 * |  2. CONSTRAINT | Is this choice valid?             | Check  |
 * |  3. GOAL       | Is the solution complete?         | Record |
 * |  4. PRUNING    | Can I skip this branch?           | Skip   |
 * |  5. BACKTRACK  | What do I undo?                   | Restore|
 * +-----------------------------------------------------------+
 *
 * ============================================================
 * TEMPLATE (Generic Backtracking Function)
 * ============================================================
 *
 * void backtrack(State state) {
 *     // 3. GOAL: check if we have a complete solution
 *     if (isGoal(state)) {
 *         recordSolution(state);
 *         return;
 *     }
 *
 *     // 4. PRUNING: skip impossible branches
 *     if (shouldPrune(state)) {
 *         return;
 *     }
 *
 *     // 1. CHOICE: iterate over available options
 *     for (each option) {
 *         // 2. CONSTRAINT: validate this choice
 *         if (isValid(option, state)) {
 *             makeChoice(option, state);      // Apply choice
 *             backtrack(state);               // Recurse
 *             undoChoice(option, state);      // 5. BACKTRACK
 *         }
 *     }
 * }
 *
 * ============================================================
 * PROBLEMS COVERED
 * ============================================================
 *
 * 1. Subset Generation     -> 02_Subset_Generation.cpp
 *    - Each element: include or exclude
 *    - 2^n subsets
 *    - No constraints (all subsets valid)
 *    - State space: binary tree
 *
 * 2. Permutations          -> 03_Permutations.cpp
 *    - Each position: pick any unused element
 *    - n! permutations
 *    - Constraint: element not already used
 *    - State space: n-ary tree, depth n
 *    - Two approaches: used[] array and swap-based
 *
 * 3. Combinations          -> 04_Combinations.cpp
 *    a) C(n, k): choose k from n
 *       - Constraint: only move forward (start index)
 *       - Fixed size output
 *
 *    b) Combination Sum: sum = target, reuse allowed
 *       - Prune: target < 0
 *       - Recurse with same index (reuse)
 *
 *    c) Subset Sum: sum = target, no reuse
 *       - Prune: target < 0 or idx == n
 *       - Recurse with idx+1 (no reuse)
 *
 * 4. Pruning Optimization  -> 05_Pruning_Optimization.cpp
 *    - Early termination when constraint violated
 *    - Bounded pruning: remaining elements cannot help
 *    - Dramatically reduces visited nodes
 *
 * ============================================================
 * COMPLEXITY CHEAT SHEET
 * ============================================================
 *
 * Problem              | Time           | Space  | Notes
 * ---------------------+----------------+--------+------------------
 * Subset Generation    | O(2^n * n)     | O(n)   | 2^n leaves, O(n) to copy
 * Permutations         | O(n! * n)      | O(n)   | n! leaves, used[] or swap
 * C(n, k)              | O(C(n,k) * k)  | O(k)   | Binomial coefficient
 * Combination Sum      | O(k^(T/m))     | O(T/m) | k=candidates, T=target, m=min
 * Subset Sum           | O(2^n * n)     | O(n)   | Can prune early
 *
 * ============================================================
 * KEY PATTERNS TO RECOGNIZE
 * ============================================================
 *
 * Pattern                  | Indicator                  | Technique
 * -------------------------+----------------------------+-------------------
 * "Find all subsets"       | No order matters           | Include/exclude
 * "Find all arrangements"  | Order matters              | used[] or swap
 * "Find all combinations"  | Order doesn't, fixed size  | start index, loop
 * "Sum equals target"      | Numeric constraint         | Prune on overshoot
 * "Each element once"      | No reuse                   | idx + 1
 * "Unlimited reuse"        | Reuse allowed              | idx (same index)
 *
 * ============================================================
 * STATE SPACE TREE CONCEPT
 * ============================================================
 *
 * The state space tree represents ALL possible partial solutions:
 *
 *   - Root: empty/initial state
 *   - Level i: decision about the i-th element/position
 *   - Branches: available choices at this decision point
 *   - Leaf: complete solution or dead end (pruned)
 *
 * Backtracking does a DEPTH-FIRST TRAVERSAL of this tree:
 *   1. Go deep (make choices, recurse)
 *   2. At leaf: record or backtrack
 *   3. Undo choice, try next branch
 *
 * Pruning cuts off ENTIRE SUBTREES that cannot contain solutions,
 * saving exponential time.
 *
 * ============================================================
 * COMMON MISTAKES
 * ============================================================
 *
 * 1. Forgetting to undo (backtrack) after recursive call.
 *    -> Result: corrupted state, wrong answers.
 *
 * 2. Using wrong index progression (idx vs idx+1).
 *    -> Result: infinite recursion or missing solutions.
 *
 * 3. Not checking constraints BEFORE recursing.
 *    -> Result: explores invalid branches unnecessarily.
 *
 * 4. Missing the base case (goal check).
 *    -> Result: infinite recursion / stack overflow.
 *
 * 5. Pruning too aggressively (skipping valid solutions).
 *    -> Result: missing correct answers.
 */

// Demonstration: run all patterns on a small example
void demoSubset(int arr[], int n, int idx, int current[], int sz) {
    if (idx == n) {
        cout << "  {";
        for (int i = 0; i < sz; i++) {
            cout << current[i];
            if (i + 1 < sz) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }
    current[sz] = arr[idx];
    demoSubset(arr, n, idx + 1, current, sz + 1);
    demoSubset(arr, n, idx + 1, current, sz);
}

void demoPermutations(int arr[], int n, int cur[], int pos, bool used[]) {
    if (pos == n) {
        cout << "  [";
        for (int i = 0; i < n; i++) {
            cout << cur[i];
            if (i + 1 < n) cout << ", ";
        }
        cout << "]" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        used[i] = true;
        cur[pos] = arr[i];
        demoPermutations(arr, n, cur, pos + 1, used);
        used[i] = false;
    }
}

void demoCombinations(int n, int k, int start, int cur[], int sz) {
    if (sz == k) {
        cout << "  {";
        for (int i = 0; i < sz; i++) {
            cout << cur[i];
            if (i + 1 < sz) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }
    for (int i = start; i <= n; i++) {
        cur[sz] = i;
        demoCombinations(n, k, i + 1, cur, sz + 1);
    }
}

int main() {
    cout << "=== Backtracking Framework Summary ===" << endl;
    cout << endl;

    cout << "The Framework:" << endl;
    cout << "  CHOICE -> CONSTRAINT -> GOAL -> PRUNE -> BACKTRACK" << endl;
    cout << endl;

    // Quick demos
    int arr[] = {1, 2, 3};
    int n = 3;

    cout << "Subsets of {1,2,3}:" << endl;
    int cur[3];
    demoSubset(arr, n, 0, cur, 0);
    cout << endl;

    cout << "Permutations of {1,2,3}:" << endl;
    int cur2[3];
    bool used[3];
    for (int i = 0; i < 3; i++) used[i] = false;
    demoPermutations(arr, n, cur2, 0, used);
    cout << endl;

    cout << "C(3,2) from {1,2,3}:" << endl;
    int cur3[2];
    demoCombinations(3, 2, 1, cur3, 0);
    cout << endl;

    cout << "Files in this folder:" << endl;
    cout << "  01_What_Is_Backtracking.cpp   - Paradigm + state space tree" << endl;
    cout << "  02_Subset_Generation.cpp      - Include/exclude, 2^n subsets" << endl;
    cout << "  03_Permutations.cpp           - used[] array, n! permutations" << endl;
    cout << "  04_Combinations.cpp           - C(n,k), combination sum, subset sum" << endl;
    cout << "  05_Pruning_Optimization.cpp   - Early termination, advanced pruning" << endl;
    cout << "  06_Backtracking_Framework_Summary.cpp - This file" << endl;
    cout << endl;

    cout << "Next: 11.2 Classic Problems (N-Queens, Sudoku, Rat in Maze, ...)" << endl;

    return 0;
}
