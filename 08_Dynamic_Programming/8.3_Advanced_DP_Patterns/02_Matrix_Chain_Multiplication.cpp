#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

// ============================================================
// Matrix Chain Multiplication (MCM)
// Find optimal parenthesization to minimize scalar multiplications
//
// State: dp[i][j] = min multiplications for matrices i..j
// Transition: dp[i][j] = min over k from i to j-1 of:
//             dp[i][k] + dp[k+1][j] + dims[i-1]*dims[k]*dims[j]
//
// dims[] array has n+1 elements for n matrices.
// Matrix i has dimensions dims[i-1] x dims[i]
// ============================================================

// Returns minimum number of scalar multiplications
int matrixChainMultiplication(int dims[], int n) {
    // dp table
    int dp[100][100];

    // Initialize dp table
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            dp[i][j] = 0;
        }
    }

    // n matrices means chain length from 1 to n
    // dp[i][i] = 0 (single matrix, no multiplication needed)

    // Fill table for chain length L = 2 to n
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;

            // Try all split points k
            for (int k = i; k <= j - 1; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[1][n];
}

// Print optimal parenthesization
void printOptimalParens(int splitTable[][100], int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printOptimalParens(splitTable, i, splitTable[i][j]);
        printOptimalParens(splitTable, splitTable[i][j] + 1, j);
        cout << ")";
    }
}

// MCM with parenthesization tracking
int matrixChainWithParens(int dims[], int n) {
    int dp[100][100];
    int splitTable[100][100];

    // Initialize
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            dp[i][j] = 0;
            splitTable[i][j] = 0;
        }
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    splitTable[i][j] = k;
                }
            }
        }
    }

    cout << "Optimal parenthesization: ";
    printOptimalParens(splitTable, 1, n);
    cout << endl;

    return dp[1][n];
}

// ============================================================
// Main - Test all functions
// ============================================================

int main() {
    cout << "=== Matrix Chain Multiplication ===" << endl;
    cout << endl;

    // Example 1: 3 matrices of dimensions 10x30, 30x5, 5x60
    cout << "--- Example 1: 3 Matrices ---" << endl;
    cout << "Matrix dimensions: A1(10x30), A2(30x5), A3(5x60)" << endl;
    int dims1[] = {10, 30, 5, 60};
    int n1 = 3;
    int result1 = matrixChainMultiplication(dims1, n1);
    cout << "Min multiplications: " << result1 << endl;
    cout << "Expected: 4500 ((A1*A2)*A3 = 10*30*5 + 10*5*60 = 1500+3000)" << endl;
    cout << endl;

    // Example 2: 4 matrices
    cout << "--- Example 2: 4 Matrices ---" << endl;
    cout << "Matrix dimensions: A1(40x20), A2(20x30), A3(30x10), A4(10x30)" << endl;
    int dims2[] = {40, 20, 30, 10, 30};
    int n2 = 4;
    int result2 = matrixChainWithParens(dims2, n2);
    cout << "Min multiplications: " << result2 << endl;
    cout << "Expected: 26000" << endl;
    cout << endl;

    // Example 3: 5 matrices
    cout << "--- Example 3: 5 Matrices ---" << endl;
    cout << "Matrix dimensions: A1(5x4), A2(4x6), A3(6x2), A4(2x7), A5(7x3)" << endl;
    int dims3[] = {5, 4, 6, 2, 7, 3};
    int n3 = 5;
    int result3 = matrixChainWithParens(dims3, n3);
    cout << "Min multiplications: " << result3 << endl;
    cout << "Expected: 186" << endl;
    cout << endl;

    return 0;
}
