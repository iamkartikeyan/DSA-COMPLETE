// ============================================================
// 06_DC_Framework_Summary.cpp
// Summary of the Divide and Conquer Framework
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// SUMMARY OF DIVIDE AND CONQUER FRAMEWORK
// ============================================================

// -----------------------------------------------------------
// THE D&C FRAMEWORK (3 Steps)
// -----------------------------------------------------------
//
// 1. DIVIDE
//    Break the problem into smaller sub-problems of the
//    same type.
//
// 2. CONQUER
//    Solve the sub-problems recursively.
//    When sub-problems are small enough, solve directly
//    (base case).
//
// 3. COMBINE
//    Merge the solutions of sub-problems into the solution
//    for the original problem.
//
// -----------------------------------------------------------
// GENERAL RECURRENCE
// -----------------------------------------------------------
//
//   T(n) = a * T(n / b) + f(n)
//
//   a    = number of sub-problems
//   b    = factor by which problem size decreases
//   f(n) = cost to divide + combine
//
// -----------------------------------------------------------
// MASTER THEOREM (Quick Reference)
// -----------------------------------------------------------
//
//   Compare a with b^d (where f(n) = O(n^d)):
//
//   Case 1: a > b^d   =>  T(n) = O(n^(log_b(a)))
//   Case 2: a == b^d  =>  T(n) = O(n^d * log(n))
//   Case 3: a < b^d   =>  T(n) = O(n^d)
//
// -----------------------------------------------------------
// WHEN TO USE DIVIDE AND CONQUER
// -----------------------------------------------------------
//
// Use D&C when:
//   1. The problem can be split into INDEPENDENT sub-problems
//      (no overlapping sub-problems)
//   2. The sub-problems are the same type as the original
//   3. Solutions can be combined to solve the original
//
// Do NOT use D&C when:
//   1. Sub-problems OVERLAP (use Dynamic Programming instead)
//      Example: Naive Fibonacci
//   2. The problem is inherently sequential
//   3. The overhead of recursion outweighs benefits
//
// D&C vs DP:
//   - D&C: sub-problems are independent (no overlap)
//   - DP:  sub-problems overlap (memoize or tabulate)
//
// ============================================================

// -----------------------------------------------------------
// Quick implementations for reference
// -----------------------------------------------------------

// D&C: Maximum element
int dcMax(int arr[], int low, int high)
{
    if (low == high)
    {
        return arr[low];
    }

    int mid = (low + high) / 2;
    int left = dcMax(arr, low, mid);
    int right = dcMax(arr, mid + 1, high);

    if (left > right)
    {
        return left;
    }
    return right;
}

// D&C: Power x^n
int dcPower(int x, int n)
{
    if (n == 0)
    {
        return 1;
    }

    int half = dcPower(x, n / 2);

    if (n % 2 == 0)
    {
        return half * half;
    }
    return x * half * half;
}

// D&C: Binary Search
int dcBinarySearch(int arr[], int low, int high, int key)
{
    if (low > high)
    {
        return -1;
    }

    int mid = (low + high) / 2;

    if (arr[mid] == key)
    {
        return mid;
    }
    else if (key < arr[mid])
    {
        return dcBinarySearch(arr, low, mid - 1, key);
    }
    else
    {
        return dcBinarySearch(arr, mid + 1, high, key);
    }
}

// ============================================================

int main()
{
    cout << "============================================" << endl;
    cout << "  D&C Framework Summary" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- The 3 Steps ---
    cout << "============================================" << endl;
    cout << "  The 3 Steps of D&C" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "1. DIVIDE   - Break problem into smaller" << endl;
    cout << "              sub-problems of the same type" << endl;
    cout << endl;
    cout << "2. CONQUER  - Solve sub-problems recursively" << endl;
    cout << "              Base case when small enough" << endl;
    cout << endl;
    cout << "3. COMBINE  - Merge sub-solutions into" << endl;
    cout << "              the final answer" << endl;
    cout << endl;

    // --- Recurrence ---
    cout << "============================================" << endl;
    cout << "  General Recurrence" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "T(n) = a * T(n/b) + f(n)" << endl;
    cout << endl;

    // --- All problems covered ---
    cout << "============================================" << endl;
    cout << "  All D&C Problems Covered in This Section" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Problem              | Recurrence          | Time" << endl;
    cout << "---------------------|---------------------|----------" << endl;
    cout << "Find Max (D&C)       | T(n)=2T(n/2)+O(1)   | O(n)" << endl;
    cout << "Find Min (D&C)       | T(n)=2T(n/2)+O(1)   | O(n)" << endl;
    cout << "Array Sum (D&C)      | T(n)=2T(n/2)+O(1)   | O(n)" << endl;
    cout << "Power x^n            | T(n)=T(n/2)+O(1)    | O(log n)" << endl;
    cout << "Binary Search        | T(n)=T(n/2)+O(1)    | O(log n)" << endl;
    cout << "Merge Sort           | T(n)=2T(n/2)+O(n)   | O(n log n)" << endl;
    cout << "Quick Sort (avg)     | T(n)=2T(n/2)+O(n)   | O(n log n)" << endl;
    cout << "Closest Pair         | T(n)=2T(n/2)+O(n)   | O(n log n)" << endl;
    cout << "Strassen's Matrix    | T(n)=7T(n/2)+O(n^2) | O(n^2.81)" << endl;
    cout << endl;

    // --- D&C vs DP ---
    cout << "============================================" << endl;
    cout << "  D&C vs Dynamic Programming" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Divide and Conquer:" << endl;
    cout << "  - Sub-problems are INDEPENDENT" << endl;
    cout << "  - No overlapping work" << endl;
    cout << "  - Examples: Merge Sort, Binary Search" << endl;
    cout << endl;
    cout << "Dynamic Programming:" << endl;
    cout << "  - Sub-problems OVERLAP" << endl;
    cout << "  - Same work would be repeated" << endl;
    cout << "  - Store results to avoid recomputation" << endl;
    cout << "  - Examples: Fibonacci, Knapsack, LCS" << endl;
    cout << endl;

    // --- Files in this folder ---
    cout << "============================================" << endl;
    cout << "  Files in 10.1_DC_Framework" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "01_What_Is_Divide_Conquer.cpp" << endl;
    cout << "  - D&C paradigm: Divide, Conquer, Combine" << endl;
    cout << "  - Examples: Max, Min, Sum using D&C" << endl;
    cout << endl;
    cout << "02_Master_Theorem.cpp" << endl;
    cout << "  - Master Theorem: all 3 cases" << endl;
    cout << "  - Examples: Merge Sort, Binary Search, Max, Strassen's" << endl;
    cout << endl;
    cout << "03_Divide_Conquer_Power.cpp" << endl;
    cout << "  - Compute x^n in O(log n)" << endl;
    cout << "  - Handle negative exponents" << endl;
    cout << endl;
    cout << "04_Divide_Conquer_Binary_Search.cpp" << endl;
    cout << "  - Recursive binary search as D&C" << endl;
    cout << "  - T(n) = T(n/2) + O(1)" << endl;
    cout << endl;
    cout << "05_Divide_Conquer_Fibonacci.cpp" << endl;
    cout << "  - Naive recursive Fibonacci as BAD D&C" << endl;
    cout << "  - Overlapping subproblems, exponential time" << endl;
    cout << endl;
    cout << "06_DC_Framework_Summary.cpp" << endl;
    cout << "  - This file: summary of all concepts" << endl;
    cout << endl;

    // --- Quick demo ---
    int arr[] = {5, 2, 9, 1, 7, 6, 3, 8};
    int n = 8;

    cout << "============================================" << endl;
    cout << "  Quick Demos" << endl;
    cout << "============================================" << endl;
    cout << endl;

    cout << "Array: ";
    for (int i = 0; i < n; i = i + 1)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Max (D&C): " << dcMax(arr, 0, n - 1) << endl;
    cout << "2^10: " << dcPower(2, 10) << endl;
    cout << endl;

    int sortedArr[] = {2, 5, 8, 12, 16, 23, 38, 56};
    int sn = 8;
    int key = 23;

    cout << "Sorted Array: ";
    for (int i = 0; i < sn; i = i + 1)
    {
        cout << sortedArr[i] << " ";
    }
    cout << endl;

    int idx = dcBinarySearch(sortedArr, 0, sn - 1, key);
    if (idx == -1)
    {
        cout << key << " not found" << endl;
    }
    else
    {
        cout << key << " found at index " << idx << endl;
    }

    return 0;
}
