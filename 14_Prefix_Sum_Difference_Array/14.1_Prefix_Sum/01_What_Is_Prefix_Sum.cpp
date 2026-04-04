// What Is Prefix Sum?
// Prefix sum is a preprocessing technique that precomputes cumulative sums
// so that range sum queries can be answered in O(1) time.
//
// Core Formula:
//   prefix[0] = 0
//   prefix[i] = prefix[i-1] + arr[i-1]    for i = 1 to n
//
// Range Sum Query:
//   sum(arr[l..r]) = prefix[r+1] - prefix[l]
//
// Why prefix[0] = 0? This sentinel makes the formula work for l=0:
//   sum(arr[0..r]) = prefix[r+1] - prefix[0] = prefix[r+1]
//
// Example:
//   arr:    [2, 4, 1, 3, 5]
//   prefix: [0, 2, 6, 7, 10, 15]
//
//   sum(arr[1..3]) = prefix[4] - prefix[1] = 10 - 2 = 8  (which is 4+1+3)
//   sum(arr[0..4]) = prefix[5] - prefix[0] = 15 - 0 = 15 (which is 2+4+1+3+5)
//
// Time Complexity:
//   Build:  O(n)
//   Query:  O(1) per range sum
//   Space:  O(n) for the prefix array
//
// When to Use:
//   - Static arrays (no updates between queries)
//   - Many range sum queries on the same array
//   - Need O(1) per query after O(n) preprocessing

#include <iostream>
using namespace std;

int main() {
    cout << "=== What Is Prefix Sum? ===" << endl;
    cout << endl;

    // Example array
    int arr[] = {2, 4, 1, 3, 5};
    int n = 5;

    // Build prefix sum array
    // prefix[i] = sum of arr[0..i-1]
    int prefix[6];
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }

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

    // Demonstrate range sum formula: sum[l..r] = prefix[r+1] - prefix[l]
    cout << "Range Sum Examples:" << endl;

    // sum arr[1..3] = 4 + 1 + 3 = 8
    int l = 1, r = 3;
    int sum = prefix[r + 1] - prefix[l];
    cout << "  sum arr[" << l << ".." << r << "] = prefix[" << r + 1 << "] - prefix[" << l << "]";
    cout << " = " << prefix[r + 1] << " - " << prefix[l] << " = " << sum << endl;

    // sum arr[0..4] = 2 + 4 + 1 + 3 + 5 = 15
    l = 0; r = 4;
    sum = prefix[r + 1] - prefix[l];
    cout << "  sum arr[" << l << ".." << r << "] = prefix[" << r + 1 << "] - prefix[" << l << "]";
    cout << " = " << prefix[r + 1] << " - " << prefix[l] << " = " << sum << endl;

    // sum arr[2..2] = 1
    l = 2; r = 2;
    sum = prefix[r + 1] - prefix[l];
    cout << "  sum arr[" << l << ".." << r << "] = prefix[" << r + 1 << "] - prefix[" << l << "]";
    cout << " = " << prefix[r + 1] << " - " << prefix[l] << " = " << sum << endl;

    cout << endl;
    cout << "Key Insight: After O(n) preprocessing, every range sum is O(1)." << endl;
    cout << "Without prefix sum, each range sum would take O(r-l+1) = O(n)." << endl;
    cout << "With m queries: brute force = O(m*n), prefix sum = O(n + m)." << endl;

    return 0;
}
