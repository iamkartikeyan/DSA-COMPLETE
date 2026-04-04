// 03_Permutations.cpp
// Generate all n! permutations of a given set of n distinct elements.
//
// Approach: used[] array to track which elements are already placed.
// At each position, try every unused element, mark it used, recurse,
// then unmark it (backtrack).
//
// Time Complexity: O(n! * n) - n! permutations, each takes O(n) to copy/print.
// Space Complexity: O(n) - recursion depth + used[] array + current[] buffer.

#include <iostream>
using namespace std;

int permCount = 0;

/*
 * generatePermutations - Generate all permutations using used[] array
 *
 * Parameters:
 *   arr[]     - input array of distinct elements
 *   n         - total number of elements
 *   current[] - buffer holding the permutation being built
 *   pos       - current position we are filling (0 to n-1)
 *   used[]    - boolean array: used[i] = true if arr[i] is already placed
 *
 * Backtracking flow:
 *   CHOICE:     Pick any unused element arr[i] for position pos.
 *   CONSTRAINT: Element must not already be used (used[i] == false).
 *   GOAL:       pos == n (all positions filled = complete permutation).
 *   PRUNING:    Not needed here (all orderings are valid permutations).
 *   BACKTRACK:  After recursive call, set used[i] = false to allow
 *               arr[i] to be used in other positions in different permutations.
 */
void generatePermutations(int arr[], int n, int current[], int pos, bool used[]) {
    // GOAL: all positions filled, we have a complete permutation
    if (pos == n) {
        permCount++;
        cout << "Perm " << permCount << ": [";
        for (int i = 0; i < n; i++) {
            cout << current[i];
            if (i + 1 < n) cout << ", ";
        }
        cout << "]" << endl;
        return;
    }

    // Try every element for position pos
    for (int i = 0; i < n; i++) {
        // CONSTRAINT: skip if arr[i] is already used
        if (used[i]) continue;

        // CHOICE: place arr[i] at position pos
        current[pos] = arr[i];
        used[i] = true;                    // mark as used

        generatePermutations(arr, n, current, pos + 1, used);  // recurse for next position

        // BACKTRACK: undo choice
        used[i] = false;                   // unmark so arr[i] can be used elsewhere
        // current[pos] will be overwritten by next iteration, no explicit undo needed
    }
}

/*
 * Alternative: Swap-based permutation (in-place)
 * Instead of used[] array, swap elements to fix positions.
 * This modifies the original array but uses less auxiliary space.
 */
void permuteSwap(int arr[], int n, int pos) {
    if (pos == n) {
        permCount++;
        cout << "Perm " << permCount << ": [";
        for (int i = 0; i < n; i++) {
            cout << arr[i];
            if (i + 1 < n) cout << ", ";
        }
        cout << "]" << endl;
        return;
    }

    for (int i = pos; i < n; i++) {
        // CHOICE: swap arr[pos] with arr[i]
        int temp = arr[pos];
        arr[pos] = arr[i];
        arr[i] = temp;

        permuteSwap(arr, n, pos + 1);  // recurse for next position

        // BACKTRACK: undo swap (restore original order)
        temp = arr[pos];
        arr[pos] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    cout << "=== Permutations ===" << endl;
    cout << endl;

    int arr[] = {1, 2, 3};
    int n = 3;
    int current[3];
    bool used[3];

    // Initialize used[] array
    for (int i = 0; i < n; i++) used[i] = false;

    cout << "Input: {1, 2, 3}" << endl;
    cout << "Expected permutations: 3! = 6" << endl;
    cout << endl;

    cout << "--- Method 1: used[] array approach ---" << endl;
    permCount = 0;
    generatePermutations(arr, n, current, 0, used);
    cout << "Total: " << permCount << " permutations" << endl;
    cout << endl;

    cout << "--- Method 2: Swap-based (in-place) ---" << endl;
    permCount = 0;
    permuteSwap(arr, n, 0);
    cout << "Total: " << permCount << " permutations" << endl;
    cout << endl;

    cout << "Comparison of the two methods:" << endl;
    cout << "  used[] array:" << endl;
    cout << "    - Does not modify original array" << endl;
    cout << "    - Needs O(n) extra space for used[] and current[]" << endl;
    cout << "    - More intuitive: 'pick unused element for position'" << endl;
    cout << endl;
    cout << "  Swap-based:" << endl;
    cout << "    - Modifies original array (but restores it via backtracking)" << endl;
    cout << "    - Less auxiliary space (no used[] needed)" << endl;
    cout << "    - Trickier to understand: 'swap to fix position, then undo'" << endl;
    cout << endl;

    cout << "Backtracking logic:" << endl;
    cout << "  At each position, we have (n - pos) choices (remaining unused elements)." << endl;
    cout << "  We pick one, mark it used, recurse for the next position." << endl;
    cout << "  When the recursion returns, we unmark it (backtrack)" << endl;
    cout << "  so it can be used in a different position in another permutation." << endl;
    cout << endl;

    // n = 4 example
    int arr2[] = {1, 2, 3, 4};
    int n2 = 4;
    int current2[4];
    bool used2[4];
    for (int i = 0; i < n2; i++) used2[i] = false;

    cout << "Permutations of {1, 2, 3, 4} (4! = 24):" << endl;
    permCount = 0;
    generatePermutations(arr2, n2, current2, 0, used2);
    cout << "Total: " << permCount << " permutations" << endl;

    return 0;
}
