/*
 * File: 04_Merge_Sort.cpp
 * Topic: Merge Sort - Divide, sort halves, merge
 * Description: Guaranteed O(n log n), stable, uses extra space
 */
#include <iostream>
using namespace std;

// Merge two sorted halves [lo..mid] and [mid+1..hi]
void merge(int arr[], int lo, int mid, int hi) {
    int n1 = mid - lo + 1;
    int n2 = hi - mid;

    // Create temporary arrays
    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[lo + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    // Merge back into original array
    int i = 0, j = 0, k = lo;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i = i + 1;
        } else {
            arr[k] = rightArr[j];
            j = j + 1;
        }
        k = k + 1;
    }

    // Copy remaining elements
    while (i < n1) {
        arr[k] = leftArr[i];
        i = i + 1;
        k = k + 1;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j = j + 1;
        k = k + 1;
    }

    delete[] leftArr;
    delete[] rightArr;
}

// Recursive merge sort
void mergeSort(int arr[], int lo, int hi) {
    if (lo >= hi) {
        return; // base case: single element
    }

    int mid = lo + (hi - lo) / 2;
    mergeSort(arr, lo, mid);      // sort left half
    mergeSort(arr, mid + 1, hi);  // sort right half
    merge(arr, lo, mid, hi);      // merge both halves
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Merge Sort ===" << endl;
    cout << endl;

    int arr[] = {64, 25, 12, 22, 11, 90, 15};
    int n = 7;

    cout << "Before: ";
    printArray(arr, n);

    mergeSort(arr, 0, n - 1);

    cout << "After:  ";
    printArray(arr, n);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Divide array into two halves" << endl;
    cout << "  2. Recursively sort each half" << endl;
    cout << "  3. Merge the two sorted halves" << endl;
    cout << endl;

    /*
     * Divide phase:
     * [64 25 12 22 11 90 15]
     * -> [64 25 12] [22 11 90 15]
     * -> [64] [25 12] [22 11] [90 15]
     * -> [64] [25] [12] [22] [11] [90] [15]
     *
     * Merge phase:
     * -> [25 12 64] [11 22 15 90]
     * -> [11 12 15 22 25 64 90]
     */

    cout << "Time: O(n log n) ALWAYS (best, avg, worst)" << endl;
    cout << "Space: O(n) - needs temporary arrays for merge" << endl;
    cout << "Stable: Yes (uses <= in merge)" << endl;
    cout << "Use: When stability needed, external sorting," << endl;
    cout << "     guaranteed O(n log n), linked lists" << endl;

    return 0;
}
