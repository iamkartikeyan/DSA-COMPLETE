// 11.1 Backtracking Fundamentals
// Backtracking = Choice -> Constraints -> Goal -> Prune -> Backtrack
// State Space Tree: each node = partial solution, leaves = complete or dead end

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// CONCEPTS
// Choice:    Pick an option from available candidates
// Constraint: Valid? Does this choice violate any rules?
// Goal:      Have we reached a complete, valid solution?
// Pruning:   Skip branches that cannot lead to a solution (optimization)
// Backtrack: Undo choice and try next option
// ============================================================

// ============================================================
// 1. SUBSET GENERATION
// Each element: either include or exclude (2^n subsets)
// State space tree: binary tree of depth n
// ============================================================
void subsets(const vector<int>& nums, int idx, vector<int>& current,
             vector<vector<int>>& result) {
    if (idx == (int)nums.size()) {            // Goal: processed all elements
        result.push_back(current);
        return;
    }
    // Choice 1: Include nums[idx]
    current.push_back(nums[idx]);
    subsets(nums, idx + 1, current, result);
    current.pop_back();                        // Backtrack (undo)

    // Choice 2: Exclude nums[idx]
    subsets(nums, idx + 1, current, result);
    // No undo needed (didn't add anything)
}

// ============================================================
// 2. PERMUTATIONS
// Fix each element at current position, recurse for rest
// n! permutations, use used[] array to track picked elements
// ============================================================
void permutations(const vector<int>& nums, vector<int>& current,
                  vector<bool>& used, vector<vector<int>>& result) {
    if ((int)current.size() == (int)nums.size()) {  // Goal: all positions filled
        result.push_back(current);
        return;
    }
    for (int i = 0; i < (int)nums.size(); i++) {
        if (used[i]) continue;                     // Constraint: skip used
        used[i] = true;                            // Choice: pick nums[i]
        current.push_back(nums[i]);
        permutations(nums, current, used, result);
        current.pop_back();                        // Backtrack
        used[i] = false;                           // Undo choice
    }
}

// ============================================================
// 3. COMBINATIONS (choose k from n)
// C(n,k) combinations, each element picked at most once
// ============================================================
void combinations(int n, int k, int start, vector<int>& current,
                  vector<vector<int>>& result) {
    if ((int)current.size() == k) {              // Goal: picked k elements
        result.push_back(current);
        return;
    }
    for (int i = start; i <= n; i++) {
        current.push_back(i);                    // Choice: pick i
        combinations(n, k, i + 1, current, result);
        current.pop_back();                      // Backtrack
    }
}

// ============================================================
// 4. COMBINATION SUM (with duplicates allowed)
// Each candidate can be reused; constraint: sum <= target
// ============================================================
void combinationSum(const vector<int>& candidates, int target, int idx,
                    vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {                          // Goal: exact sum reached
        result.push_back(current);
        return;
    }
    if (target < 0 || idx == (int)candidates.size()) return; // Prune

    // Choice 1: Include candidates[idx] (can reuse)
    current.push_back(candidates[idx]);
    combinationSum(candidates, target - candidates[idx], idx, current, result);
    current.pop_back();

    // Choice 2: Skip candidates[idx]
    combinationSum(candidates, target, idx + 1, current, result);
}

// ============================================================
// 5. SUBSET SUM (target sum subset)
// Find all subsets that sum to target
// ============================================================
void subsetSum(const vector<int>& nums, int target, int idx,
               vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    if (target < 0 || idx == (int)nums.size()) return; // Prune

    // Include nums[idx]
    current.push_back(nums[idx]);
    subsetSum(nums, target - nums[idx], idx + 1, current, result);
    current.pop_back();

    // Skip nums[idx]
    subsetSum(nums, target, idx + 1, current, result);
}

// ============================================================
// 6. PRUNING DEMO: Early termination when impossible
// ============================================================
bool canReachTarget(const vector<int>& nums, int idx, int currentSum, int target) {
    if (currentSum == target) return true;       // Goal
    if (currentSum > target || idx == (int)nums.size()) return false; // Prune
    // Try include or exclude
    return canReachTarget(nums, idx + 1, currentSum + nums[idx], target) ||
           canReachTarget(nums, idx + 1, currentSum, target);
}

// Print helper
void printMatrix(const vector<vector<int>>& mat, const string& label) {
    cout << label << "\n";
    for (auto& row : mat) {
        cout << "[";
        for (int i = 0; i < (int)row.size(); i++) {
            cout << row[i] << (i + 1 < (int)row.size() ? ", " : "");
        }
        cout << "] ";
    }
    cout << "\n";
}

int main() {
    cout << "=== 11.1 Backtracking Fundamentals ===\n\n";

    // --- Subsets ---
    vector<int> nums = {1, 2, 3};
    cout << "Subsets of {1, 2, 3} (2^3 = 8 subsets):\n";
    vector<vector<int>> subs;
    vector<int> temp;
    subsets(nums, 0, temp, subs);
    printMatrix(subs, "");

    // --- Permutations ---
    cout << "\nPermutations of {1, 2, 3} (3! = 6):\n";
    vector<vector<int>> perms;
    vector<int> cur;
    vector<bool> used(3, false);
    permutations(nums, cur, used, perms);
    printMatrix(perms, "");

    // --- Combinations C(4,2) ---
    cout << "\nCombinations C(4,2) = 6:\n";
    vector<vector<int>> combs;
    cur.clear();
    combinations(4, 2, 1, cur, combs);
    printMatrix(combs, "");

    // --- Combination Sum ---
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    cout << "\nCombination Sum of {2,3,6,7} target=7:\n";
    vector<vector<int>> combSums;
    cur.clear();
    combinationSum(candidates, target, 0, cur, combSums);
    printMatrix(combSums, "");

    // --- Subset Sum ---
    vector<int> vals = {1, 2, 3, 4};
    target = 5;
    cout << "\nSubsets of {1,2,3,4} summing to 5:\n";
    vector<vector<int>> subSums;
    cur.clear();
    subsetSum(vals, target, 0, cur, subSums);
    printMatrix(subSums, "");

    // --- Pruning ---
    cout << "\nCan {1,2,3,4} reach sum=6? "
         << (canReachTarget(vals, 0, 0, 6) ? "Yes" : "No") << "\n";
    cout << "Can {1,2,3,4} reach sum=15? "
         << (canReachTarget(vals, 0, 0, 15) ? "Yes" : "No") << "\n";

    cout << "\n--- State Space Tree ---\n";
    cout << "Each node = partial solution\n";
    cout << "Branches = available choices\n";
    cout << "Leaf = complete solution or dead end (pruned)\n";
    cout << "Backtracking = DFS with undo of choices\n";

    return 0;
}
