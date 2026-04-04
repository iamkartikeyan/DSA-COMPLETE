/*
 * File: 07_Searching_Summary.cpp
 * Topic: All Searching Algorithms Summary
 * Description: Complexity table and when to use each
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Searching Algorithms - Summary ===" << endl;
    cout << endl;

    cout << "--- Complexity Table ---" << endl;
    cout << endl;
    cout << "Algorithm      | Best   | Average    | Worst      | Space  | Sorted?" << endl;
    cout << "---------------|--------|------------|------------|--------|----------" << endl;
    cout << "Linear         | O(1)   | O(n)       | O(n)       | O(1)   | No" << endl;
    cout << "Binary         | O(1)   | O(log n)   | O(log n)   | O(1)   | Yes" << endl;
    cout << "Ternary        | O(1)   | O(log3 n)  | O(log3 n)  | O(1)   | Yes" << endl;
    cout << "Jump           | O(1)   | O(sqrt(n)) | O(sqrt(n)) | O(1)   | Yes" << endl;
    cout << "Interpolation  | O(1)   | O(log log n)| O(n)      | O(1)   | Yes" << endl;
    cout << "Exponential    | O(1)   | O(log n)   | O(log n)   | O(1)   | Yes" << endl;
    cout << endl;

    cout << "--- When to Use ---" << endl;
    cout << "Linear:         Small or unsorted arrays" << endl;
    cout << "Binary:         Sorted arrays (MOST PRACTICAL)" << endl;
    cout << "Ternary:        Theoretical interest; rarely faster than binary" << endl;
    cout << "Jump:           When jumping is cheaper than full binary" << endl;
    cout << "Interpolation:  Uniformly distributed sorted data" << endl;
    cout << "Exponential:    Unbounded arrays, target near beginning" << endl;
    cout << endl;

    cout << "--- Topics Covered in 4.1 ---" << endl;
    cout << "01. Linear Search          - Scan every element" << endl;
    cout << "02. Binary Search          - Halve search space" << endl;
    cout << "03. Ternary Search         - Divide into 3 parts" << endl;
    cout << "04. Jump Search            - Jump by sqrt(n) blocks" << endl;
    cout << "05. Interpolation Search   - Estimate position" << endl;
    cout << "06. Exponential Search     - Double index to find range" << endl;
    cout << "07. Searching Summary      - This file" << endl;

    return 0;
}
