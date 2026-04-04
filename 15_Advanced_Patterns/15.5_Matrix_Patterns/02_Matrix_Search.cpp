// 15.5 - Matrix Search
// Search in a sorted 2D matrix where:
//   - Each row is sorted left to right
//   - The first element of each row is greater than the last element of the previous row
//
// This means the entire matrix can be "flattened" into a single sorted array.
//
// APPROACH 1: Binary search on flattened matrix - O(log(m*n))
// APPROACH 2: Start from top-right, move left or down - O(m+n)

#include <iostream>

using namespace std;

const int MAX_N = 20;

void printMatrix(const int matrix[][MAX_N], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j > 0) cout << " ";
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

// ============================================================
// BINARY SEARCH ON FLATTENED MATRIX - O(log(m*n))
// Treat the 2D matrix as a 1D sorted array of size m*n.
// Map 1D index to 2D coordinates: row = idx/n, col = idx%n
// ============================================================

bool searchMatrix(const int matrix[][MAX_N], int m, int n, int target) {
    int low = 0, high = m * n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int row = mid / n;
        int col = mid % n;
        int val = matrix[row][col];

        if (val == target) return true;
        else if (val < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

// ============================================================
// SEARCH IN SORTED 2D MATRIX (rows sorted, cols sorted)
// Each row sorted, each column sorted. But NOT necessarily
// the "flattened" property (first of row > last of prev row).
//
// Start from top-right corner:
//   - If target < current: move left (eliminate column)
//   - If target > current: move down (eliminate row)
//   - If target == current: found!
// Time: O(m + n)
// ============================================================

bool searchMatrix2(const int matrix[][MAX_N], int m, int n, int target) {
    // Start from top-right
    int row = 0, col = n - 1;

    while (row < m && col >= 0) {
        if (matrix[row][col] == target) return true;
        else if (matrix[row][col] > target) {
            col--;  // Move left
        } else {
            row++;  // Move down
        }
    }
    return false;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoBinarySearch() {
    cout << "=== Search in Sorted 2D Matrix (Binary Search) ===" << endl;
    int matrix[4][MAX_N] = {
        {1,  3,  5,  7},
        {10, 11, 16, 20},
        {23, 30, 34, 60},
        {65, 70, 80, 90}
    };
    int m = 4, n = 4;

    printMatrix((const int(*)[MAX_N])matrix, m, n);
    cout << endl;

    int targets[] = {3, 16, 23, 13, 65, 100};
    int numTargets = 6;

    for (int i = 0; i < numTargets; i++) {
        bool found = searchMatrix((const int(*)[MAX_N])matrix, m, n, targets[i]);
        cout << "Search " << targets[i] << ": " << (found ? "Found" : "Not found") << endl;
    }
    cout << endl;
}

void demoStaircaseSearch() {
    cout << "=== Search in Row/Column Sorted Matrix (Staircase) ===" << endl;
    int matrix[5][MAX_N] = {
        {1,  4,  7,  11, 15},
        {2,  5,  8,  12, 19},
        {3,  6,  9,  16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    int m = 5, n = 5;

    printMatrix((const int(*)[MAX_N])matrix, m, n);
    cout << endl;

    int targets[] = {5, 14, 20, 26};
    int numTargets = 4;

    for (int i = 0; i < numTargets; i++) {
        bool found = searchMatrix2((const int(*)[MAX_N])matrix, m, n, targets[i]);
        cout << "Search " << targets[i] << ": " << (found ? "Found" : "Not found") << endl;
    }
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Binary Search for target=16 ===" << endl;
    cout << "Matrix (4x4):" << endl;
    cout << "  1   3   5   7" << endl;
    cout << "  10  11  16  20" << endl;
    cout << "  23  30  34  60" << endl;
    cout << "  65  70  80  90" << endl;
    cout << endl;
    cout << "Flattened: [1,3,5,7,10,11,16,20,23,30,34,60,65,70,80,90]" << endl;
    cout << "low=0, high=15" << endl;
    cout << "  mid=7, matrix[1][3]=20 > 16 -> high=6" << endl;
    cout << "  mid=3, matrix[0][3]=7 < 16 -> low=4" << endl;
    cout << "  mid=5, matrix[1][1]=11 < 16 -> low=6" << endl;
    cout << "  mid=6, matrix[1][2]=16 == 16 -> Found!" << endl;
    cout << endl;

    cout << "=== Walkthrough: Staircase Search for target=14 ===" << endl;
    cout << "Start at top-right (row=0, col=4): value=15" << endl;
    cout << "  15 > 14 -> move left (col=3): value=11" << endl;
    cout << "  11 < 14 -> move down (row=1, col=3): value=12" << endl;
    cout << "  12 < 14 -> move down (row=2, col=3): value=16" << endl;
    cout << "  16 > 14 -> move left (row=2, col=2): value=9" << endl;
    cout << "  9 < 14 -> move down (row=3, col=2): value=14 -> Found!" << endl;
    cout << endl;
}

void demoComparison() {
    cout << "=== Approach Comparison ===" << endl;
    cout << endl;
    cout << "Binary Search (flattened):" << endl;
    cout << "  Requires: first element of each row > last element of previous row" << endl;
    cout << "  Time: O(log(m*n))" << endl;
    cout << "  Space: O(1)" << endl;
    cout << endl;
    cout << "Staircase Search (top-right):" << endl;
    cout << "  Requires: each row sorted AND each column sorted" << endl;
    cout << "  Does NOT require flattened property" << endl;
    cout << "  Time: O(m + n)" << endl;
    cout << "  Space: O(1)" << endl;
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoBinarySearch();
    demoStaircaseSearch();
    demoComparison();
    return 0;
}
