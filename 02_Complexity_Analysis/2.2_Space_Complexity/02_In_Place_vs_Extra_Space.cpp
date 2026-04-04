/*
 * File: 02_In_Place_vs_Extra_Space.cpp
 * Topic: In-place algorithms vs extra space algorithms
 * Description: Compare memory usage of different approaches
 */
#include <iostream>
using namespace std;

// O(1) auxiliary space - IN PLACE
void reverseInPlace(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        // Swap using temp variable (only 1 extra variable)
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

// O(n) auxiliary space - EXTRA SPACE
void reverseWithExtraSpace(int arr[], int n, int result[]) {
    for (int i = 0; i < n; i++) {
        result[i] = arr[n - 1 - i];
    }
}

// Bubble sort: O(1) auxiliary - IN PLACE
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== In-Place vs Extra Space ===" << endl;
    cout << endl;

    // In-place reverse
    int arr1[] = {1, 2, 3, 4, 5};
    int n = 5;

    cout << "--- In-Place Reverse (O(1) space) ---" << endl;
    cout << "Before: ";
    printArray(arr1, n);
    reverseInPlace(arr1, n);
    cout << "After:  ";
    printArray(arr1, n);
    cout << "Only uses 'temp' variable -> O(1) extra space" << endl;
    cout << endl;

    // Extra space reverse
    int arr2[] = {1, 2, 3, 4, 5};
    int result[5];

    cout << "--- Extra Space Reverse (O(n) space) ---" << endl;
    cout << "Original: ";
    printArray(arr2, n);
    reverseWithExtraSpace(arr2, n, result);
    cout << "Reversed: ";
    printArray(result, n);
    cout << "Creates new array of size n -> O(n) extra space" << endl;
    cout << endl;

    // In-place sort
    int arr3[] = {64, 25, 12, 22, 11};
    cout << "--- Bubble Sort (O(1) space) ---" << endl;
    cout << "Before: ";
    printArray(arr3, 5);
    bubbleSort(arr3, 5);
    cout << "After:  ";
    printArray(arr3, 5);
    cout << "Only swaps in place -> O(1) extra space" << endl;

    cout << endl;
    cout << "--- In-Place vs Extra Space Sorting ---" << endl;
    cout << "Algorithm  | Space    | Type" << endl;
    cout << "-----------|----------|----------------" << endl;
    cout << "Bubble     | O(1)     | In-place" << endl;
    cout << "Selection  | O(1)     | In-place" << endl;
    cout << "Insertion  | O(1)     | In-place" << endl;
    cout << "Quick      | O(log n) | In-place (stack)" << endl;
    cout << "Merge      | O(n)     | Extra space" << endl;
    cout << "Heap       | O(1)     | In-place" << endl;

    return 0;
}
