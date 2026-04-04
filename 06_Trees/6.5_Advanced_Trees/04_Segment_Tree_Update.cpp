/*
 * File: 04_Segment_Tree_Update.cpp
 * Topic: Segment Tree - Point Update + Range Sum
 * Description: Update a value and re-query
 */
#include <iostream>
#include <vector>
using namespace std;

vector<int> tree;

// Build segment tree
void build(vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(arr, 2 * node + 1, start, mid);
    build(arr, 2 * node + 2, mid + 1, end);
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

// Range sum query
int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    return query(2 * node + 1, start, mid, l, r) +
           query(2 * node + 2, mid + 1, end, l, r);
}

// Point update: change arr[idx] to val
void update(int node, int start, int end, int idx, int val) {
    // Leaf node - update value
    if (start == end) {
        tree[node] = val;
        return;
    }

    int mid = (start + end) / 2;
    // Go left or right depending on where idx falls
    if (idx <= mid) {
        update(2 * node + 1, start, mid, idx, val);
    } else {
        update(2 * node + 2, mid + 1, end, idx, val);
    }

    // Update this node after child changed
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

int main() {
    cout << "=== Segment Tree - Point Update ===" << endl;
    cout << endl;

    vector<int> arr;
    arr.push_back(1);
    arr.push_back(3);
    arr.push_back(5);
    arr.push_back(7);
    arr.push_back(9);
    arr.push_back(11);

    int n = arr.size();

    cout << "Original array: 1 3 5 7 9 11" << endl;
    cout << endl;

    // Build tree
    tree.assign(4 * n, 0);
    build(arr, 0, 0, n - 1);

    // Query before update
    int sumBefore = query(0, 0, n - 1, 0, 5);
    cout << "Sum[0..5] before update = " << sumBefore << " (expected: 36)" << endl;

    // Update: change arr[2] from 5 to 10
    cout << endl;
    cout << "Update: arr[2] = 5 -> 10" << endl;
    update(0, 0, n - 1, 2, 10);

    // Query after update
    int sumAfter = query(0, 0, n - 1, 0, 5);
    cout << "Sum[0..5] after update  = " << sumAfter << " (expected: 41)" << endl;

    int sumPartial = query(0, 0, n - 1, 1, 3);
    cout << "Sum[1..3] after update  = " << sumPartial << " (expected: 3+10+7 = 20)" << endl;

    cout << endl;
    cout << "How update works:" << endl;
    cout << "  1. Find the leaf node for the index" << endl;
    cout << "  2. Update the leaf value" << endl;
    cout << "  3. On the way back up, update all parent nodes" << endl;
    cout << "  4. Only O(log n) nodes need to be updated" << endl;
    cout << endl;
    cout << "Time: Update = O(log n), Query = O(log n)" << endl;

    return 0;
}
