/*
 * File: 04_Mountain_Array.cpp
 * Topic: Find peak and search in mountain array
 * Description: Mountain = ascending then descending
 */
#include <iostream>
using namespace std;

// Find peak in mountain array
int findPeakInMountain(int arr[], int n) {
    int lo = 0;
    int hi = n - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] < arr[mid + 1]) {
            // We're on ascending slope -> peak is to the right
            lo = mid + 1;
        } else {
            // We're on descending slope -> peak is at mid or left
            hi = mid;
        }
    }

    return lo; // peak index
}

// Binary search in ascending portion
int binarySearchAscending(int arr[], int lo, int hi, int target) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// Binary search in descending portion
int binarySearchDescending(int arr[], int lo, int hi, int target) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        // Reversed direction: larger means go left
        if (arr[mid] > target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// Search in mountain array
int searchInMountain(int arr[], int n, int target) {
    // Step 1: Find peak
    int peak = findPeakInMountain(arr, n);

    // Step 2: Search in ascending left half
    int idx = binarySearchAscending(arr, 0, peak, target);
    if (idx != -1) {
        return idx;
    }

    // Step 3: Search in descending right half
    return binarySearchDescending(arr, peak + 1, n - 1, target);
}

int main() {
    cout << "=== Mountain Array ===" << endl;
    cout << endl;

    /*
     * Mountain Array:
     * - arr[0] < arr[1] < ... < arr[peak] > ... > arr[n-1]
     * - Length >= 3
     * - Exactly one peak
     *
     * Example: [0, 2, 5, 8, 12, 9, 6, 3, 1]
     *                    ^ peak at index 4
     */

    int arr[] = {0, 2, 5, 8, 12, 9, 6, 3, 1};
    int n = 9;

    cout << "Array: 0 2 5 8 12 9 6 3 1" << endl;
    cout << endl;

    // Find peak
    int peakIdx = findPeakInMountain(arr, n);
    cout << "Peak at index " << peakIdx << " (value: " << arr[peakIdx] << ")" << endl;
    cout << endl;

    // Search for elements
    int target1 = 5;
    int idx1 = searchInMountain(arr, n, target1);
    if (idx1 != -1) {
        cout << "Search " << target1 << ": Found at index " << idx1 << endl;
    } else {
        cout << "Search " << target1 << ": Not found" << endl;
    }

    int target2 = 9;
    int idx2 = searchInMountain(arr, n, target2);
    if (idx2 != -1) {
        cout << "Search " << target2 << ": Found at index " << idx2 << endl;
    } else {
        cout << "Search " << target2 << ": Not found" << endl;
    }

    int target3 = 10;
    int idx3 = searchInMountain(arr, n, target3);
    if (idx3 != -1) {
        cout << "Search " << target3 << ": Found at index " << idx3 << endl;
    } else {
        cout << "Search " << target3 << ": Not found" << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Find peak using binary search (same as peak element)" << endl;
    cout << "  2. Binary search in ascending left half [0..peak]" << endl;
    cout << "  3. If not found, binary search in descending right half [peak+1..n-1]" << endl;
    cout << "  4. For descending search, REVERSE the comparison direction" << endl;
    cout << endl;
    cout << "Time: O(log n) for peak + O(log n) for search = O(log n)" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
