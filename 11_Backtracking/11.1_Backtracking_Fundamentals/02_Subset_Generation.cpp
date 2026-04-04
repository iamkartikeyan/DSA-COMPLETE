// 02_Subset_Generation.cpp
// Generate all 2^n subsets of a given set.
// Each element has exactly 2 choices: include it or exclude it.
// Total subsets = 2^n (including the empty set).
//
// Time Complexity: O(2^n) - we visit every leaf in the binary state space tree.
// Space Complexity: O(n) - recursion depth + current subset buffer.

#include <iostream>
using namespace std;

// Count subsets (just to track)
int subsetCount = 0;

/*
 * generateSubsets - Print all subsets using include/exclude pattern
 *
 * Parameters:
 *   arr[]        - input array of elements
 *   n            - number of elements
 *   idx          - current index being considered
 *   current[]    - buffer holding the current subset
 *   currentSize  - number of elements currently in subset
 *
 * Backtracking flow:
 *   CHOICE:     include arr[idx] OR exclude arr[idx]
 *   CONSTRAINT: none (all subsets are valid for this problem)
 *   GOAL:       idx == n (all elements processed)
 *   PRUNING:    not needed here (no invalid subsets)
 *   BACKTRACK:  after including, the recursive call returns and we
 *               implicitly "undo" by not incrementing currentSize in the exclude branch.
 */
void generateSubsets(int arr[], int n, int idx, int current[], int currentSize) {
    // GOAL: all elements processed, print the subset
    if (idx == n) {
        subsetCount++;
        cout << "Subset " << subsetCount << ": {";
        for (int i = 0; i < currentSize; i++) {
            cout << current[i];
            if (i + 1 < currentSize) cout << ", ";
        }
        cout << "}" << endl;
        return;
    }

    // ---- CHOICE 1: Include arr[idx] ----
    current[currentSize] = arr[idx];           // add to current subset
    generateSubsets(arr, n, idx + 1, current, currentSize + 1);  // recurse
    // BACKTRACK: undo include (currentSize not passed to exclude branch, so implicit undo)

    // ---- CHOICE 2: Exclude arr[idx] ----
    generateSubsets(arr, n, idx + 1, current, currentSize);  // recurse without adding
}

/*
 * Alternative approach: bitmask enumeration
 * For small n (n <= 20), we can use an integer bitmask.
 * Each bit represents include (1) or exclude (0) for that element.
 * This is iterative, not recursive backtracking, but produces the same result.
 */
void generateSubsetsBitmask(int arr[], int n) {
    int total = 1 << n;  // 2^n
    cout << "  (Using bitmask method)" << endl;
    for (int mask = 0; mask < total; mask++) {
        cout << "  {";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {  // bit i is set -> include arr[i]
                if (!first) cout << ", ";
                cout << arr[i];
                first = false;
            }
        }
        cout << "}" << endl;
    }
}

int main() {
    cout << "=== Subset Generation ===" << endl;
    cout << endl;

    int arr[] = {1, 2, 3};
    int n = 3;
    int current[3];  // buffer, max size = n

    cout << "Input set: {1, 2, 3}" << endl;
    cout << "Expected subsets: 2^3 = 8" << endl;
    cout << endl;

    cout << "--- Backtracking (Include/Exclude) ---" << endl;
    subsetCount = 0;
    generateSubsets(arr, n, 0, current, 0);
    cout << "Total: " << subsetCount << " subsets" << endl;
    cout << endl;

    cout << "--- Bitmask (Iterative) ---" << endl;
    generateSubsetsBitmask(arr, n);
    cout << endl;

    cout << "Key observations:" << endl;
    cout << "  - Each element = 2 choices (include / exclude)" << endl;
    cout << "  - State space tree = binary tree of depth n" << endl;
    cout << "  - Total leaves = 2^n (all possible subsets)" << endl;
    cout << "  - No pruning needed (no constraints to violate)" << endl;
    cout << "  - Backtracking still useful: easy to add constraints" << endl;
    cout << "    (e.g., 'only subsets with sum <= K')" << endl;

    // Larger example: n = 4
    cout << endl;
    int arr2[] = {1, 2, 3, 4};
    int n2 = 4;
    int current2[4];
    cout << "Subsets of {1, 2, 3, 4} (2^4 = 16):" << endl;
    subsetCount = 0;
    generateSubsets(arr2, n2, 0, current2, 0);
    cout << "Total: " << subsetCount << " subsets" << endl;

    return 0;
}
