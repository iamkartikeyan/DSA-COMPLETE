/*
 * File: 03_Ternary_Search.cpp
 * Topic: Ternary Search - Divide into 3 parts
 * Description: Like binary search but with two mid points
 */
#include <iostream>
using namespace std;

// Ternary Search
int ternarySearch(int arr[], int n, int target) {
    int lo = 0;
    int hi = n - 1;

    while (lo <= hi) {
        int mid1 = lo + (hi - lo) / 3;
        int mid2 = hi - (hi - lo) / 3;

        if (arr[mid1] == target) {
            return mid1;
        }
        if (arr[mid2] == target) {
            return mid2;
        }

        if (target < arr[mid1]) {
            // Target in first third
            hi = mid1 - 1;
        }
        else if (target > arr[mid2]) {
            // Target in last third
            lo = mid2 + 1;
        }
        else {
            // Target in middle third
            lo = mid1 + 1;
            hi = mid2 - 1;
        }
    }
    return -1; // not found
}

int main() {
    cout << "=== Ternary Search ===" << endl;
    cout << endl;

    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = 10;

    cout << "Array: 2 5 8 12 16 23 38 56 72 91" << endl;
    cout << endl;

    int target = 23;
    int idx = ternarySearch(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Divide array into 3 parts using two mid points" << endl;
    cout << "  2. mid1 = lo + (hi-lo)/3" << endl;
    cout << "  3. mid2 = hi - (hi-lo)/3" << endl;
    cout << "  4. If target equals either mid -> found" << endl;
    cout << "  5. Else narrow down to one of the 3 parts" << endl;
    cout << endl;
    cout << "Time: O(log3 n) - slightly fewer steps than binary" << endl;
    cout << "BUT: 2 comparisons per step vs 1 in binary search" << endl;
    cout << "Result: Practically SLOWER than binary search" << endl;
    cout << "Use: Mostly theoretical interest" << endl;

    return 0;
}
