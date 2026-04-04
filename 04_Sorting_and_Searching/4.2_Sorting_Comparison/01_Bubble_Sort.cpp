/*
 * File: 01_Bubble_Sort.cpp
 * Topic: Bubble Sort - Swap adjacent out-of-order elements
 * Description: Largest element "bubbles" to end each pass
 */
#include <iostream>
using namespace std;

void swapVal(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; // optimization: stop if already sorted

        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swapVal(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no swaps happened, array is sorted
        if (swapped == false) {
            break;
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Bubble Sort ===" << endl;
    cout << endl;

    int arr[] = {64, 25, 12, 22, 11, 90, 15};
    int n = 7;

    cout << "Before: ";
    printArray(arr, n);

    bubbleSort(arr, n);

    cout << "After:  ";
    printArray(arr, n);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Compare adjacent elements" << endl;
    cout << "  2. If left > right -> swap them" << endl;
    cout << "  3. After each pass, largest unsorted element reaches end" << endl;
    cout << "  4. If no swaps in a pass -> array is sorted, stop early" << endl;
    cout << endl;

    /*
     * Pass 1: [25 12 22 11 64 15 90]  (90 bubbled to end)
     * Pass 2: [12 22 11 25 15 64 90]  (64 bubbled)
     * Pass 3: [12 11 22 15 25 64 90]  (25 bubbled)
     * Pass 4: [11 12 15 22 25 64 90]  (sorted!)
     * Pass 5: No swaps -> stop
     */

    cout << "Time: O(n^2) worst/avg, O(n) best (already sorted)" << endl;
    cout << "Space: O(1) - in-place" << endl;
    cout << "Stable: Yes (equal elements keep their order)" << endl;
    cout << "Use: Educational, tiny or nearly-sorted arrays" << endl;

    return 0;
}
