/*
 * File: 02_Selection_Sort.cpp
 * Topic: Selection Sort - Find minimum, swap to front
 * Description: Builds sorted portion from left to right
 */
#include <iostream>
using namespace std;

void swapVal(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Find minimum element in unsorted part
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        // Swap minimum to position i
        if (minIdx != i) {
            swapVal(arr[i], arr[minIdx]);
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
    cout << "=== Selection Sort ===" << endl;
    cout << endl;

    int arr[] = {64, 25, 12, 22, 11, 90, 15};
    int n = 7;

    cout << "Before: ";
    printArray(arr, n);

    selectionSort(arr, n);

    cout << "After:  ";
    printArray(arr, n);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Find the minimum element in unsorted part" << endl;
    cout << "  2. Swap it with the first unsorted position" << endl;
    cout << "  3. Move boundary one step right" << endl;
    cout << "  4. Repeat until entire array is sorted" << endl;
    cout << endl;

    /*
     * Pass 1: Find 11, swap with 64 -> [11 25 12 22 64 90 15]
     * Pass 2: Find 12, swap with 25 -> [11 12 25 22 64 90 15]
     * Pass 3: Find 15, swap with 25 -> [11 12 15 22 64 90 25]
     * ...
     */

    cout << "Time: O(n^2) always (even if already sorted)" << endl;
    cout << "Space: O(1) - in-place" << endl;
    cout << "Swaps: O(n) - only 1 swap per pass (MINIMUM swaps!)" << endl;
    cout << "Stable: No (swapping can change order of equal elements)" << endl;
    cout << "Use: When writes/swaps are expensive" << endl;

    return 0;
}
