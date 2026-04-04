/*
 * File: 03_Segment_Tree_Basics.cpp
 * Topic: Segment Tree - Build and Range Sum Query
 * Description: Tree for efficient range queries
 */
#include <iostream>
#include <vector>
using namespace std;

vector<int> tree; // segment tree array
int n; // size of original array

// Build segment tree
// node = current node index in tree array
// start, end = range this node covers
void build(vector<int>& arr, int node, int start, int end) {
    // Leaf node
    if (start == end) {
        tree[node] = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    // Build left child
    build(arr, 2 * node + 1, start, mid);
    // Build right child
    build(arr, 2 * node + 2, mid + 1, end);
    // Combine: sum of both children
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

// Range sum query: find sum in range [l, r]
int query(int node, int start, int end, int l, int r) {
    // Range completely outside
    if (r < start || end < l) {
        return 0;
    }

    // Range completely inside
    if (l <= start && end <= r) {
        return tree[node];
    }

    // Range partially overlaps
    int mid = (start + end) / 2;
    int leftSum = query(2 * node + 1, start, mid, l, r);
    int rightSum = query(2 * node + 2, mid + 1, end, l, r);
    return leftSum + rightSum;
}

int main() {
    cout << "=== Segment Tree - Range Sum ===" << endl;
    cout << endl;

    vector<int> arr;
    arr.push_back(1);
    arr.push_back(3);
    arr.push_back(5);
    arr.push_back(7);
    arr.push_back(9);
    arr.push_back(11);

    n = arr.size();

    cout << "Array: 1 3 5 7 9 11" << endl;
    cout << endl;

    /*
     * Segment Tree for sum:
     *
     *               [0-5]=36
     *            /            \
     *       [0-2]=9         [3-5]=27
     *      /      \         /      \
     *   [0-1]=4  [2]=5   [3-4]=16  [5]=11
     *   /    \           /    \
     * [0]=1 [1]=3     [3]=7  [4]=9
     */

    // Build tree (4*n is safe upper bound for tree size)
    tree.assign(4 * n, 0);
    build(arr, 0, 0, n - 1);

    cout << "--- Range Sum Queries ---" << endl;

    int sum1 = query(0, 0, n - 1, 0, 5);
    cout << "Sum[0..5] = " << sum1 << " (expected: 1+3+5+7+9+11 = 36)" << endl;

    int sum2 = query(0, 0, n - 1, 1, 3);
    cout << "Sum[1..3] = " << sum2 << " (expected: 3+5+7 = 15)" << endl;

    int sum3 = query(0, 0, n - 1, 2, 4);
    cout << "Sum[2..4] = " << sum3 << " (expected: 5+7+9 = 21)" << endl;

    int sum4 = query(0, 0, n - 1, 0, 0);
    cout << "Sum[0..0] = " << sum4 << " (expected: 1)" << endl;

    cout << endl;
    cout << "How it works:" << endl;
    cout << "  1. Build tree: each node stores sum of its range" << endl;
    cout << "  2. Leaf nodes store individual array values" << endl;
    cout << "  3. Internal nodes store sum of their children" << endl;
    cout << "  4. Query: combine results from overlapping nodes" << endl;
    cout << endl;
    cout << "Time: Build = O(n), Query = O(log n)" << endl;
    cout << "Space: O(n) for tree array" << endl;

    return 0;
}
