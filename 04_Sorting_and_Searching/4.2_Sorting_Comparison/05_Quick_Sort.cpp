/*
 * File: 05_Quick_Sort.cpp
 * Topic: Quick Sort - Pick pivot, partition, recurse
 * Description: Fastest in practice, in-place but not stable
 */
#include <iostream>
using namespace std;

void swapVal(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition: put elements <= pivot on left, > pivot on right
int partition(int arr[], int lo, int hi) {
    int pivot = arr[hi]; // choose last element as pivot
    int i = lo - 1;      // index of smaller element

    for (int j = lo; j < hi; j++) {
        if (arr[j] <= pivot) {
            i = i + 1;
            swapVal(arr[i], arr[j]);
        }
    }

    // Place pivot in correct position
    swapVal(arr[i + 1], arr[hi]);
    return i + 1; // return pivot index
}

// Recursive quick sort
void quickSort(int arr[], int lo, int hi) {
    if (lo < hi) {
        // Get pivot index
        int pi = partition(arr, lo, hi);

        // Sort elements before and after pivot
        quickSort(arr, lo, pi - 1);
        quickSort(arr, pi + 1, hi);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Quick Sort ===" << endl;
    cout << endl;

    int arr[] = {64, 25, 12, 22, 11, 90, 15};
    int n = 7;

    cout << "Before: ";
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    cout << "After:  ";
    printArray(arr, n);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Pick a pivot (here: last element)" << endl;
    cout << "  2. Partition: move smaller elements to left of pivot" << endl;
    cout << "  3. Pivot is now in its final sorted position" << endl;
    cout << "  4. Recursively sort left and right of pivot" << endl;
    cout << endl;

    /*
     * Example with pivot=15:
     * [64 25 12 22 11 90 15]
     * Partition around 15:
     * [12 11] 15 [25 64 90 22]
     *        ^ pivot in correct position
     *
     * Then sort [12 11] and [25 64 90 22] recursively
     */

    cout << "Time: O(n log n) average, O(n^2) worst (already sorted + bad pivot)" << endl;
    cout << "Space: O(log n) - call stack" << endl;
    cout << "Stable: No (partitioning changes order)" << endl;
    cout << "Use: General purpose, best in practice" << endl;
    cout << "     Used in C++ std::sort (hybrid with introsort)" << endl;

    return 0;
}
