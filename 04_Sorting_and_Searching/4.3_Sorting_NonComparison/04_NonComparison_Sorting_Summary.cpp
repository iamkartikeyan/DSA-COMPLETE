/*
 * File: 04_NonComparison_Sorting_Summary.cpp
 * Topic: Counting, Radix, Bucket Sort Summary
 * Description: Comparison of non-comparison sorts and when to use
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Non-Comparison Sorting - Summary ===" << endl;
    cout << endl;

    cout << "--- Why Non-Comparison? ---" << endl;
    cout << "Comparison-based sorts have O(n log n) lower bound." << endl;
    cout << "Non-comparison sorts can BREAK this bound by NOT" << endl;
    cout << "comparing elements directly." << endl;
    cout << endl;

    cout << "--- Complexity Table ---" << endl;
    cout << endl;
    cout << "Algorithm  | Best     | Average  | Worst    | Space    | Stable" << endl;
    cout << "-----------|----------|----------|----------|----------|--------" << endl;
    cout << "Counting   | O(n+k)   | O(n+k)   | O(n+k)   | O(n+k)   | Yes" << endl;
    cout << "Radix      | O(d*(n+b))| O(d*(n+b))| O(d*(n+b))| O(n+b)  | Yes" << endl;
    cout << "Bucket     | O(n+k)   | O(n+k)   | O(n^2)   | O(n+k)   | Depends" << endl;
    cout << endl;
    cout << "n = elements, k = range, d = digits, b = base" << endl;
    cout << endl;

    cout << "--- Counting Sort ---" << endl;
    cout << "Idea:      Count frequency of each value" << endl;
    cout << "Best when: Range of values (k) is small" << endl;
    cout << "Example:   Sorting ages (0-120), grades (0-100)" << endl;
    cout << endl;

    cout << "--- Radix Sort ---" << endl;
    cout << "Idea:      Sort digit by digit using counting sort" << endl;
    cout << "Best when: Large integer range, fixed-length keys" << endl;
    cout << "Example:   Phone numbers, large IDs, strings" << endl;
    cout << endl;

    cout << "--- Bucket Sort ---" << endl;
    cout << "Idea:      Distribute into buckets, sort each bucket" << endl;
    cout << "Best when: Uniformly distributed float data" << endl;
    cout << "Example:   Probabilities, test scores, percentages" << endl;
    cout << endl;

    cout << "--- Topics Covered in 4.3 ---" << endl;
    cout << "01. Counting Sort           - Frequency-based sort" << endl;
    cout << "02. Radix Sort              - Digit by digit sort" << endl;
    cout << "03. Bucket Sort             - Distribute into buckets" << endl;
    cout << "04. NonComparison Summary   - This file" << endl;

    return 0;
}
