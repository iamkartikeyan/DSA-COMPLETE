/*
 * File: 01_What_Is_Time_Complexity.cpp
 * Topic: What is Time Complexity, why we measure it
 * Description: Big O notation, counting operations
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== What is Time Complexity? ===" << endl;
    cout << endl;

    cout << "--- Why Measure Time Complexity? ---" << endl;
    cout << "We want to know how an algorithm's runtime grows" << endl;
    cout << "as the INPUT SIZE increases." << endl;
    cout << endl;
    cout << "NOT about actual seconds - about HOW MANY OPERATIONS." << endl;
    cout << endl;

    cout << "--- Big O Notation ---" << endl;
    cout << "Big O describes the WORST CASE growth rate." << endl;
    cout << "It ignores constants and small terms." << endl;
    cout << endl;

    cout << "--- Examples ---" << endl;
    cout << endl;

    // O(1) - Constant time
    cout << "O(1) - Constant time:" << endl;
    cout << "  int arr[5] = {10, 20, 30, 40, 50};" << endl;
    cout << "  cout << arr[0]; // Always 1 operation" << endl;
    cout << "  Same time whether array has 5 or 5000 elements" << endl;
    cout << endl;

    // O(n) - Linear time
    cout << "O(n) - Linear time:" << endl;
    cout << "  for (int i = 0; i < n; i++) {" << endl;
    cout << "    cout << arr[i];" << endl;
    cout << "  }" << endl;
    cout << "  If n=10 -> 10 operations" << endl;
    cout << "  If n=1000 -> 1000 operations" << endl;
    cout << "  Time grows LINEARLY with n" << endl;
    cout << endl;

    // O(n^2) - Quadratic time
    cout << "O(n^2) - Quadratic time:" << endl;
    cout << "  for (int i = 0; i < n; i++) {" << endl;
    cout << "    for (int j = 0; j < n; j++) {" << endl;
    cout << "      cout << arr[i] << arr[j];" << endl;
    cout << "    }" << endl;
    cout << "  }" << endl;
    cout << "  If n=10 -> 100 operations" << endl;
    cout << "  If n=1000 -> 1,000,000 operations" << endl;
    cout << "  Time grows with SQUARE of n" << endl;
    cout << endl;

    cout << "--- Rules for Counting ---" << endl;
    cout << "1. Drop constants: O(2n) -> O(n)" << endl;
    cout << "2. Drop lower terms: O(n^2 + n) -> O(n^2)" << endl;
    cout << "3. Count the dominant operation" << endl;
    cout << "4. Focus on WORST case" << endl;

    return 0;
}
