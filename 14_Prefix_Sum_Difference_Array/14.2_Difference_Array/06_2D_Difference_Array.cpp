// 2D Difference Array
// Supports O(1) range updates on 2D submatrices.
// After all updates, reconstruct the final matrix in O(m*n).
//
// 2D Range Update: Add val to submatrix [r1..r2][c1..c2]
//   4-corner update rule:
//     diff[r1][c1]       += val
//     diff[r2+1][c1]     -= val
//     diff[r1][c2+1]     -= val
//     diff[r2+1][c2+1]   += val
//
// Reconstruct: 2D prefix sum
//   1. Row-wise prefix sum
//   2. Column-wise prefix sum
//
// Why 4 corners? In 2D, adding val at (r1,c1) affects everything
// below and to the right. We need 4 corrections to limit the effect
// to exactly the rectangle [r1..r2][c1..c2].
//
// Time Complexity:
//   Update:    O(1) per submatrix
//   Reconstruct: O(m * n)
//   Total:     O(m*n + numUpdates)

#include <iostream>
#include <iomanip>
using namespace std;

const int MAXM = 20;
const int MAXN = 20;

// 2D range update: add val to submatrix [r1..r2][c1..c2]
void rangeUpdate2D(int diff[][MAXN], int m, int n, int r1, int c1, int r2, int c2, int val) {
    diff[r1][c1] += val;
    if (r2 + 1 < m) diff[r2 + 1][c1] -= val;
    if (c2 + 1 < n) diff[r1][c2 + 1] -= val;
    if (r2 + 1 < m && c2 + 1 < n) diff[r2 + 1][c2 + 1] += val;
}

// Reconstruct 2D array: row-wise then column-wise prefix sum
void reconstruct2D(const int diff[][MAXN], int m, int n, int result[][MAXN]) {
    // Copy diff to result
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = diff[i][j];
        }
    }

    // Row-wise prefix sum
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            result[i][j] += result[i][j - 1];
        }
    }

    // Column-wise prefix sum
    for (int j = 0; j < n; j++) {
        for (int i = 1; i < m; i++) {
            result[i][j] += result[i - 1][j];
        }
    }
}

// Print matrix
void printMatrix(const int mat[][MAXN], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << mat[i][j];
        }
        cout << endl;
    }
}

int main() {
    cout << "=== 2D Difference Array ===" << endl;
    cout << endl;

    int m = 4, n = 4;
    int diff[MAXM][MAXN];
    int result[MAXM][MAXN];

    // Initialize with zeros
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            diff[i][j] = 0;
        }
    }

    cout << "Initial 4x4 matrix (all zeros):" << endl;
    printMatrix(diff, m, n);
    cout << endl;

    // Update 1: Add 5 to submatrix [0,0] to [1,1] (top-left 2x2)
    int r1 = 0, c1 = 0, r2 = 1, c2 = 1, val = 5;
    cout << "Update 1: Add " << val << " to submatrix (" << r1 << "," << c1 << ") to (" << r2 << "," << c2 << ")" << endl;
    rangeUpdate2D(diff, m, n, r1, c1, r2, c2, val);

    cout << "  4-corner changes on diff:" << endl;
    cout << "    diff[" << r1 << "][" << c1 << "] += " << val << endl;
    cout << "    diff[" << r2 + 1 << "][" << c1 << "] -= " << val << endl;
    cout << "    diff[" << r1 << "][" << c2 + 1 << "] -= " << val << endl;
    cout << "    diff[" << r2 + 1 << "][" << c2 + 1 << "] += " << val << endl;
    cout << endl;

    // Update 2: Add 3 to submatrix [1,1] to [3,3] (bottom-right 3x3)
    r1 = 1; c1 = 1; r2 = 3; c2 = 3; val = 3;
    cout << "Update 2: Add " << val << " to submatrix (" << r1 << "," << c1 << ") to (" << r2 << "," << c2 << ")" << endl;
    rangeUpdate2D(diff, m, n, r1, c1, r2, c2, val);
    cout << endl;

    // Show diff array after updates
    cout << "Difference array after both updates:" << endl;
    printMatrix(diff, m, n);
    cout << endl;

    // Reconstruct
    reconstruct2D(diff, m, n, result);
    cout << "Final matrix (after 2D prefix sum reconstruction):" << endl;
    printMatrix(result, m, n);
    cout << endl;

    // Verification
    cout << "Manual verification:" << endl;
    cout << "  Cell (0,0): only in update 1 -> 5" << endl;
    cout << "  Cell (0,1): only in update 1 -> 5" << endl;
    cout << "  Cell (1,1): in both updates -> 5 + 3 = 8" << endl;
    cout << "  Cell (1,2): only in update 2 -> 3" << endl;
    cout << "  Cell (2,2): only in update 2 -> 3" << endl;
    cout << "  Cell (3,3): only in update 2 -> 3" << endl;

    cout << endl;
    cout << "4-Corner Update Explained:" << endl;
    cout << "  diff[r1][c1]     += val  -> starts val effect at top-left" << endl;
    cout << "  diff[r2+1][c1]   -= val  -> cancels val below the rectangle" << endl;
    cout << "  diff[r1][c2+1]   -= val  -> cancels val right of rectangle" << endl;
    cout << "  diff[r2+1][c2+1] += val  -> double-cancel correction" << endl;
    cout << "  After 2D prefix sum, only cells in [r1..r2][c1..c2] get +val" << endl;

    return 0;
}
