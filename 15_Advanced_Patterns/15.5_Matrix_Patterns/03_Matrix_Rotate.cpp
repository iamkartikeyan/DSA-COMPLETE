// 15.5 - Matrix Rotate
// Rotate an n x n matrix 90 degrees clockwise, in-place.
//
// TWO-STEP APPROACH (most intuitive):
//   Step 1: Transpose the matrix (swap matrix[i][j] with matrix[j][i])
//   Step 2: Reverse each row
//
// This achieves 90-degree clockwise rotation.
//
// For 90-degree counter-clockwise:
//   Step 1: Reverse each row
//   Step 2: Transpose
//
// Time: O(n^2), Space: O(1) - truly in-place.

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_N = 20;

void printMatrix(const int matrix[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << matrix[i][j];
        }
        cout << endl;
    }
}

void copyMatrix(int dest[][MAX_N], const int src[][MAX_N], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dest[i][j] = src[i][j];
}

// ============================================================
// ROTATE 90 DEGREES CLOCKWISE
// Transpose + Reverse each row
// ============================================================

void rotateClockwise(int matrix[][MAX_N], int n) {
    // Step 1: Transpose
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }

    // Step 2: Reverse each row
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n / 2; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][n - 1 - j];
            matrix[i][n - 1 - j] = temp;
        }
}

// ============================================================
// ROTATE 90 DEGREES COUNTER-CLOCKWISE
// Reverse each row + Transpose
// ============================================================

void rotateCounterClockwise(int matrix[][MAX_N], int n) {
    // Step 1: Reverse each row
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n / 2; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][n - 1 - j];
            matrix[i][n - 1 - j] = temp;
        }

    // Step 2: Transpose
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
}

// ============================================================
// ROTATE 180 DEGREES
// Can be done by rotating 90 degrees twice, or:
// Reverse each row, then reverse each column.
// ============================================================

void rotate180(int matrix[][MAX_N], int n) {
    // Reverse each row
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n / 2; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][n - 1 - j];
            matrix[i][n - 1 - j] = temp;
        }

    // Reverse each column
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n / 2; i++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[n - 1 - i][j];
            matrix[n - 1 - i][j] = temp;
        }
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoClockwise() {
    cout << "=== Rotate 90 Degrees Clockwise ===" << endl;
    int original[3][MAX_N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int matrix[MAX_N][MAX_N];
    copyMatrix((int(*)[MAX_N])matrix, (const int(*)[MAX_N])original, 3);

    cout << "Original:" << endl;
    printMatrix((const int(*)[MAX_N])original, 3);
    cout << endl;

    rotateClockwise((int(*)[MAX_N])matrix, 3);

    cout << "Rotated 90 CW:" << endl;
    printMatrix((const int(*)[MAX_N])matrix, 3);
    cout << "Expected:" << endl;
    cout << "  7  4  1" << endl;
    cout << "  8  5  2" << endl;
    cout << "  9  6  3" << endl;
    cout << endl;
}

void demoCounterClockwise() {
    cout << "=== Rotate 90 Degrees Counter-Clockwise ===" << endl;
    int original[3][MAX_N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int matrix[MAX_N][MAX_N];
    copyMatrix((int(*)[MAX_N])matrix, (const int(*)[MAX_N])original, 3);

    cout << "Original:" << endl;
    printMatrix((const int(*)[MAX_N])original, 3);
    cout << endl;

    rotateCounterClockwise((int(*)[MAX_N])matrix, 3);

    cout << "Rotated 90 CCW:" << endl;
    printMatrix((const int(*)[MAX_N])matrix, 3);
    cout << "Expected:" << endl;
    cout << "  3  6  9" << endl;
    cout << "  2  5  8" << endl;
    cout << "  1  4  7" << endl;
    cout << endl;
}

void demo180() {
    cout << "=== Rotate 180 Degrees ===" << endl;
    int original[3][MAX_N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int matrix[MAX_N][MAX_N];
    copyMatrix((int(*)[MAX_N])matrix, (const int(*)[MAX_N])original, 3);

    cout << "Original:" << endl;
    printMatrix((const int(*)[MAX_N])original, 3);
    cout << endl;

    rotate180((int(*)[MAX_N])matrix, 3);

    cout << "Rotated 180:" << endl;
    printMatrix((const int(*)[MAX_N])matrix, 3);
    cout << "Expected:" << endl;
    cout << "  9  8  7" << endl;
    cout << "  6  5  4" << endl;
    cout << "  3  2  1" << endl;
    cout << endl;
}

void demo4x4() {
    cout << "=== Rotate 4x4 Clockwise ===" << endl;
    int original[4][MAX_N] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9,  10, 11, 12},
        {13, 14, 15, 16}
    };
    int matrix[MAX_N][MAX_N];
    copyMatrix((int(*)[MAX_N])matrix, (const int(*)[MAX_N])original, 4);

    cout << "Original:" << endl;
    printMatrix((const int(*)[MAX_N])original, 4);
    cout << endl;

    rotateClockwise((int(*)[MAX_N])matrix, 4);

    cout << "Rotated 90 CW:" << endl;
    printMatrix((const int(*)[MAX_N])matrix, 4);
    cout << "Expected:" << endl;
    cout << " 13  9  5  1" << endl;
    cout << " 14 10  6  2" << endl;
    cout << " 15 11  7  3" << endl;
    cout << " 16 12  8  4" << endl;
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Rotate 90 CW for 3x3 ===" << endl;
    cout << "Original:" << endl;
    cout << "  1  2  3" << endl;
    cout << "  4  5  6" << endl;
    cout << "  7  8  9" << endl;
    cout << endl;
    cout << "Step 1: Transpose (swap [i][j] with [j][i])" << endl;
    cout << "  1  4  7" << endl;
    cout << "  2  5  8" << endl;
    cout << "  3  6  9" << endl;
    cout << endl;
    cout << "Step 2: Reverse each row" << endl;
    cout << "  7  4  1" << endl;
    cout << "  8  5  2" << endl;
    cout << "  9  6  3" << endl;
    cout << endl;
    cout << "This is the 90-degree clockwise rotation!" << endl;
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoClockwise();
    demoCounterClockwise();
    demo180();
    demo4x4();
    return 0;
}
