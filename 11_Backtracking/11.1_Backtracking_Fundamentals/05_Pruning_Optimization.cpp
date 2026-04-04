// 05_Pruning_Optimization.cpp
// Pruning = cutting off branches of the state space tree that cannot
// possibly lead to a valid solution. This is the key optimization that
// distinguishes backtracking from brute force.
//
// When to prune:
//   1. Current partial solution already violates a constraint.
//   2. Even the best possible continuation cannot reach the goal.
//   3. Symmetry: this branch is equivalent to one already explored.
//
// This file demonstrates pruning with the "can reach target" problem
// and shows how pruning reduces the search space dramatically.

#include <iostream>
using namespace std;

int totalNodes = 0;       // total recursive calls (with and without pruning)
int prunedNodes = 0;      // calls that returned early due to pruning

/*
 * ============================================================
 * PROBLEM: Can we pick a subset of nums[] that sums to target?
 *
 * Without pruning: explore all 2^n subsets.
 * With pruning: stop early when:
 *   - currentSum == target (found it, no need to continue)
 *   - currentSum > target (overshot, impossible to fix by adding more)
 *   - idx == n (no more elements, and sum != target)
 * ============================================================
 */

// Version WITHOUT pruning (pure brute force)
bool canReachNoPruning(int nums[], int n, int idx, int currentSum, int target) {
    totalNodes++;

    if (currentSum == target) return true;
    if (idx == n) return false;

    // Try both branches always
    return canReachNoPruning(nums, n, idx + 1, currentSum + nums[idx], target) ||
           canReachNoPruning(nums, n, idx + 1, currentSum, target);
}

// Version WITH pruning
bool canReachWithPruning(int nums[], int n, int idx, int currentSum, int target) {
    totalNodes++;

    if (currentSum == target) return true;

    // PRUNE: overshot or no more elements
    if (currentSum > target || idx == n) {
        prunedNodes++;
        return false;
    }

    // Try include (if it won't overshoot) and exclude
    return canReachWithPruning(nums, n, idx + 1, currentSum + nums[idx], target) ||
           canReachWithPruning(nums, n, idx + 1, currentSum, target);
}

/*
 * ============================================================
 * ADVANCED PRUNING: Bounded subset sum
 * Find ALL subsets that sum to target, with pruning.
 *
 * Advanced prune: if currentSum + sum(remaining elements) < target,
 * we can never reach the target even if we take everything left.
 * ============================================================
 */
void subsetSumWithPruning(int nums[], int n, int target, int idx,
                           int currentSum, int current[], int currentSize,
                           int remainingSum) {
    totalNodes++;

    // GOAL
    if (currentSum == target) {
        cout << "  {";
        for (int i = 0; i < currentSize; i++) {
            cout << current[i];
            if (i + 1 < currentSize) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }

    // PRUNE 1: overshot
    if (currentSum > target) {
        prunedNodes++;
        return;
    }

    // PRUNE 2: even taking all remaining elements, cannot reach target
    if (currentSum + remainingSum < target) {
        prunedNodes++;
        return;
    }

    // PRUNE 3: no more elements
    if (idx == n) {
        prunedNodes++;
        return;
    }

    // CHOICE 1: Include nums[idx]
    current[currentSize] = nums[idx];
    subsetSumWithPruning(nums, n, target, idx + 1,
                         currentSum + nums[idx], current, currentSize + 1,
                         remainingSum - nums[idx]);
    // BACKTRACK: implicit

    // CHOICE 2: Exclude nums[idx]
    subsetSumWithPruning(nums, n, target, idx + 1,
                         currentSum, current, currentSize,
                         remainingSum - nums[idx]);
}

/*
 * ============================================================
 * DEMO: Count visited nodes with and without pruning
 * ============================================================
 */
void demoPruningBenefit() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = 10;
    int target = 15;

    cout << "Array: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}" << endl;
    cout << "Target: " << target << endl;
    cout << endl;

    // Without pruning
    totalNodes = 0;
    canReachNoPruning(nums, n, 0, 0, target);
    int nodesWithoutPruning = totalNodes;
    cout << "Without pruning: " << nodesWithoutPruning << " nodes visited" << endl;

    // With pruning
    totalNodes = 0;
    prunedNodes = 0;
    canReachWithPruning(nums, n, 0, 0, target);
    int nodesWithPruning = totalNodes;
    cout << "With pruning:    " << nodesWithPruning << " nodes visited ("
         << prunedNodes << " pruned)" << endl;

    cout << "Saved: " << (nodesWithoutPruning - nodesWithPruning)
         << " nodes ("
         << (100 * (nodesWithoutPruning - nodesWithPruning)) / nodesWithoutPruning
         << "% reduction)" << endl;
}

int main() {
    cout << "=== Pruning Optimization ===" << endl;
    cout << endl;

    cout << "What is pruning?" << endl;
    cout << "  Pruning = cutting off branches that cannot lead to a solution." << endl;
    cout << "  It is the key optimization that makes backtracking faster than brute force." << endl;
    cout << endl;

    cout << "When to prune:" << endl;
    cout << "  1. Constraint violated (e.g., sum > target)" << endl;
    cout << "  2. Goal unreachable (e.g., remaining elements cannot close the gap)" << endl;
    cout << "  3. Symmetry detected (e.g., equivalent state already explored)" << endl;
    cout << endl;

    // ---- Demo: pruning benefit ----
    cout << "--- Pruning Benefit Demo ---" << endl;
    demoPruningBenefit();
    cout << endl;

    // ---- Subset sum with advanced pruning ----
    cout << "--- Subset Sum with Advanced Pruning ---" << endl;
    int nums[] = {1, 2, 3, 4, 5};
    int n = 5;
    int target = 7;
    int current[5];
    int remainingSum = 0;
    for (int i = 0; i < n; i++) remainingSum += nums[i];

    cout << "Nums: {1, 2, 3, 4, 5}, Target: " << target << endl;
    totalNodes = 0;
    prunedNodes = 0;
    subsetSumWithPruning(nums, n, target, 0, 0, current, 0, remainingSum);
    cout << "Nodes visited: " << totalNodes << " (pruned: " << prunedNodes << ")" << endl;
    cout << endl;

    // ---- Impossibility demo ----
    cout << "--- Impossibility Detection ---" << endl;
    totalNodes = 0;
    prunedNodes = 0;
    bool possible = canReachWithPruning(nums, n, 0, 0, 100);
    cout << "Can {1,2,3,4,5} reach sum=100? " << (possible ? "Yes" : "No") << endl;
    cout << "Nodes visited: " << totalNodes << " (pruned: " << prunedNodes << ")" << endl;
    cout << "  (Pruning detects impossibility very early)" << endl;
    cout << endl;

    cout << "Summary:" << endl;
    cout << "  Pruning transforms O(2^n) brute force into a much faster search" << endl;
    cout << "  by eliminating impossible branches before they are explored." << endl;
    cout << "  The more aggressive the pruning, the faster the algorithm," << endl;
    cout << "  as long as the pruning logic itself is correct and does not" << endl;
    cout << "  accidentally skip valid solutions." << endl;

    return 0;
}
