// 14.1 Prefix Sum - 1D, 2D, and Range Sum Queries in O(1)
// Prefix sum precomputes cumulative sums to answer range queries instantly.
// Formula: prefix[i] = prefix[i-1] + arr[i-1]; sum[l..r] = prefix[r+1] - prefix[l]

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ============================================================
// 1D PREFIX SUM ARRAY
// Build: O(n), Query: O(1)
// ============================================================

// Build 1D prefix sum array
vector<int> buildPrefix1D(const vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n + 1, 0);  // prefix[0] = 0
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];
    return prefix;
}

// Range sum query: sum of arr[l..r] inclusive
int rangeSum1D(const vector<int>& prefix, int l, int r) {
    return prefix[r + 1] - prefix[l];
}

void demo1DPrefixSum() {
    cout << "=== 1D Prefix Sum ===" << endl;
    vector<int> arr = {2, 4, 1, 3, 5, 2, 7};
    vector<int> prefix = buildPrefix1D(arr);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Query: sum from index 1 to 4 => 4+1+3+5 = 13
    cout << "Sum arr[1..4] = " << rangeSum1D(prefix, 1, 4) << endl;
    cout << "Sum arr[0..6] = " << rangeSum1D(prefix, 0, 6) << endl;
    cout << "Sum arr[3..3] = " << rangeSum1D(prefix, 3, 3) << endl;
    cout << endl;
}

// ============================================================
// 2D PREFIX SUM MATRIX (Summed Area Table)
// Build: O(m*n), Query: O(1)
// ============================================================

// Build 2D prefix sum: prefix[i][j] = sum of submatrix [0..i-1][0..j-1]
vector<vector<int>> buildPrefix2D(const vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            // Include cell + top + left - overlap (inclusion-exclusion)
            prefix[i][j] = matrix[i-1][j-1]
                         + prefix[i-1][j] + prefix[i][j-1]
                         - prefix[i-1][j-1];
    return prefix;
}

// Range sum: sum of submatrix from (r1,c1) to (r2,c2) inclusive
int rangeSum2D(const vector<vector<int>>& prefix, int r1, int c1, int r2, int c2) {
    // Inclusion-exclusion principle
    return prefix[r2+1][c2+1]
         - prefix[r1][c2+1] - prefix[r2+1][c1]
         + prefix[r1][c1];
}

void demo2DPrefixSum() {
    cout << "=== 2D Prefix Sum Matrix ===" << endl;
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Matrix:" << endl;
    for (auto& row : matrix) {
        for (int x : row) cout << setw(3) << x;
        cout << endl;
    }

    auto prefix = buildPrefix2D(matrix);

    // Query: sum of submatrix from (1,1) to (2,2) => 5+6+8+9 = 28
    cout << "\nSum submatrix (1,1) to (2,2) = " << rangeSum2D(prefix, 1, 1, 2, 2) << endl;
    cout << "Sum entire matrix = " << rangeSum2D(prefix, 0, 0, 2, 2) << endl;
    cout << "Sum submatrix (0,0) to (0,2) = " << rangeSum2D(prefix, 0, 0, 0, 2) << endl;
    cout << endl;
}

// ============================================================
// APPLICATION: Subarray Sum Equals K
// Uses hash map + prefix sum to count subarrays with sum = k
// ============================================================

int countSubarraysWithSum(const vector<int>& arr, int k) {
    unordered_map<int, int> count;
    count[0] = 1;  // Empty prefix sum = 0
    int prefixSum = 0, result = 0;
    for (int x : arr) {
        prefixSum += x;
        if (count.count(prefixSum - k))
            result += count[prefixSum - k];
        count[prefixSum]++;
    }
    return result;
}

void demoSubarraySumK() {
    cout << "=== Application: Subarray Sum Equals K ===" << endl;
    vector<int> arr = {1, 2, 3, -1, 2, 1};
    int k = 5;
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nSubarrays with sum = " << k << " : " << countSubarraysWithSum(arr, k) << endl;
    // [2,3], [3,-1,2,1], [1,2,3,-1] => 3 subarrays
    cout << endl;
}

// ============================================================
// APPLICATION: Range Sum Query Mutable (Fenwick / BIT)
// Simplified Fenwick Tree for point update + range sum in O(log n)
// ============================================================

class FenwickTree {
    int n;
    vector<int> bit;
public:
    FenwickTree(const vector<int>& arr) : n(arr.size()), bit(n + 1, 0) {
        for (int i = 0; i < n; i++) update(i + 1, arr[i]);
    }
    // Add delta to index i (1-based)
    void update(int i, int delta) {
        for (; i <= n; i += i & (-i)) bit[i] += delta;
    }
    // Prefix sum from 1 to i (1-based)
    int query(int i) {
        int s = 0;
        for (; i > 0; i -= i & (-i)) s += bit[i];
        return s;
    }
    // Range sum l..r (1-based)
    int rangeSum(int l, int r) { return query(r) - query(l - 1); }
};

void demoFenwickTree() {
    cout << "=== Fenwick Tree (Binary Indexed Tree) ===" << endl;
    vector<int> arr = {1, 3, 5, 7, 9};
    FenwickTree ft(arr);
    cout << "Array: 1 3 5 7 9" << endl;
    cout << "Sum [1..3] = " << ft.rangeSum(1, 3) << endl;   // 3+5+7 = 15
    cout << "Sum [2..5] = " << ft.rangeSum(2, 5) << endl;   // 5+7+9 = 21
    ft.update(3, 10);  // Add 10 to index 3 => arr becomes {1,3,15,7,9}
    cout << "After adding 10 to index 3, Sum [1..3] = " << ft.rangeSum(1, 3) << endl;
    cout << endl;
}

int main() {
    demo1DPrefixSum();
    demo2DPrefixSum();
    demoSubarraySumK();
    demoFenwickTree();
    return 0;
}
