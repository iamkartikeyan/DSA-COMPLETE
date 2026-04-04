/*
 * File: 02_Binary_Search.cpp
 * Topic: Binary Search - Iterative and Recursive
 * Description: Halve search space each step, requires sorted array
 */
#include <iostream>
using namespace std;

// Iterative Binary Search
int binarySearch(int arr[], int n, int target) {
    int lo = 0;
    int hi = n - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2; // avoids overflow

        if (arr[mid] == target) {
            return mid; // found
        }
        else if (arr[mid] < target) {
            lo = mid + 1; // target in right half
        }
        else {
            hi = mid - 1; // target in left half
        }
    }
    return -1; // not found
}

// Recursive Binary Search
int binarySearchRec(int arr[], int lo, int hi, int target) {
    // Base case: not found
    if (lo > hi) {
        return -1;
    }

    int mid = lo + (hi - lo) / 2;

    if (arr[mid] == target) {
        return mid; // found
    }
    else if (arr[mid] < target) {
        return binarySearchRec(arr, mid + 1, hi, target); // search right
    }
    else {
        return binarySearchRec(arr, lo, mid - 1, target); // search left
    }
}

int main() {
    cout << "=== Binary Search ===" << endl;
    cout << endl;

    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = 10;

    cout << "Array: 2 5 8 12 16 23 38 56 72 91" << endl;
    cout << endl;

    // Iterative search
    int target = 23;
    cout << "--- Iterative Binary Search ---" << endl;
    int idx = binarySearch(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    // Recursive search
    cout << endl;
    cout << "--- Recursive Binary Search ---" << endl;
    idx = binarySearchRec(arr, 0, n - 1, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Find middle element" << endl;
    cout << "  2. If target == middle -> found" << endl;
    cout << "  3. If target > middle -> search right half" << endl;
    cout << "  4. If target < middle -> search left half" << endl;
    cout << "  5. Repeat until found or range is empty" << endl;
    cout << endl;
    cout << "Time: O(log n) - halves search space each step" << endl;
    cout << "Space: O(1) iterative, O(log n) recursive (call stack)" << endl;
    cout << "Requires: SORTED array" << endl;
    cout << endl;
    cout << "Note: mid = lo + (hi-lo)/2 prevents integer overflow" << endl;

    return 0;
}
