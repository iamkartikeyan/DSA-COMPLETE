// 2D Prefix Sum Matrix (Summed Area Table)
// Extends prefix sum to 2D matrices for O(1) submatrix sum queries.
//
// Build formula (inclusion-exclusion):
//   prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]
//
// Query formula (inclusion-exclusion):
//   sum(r1,c1,r2,c2) = prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1]
//
// Time Complexity:
//   Build:  O(m * n)
//   Query:  O(1) per submatrix sum
//   Space:  O(m * n)

#include <iostream>
#include <iomanip>
using namespace std;

const int MAXM = 100;
const int MAXN = 100;
const int MAXP = MAXN + 1;  // prefix array needs +1 dimension

// Build 2D prefix sum matrix
// prefix[i][j] = sum of submatrix matrix[0..i-1][0..j-1]
void buildPrefix2D(const int matrix[][MAXN], int m, int n, int prefix[][MAXP]) {
    // Initialize border with zeros
    for (int i = 0; i <= m; i++) {
        prefix[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        prefix[0][j] = 0;
    }

    // Fill using inclusion-exclusion
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] = matrix[i - 1][j - 1]
                         + prefix[i - 1][j]
                         + prefix[i][j - 1]
                         - prefix[i - 1][j - 1];
        }
    }
}

// Range sum: sum of submatrix from (r1,c1) to (r2,c2) inclusive
int rangeSum2D(const int prefix[][MAXP], int r1, int c1, int r2, int c2) {
    return prefix[r2 + 1][c2 + 1]
         - prefix[r1][c2 + 1]
         - prefix[r2 + 1][c1]
         + prefix[r1][c1];
}

// Print a matrix with fixed second dimension
void printMatrix(const int mat[][MAXN], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << mat[i][j];
        }
        cout << endl;
    }
}

// Print prefix matrix (with +1 dimension)
void printPrefixMatrix(const int mat[][MAXP], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << mat[i][j];
        }
        cout << endl;
    }
}

int main() {
    cout << "=== 2D Prefix Sum Matrix ===" << endl;
    cout << endl;

    // 3x3 example matrix
    int m = 3, n = 3;
    int matrix[MAXM][MAXN] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int prefix[MAXM + 1][MAXN + 1];

    cout << "Matrix:" << endl;
    printMatrix(matrix, m, n);
    cout << endl;

    buildPrefix2D(matrix, m, n, prefix);

    cout << "Prefix Sum Matrix (size " << m + 1 << "x" << n + 1 << "):" << endl;
    printPrefixMatrix(prefix, m + 1, n + 1);
    cout << endl;

    // Explain inclusion-exclusion visually
    cout << "Inclusion-Exclusion for submatrix (1,1) to (2,2):" << endl;
    cout << "  = prefix[3][3] - prefix[1][3] - prefix[3][1] + prefix[1][1]" << endl;
    cout << "  = " << prefix[3][3] << " - " << prefix[1][3] << " - " << prefix[3][1] << " + " << prefix[1][1] << endl;
    cout << "  = " << rangeSum2D(prefix, 1, 1, 2, 2) << endl;
    cout << "  (Expected: 5 + 6 + 8 + 9 = 28)" << endl;
    cout << endl;

    // Multiple submatrix queries
    cout << "Submatrix Sum Queries:" << endl;

    // Query 1: entire matrix (0,0) to (2,2)
    int r1 = 0, c1 = 0, r2 = 2, c2 = 2;
    cout << "  Sum entire matrix (" << r1 << "," << c1 << ") to (" << r2 << "," << c2 << ") = ";
    cout << rangeSum2D(prefix, r1, c1, r2, c2) << endl;

    // Query 2: top row (0,0) to (0,2)
    r1 = 0; c1 = 0; r2 = 0; c2 = 2;
    cout << "  Sum top row (" << r1 << "," << c1 << ") to (" << r2 << "," << c2 << ") = ";
    cout << rangeSum2D(prefix, r1, c1, r2, c2) << endl;

    // Query 3: single cell (1,1) to (1,1)
    r1 = 1; c1 = 1; r2 = 1; c2 = 1;
    cout << "  Sum single cell (" << r1 << "," << c1 << ") to (" << r2 << "," << c2 << ") = ";
    cout << rangeSum2D(prefix, r1, c1, r2, c2) << endl;

    // Query 4: bottom-right 2x2 (1,1) to (2,2)
    r1 = 1; c1 = 1; r2 = 2; c2 = 2;
    cout << "  Sum bottom-right 2x2 (" << r1 << "," << c1 << ") to (" << r2 << "," << c2 << ") = ";
    cout << rangeSum2D(prefix, r1, c1, r2, c2) << endl;

    cout << endl;
    cout << "All submatrix queries answered in O(1) after O(m*n) preprocessing." << endl;

    return 0;
}
