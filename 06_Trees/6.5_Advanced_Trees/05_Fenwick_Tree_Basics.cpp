/*
 * File: 05_Fenwick_Tree_Basics.cpp
 * Topic: Fenwick Tree (Binary Indexed Tree) - Prefix Sum & Range Sum
 * Description: Simpler alternative to Segment Tree
 */
#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
    vector<int> bit; // Binary Indexed Tree (1-indexed)
    int n;

public:
    FenwickTree(vector<int>& arr) {
        n = arr.size();
        // Initialize BIT array with zeros
        bit.assign(n + 1, 0);
        // Add each element
        for (int i = 0; i < n; i++) {
            add(i, arr[i]);
        }
    }

    // Add val to arr[i] (point update)
    void add(int i, int val) {
        // Convert to 1-indexed
        i = i + 1;
        while (i <= n) {
            bit[i] = bit[i] + val;
            // Move to parent: add lowest set bit
            i = i + (i & (-i));
        }
    }

    // Get prefix sum from arr[0] to arr[i]
    int prefixSum(int i) {
        // Convert to 1-indexed
        i = i + 1;
        int sum = 0;
        while (i > 0) {
            sum = sum + bit[i];
            // Move to parent: subtract lowest set bit
            i = i - (i & (-i));
        }
        return sum;
    }

    // Get range sum from arr[l] to arr[r]
    int rangeSum(int l, int r) {
        if (l == 0) {
            return prefixSum(r);
        }
        return prefixSum(r) - prefixSum(l - 1);
    }
};

int main() {
    cout << "=== Fenwick Tree (Binary Indexed Tree) ===" << endl;
    cout << endl;

    vector<int> arr;
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(4);
    arr.push_back(6);
    arr.push_back(3);
    arr.push_back(5);

    cout << "Array: 2 1 4 6 3 5" << endl;
    cout << endl;

    FenwickTree ft(arr);

    cout << "--- Prefix Sums ---" << endl;
    int p1 = ft.prefixSum(3);
    cout << "PrefixSum[0..3] = " << p1 << " (expected: 2+1+4+6 = 13)" << endl;

    int p2 = ft.prefixSum(5);
    cout << "PrefixSum[0..5] = " << p2 << " (expected: 2+1+4+6+3+5 = 21)" << endl;

    cout << endl;
    cout << "--- Range Sums ---" << endl;
    int r1 = ft.rangeSum(1, 4);
    cout << "RangeSum[1..4]  = " << r1 << " (expected: 1+4+6+3 = 14)" << endl;

    int r2 = ft.rangeSum(0, 2);
    cout << "RangeSum[0..2]  = " << r2 << " (expected: 2+1+4 = 7)" << endl;

    cout << endl;
    cout << "--- Point Update ---" << endl;
    cout << "Add 5 to arr[2]: arr[2] goes from 4 to 9" << endl;
    ft.add(2, 5);

    int p3 = ft.prefixSum(3);
    cout << "PrefixSum[0..3] = " << p3 << " (expected: 2+1+9+6 = 18)" << endl;

    int r3 = ft.rangeSum(1, 4);
    cout << "RangeSum[1..4]  = " << r3 << " (expected: 1+9+6+3 = 19)" << endl;

    cout << endl;
    cout << "How it works:" << endl;
    cout << "  1. BIT array is 1-indexed" << endl;
    cout << "  2. Each index i stores sum of a range" << endl;
    cout << "  3. i & (-i) gives the lowest set bit" << endl;
    cout << "  4. To go UP (add): i += i & (-i)" << endl;
    cout << "  5. To go DOWN (query): i -= i & (-i)" << endl;
    cout << endl;
    cout << "Time: Build = O(n), Query = O(log n), Update = O(log n)" << endl;
    cout << "Space: O(n)" << endl;

    return 0;
}
