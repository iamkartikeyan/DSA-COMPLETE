/*
 * File: 01_Search_Rotated_Sorted_Array.cpp
 * Topic: Search in a rotated sorted array
 * Description: Modified binary search - one half is always sorted
 */
#include <iostream>
using namespace std;

int searchRotated(int arr[], int n, int target) {
    int lo = 0;
    int hi = n - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] == target) {
            return mid; // found
        }

        // Check which half is sorted
        if (arr[lo] <= arr[mid]) {
            // Left half is sorted
            if (arr[lo] <= target && target < arr[mid]) {
                hi = mid - 1; // target is in sorted left half
            } else {
                lo = mid + 1; // target is in right half
            }
        } else {
            // Right half is sorted
            if (arr[mid] < target && target <= arr[hi]) {
                lo = mid + 1; // target is in sorted right half
            } else {
                hi = mid - 1; // target is in left half
            }
        }
    }
    return -1; // not found
}

int main() {
    cout << "=== Search in Rotated Sorted Array ===" << endl;
    cout << endl;

    /*
     * Array was sorted then rotated at unknown pivot:
     * Original: [0, 1, 2, 4, 5, 6, 7]
     * Rotated:  [4, 5, 6, 7, 0, 1, 2]
     *                    ^ pivot point
     *
     * Key insight: One half is ALWAYS sorted!
     */

    int arr[] = {4, 5, 6, 7, 0, 1, 2};
    int n = 7;

    cout << "Array: 4 5 6 7 0 1 2" << endl;
    cout << "(Originally [0,1,2,4,5,6,7] rotated at index 4)" << endl;
    cout << endl;

    // Search for 0
    int target = 0;
    int idx = searchRotated(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    // Search for 3 (not present)
    target = 3;
    idx = searchRotated(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    // Search for 5
    target = 5;
    idx = searchRotated(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Find mid point" << endl;
    cout << "  2. Check if left half [lo..mid] is sorted" << endl;
    cout << "  3. If left is sorted AND target in that range -> search left" << endl;
    cout << "  4. Otherwise -> search right" << endl;
    cout << "  5. Same logic if right half is sorted" << endl;
    cout << endl;
    cout << "Time: O(log n)" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
