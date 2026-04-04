// Basic Difference Array - Build, Update, Reconstruct
// Demonstrates the core difference array operations:
//   1. Build difference array from initial array
//   2. Apply range updates in O(1)
//   3. Reconstruct final array using prefix sum

#include <iostream>
using namespace std;

const int MAXN = 100;

// Build difference array: diff[i] = arr[i] - arr[i-1]
// diff[0] = arr[0]
void buildDiff(const int arr[], int n, int diff[]) {
    diff[0] = arr[0];
    for (int i = 1; i < n; i++) {
        diff[i] = arr[i] - arr[i - 1];
    }
}

// Range update: add val to arr[l..r] inclusive, O(1)
void rangeUpdate(int diff[], int n, int l, int r, int val) {
    diff[l] += val;
    if (r + 1 < n) {
        diff[r + 1] -= val;
    }
}

// Reconstruct array from difference array using prefix sum, O(n)
void reconstruct(const int diff[], int n, int arr[]) {
    arr[0] = diff[0];
    for (int i = 1; i < n; i++) {
        arr[i] = arr[i - 1] + diff[i];
    }
}

// Print array
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Basic Difference Array ===" << endl;
    cout << endl;

    // Initial array
    int arr[MAXN];
    int diff[MAXN];
    int result[MAXN];
    int n = 6;

    int initial[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < n; i++) {
        arr[i] = initial[i];
    }

    cout << "Step 1: Initial array" << endl;
    printArray(arr, n);
    cout << endl;

    // Build difference array
    buildDiff(arr, n, diff);
    cout << "Step 2: Build difference array" << endl;
    cout << "  diff: ";
    printArray(diff, n);
    cout << endl;

    // Apply range updates
    cout << "Step 3: Apply range updates (each O(1))" << endl;

    // Update 1: add 5 to indices 1-3
    int l = 1, r = 3, val = 5;
    cout << "  Update: add " << val << " to arr[" << l << ".." << r << "]" << endl;
    rangeUpdate(diff, n, l, r, val);
    cout << "  After update, diff: ";
    printArray(diff, n);

    // Update 2: add 3 to indices 2-5
    l = 2; r = 5; val = 3;
    cout << "  Update: add " << val << " to arr[" << l << ".." << r << "]" << endl;
    rangeUpdate(diff, n, l, r, val);
    cout << "  After update, diff: ";
    printArray(diff, n);

    cout << endl;

    // Reconstruct final array
    reconstruct(diff, n, result);
    cout << "Step 4: Reconstruct via prefix sum" << endl;
    cout << "  Result: ";
    printArray(result, n);

    cout << endl;
    cout << "Verification (manual calculation):" << endl;
    cout << "  arr[0] = 1  (unchanged)" << endl;
    cout << "  arr[1] = 2 + 5 = 7" << endl;
    cout << "  arr[2] = 3 + 5 + 3 = 11" << endl;
    cout << "  arr[3] = 4 + 5 + 3 = 12" << endl;
    cout << "  arr[4] = 5 + 3 = 8" << endl;
    cout << "  arr[5] = 6 + 3 = 9" << endl;

    cout << endl;
    cout << "Complexity Analysis:" << endl;
    cout << "  Naive approach: 2 updates * O(n) each = O(n) for updates" << endl;
    cout << "  Difference array: 2 * O(1) + O(n) reconstruct = O(n) total" << endl;
    cout << "  With m updates: naive = O(m*n), diff array = O(n + m)" << endl;

    return 0;
}
