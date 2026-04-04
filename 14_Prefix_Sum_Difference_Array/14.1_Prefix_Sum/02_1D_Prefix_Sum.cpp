// 1D Prefix Sum - Build and Range Sum Queries in O(1)
// This file demonstrates building a 1D prefix sum array and answering
// multiple range sum queries in constant time.
//
// Formula:
//   prefix[0] = 0
//   prefix[i] = prefix[i-1] + arr[i-1]
//   sum(l, r) = prefix[r+1] - prefix[l]

#include <iostream>
using namespace std;

// Build 1D prefix sum array
// prefix[i] stores the sum of arr[0..i-1]
// Size is n+1 so that prefix[0] = 0 acts as a sentinel
void buildPrefix1D(const int arr[], int n, int prefix[]) {
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
}

// Range sum query: returns sum of arr[l..r] inclusive in O(1)
int rangeSum1D(const int prefix[], int l, int r) {
    return prefix[r + 1] - prefix[l];
}

int main() {
    cout << "=== 1D Prefix Sum ===" << endl;
    cout << endl;

    // Example array
    int arr[] = {2, 4, 1, 3, 5, 2, 7};
    int n = 7;
    int prefix[8];  // n + 1

    buildPrefix1D(arr, n, prefix);

    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Prefix: ";
    for (int i = 0; i <= n; i++) {
        cout << prefix[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Multiple range sum queries
    cout << "Range Sum Queries:" << endl;

    // Query 1: sum arr[1..4] = 4 + 1 + 3 + 5 = 13
    int l = 1, r = 4;
    cout << "  sum arr[" << l << ".." << r << "] = " << rangeSum1D(prefix, l, r) << endl;

    // Query 2: sum arr[0..6] = total sum = 24
    l = 0; r = 6;
    cout << "  sum arr[" << l << ".." << r << "] = " << rangeSum1D(prefix, l, r) << endl;

    // Query 3: sum arr[3..3] = single element = 3
    l = 3; r = 3;
    cout << "  sum arr[" << l << ".." << r << "] = " << rangeSum1D(prefix, l, r) << endl;

    // Query 4: sum arr[0..2] = 2 + 4 + 1 = 7
    l = 0; r = 2;
    cout << "  sum arr[" << l << ".." << r << "] = " << rangeSum1D(prefix, l, r) << endl;

    // Query 5: sum arr[4..6] = 5 + 2 + 7 = 14
    l = 4; r = 6;
    cout << "  sum arr[" << l << ".." << r << "] = " << rangeSum1D(prefix, l, r) << endl;

    cout << endl;
    cout << "All queries answered in O(1) after O(n) preprocessing." << endl;

    // Show step-by-step prefix sum construction
    cout << endl;
    cout << "Step-by-step construction:" << endl;
    cout << "  prefix[0] = 0" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  prefix[" << i + 1 << "] = prefix[" << i << "] + arr[" << i << "]";
        cout << " = " << prefix[i] << " + " << arr[i] << " = " << prefix[i + 1] << endl;
    }

    return 0;
}
