// ============================================================
// 05_Divide_Conquer_Fibonacci.cpp
// Naive Recursive Fibonacci as a BAD Divide and Conquer Example
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// FIBONACCI SEQUENCE
//
// Fib(0) = 0
// Fib(1) = 1
// Fib(n) = Fib(n-1) + Fib(n-2)   for n >= 2
//
// Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
//
// ============================================================

// -----------------------------------------------------------
// NAIVE RECURSIVE FIBONACCI (BAD D&C)
// -----------------------------------------------------------
//
// This LOOKS like divide and conquer but it is NOT good D&C!
//
// Why? Because the sub-problems OVERLAP.
// Fib(n) calls Fib(n-1) and Fib(n-2)
// Fib(n-1) also calls Fib(n-2) and Fib(n-3)
// So Fib(n-2) is computed TWICE!
//
// Recurrence: T(n) = T(n-1) + T(n-2) + O(1)
// This gives T(n) = O(2^n)  -- EXPONENTIAL TIME!
//
// This is BAD because:
//   - Same sub-problems are solved again and again
//   - The recursion tree has overlapping branches
//   - This is where Dynamic Programming is needed instead
// -----------------------------------------------------------

int fibonacciNaive(int n)
{
    // Base cases
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }

    // Recursive step (this causes overlapping subproblems!)
    return fibonacciNaive(n - 1) + fibonacciNaive(n - 2);
}

// -----------------------------------------------------------
// GOOD approach: Iterative Fibonacci O(n)
// -----------------------------------------------------------

int fibonacciIterative(int n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }

    int prev2 = 0;
    int prev1 = 1;
    int current = 0;

    for (int i = 2; i <= n; i = i + 1)
    {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

// ============================================================
// OVERLAPPING SUBPROBLEMS DEMONSTRATION
// ============================================================
//
// For Fib(5), the recursion tree looks like:
//
//                     Fib(5)
//                   /       \
//              Fib(4)       Fib(3)
//             /     \       /     \
//         Fib(3)   Fib(2) Fib(2)  Fib(1)
//         /   \     /  \   /   \
//     Fib(2) Fib(1) F(1)F(0) F(1)F(0)
//     /   \
//   F(1)  F(0)
//
// Notice Fib(3) is computed TWICE!
// Notice Fib(2) is computed THREE TIMES!
// This is why naive recursion is terrible here.
// ============================================================

// -----------------------------------------------------------
// Counter to track calls for demonstration
// -----------------------------------------------------------

int callCount = 0;

int fibonacciWithCount(int n)
{
    callCount = callCount + 1;

    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }

    return fibonacciWithCount(n - 1) + fibonacciWithCount(n - 2);
}

// ============================================================

int main()
{
    cout << "============================================" << endl;
    cout << "  Fibonacci: BAD Divide and Conquer" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- Compare naive vs iterative for small values ---
    cout << "n\tNaive\tIterative" << endl;
    cout << "--\t-----\t---------" << endl;

    for (int i = 0; i <= 10; i = i + 1)
    {
        cout << i << "\t" << fibonacciNaive(i) << "\t" << fibonacciIterative(i) << endl;
    }
    cout << endl;

    // --- Show the explosion of calls ---
    cout << "============================================" << endl;
    cout << "  Function Calls (Overlapping Subproblems)" << endl;
    cout << "============================================" << endl;
    cout << endl;

    for (int i = 1; i <= 10; i = i + 1)
    {
        callCount = 0;
        fibonacciWithCount(i);
        cout << "Fib(" << i << "): " << callCount << " function calls" << endl;
    }
    cout << endl;

    // --- Key insight ---
    cout << "============================================" << endl;
    cout << "  Why is Naive Fibonacci BAD D&C?" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Good D&C problems (like binary search):" << endl;
    cout << "  - Sub-problems are INDEPENDENT" << endl;
    cout << "  - No overlap between sub-problems" << endl;
    cout << "  - Each sub-problem is solved ONCE" << endl;
    cout << endl;
    cout << "Bad D&C problems (like naive Fibonacci):" << endl;
    cout << "  - Sub-problems OVERLAP" << endl;
    cout << "  - Same values are computed MANY times" << endl;
    cout << "  - Exponential time: O(2^n)" << endl;
    cout << endl;

    // --- Recurrence comparison ---
    cout << "============================================" << endl;
    cout << "  Recurrence Comparison" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "GOOD D&C - Binary Search:" << endl;
    cout << "  T(n) = T(n/2) + O(1)   => O(log n)" << endl;
    cout << "  Problem halves each time, no overlap" << endl;
    cout << endl;
    cout << "GOOD D&C - Merge Sort:" << endl;
    cout << "  T(n) = 2*T(n/2) + O(n) => O(n log n)" << endl;
    cout << "  Sub-problems are independent (different halves)" << endl;
    cout << endl;
    cout << "BAD D&C - Naive Fibonacci:" << endl;
    cout << "  T(n) = T(n-1) + T(n-2) + O(1) => O(2^n)" << endl;
    cout << "  Sub-problems OVERLAP, same work repeated" << endl;
    cout << endl;

    // --- Solution: Dynamic Programming ---
    cout << "============================================" << endl;
    cout << "  Solution: Use Dynamic Programming!" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "When sub-problems overlap, use DP instead of" << endl;
    cout << "naive D&C. DP stores results of sub-problems" << endl;
    cout << "so they are computed only once." << endl;
    cout << endl;
    cout << "Iterative Fibonacci: O(n) time, O(1) space" << endl;
    cout << "(Much better than O(2^n)!)" << endl;

    return 0;
}
