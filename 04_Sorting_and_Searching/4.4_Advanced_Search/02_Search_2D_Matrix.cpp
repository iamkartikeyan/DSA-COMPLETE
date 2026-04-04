/*
 * File: 02_Search_2D_Matrix.cpp
 * Topic: Search in a sorted 2D matrix
 * Description: Treat 2D matrix as flattened 1D sorted array
 */
#include <iostream>
using namespace std;

bool searchMatrix(int** matrix, int rows, int cols, int target) {
    int lo = 0;
    int hi = rows * cols - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        // Convert 1D index to 2D coordinates
        int row = mid / cols;
        int col = mid % cols;
        int val = matrix[row][col];

        if (val == target) {
            return true; // found
        }
        else if (val < target) {
            lo = mid + 1; // search right
        }
        else {
            hi = mid - 1; // search left
        }
    }
    return false; // not found
}

int main() {
    cout << "=== Search in 2D Sorted Matrix ===" << endl;
    cout << endl;

    /*
     * Matrix properties:
     * - Each row is sorted left to right
     * - First element of each row > last element of previous row
     * - This means ENTIRE matrix is sorted!
     *
     * Matrix:
     *  1   3   5   7
     * 10  11  16  20
     * 23  30  34  60
     *
     * Flattened: [1, 3, 5, 7, 10, 11, 16, 20, 23, 30, 34, 60]
     *
     * Key trick: 1D index -> 2D coordinates
     *   row = index / cols
     *   col = index % cols
     */

    // Create 2D matrix
    int rows = 3, cols = 4;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    // Initialize matrix
    int values[3][4] = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = values[i][j];
        }
    }

    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "  ";
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Search for 3
    int target = 3;
    cout << "Search " << target << ": " << (searchMatrix(matrix, rows, cols, target) ? "Found" : "Not Found") << endl;

    // Search for 13
    target = 13;
    cout << "Search " << target << ": " << (searchMatrix(matrix, rows, cols, target) ? "Found" : "Not Found") << endl;

    // Search for 34
    target = 34;
    cout << "Search " << target << ": " << (searchMatrix(matrix, rows, cols, target) ? "Found" : "Not Found") << endl;

    // Free memory
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Treat 2D matrix as 1D sorted array (size = rows*cols)" << endl;
    cout << "  2. Binary search on this 1D array" << endl;
    cout << "  3. Convert 1D index to 2D: row=idx/cols, col=idx%cols" << endl;
    cout << endl;
    cout << "Time: O(log(m*n)) where m=rows, n=cols" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
