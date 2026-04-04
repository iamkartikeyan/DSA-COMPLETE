// 15.5 - Matrix Traversal Patterns
// Common 2D matrix traversal techniques.
// Key idea: track boundaries (top, bottom, left, right) and shrink them.
// Spiral traversal, diagonal traversal, generating spiral matrices.

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_N = 20;

// ============================================================
// PRINT MATRIX
// ============================================================

void printMatrix(const int matrix[][MAX_N], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << matrix[i][j];
        }
        cout << endl;
    }
}

// ============================================================
// SPIRAL TRAVERSAL (LeetCode 54)
// Traverse matrix in spiral order: right, down, left, up.
// Shrink boundaries after each direction.
// Time: O(m*n)
// ============================================================

void spiralOrder(const int matrix[][MAX_N], int m, int n, int result[], int &count) {
    count = 0;
    int top = 0, bottom = m - 1;
    int left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        // Traverse right (top row)
        for (int j = left; j <= right; j++) {
            result[count++] = matrix[top][j];
        }
        top++;

        // Traverse down (right column)
        for (int i = top; i <= bottom; i++) {
            result[count++] = matrix[i][right];
        }
        right--;

        // Traverse left (bottom row) - check boundary
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                result[count++] = matrix[bottom][j];
            }
            bottom--;
        }

        // Traverse up (left column) - check boundary
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                result[count++] = matrix[i][left];
            }
            left++;
        }
    }
}

// ============================================================
// GENERATE SPIRAL MATRIX (LeetCode 59)
// Fill an n x n matrix with 1..n^2 in spiral order.
// ============================================================

void generateSpiralMatrix(int matrix[][MAX_N], int n) {
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    int num = 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) matrix[top][j] = num++;
        top++;
        for (int i = top; i <= bottom; i++) matrix[i][right] = num++;
        right--;
        if (top <= bottom)
            for (int j = right; j >= left; j--) matrix[bottom][j] = num++;
        bottom--;
        if (left <= right)
            for (int i = bottom; i >= top; i--) matrix[i][left] = num++;
        left++;
    }
}

// ============================================================
// DIAGONAL TRAVERSAL (Zigzag)
// Traverse matrix diagonally, alternating up-right and down-left.
// ============================================================

int minInt(int a, int b) { return (a < b) ? a : b; }

void diagonalTraversal(const int matrix[][MAX_N], int m, int n, int result[], int &count) {
    count = 0;

    for (int d = 0; d < m + n - 1; d++) {
        bool up = (d % 2 == 0);
        int r, c;

        if (up) {
            r = minInt(d, m - 1);
            c = d - r;
        } else {
            c = minInt(d, n - 1);
            r = d - c;
        }

        while ((up && r >= 0 && c < n) || (!up && c >= 0 && r < m)) {
            result[count++] = matrix[r][c];
            if (up) { r--; c++; }
            else { r++; c--; }
        }
    }
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoSpiralTraversal() {
    cout << "=== Spiral Traversal ===" << endl;
    int matrix[3][MAX_N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    printMatrix((const int(*)[MAX_N])matrix, 3, 3);

    int result[100];
    int count = 0;
    spiralOrder((const int(*)[MAX_N])matrix, 3, 3, result, count);

    cout << "Spiral: ";
    for (int i = 0; i < count; i++) cout << result[i] << " ";
    cout << endl;  // 1 2 3 6 9 8 7 4 5
    cout << endl;
}

void demoGenerateSpiral() {
    cout << "=== Generate Spiral Matrix ===" << endl;
    int matrix[MAX_N][MAX_N];
    int n = 4;

    cout << "n = " << n << endl;
    generateSpiralMatrix((int(*)[MAX_N])matrix, n);
    printMatrix((const int(*)[MAX_N])matrix, n, n);
    cout << endl;
}

void demoDiagonalTraversal() {
    cout << "=== Diagonal Traversal ===" << endl;
    int matrix[3][MAX_N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    printMatrix((const int(*)[MAX_N])matrix, 3, 3);

    int result[100];
    int count = 0;
    diagonalTraversal((const int(*)[MAX_N])matrix, 3, 3, result, count);

    cout << "Diagonal: ";
    for (int i = 0; i < count; i++) cout << result[i] << " ";
    cout << endl;  // 1 2 4 7 5 3 6 8 9
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Spiral for 3x3 ===" << endl;
    cout << "Matrix:" << endl;
    cout << "  1  2  3" << endl;
    cout << "  4  5  6" << endl;
    cout << "  7  8  9" << endl;
    cout << endl;
    cout << "top=0, bottom=2, left=0, right=2" << endl;
    cout << "  Right:  [0][0..2] = 1 2 3, top=1" << endl;
    cout << "  Down:   [1..2][2] = 6 9, right=1" << endl;
    cout << "  Left:   [2][1..0] = 8 7, bottom=1" << endl;
    cout << "  Up:     [1..1][0] = 4, left=1" << endl;
    cout << "top=1, bottom=1, left=1, right=1" << endl;
    cout << "  Right:  [1][1..1] = 5, top=2" << endl;
    cout << "top > bottom, done." << endl;
    cout << "Result: 1 2 3 6 9 8 7 4 5" << endl;
    cout << endl;
}

void demoRectangularMatrix() {
    cout << "=== Spiral on Rectangular Matrix (3x4) ===" << endl;
    int matrix[3][MAX_N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    printMatrix((const int(*)[MAX_N])matrix, 3, 4);

    int result[100];
    int count = 0;
    spiralOrder((const int(*)[MAX_N])matrix, 3, 4, result, count);

    cout << "Spiral: ";
    for (int i = 0; i < count; i++) cout << result[i] << " ";
    cout << endl;  // 1 2 3 4 8 12 11 10 9 5 6 7
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoSpiralTraversal();
    demoGenerateSpiral();
    demoDiagonalTraversal();
    demoRectangularMatrix();
    return 0;
}
