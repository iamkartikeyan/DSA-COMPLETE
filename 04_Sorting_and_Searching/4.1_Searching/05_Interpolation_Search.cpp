/*
 * File: 05_Interpolation_Search.cpp
 * Topic: Interpolation Search - Estimate position using values
 * Description: Like looking up a name in a phone book
 */
#include <iostream>
using namespace std;

// Interpolation Search
int interpolationSearch(int arr[], int n, int target) {
    int lo = 0;
    int hi = n - 1;

    while (lo <= hi && target >= arr[lo] && target <= arr[hi]) {
        // If only one element
        if (lo == hi) {
            if (arr[lo] == target) return lo;
            return -1;
        }

        // Interpolation formula: estimate position
        int pos = lo + ((target - arr[lo]) * (hi - lo)) / (arr[hi] - arr[lo]);

        if (arr[pos] == target) {
            return pos;
        }
        else if (arr[pos] < target) {
            lo = pos + 1; // target is in upper part
        }
        else {
            hi = pos - 1; // target is in lower part
        }
    }
    return -1;
}

int main() {
    cout << "=== Interpolation Search ===" << endl;
    cout << endl;

    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int n = 9;

    cout << "Array: 10 20 30 40 50 60 70 80 90" << endl;
    cout << "(Uniformly distributed)" << endl;
    cout << endl;

    int target = 70;
    int idx = interpolationSearch(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  Instead of always checking the middle," << endl;
    cout << "  estimate where target might be based on values." << endl;
    cout << endl;
    cout << "  pos = lo + (target - arr[lo]) * (hi - lo) / (arr[hi] - arr[lo])" << endl;
    cout << endl;
    cout << "  If values are uniformly spaced, estimate is very accurate!" << endl;
    cout << endl;
    cout << "Time: O(log log n) average (BEST of all searches!)" << endl;
    cout << "Time: O(n) worst case (if values not uniform)" << endl;
    cout << "Space: O(1)" << endl;
    cout << "Best for: Uniformly distributed sorted data" << endl;

    return 0;
}
