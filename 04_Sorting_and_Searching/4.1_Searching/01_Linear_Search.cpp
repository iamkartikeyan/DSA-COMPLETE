/*
 * File: 01_Linear_Search.cpp
 * Topic: Linear Search - Scan every element
 * Description: Simplest search, works on any array (sorted or not)
 */
#include <iostream>
using namespace std;

// Linear Search: returns index of target, or -1 if not found
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i; // found at index i
        }
    }
    return -1; // not found
}

int main() {
    cout << "=== Linear Search ===" << endl;
    cout << endl;

    int arr[] = {64, 25, 12, 22, 90, 11, 15};
    int n = 7;

    cout << "Array: 64 25 12 22 90 11 15" << endl;
    cout << endl;

    // Search for 22
    int target = 22;
    int idx = linearSearch(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    // Search for 99 (not present)
    target = 99;
    idx = linearSearch(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Start from first element" << endl;
    cout << "  2. Compare each element with target" << endl;
    cout << "  3. If match -> return index" << endl;
    cout << "  4. If end reached -> not found" << endl;
    cout << endl;
    cout << "Time: O(n) - may scan all elements" << endl;
    cout << "Space: O(1) - no extra memory" << endl;
    cout << "Works on: Sorted AND unsorted arrays" << endl;

    return 0;
}
