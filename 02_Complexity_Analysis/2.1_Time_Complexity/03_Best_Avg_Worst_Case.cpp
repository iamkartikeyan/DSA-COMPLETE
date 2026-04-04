/*
 * File: 03_Best_Avg_Worst_Case.cpp
 * Topic: Best case, Average case, Worst case analysis
 * Description: Understanding different scenarios for same algorithm
 */
#include <iostream>
using namespace std;

// Linear search to demonstrate all 3 cases
int linearSearch(int arr[], int n, int target) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count++;
        if (arr[i] == target) {
            cout << "  Found at index " << i << " after " << count << " comparison(s)" << endl;
            return i;
        }
    }
    cout << "  Not found after " << count << " comparison(s)" << endl;
    return -1;
}

int main() {
    cout << "=== Best, Average, Worst Case ===" << endl;
    cout << endl;

    int arr[] = {10, 20, 30, 40, 50};
    int n = 5;

    cout << "Array: 10 20 30 40 50" << endl;
    cout << endl;

    // Best case: O(1)
    cout << "--- Best Case: O(1) ---" << endl;
    cout << "Element at FIRST position:" << endl;
    linearSearch(arr, n, 10);
    cout << "  Only 1 comparison needed!" << endl;
    cout << endl;

    // Average case: O(n/2) = O(n)
    cout << "--- Average Case: O(n) ---" << endl;
    cout << "Element somewhere in MIDDLE:" << endl;
    linearSearch(arr, n, 30);
    cout << "  About n/2 comparisons on average" << endl;
    cout << endl;

    // Worst case: O(n)
    cout << "--- Worst Case: O(n) ---" << endl;
    cout << "Element at LAST position:" << endl;
    linearSearch(arr, n, 50);
    cout << "  All n comparisons needed!" << endl;
    cout << endl;

    cout << "Element NOT present:" << endl;
    linearSearch(arr, n, 99);
    cout << "  Still all n comparisons!" << endl;
    cout << endl;

    cout << "--- Key Points ---" << endl;
    cout << "Best case:    Minimum time (rarely happens)" << endl;
    cout << "Average case: Expected time (random input)" << endl;
    cout << "Worst case:   Maximum time (BIG O measures this!)" << endl;
    cout << endl;
    cout << "We use BIG O for WORST case because:" << endl;
    cout << "  - It gives an UPPER BOUND (guarantee)" << endl;
    cout << "  - We prepare for the worst" << endl;
    cout << endl;

    cout << "--- More Examples ---" << endl;
    cout << endl;
    cout << "Algorithm  | Best      | Average   | Worst" << endl;
    cout << "-----------|-----------|-----------|----------" << endl;
    cout << "Linear S.  | O(1)      | O(n)      | O(n)" << endl;
    cout << "Binary S.  | O(1)      | O(log n)  | O(log n)" << endl;
    cout << "Bubble S.  | O(n)      | O(n^2)    | O(n^2)" << endl;
    cout << "Quick S.   | O(n log n)| O(n log n)| O(n^2)" << endl;
    cout << "Merge S.   | O(n log n)| O(n log n)| O(n log n)" << endl;

    return 0;
}
