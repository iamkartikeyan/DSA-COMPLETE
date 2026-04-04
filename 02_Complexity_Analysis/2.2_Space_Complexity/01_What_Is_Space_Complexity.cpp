/*
 * File: 01_What_Is_Space_Complexity.cpp
 * Topic: What is Space Complexity, Auxiliary vs Input space
 * Description: Measuring extra memory used by algorithm
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== What is Space Complexity? ===" << endl;
    cout << endl;

    cout << "--- What Do We Measure? ---" << endl;
    cout << "Space complexity = EXTRA memory used by algorithm." << endl;
    cout << "NOT including the input data itself." << endl;
    cout << endl;

    cout << "--- Two Types of Space ---" << endl;
    cout << endl;

    cout << "1. Input Space: Memory for the input data" << endl;
    cout << "   - NOT counted in space complexity" << endl;
    cout << "   - Example: array of n integers = O(n) input" << endl;
    cout << endl;

    cout << "2. Auxiliary Space: EXTRA memory used" << endl;
    cout << "   - THIS is what we measure" << endl;
    cout << "   - Variables, temporary arrays, recursion stack" << endl;
    cout << endl;

    cout << "--- Examples ---" << endl;
    cout << endl;

    // O(1) auxiliary space
    cout << "O(1) Auxiliary Space:" << endl;
    cout << "  int sum = 0;           // 1 variable" << endl;
    cout << "  for (int i = 0; i < n; i++) {" << endl;
    cout << "    sum += arr[i];       // no extra space" << endl;
    cout << "  }" << endl;
    cout << "  Only uses 'sum' variable -> O(1)" << endl;
    cout << endl;

    // O(n) auxiliary space
    cout << "O(n) Auxiliary Space:" << endl;
    cout << "  int* temp = new int[n];  // new array of size n" << endl;
    cout << "  for (int i = 0; i < n; i++) {" << endl;
    cout << "    temp[i] = arr[i] * 2;" << endl;
    cout << "  }" << endl;
    cout << "  Creates new array -> O(n)" << endl;
    cout << endl;

    // O(log n) auxiliary space (recursion stack)
    cout << "O(log n) Auxiliary Space:" << endl;
    cout << "  Recursive binary search uses stack space." << endl;
    cout << "  Each recursive call adds a frame." << endl;
    cout << "  Depth = log n -> O(log n) stack space" << endl;
    cout << endl;

    cout << "--- Space vs Time Tradeoff ---" << endl;
    cout << "Often we trade space for time:" << endl;
    cout << "  - Hash table: O(n) space for O(1) time" << endl;
    cout << "  - Merge sort: O(n) space for O(n log n) time" << endl;
    cout << "  - Counting sort: O(k) space for O(n+k) time" << endl;

    return 0;
}
