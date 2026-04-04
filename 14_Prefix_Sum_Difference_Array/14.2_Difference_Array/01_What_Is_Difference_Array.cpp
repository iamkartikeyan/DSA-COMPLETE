// What Is Difference Array?
// The difference array is the inverse operation of prefix sum.
// It enables efficient range updates: apply O(1) per update, reconstruct in O(n).
//
// Core Concept:
//   diff[0] = arr[0]
//   diff[i] = arr[i] - arr[i-1]    for i >= 1
//
// This means: arr[i] = diff[0] + diff[1] + ... + diff[i]
// (The original array is the prefix sum of the difference array!)
//
// Range Update in O(1):
//   To add val to arr[l..r]:
//     diff[l]   += val    // Start adding val from index l
//     diff[r+1] -= val    // Stop adding val after index r
//
// Reconstruct in O(n):
//   arr[0] = diff[0]
//   arr[i] = arr[i-1] + diff[i]    (prefix sum of diff)
//
// Example:
//   arr:    [1, 2, 3, 4, 5, 6]
//   diff:   [1, 1, 1, 1, 1, 1]
//
//   Update: add 5 to arr[1..3]
//   diff[1] += 5  -> diff: [1, 6, 1, 1, 1, 1]
//   diff[4] -= 5  -> diff: [1, 6, 1, 1, -4, 1]
//
//   Reconstruct: prefix sum of diff
//   arr: [1, 7, 8, 9, 5, 6]  (indices 1-3 got +5)
//
// Time Complexity:
//   Build:       O(n)
//   Range Update: O(1) per update
//   Reconstruct:  O(n) total
//
// vs Prefix Sum:
//   Prefix Sum:     fast queries O(1), no updates
//   Difference Array: fast updates O(1), queries after reconstruction O(n)
//
// When to Use:
//   - Many range updates on an array
//   - Only need final state after all updates
//   - Do not need intermediate query results between updates

#include <iostream>
using namespace std;

int main() {
    cout << "=== What Is Difference Array? ===" << endl;
    cout << endl;

    // Original array
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = 6;

    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Build difference array
    int diff[7];  // n + 1 for safety
    diff[0] = arr[0];
    for (int i = 1; i < n; i++) {
        diff[i] = arr[i] - arr[i - 1];
    }

    cout << "Difference array: ";
    for (int i = 0; i < n; i++) {
        cout << diff[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Demonstrate: diff[i] = arr[i] - arr[i-1]
    cout << "Verification (diff[i] = arr[i] - arr[i-1]):" << endl;
    cout << "  diff[0] = arr[0] = " << diff[0] << endl;
    for (int i = 1; i < n; i++) {
        cout << "  diff[" << i << "] = arr[" << i << "] - arr[" << i - 1 << "]";
        cout << " = " << arr[i] << " - " << arr[i - 1] << " = " << diff[i] << endl;
    }
    cout << endl;

    // Show reconstruction: prefix sum of diff recovers original arr
    cout << "Reconstruction (prefix sum of diff):" << endl;
    int recovered[6];
    recovered[0] = diff[0];
    cout << "  arr[0] = diff[0] = " << recovered[0] << endl;
    for (int i = 1; i < n; i++) {
        recovered[i] = recovered[i - 1] + diff[i];
        cout << "  arr[" << i << "] = arr[" << i - 1 << "] + diff[" << i << "]";
        cout << " = " << recovered[i - 1] << " + " << diff[i] << " = " << recovered[i] << endl;
    }
    cout << endl;

    cout << "Recovered array: ";
    for (int i = 0; i < n; i++) {
        cout << recovered[i] << " ";
    }
    cout << " (matches original)" << endl;
    cout << endl;

    // Key relationship
    cout << "Key Relationship:" << endl;
    cout << "  Prefix Sum and Difference Array are inverse operations." << endl;
    cout << "  Prefix sum of diff[] recovers arr[]" << endl;
    cout << "  Difference array of prefix[] recovers original values" << endl;
    cout << endl;

    cout << "Difference array excels at:" << endl;
    cout << "  - Batch range updates in O(1) each" << endl;
    cout << "  - Reconstruct final state in O(n)" << endl;
    cout << "  - Total: O(n + m) for m updates vs O(m*n) naive" << endl;

    return 0;
}
