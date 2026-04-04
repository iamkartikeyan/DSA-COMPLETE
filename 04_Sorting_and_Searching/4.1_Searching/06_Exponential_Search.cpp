/*
 * File: 06_Exponential_Search.cpp
 * Topic: Exponential Search - Double index to find range
 * Description: Useful when array size is unknown or target is near start
 */
#include <iostream>
using namespace std;

int minVal(int a, int b) {
    if (a < b) return a;
    return b;
}

// Binary Search helper (iterative)
int binarySearch(int arr[], int lo, int hi, int target) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    return -1;
}

// Exponential Search
int exponentialSearch(int arr[], int n, int target) {
    // Check first element
    if (arr[0] == target) {
        return 0;
    }

    // Find range by doubling: 1, 2, 4, 8, 16, ...
    int i = 1;
    while (i < n && arr[i] <= target) {
        i = i * 2;
    }

    // Binary search in the range [i/2, min(i, n-1)]
    return binarySearch(arr, i / 2, minVal(i, n - 1), target);
}

int main() {
    cout << "=== Exponential Search ===" << endl;
    cout << endl;

    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = 10;

    cout << "Array: 2 5 8 12 16 23 38 56 72 91" << endl;
    cout << endl;

    int target = 23;
    int idx = exponentialSearch(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Check arr[0]" << endl;
    cout << "  2. Double index: 1, 2, 4, 8, ... until arr[i] >= target" << endl;
    cout << "  3. Binary search in range [i/2, i]" << endl;
    cout << endl;

    /*
     * Example with target=23:
     * arr[1]=5 < 23, double
     * arr[2]=8 < 23, double
     * arr[4]=16 < 23, double
     * arr[8]=72 >= 23, stop
     * Range found: [4, 8]
     * Binary search in [4,8] -> find 23 at index 5
     */

    cout << "Time: O(log n) - same as binary search" << endl;
    cout << "Space: O(1)" << endl;
    cout << "Requires: Sorted array" << endl;
    cout << "Use: Unbounded/infinite arrays, target likely near start" << endl;
    cout << "     Advantage: finds range in O(log p) where p = position" << endl;

    return 0;
}
