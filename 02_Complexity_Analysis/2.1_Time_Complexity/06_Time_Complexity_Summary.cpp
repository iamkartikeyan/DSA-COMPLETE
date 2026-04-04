/*
 * File: 06_Time_Complexity_Summary.cpp
 * Topic: Complete time complexity summary
 * Description: All rules, patterns, and quick reference
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Time Complexity - Summary ===" << endl;
    cout << endl;

    cout << "--- Hierarchy (Fastest to Slowest) ---" << endl;
    cout << endl;
    cout << "O(1)        < Constant        < Array access" << endl;
    cout << "O(log n)    < Logarithmic     < Binary search" << endl;
    cout << "O(n)        < Linear          < Linear search" << endl;
    cout << "O(n log n)  < Linearithmic    < Merge sort" << endl;
    cout << "O(n^2)      < Quadratic       < Bubble sort" << endl;
    cout << "O(n^3)      < Cubic           < Matrix multiplication" << endl;
    cout << "O(2^n)      < Exponential     < Recursive Fibonacci" << endl;
    cout << "O(n!)       < Factorial       < All permutations" << endl;
    cout << endl;

    cout << "--- Loop Analysis Rules ---" << endl;
    cout << "Single loop (i++):       O(n)" << endl;
    cout << "Single loop (i *= 2):    O(log n)" << endl;
    cout << "Nested loops (both n):   O(n^2)" << endl;
    cout << "Nested (n + log n):      O(n log n)" << endl;
    cout << "Consecutive loops:       ADD them -> O(n + n) = O(n)" << endl;
    cout << endl;

    cout << "--- Recursive Analysis ---" << endl;
    cout << "f(n) = f(n-1)          -> O(n)" << endl;
    cout << "f(n) = f(n/2)          -> O(log n)" << endl;
    cout << "f(n) = f(n-1) + f(n-2) -> O(2^n)" << endl;
    cout << endl;

    cout << "--- Big O Rules ---" << endl;
    cout << "1. Drop constants:    O(3n) -> O(n)" << endl;
    cout << "2. Drop lower terms:  O(n^2 + n) -> O(n^2)" << endl;
    cout << "3. Worst case matters: Big O = upper bound" << endl;
    cout << endl;

    cout << "--- Notations ---" << endl;
    cout << "Big O:    Upper bound (worst case)" << endl;
    cout << "Big Omega: Lower bound (best case)" << endl;
    cout << "Big Theta: Tight bound (exact)" << endl;
    cout << endl;
    cout << "In practice, we mostly use Big O." << endl;

    return 0;
}
