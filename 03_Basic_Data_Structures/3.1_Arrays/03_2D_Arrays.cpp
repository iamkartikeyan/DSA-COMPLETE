/*
 * File: 03_2D_Arrays.cpp
 * Topic: 2D arrays, row-major order, matrix operations
 * Description: Arrays of arrays, matrix representation
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== 2D Arrays ===" << endl;
    cout << endl;

    // --- Declaration + Initialization ---
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Matrix:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // --- Row-major traversal (C++ default) ---
    cout << "--- Row-Major Order ---" << endl;
    cout << "Elements are stored row by row in memory." << endl;
    cout << "Address formula: base + (i * cols + j) * size" << endl;
    cout << endl;

    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j] << endl;
        }
    }
    cout << endl;

    // --- Dynamic 2D Array ---
    cout << "--- Dynamic 2D Array ---" << endl;
    int rows = 3, cols = 3;

    // Allocate
    int** dynMatrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        dynMatrix[i] = new int[cols];
    }

    // Initialize
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dynMatrix[i][j] = i * cols + j + 1;
        }
    }

    // Print
    cout << "Dynamic matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << dynMatrix[i][j] << " ";
        }
        cout << endl;
    }

    // Free memory
    for (int i = 0; i < rows; i++) {
        delete[] dynMatrix[i];
    }
    delete[] dynMatrix;

    cout << endl;
    cout << "--- 3D Arrays ---" << endl;
    cout << "int arr3D[2][3][4];" << endl;
    cout << "Address: base + (i*3*4 + j*4 + k) * size" << endl;
    cout << "Think of it as: 2 matrices of size 3x4" << endl;
    cout << endl;
    cout << "Access: O(1) for any element" << endl;
    cout << "Space: O(rows * cols)" << endl;

    return 0;
}
