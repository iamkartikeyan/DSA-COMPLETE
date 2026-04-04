// Fenwick Tree (Binary Indexed Tree)
// Supports point updates and range sum queries in O(log n).
//
// Core Operations:
//   1. add(idx, delta): Add delta to element at idx (1-based)
//   2. query(idx): Sum of elements from index 1 to idx
//   3. rangeSum(l, r): Sum of elements from index l to r = query(r) - query(l-1)
//
// Key Insight:
//   Each BIT node i stores the sum of a specific range.
//   Parent navigation: i += i & (-i) for updates (move right/up)
//   Child navigation: i -= i & (-i) for queries (move left/down)
//
// Time Complexity:
//   Build:  O(n log n) or O(n) with optimized build
//   Update: O(log n)
//   Query:  O(log n)
//   Space:  O(n)
//
// Unlike prefix sum array, BIT supports efficient point updates.

#include <iostream>
using namespace std;

const int MAXN = 1000;

class FenwickTree {
    int n;
    int bit[MAXN + 1];

public:
    FenwickTree() {
        n = 0;
        for (int i = 0; i <= MAXN; i++) {
            bit[i] = 0;
        }
    }

    // Initialize with an array (size sz)
    void init(const int arr[], int sz) {
        n = sz;
        for (int i = 1; i <= n; i++) {
            bit[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            update(i + 1, arr[i]);
        }
    }

    // Add delta to element at index i (1-based)
    void update(int i, int delta) {
        for (; i <= n; i += i & (-i)) {
            bit[i] += delta;
        }
    }

    // Prefix sum from index 1 to i (1-based)
    int query(int i) {
        int s = 0;
        for (; i > 0; i -= i & (-i)) {
            s += bit[i];
        }
        return s;
    }

    // Range sum from index l to r (1-based)
    int rangeSum(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    cout << "=== Fenwick Tree (Binary Indexed Tree) ===" << endl;
    cout << endl;

    // Initialize array
    int arr[] = {1, 3, 5, 7, 9};
    int n = 5;

    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Build Fenwick Tree
    FenwickTree ft;
    ft.init(arr, n);

    cout << endl;
    cout << "Range Sum Queries (1-based indexing):" << endl;

    // Query 1: sum [1..3] = 3 + 5 + 7 = 15
    cout << "  Sum [1..3] = " << ft.rangeSum(1, 3) << "  (expected: 3+5+7=15)" << endl;

    // Query 2: sum [2..5] = 5 + 7 + 9 = 21
    cout << "  Sum [2..5] = " << ft.rangeSum(2, 5) << "  (expected: 5+7+9=21)" << endl;

    // Query 3: sum [1..5] = total = 25
    cout << "  Sum [1..5] = " << ft.rangeSum(1, 5) << "  (expected: 1+3+5+7+9=25)" << endl;

    cout << endl;
    cout << "Point Update: Add 10 to index 3 (1-based)" << endl;
    ft.update(3, 10);
    // Array conceptually becomes: {1, 3, 15, 7, 9}

    cout << "  After update, Sum [1..3] = " << ft.rangeSum(1, 3) << "  (expected: 1+3+15=19)" << endl;
    cout << "  After update, Sum [1..5] = " << ft.rangeSum(1, 5) << "  (expected: 1+3+15+7+9=35)" << endl;

    cout << endl;
    cout << "BIT Navigation Explained:" << endl;
    cout << "  Update: i += i & (-i)  (moves to parent covering larger range)" << endl;
    cout << "  Query:  i -= i & (-i)  (moves to child covering smaller range)" << endl;
    cout << endl;

    // Show BIT internal structure
    cout << "BIT internal structure (1-based):" << endl;
    cout << "  i   binary   i&(-i)   covers range" << endl;
    for (int i = 1; i <= n; i++) {
        int lowbit = i & (-i);
        cout << "  " << i << "   ";
        // Print binary representation
        int bits[4];
        int temp = i;
        for (int b = 3; b >= 0; b--) {
            bits[b] = temp % 2;
            temp /= 2;
        }
        for (int b = 0; b < 4; b++) cout << bits[b];
        cout << "      " << lowbit;
        cout << "      [" << (i - lowbit + 1) << ".." << i << "]" << endl;
    }

    return 0;
}
