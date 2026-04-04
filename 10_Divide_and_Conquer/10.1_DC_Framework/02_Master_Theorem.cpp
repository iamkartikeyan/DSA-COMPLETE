// ============================================================
// 02_Master_Theorem.cpp
// Master Theorem for Solving Divide & Conquer Recurrences
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// MASTER THEOREM
// ============================================================
//
// For recurrences of the form:
//   T(n) = a * T(n / b) + O(n^d)
//
//   where:
//     a >= 1  (number of sub-problems)
//     b > 1   (factor by which problem size shrinks)
//     d >= 0  (cost of divide + combine)
//
// Compare a with b^d to determine which case applies:
//
// Case 1: a > b^d
//   The recursive work dominates.
//   T(n) = O(n^(log_b(a)))
//
// Case 2: a == b^d
//   The work is evenly spread across levels.
//   T(n) = O(n^d * log(n))
//
// Case 3: a < b^d
//   The root-level work dominates.
//   T(n) = O(n^d)
//
// ============================================================

// -----------------------------------------------------------
// Helper: log base b of a (integer approximation)
// -----------------------------------------------------------
// This is for demonstration purposes only.
// In practice, we compute log_b(a) mathematically.
// -----------------------------------------------------------

double logBaseB(int a, int b)
{
    // log_b(a) = log(a) / log(b)
    // We use a simple approach for demonstration
    double logA = 0.0;
    double logB = 0.0;
    double valA = (double)a;
    double valB = (double)b;

    // Compute log using repeated multiplication
    // Approximation: count how many times we multiply by 2.718
    // Simple method: use known values for small numbers
    // For exact computation, use math library
    // Here we just demonstrate the concept

    // Using the change of base formula with base 2:
    // log_b(a) = log2(a) / log2(b)

    int countA = 0;
    double temp = 1.0;
    while (temp < valA)
    {
        temp = temp * 2.0;
        countA = countA + 1;
    }
    logA = (double)countA;

    int countB = 0;
    temp = 1.0;
    while (temp < valB)
    {
        temp = temp * 2.0;
        countB = countB + 1;
    }
    logB = (double)countB;

    if (logB == 0.0)
    {
        return logA;
    }
    return logA / logB;
}

// -----------------------------------------------------------
// Example 1: Merge Sort
// T(n) = 2*T(n/2) + O(n)
// a = 2, b = 2, d = 1
// b^d = 2^1 = 2
// a == b^d  =>  Case 2
// T(n) = O(n^1 * log(n)) = O(n log n)
// -----------------------------------------------------------

void explainMergeSort()
{
    cout << "--- Merge Sort ---" << endl;
    cout << "Recurrence: T(n) = 2*T(n/2) + O(n)" << endl;
    cout << "  a = 2  (two sub-problems)" << endl;
    cout << "  b = 2  (each half the size)" << endl;
    cout << "  d = 1  (merge costs O(n))" << endl;
    cout << "  b^d = 2^1 = 2" << endl;
    cout << "  a == b^d  =>  Case 2" << endl;
    cout << "  T(n) = O(n^1 * log(n)) = O(n log n)" << endl;
    cout << endl;
}

// -----------------------------------------------------------
// Example 2: Binary Search
// T(n) = T(n/2) + O(1)
// a = 1, b = 2, d = 0
// b^d = 2^0 = 1
// a == b^d  =>  Case 2
// T(n) = O(n^0 * log(n)) = O(log n)
// -----------------------------------------------------------

void explainBinarySearch()
{
    cout << "--- Binary Search ---" << endl;
    cout << "Recurrence: T(n) = 1*T(n/2) + O(1)" << endl;
    cout << "  a = 1  (one sub-problem)" << endl;
    cout << "  b = 2  (half the size)" << endl;
    cout << "  d = 0  (comparison costs O(1) = O(n^0))" << endl;
    cout << "  b^d = 2^0 = 1" << endl;
    cout << "  a == b^d  =>  Case 2" << endl;
    cout << "  T(n) = O(n^0 * log(n)) = O(log n)" << endl;
    cout << endl;
}

// -----------------------------------------------------------
// Example 3: Max Element (D&C)
// T(n) = 2*T(n/2) + O(1)
// a = 2, b = 2, d = 0
// b^d = 2^0 = 1
// a > b^d  =>  Case 1
// T(n) = O(n^(log_2(2))) = O(n^1) = O(n)
// -----------------------------------------------------------

void explainMaxElement()
{
    cout << "--- Max Element (D&C) ---" << endl;
    cout << "Recurrence: T(n) = 2*T(n/2) + O(1)" << endl;
    cout << "  a = 2  (two sub-problems)" << endl;
    cout << "  b = 2  (each half the size)" << endl;
    cout << "  d = 0  (comparison costs O(1) = O(n^0))" << endl;
    cout << "  b^d = 2^0 = 1" << endl;
    cout << "  a > b^d (2 > 1)  =>  Case 1" << endl;
    cout << "  log_b(a) = log_2(2) = 1" << endl;
    cout << "  T(n) = O(n^1) = O(n)" << endl;
    cout << endl;
}

// -----------------------------------------------------------
// Example 4: Strassen's Matrix Multiplication
// T(n) = 7*T(n/2) + O(n^2)
// a = 7, b = 2, d = 2
// b^d = 2^2 = 4
// a > b^d  =>  Case 1
// T(n) = O(n^(log_2(7))) = O(n^2.81)
// -----------------------------------------------------------

void explainStrassens()
{
    cout << "--- Strassen's Matrix Multiplication ---" << endl;
    cout << "Recurrence: T(n) = 7*T(n/2) + O(n^2)" << endl;
    cout << "  a = 7  (seven sub-problems)" << endl;
    cout << "  b = 2  (each half the size)" << endl;
    cout << "  d = 2  (matrix add/subtract costs O(n^2))" << endl;
    cout << "  b^d = 2^2 = 4" << endl;
    cout << "  a > b^d (7 > 4)  =>  Case 1" << endl;
    cout << "  log_b(a) = log_2(7) approx 2.81" << endl;
    cout << "  T(n) = O(n^2.81)" << endl;
    cout << endl;
}

// ============================================================

int main()
{
    cout << "============================================" << endl;
    cout << "  Master Theorem" << endl;
    cout << "============================================" << endl;
    cout << endl;

    cout << "General Form: T(n) = a*T(n/b) + O(n^d)" << endl;
    cout << endl;
    cout << "Case 1: a > b^d   =>  T(n) = O(n^(log_b(a)))" << endl;
    cout << "Case 2: a == b^d  =>  T(n) = O(n^d * log(n))" << endl;
    cout << "Case 3: a < b^d   =>  T(n) = O(n^d)" << endl;
    cout << endl;

    cout << "============================================" << endl;
    cout << "  Examples" << endl;
    cout << "============================================" << endl;
    cout << endl;

    explainMergeSort();
    explainBinarySearch();
    explainMaxElement();
    explainStrassens();

    // --- Summary Table ---
    cout << "============================================" << endl;
    cout << "  Summary Table" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Algorithm   | a  | b  | d  | Case  | Complexity" << endl;
    cout << "------------|----|----|----|-------|------------" << endl;
    cout << "Merge Sort  | 2  | 2  | 1  |   2   | O(n log n)" << endl;
    cout << "Bin. Search | 1  | 2  | 0  |   2   | O(log n)" << endl;
    cout << "Max Element | 2  | 2  | 0  |   1   | O(n)" << endl;
    cout << "Strassen's  | 7  | 2  | 2  |   1   | O(n^2.81)" << endl;
    cout << endl;

    // --- Visualizing the Master Theorem ---
    cout << "============================================" << endl;
    cout << "  Intuition Behind Master Theorem" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Think of the recursion tree:" << endl;
    cout << endl;
    cout << "Case 1 (a > b^d): The number of leaves dominates." << endl;
    cout << "  Most work happens at the bottom of the tree." << endl;
    cout << "  Example: Max Element - many small comparisons." << endl;
    cout << endl;
    cout << "Case 2 (a == b^d): Work is equal at every level." << endl;
    cout << "  Total = (work per level) * (number of levels)" << endl;
    cout << "  Example: Merge Sort - each level costs O(n)." << endl;
    cout << endl;
    cout << "Case 3 (a < b^d): The root dominates." << endl;
    cout << "  Most work happens at the top of the tree." << endl;
    cout << "  Example: Some problems where divide+combine is very expensive." << endl;

    return 0;
}
