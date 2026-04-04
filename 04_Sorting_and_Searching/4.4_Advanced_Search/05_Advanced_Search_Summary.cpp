/*
 * File: 05_Advanced_Search_Summary.cpp
 * Topic: Summary of all advanced search problems
 * Description: Key insights and patterns
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Advanced Search - Summary ===" << endl;
    cout << endl;

    cout << "--- Problem Patterns ---" << endl;
    cout << endl;

    cout << "1. Rotated Sorted Array" << endl;
    cout << "   Key: One half is ALWAYS sorted, check which one" << endl;
    cout << "   If target in sorted half -> go there, else go other" << endl;
    cout << endl;

    cout << "2. 2D Sorted Matrix" << endl;
    cout << "   Key: Flatten to 1D, binary search with index conversion" << endl;
    cout << "   row = index / cols, col = index % cols" << endl;
    cout << endl;

    cout << "3. Peak Element" << endl;
    cout << "   Key: Compare arr[mid] with arr[mid+1]" << endl;
    cout << "   Going UP -> peak on right, Going DOWN -> peak at mid or left" << endl;
    cout << "   Multiple peaks possible, return ANY one" << endl;
    cout << endl;

    cout << "4. Mountain Array" << endl;
    cout << "   Key: Find peak first, then search both slopes" << endl;
    cout << "   Left half: ascending (normal binary search)" << endl;
    cout << "   Right half: descending (reversed binary search)" << endl;
    cout << endl;

    cout << "--- Common Theme ---" << endl;
    cout << "ALL use MODIFIED binary search!" << endl;
    cout << "The trick is figuring out WHICH direction to go." << endl;
    cout << endl;

    cout << "--- Topics Covered in 4.4 ---" << endl;
    cout << "01. Rotated Sorted Array   - Modified binary, one half sorted" << endl;
    cout << "02. 2D Sorted Matrix       - Flatten + binary search" << endl;
    cout << "03. Peak Element           - Compare with neighbor" << endl;
    cout << "04. Mountain Array         - Find peak, search both slopes" << endl;
    cout << "05. Advanced Search Summary - This file" << endl;

    return 0;
}
