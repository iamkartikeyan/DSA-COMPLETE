/*
 * File: 05_Space_Complexity_Summary.cpp
 * Topic: Complete space complexity summary
 * Description: Rules, patterns, and quick reference
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Space Complexity - Summary ===" << endl;
    cout << endl;

    cout << "--- What Counts as Space? ---" << endl;
    cout << "1. Variables declared in function" << endl;
    cout << "2. Arrays/objects created with new" << endl;
    cout << "3. Recursion call stack" << endl;
    cout << "4. NOT the input data itself" << endl;
    cout << endl;

    cout << "--- Common Space Complexities ---" << endl;
    cout << endl;
    cout << "O(1)      < Constant     < Two pointers, in-place" << endl;
    cout << "O(log n)  < Logarithmic  < Recursion depth (binary)" << endl;
    cout << "O(n)      < Linear       < Hash table, merge sort" << endl;
    cout << "O(n^2)    < Quadratic    < 2D DP table, adjacency matrix" << endl;
    cout << endl;

    cout << "--- In-Place = O(1) Extra Space ---" << endl;
    cout << "Algorithm modifies data WITHOUT creating new structures." << endl;
    cout << "Examples: Bubble sort, Quick sort, Two pointers" << endl;
    cout << endl;

    cout << "--- Recursion Space = Stack Depth ---" << endl;
    cout << "NOT total calls, but MAX depth at any time." << endl;
    cout << "f(n) = f(n-1)         -> O(n) stack" << endl;
    cout << "f(n) = f(n/2)         -> O(log n) stack" << endl;
    cout << "f(n) = f(n-1) + f(n-2) -> O(n) stack (not O(2^n)!)" << endl;
    cout << endl;

    cout << "--- Tips ---" << endl;
    cout << "1. Use in-place when possible (saves memory)" << endl;
    cout << "2. Iterative > Recursive for space (no stack)" << endl;
    cout << "3. Hash table: great for time, costs O(n) space" << endl;
    cout << "4. DP: trade space for avoiding recomputation" << endl;

    return 0;
}
