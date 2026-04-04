/*
 * File: 05_Array_Summary.cpp
 * Topic: Array properties, complexity, when to use
 * Description: Summary of all array concepts
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Arrays - Summary ===" << endl;
    cout << endl;

    cout << "--- Array Properties ---" << endl;
    cout << "1. Contiguous memory allocation" << endl;
    cout << "2. Fixed size (static array)" << endl;
    cout << "3. O(1) random access" << endl;
    cout << "4. Cache friendly (elements close in memory)" << endl;
    cout << endl;

    cout << "--- Complexity ---" << endl;
    cout << "Access:   O(1)" << endl;
    cout << "Search:   O(n)" << endl;
    cout << "Insert:   O(n) - need to shift" << endl;
    cout << "Delete:   O(n) - need to shift" << endl;
    cout << endl;

    cout << "--- 2D Array ---" << endl;
    cout << "Access:   O(1)" << endl;
    cout << "Space:    O(rows * cols)" << endl;
    cout << "Row-major: elements stored row by row (C++ default)" << endl;
    cout << "Address:  base + (i * cols + j) * element_size" << endl;
    cout << endl;

    cout << "--- Vector (Dynamic Array) ---" << endl;
    cout << "Auto-resizes when full" << endl;
    cout << "push_back: O(1) amortized" << endl;
    cout << "insert/erase at position: O(n)" << endl;
    cout << "Doubles capacity when full" << endl;
    cout << endl;

    cout << "--- Topics Covered in 3.1 ---" << endl;
    cout << "01. Array Basics              - Declaration, access, memory" << endl;
    cout << "02. Array Operations          - Traversal, insert, delete, search" << endl;
    cout << "03. 2D Arrays                 - Matrix, row-major, dynamic 2D" << endl;
    cout << "04. Vector Dynamic Array      - Auto-growing array" << endl;
    cout << "05. Array Summary             - This file" << endl;

    return 0;
}
