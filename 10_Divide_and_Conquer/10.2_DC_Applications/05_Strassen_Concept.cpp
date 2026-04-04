// ============================================================
// 05_Strassen_Concept.cpp
// Strassen's Matrix Multiplication Concept
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// MATRIX MULTIPLICATION
//
// Given two n x n matrices A and B, compute C = A * B
//
// Naive approach: O(n^3)
// Strassen's: O(n^2.81)
//
// The key idea of Strassen's algorithm:
//   - Divide each matrix into 4 sub-matrices of size n/2 x n/2
//   - Naive method needs 8 multiplications of sub-matrices
//   - Strassen found a way to do it with only 7 multiplications
//   - This reduces the recurrence from T(n) = 8*T(n/2) + O(n^2)
//     to T(n) = 7*T(n/2) + O(n^2)
//   - Result: O(n^2.81) instead of O(n^3)
// ============================================================

#define MAX 4

// -----------------------------------------------------------
// Naive Matrix Multiplication: O(n^3)
// -----------------------------------------------------------

void naiveMultiply(int A[][MAX], int B[][MAX], int C[][MAX], int n)
{
    for (int i = 0; i < n; i = i + 1)
    {
        for (int j = 0; j < n; j = j + 1)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k = k + 1)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

// -----------------------------------------------------------
// Print a matrix
// -----------------------------------------------------------

void printMatrix(int mat[][MAX], int n)
{
    for (int i = 0; i < n; i = i + 1)
    {
        for (int j = 0; j < n; j = j + 1)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

// ============================================================
// STRASSEN'S ALGORITHM - CONCEPTUAL EXPLANATION
// ============================================================
//
// Step 1: Divide each matrix into 4 quadrants
//
//   A = | A11  A12 |    B = | B11  B12 |
//       | A21  A22 |        | B21  B22 |
//
// Each quadrant is n/2 x n/2.
//
// Step 2: Naive method would compute:
//
//   C11 = A11*B11 + A12*B21    (2 multiplications)
//   C12 = A11*B12 + A12*B22    (2 multiplications)
//   C21 = A21*B11 + A22*B21    (2 multiplications)
//   C22 = A21*B12 + A22*B22    (2 multiplications)
//
//   Total: 8 multiplications of n/2 x n/2 matrices
//
//   Recurrence: T(n) = 8*T(n/2) + O(n^2)
//   By Master Theorem: T(n) = O(n^3)  -- same as naive!
//
// Step 3: Strassen's clever insight
//
//   Compute these 7 products instead:
//
//   M1 = (A11 + A22) * (B11 + B22)
//   M2 = (A21 + A22) * B11
//   M3 = A11 * (B12 - B22)
//   M4 = A22 * (B21 - B11)
//   M5 = (A11 + A12) * B22
//   M6 = (A21 - A11) * (B11 + B12)
//   M7 = (A12 - A22) * (B21 + B22)
//
//   Then combine:
//
//   C11 = M1 + M4 - M5 + M7
//   C12 = M3 + M5
//   C21 = M2 + M4
//   C22 = M1 - M2 + M3 + M6
//
//   Total: 7 multiplications + 18 matrix additions
//
//   Recurrence: T(n) = 7*T(n/2) + O(n^2)
//   By Master Theorem:
//     a = 7, b = 2, d = 2
//     b^d = 2^2 = 4
//     a > b^d (7 > 4)  =>  Case 1
//     T(n) = O(n^(log_2(7))) = O(n^2.81)
//
// ============================================================

// -----------------------------------------------------------
// Explain the recurrence comparison
// -----------------------------------------------------------

void explainRecurrences()
{
    cout << "--- Naive Multiplication ---" << endl;
    cout << "8 sub-matrix multiplications per level" << endl;
    cout << "T(n) = 8 * T(n/2) + O(n^2)" << endl;
    cout << "  a = 8, b = 2, d = 2" << endl;
    cout << "  b^d = 2^2 = 4" << endl;
    cout << "  a > b^d (8 > 4)  =>  Case 1" << endl;
    cout << "  log_2(8) = 3" << endl;
    cout << "  T(n) = O(n^3)" << endl;
    cout << endl;

    cout << "--- Strassen's Multiplication ---" << endl;
    cout << "7 sub-matrix multiplications per level" << endl;
    cout << "T(n) = 7 * T(n/2) + O(n^2)" << endl;
    cout << "  a = 7, b = 2, d = 2" << endl;
    cout << "  b^d = 2^2 = 4" << endl;
    cout << "  a > b^d (7 > 4)  =>  Case 1" << endl;
    cout << "  log_2(7) approx 2.81" << endl;
    cout << "  T(n) = O(n^2.81)" << endl;
    cout << endl;
}

// ============================================================

int main()
{
    cout << "============================================" << endl;
    cout << "  Strassen's Matrix Multiplication" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- Naive multiplication demo ---
    cout << "--- Naive Matrix Multiplication Demo ---" << endl;
    cout << endl;

    int A[MAX][MAX] = {
        {1, 2},
        {3, 4}
    };
    int B[MAX][MAX] = {
        {5, 6},
        {7, 8}
    };
    int C[MAX][MAX];
    int n = 2;

    cout << "Matrix A:" << endl;
    printMatrix(A, n);
    cout << endl;

    cout << "Matrix B:" << endl;
    printMatrix(B, n);
    cout << endl;

    naiveMultiply(A, B, C, n);

    cout << "A * B = C:" << endl;
    printMatrix(C, n);
    cout << endl;

    // --- Verify manually ---
    cout << "Manual verification:" << endl;
    cout << "  C[0][0] = 1*5 + 2*7 = 5 + 14 = 19" << endl;
    cout << "  C[0][1] = 1*6 + 2*8 = 6 + 16 = 22" << endl;
    cout << "  C[1][0] = 3*5 + 4*7 = 15 + 28 = 43" << endl;
    cout << "  C[1][1] = 3*6 + 4*8 = 18 + 32 = 50" << endl;
    cout << endl;

    // --- 3x3 example ---
    int A2[MAX][MAX] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 1, 1}
    };
    int B2[MAX][MAX] = {
        {1, 1, 0},
        {0, 1, 1},
        {1, 0, 1}
    };
    int C2[MAX][MAX];
    int n2 = 3;

    cout << "--- 3x3 Example ---" << endl;
    cout << "Matrix A:" << endl;
    printMatrix(A2, n2);
    cout << endl;

    cout << "Matrix B:" << endl;
    printMatrix(B2, n2);
    cout << endl;

    naiveMultiply(A2, B2, C2, n2);

    cout << "A * B = C:" << endl;
    printMatrix(C2, n2);
    cout << endl;

    // --- Recurrence explanation ---
    explainRecurrences();

    // --- Strassen's 7 multiplications ---
    cout << "============================================" << endl;
    cout << "  Strassen's 7 Multiplications (M1-M7)" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Instead of 8 multiplications, Strassen uses 7:" << endl;
    cout << endl;
    cout << "M1 = (A11 + A22)(B11 + B22)" << endl;
    cout << "M2 = (A21 + A22)(B11)" << endl;
    cout << "M3 = (A11)(B12 - B22)" << endl;
    cout << "M4 = (A22)(B21 - B11)" << endl;
    cout << "M5 = (A11 + A12)(B22)" << endl;
    cout << "M6 = (A21 - A11)(B11 + B12)" << endl;
    cout << "M7 = (A12 - A22)(B21 + B22)" << endl;
    cout << endl;
    cout << "C11 = M1 + M4 - M5 + M7" << endl;
    cout << "C12 = M3 + M5" << endl;
    cout << "C21 = M2 + M4" << endl;
    cout << "C22 = M1 - M2 + M3 + M6" << endl;
    cout << endl;

    // --- Complexity comparison ---
    cout << "============================================" << endl;
    cout << "  Complexity Comparison" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Algorithm  | Time       | For n=1024 (relative)" << endl;
    cout << "-----------|------------|----------------------" << endl;
    cout << "Naive      | O(n^3)     | 1073741824 ops" << endl;
    cout << "Strassen's | O(n^2.81)  | 290149764 ops" << endl;
    cout << endl;
    cout << "Strassen's saves about 73% fewer operations!" << endl;
    cout << endl;

    // --- Why not always use Strassen's? ---
    cout << "============================================" << endl;
    cout << "  Why Not Always Use Strassen's?" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "1. High constant factor: Strassen has more" << endl;
    cout << "   additions and subtractions" << endl;
    cout << endl;
    cout << "2. Numerical stability: Strassen can have worse" << endl;
    cout << "   rounding errors for floating-point matrices" << endl;
    cout << endl;
    cout << "3. Space overhead: Need extra matrices for" << endl;
    cout << "   the intermediate calculations" << endl;
    cout << endl;
    cout << "4. Only better for large n: For small matrices," << endl;
    cout << "   naive is actually faster" << endl;
    cout << endl;
    cout << "5. Complex implementation: Much harder to code" << endl;
    cout << "   correctly" << endl;
    cout << endl;
    cout << "In practice: use naive for small matrices" << endl;
    cout << "and switch to Strassen for large ones." << endl;

    return 0;
}
