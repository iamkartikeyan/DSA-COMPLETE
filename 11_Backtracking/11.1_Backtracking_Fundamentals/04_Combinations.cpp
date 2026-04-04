// 04_Combinations.cpp
// Covers three combination-related problems:
//   1. C(n, k) combinations - choose k elements from {1, 2, ..., n}
//   2. Combination Sum    - find combinations that sum to target (reuse allowed)
//   3. Subset Sum         - find subsets that sum to target (no reuse)
//
// Key difference from permutations: order does NOT matter.
// {1, 2} and {2, 1} are the SAME combination.
// We enforce this by only moving FORWARD (start index increases).

#include <iostream>
using namespace std;

// Counters
int combCount = 0;

/*
 * ============================================================
 * PROBLEM 1: C(n, k) Combinations
 * Choose k distinct elements from {1, 2, ..., n}.
 * Order does not matter: {1,2} == {2,1}.
 * Total = C(n,k) = n! / (k! * (n-k)!)
 *
 * Key: use 'start' parameter to avoid reusing earlier elements
 *      and to prevent duplicate combinations.
 * ============================================================
 */
void combinations(int n, int k, int start, int current[], int currentSize) {
    // GOAL: picked k elements
    if (currentSize == k) {
        combCount++;
        cout << "  {";
        for (int i = 0; i < currentSize; i++) {
            cout << current[i];
            if (i + 1 < currentSize) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }

    // Try each element from start to n
    for (int i = start; i <= n; i++) {
        current[currentSize] = i;        // CHOICE: pick element i
        combinations(n, k, i + 1, current, currentSize + 1);  // recurse (i+1 to avoid reuse)
        // BACKTRACK: currentSize not incremented in loop, implicit undo
    }
}

/*
 * ============================================================
 * PROBLEM 2: Combination Sum (reuse allowed)
 * Given candidates[] and target, find all combinations that sum to target.
 * Each candidate can be used INFINITELY many times.
 *
 * Key: recurse with SAME index (idx, not idx+1) to allow reuse.
 * ============================================================
 */
void combinationSum(int candidates[], int n, int target, int idx,
                    int current[], int currentSize) {
    // GOAL: exact sum reached
    if (target == 0) {
        combCount++;
        cout << "  {";
        for (int i = 0; i < currentSize; i++) {
            cout << current[i];
            if (i + 1 < currentSize) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }

    // PRUNE: target < 0 (overshot) or no more candidates
    if (target < 0 || idx == n) return;

    // CHOICE 1: Include candidates[idx] (can reuse, so pass idx again)
    current[currentSize] = candidates[idx];
    combinationSum(candidates, n, target - candidates[idx], idx, current, currentSize + 1);
    // BACKTRACK: implicit via currentSize

    // CHOICE 2: Skip candidates[idx] entirely
    combinationSum(candidates, n, target, idx + 1, current, currentSize);
}

/*
 * ============================================================
 * PROBLEM 3: Subset Sum (no reuse)
 * Given nums[] and target, find all subsets that sum to target.
 * Each element can be used AT MOST ONCE.
 *
 * Key: recurse with idx+1 for both include and exclude branches.
 * ============================================================
 */
void subsetSum(int nums[], int n, int target, int idx,
               int current[], int currentSize) {
    // GOAL: exact sum reached
    if (target == 0) {
        combCount++;
        cout << "  {";
        for (int i = 0; i < currentSize; i++) {
            cout << current[i];
            if (i + 1 < currentSize) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }

    // PRUNE: target < 0 or no more elements
    if (target < 0 || idx == n) return;

    // CHOICE 1: Include nums[idx]
    current[currentSize] = nums[idx];
    subsetSum(nums, n, target - nums[idx], idx + 1, current, currentSize + 1);
    // BACKTRACK: implicit

    // CHOICE 2: Exclude nums[idx]
    subsetSum(nums, n, target, idx + 1, current, currentSize);
}

int main() {
    cout << "=== Combinations ===" << endl;
    cout << endl;

    // ---- C(n, k) ----
    cout << "--- C(n, k): Choose k from {1, 2, ..., n} ---" << endl;
    int current[4];

    cout << "C(4, 2) = 6:" << endl;
    combCount = 0;
    combinations(4, 2, 1, current, 0);
    cout << "Total: " << combCount << " combinations" << endl;
    cout << endl;

    cout << "C(5, 3) = 10:" << endl;
    combCount = 0;
    combinations(5, 3, 1, current, 0);
    cout << "Total: " << combCount << " combinations" << endl;
    cout << endl;

    // ---- Combination Sum ----
    cout << "--- Combination Sum (reuse allowed) ---" << endl;
    int candidates[] = {2, 3, 6, 7};
    int nCand = 4;
    int target = 7;
    int current2[10];  // buffer, max elements in a combination

    cout << "Candidates: {2, 3, 6, 7}, Target: " << target << endl;
    combCount = 0;
    combinationSum(candidates, nCand, target, 0, current2, 0);
    cout << "Total: " << combCount << " combinations" << endl;
    cout << endl;

    // ---- Subset Sum ----
    cout << "--- Subset Sum (no reuse) ---" << endl;
    int nums[] = {1, 2, 3, 4};
    int nNums = 4;
    target = 5;
    int current3[4];

    cout << "Nums: {1, 2, 3, 4}, Target: " << target << endl;
    combCount = 0;
    subsetSum(nums, nNums, target, 0, current3, 0);
    cout << "Total: " << combCount << " subsets" << endl;
    cout << endl;

    cout << "Key differences:" << endl;
    cout << "  C(n, k):          fixed size k, no sum constraint" << endl;
    cout << "  Combination Sum:  variable size, reuse allowed, sum = target" << endl;
    cout << "  Subset Sum:       variable size, no reuse, sum = target" << endl;
    cout << endl;
    cout << "The 'start' / 'idx' parameter is crucial:" << endl;
    cout << "  - It prevents re-picking earlier elements (avoids duplicates)" << endl;
    cout << "  - Combination Sum passes idx (reuse allowed)" << endl;
    cout << "  - Subset Sum passes idx+1 (no reuse)" << endl;
    cout << "  - C(n,k) passes i+1 (each element picked once, move forward)" << endl;

    return 0;
}
