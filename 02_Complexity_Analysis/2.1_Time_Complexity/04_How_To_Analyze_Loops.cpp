/*
 * File: 04_How_To_Analyze_Loops.cpp
 * Topic: Rules for analyzing loops and code
 * Description: Single loop, nested loops, consecutive loops
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== How to Analyze Loops ===" << endl;
    cout << endl;

    // Rule 1: Simple statements are O(1)
    cout << "--- Rule 1: Simple Statements = O(1) ---" << endl;
    cout << "  int x = 5;        // O(1)" << endl;
    cout << "  x = x + 1;        // O(1)" << endl;
    cout << "  cout << x;        // O(1)" << endl;
    cout << "  Total: O(1) + O(1) + O(1) = O(1)" << endl;
    cout << endl;

    // Rule 2: Single loop
    cout << "--- Rule 2: Single Loop = O(n) ---" << endl;
    cout << "  for (int i = 0; i < n; i++) {  // runs n times" << endl;
    cout << "    cout << i;                    // O(1)" << endl;
    cout << "  }" << endl;
    cout << "  Total: n * O(1) = O(n)" << endl;
    cout << endl;

    int n = 5;
    cout << "  n=5: loop runs 5 times" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  ";
    }
    cout << endl;
    cout << endl;

    // Rule 3: Nested loops
    cout << "--- Rule 3: Nested Loops = O(n^2) ---" << endl;
    cout << "  for (int i = 0; i < n; i++) {      // n times" << endl;
    cout << "    for (int j = 0; j < n; j++) {    // n times" << endl;
    cout << "      cout << i << j;                 // O(1)" << endl;
    cout << "    }" << endl;
    cout << "  }" << endl;
    cout << "  Total: n * n * O(1) = O(n^2)" << endl;

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count++;
        }
    }
    cout << "  n=5: " << count << " iterations (5*5=25)" << endl;
    cout << endl;

    // Rule 4: Consecutive loops
    cout << "--- Rule 4: Consecutive Loops = Add ---" << endl;
    cout << "  for (int i = 0; i < n; i++) { ... }  // O(n)" << endl;
    cout << "  for (int i = 0; i < n; i++) { ... }  // O(n)" << endl;
    cout << "  Total: O(n) + O(n) = O(2n) = O(n)" << endl;
    cout << endl;

    // Rule 5: Loop with division
    cout << "--- Rule 5: Division/Halving = O(log n) ---" << endl;
    cout << "  for (int i = n; i > 1; i = i / 2) {  // halves each time" << endl;
    cout << "    cout << i;                          // O(1)" << endl;
    cout << "  }" << endl;
    cout << "  Total: O(log n)" << endl;

    int steps = 0;
    for (int i = n; i > 1; i = i / 2) {
        steps++;
        cout << "  Step " << steps << ": i = " << i << endl;
    }
    cout << "  n=5: " << steps << " steps to reach 1" << endl;
    cout << endl;

    // Rule 6: Nested with different bounds
    cout << "--- Rule 6: Outer=n, Inner=log n = O(n log n) ---" << endl;
    cout << "  for (int i = 0; i < n; i++) {         // n times" << endl;
    cout << "    for (int j = n; j > 1; j /= 2) {    // log n times" << endl;
    cout << "      cout << i << j;                    // O(1)" << endl;
    cout << "    }" << endl;
    cout << "  }" << endl;
    cout << "  Total: n * log n * O(1) = O(n log n)" << endl;

    return 0;
}
