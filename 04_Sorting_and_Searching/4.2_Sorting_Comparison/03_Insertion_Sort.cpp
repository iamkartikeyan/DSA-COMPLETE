/*
 * File: 03_Insertion_Sort.cpp
 * Topic: Insertion Sort - Build sorted portion by inserting
 * Description: Like sorting cards in your hand
 */
#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // element to insert
        int j = i - 1;

        // Shift elements greater than key to the right
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // Insert key at correct position
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Insertion Sort ===" << endl;
    cout << endl;

    int arr[] = {64, 25, 12, 22, 11, 90, 15};
    int n = 7;

    cout << "Before: ";
    printArray(arr, n);

    insertionSort(arr, n);

    cout << "After:  ";
    printArray(arr, n);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Start from second element (i=1)" << endl;
    cout << "  2. Pick current element as 'key'" << endl;
    cout << "  3. Shift all greater elements one position right" << endl;
    cout << "  4. Insert key at correct position" << endl;
    cout << "  5. Move to next element" << endl;
    cout << endl;

    /*
     * Step 1: [25 64] 12 22 11 90 15  (inserted 25)
     * Step 2: [12 25 64] 22 11 90 15  (inserted 12)
     * Step 3: [12 22 25 64] 11 90 15  (inserted 22)
     * Step 4: [11 12 22 25 64] 90 15  (inserted 11)
     * Step 5: [11 12 22 25 64 90] 15  (inserted 90)
     * Step 6: [11 12 15 22 25 64 90]  (inserted 15)
     */

    cout << "Time: O(n^2) worst, O(n) best (already sorted)" << endl;
    cout << "Space: O(1) - in-place" << endl;
    cout << "Stable: Yes" << endl;
    cout << "Use: Small arrays, nearly-sorted data, online sorting" << endl;
    cout << "     Best practical O(n^2) algorithm!" << endl;

    return 0;
}
