/*
 * File: 01_Counting_Sort.cpp
 * Topic: Counting Sort - Count frequencies, build output
 * Description: O(n + k) sort for integers with small range
 */
#include <iostream>
using namespace std;

void countingSort(int arr[], int n) {
    if (n <= 0) return;

    // Find min and max to handle negative numbers
    int minVal = arr[0];
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    int range = maxVal - minVal + 1;

    // Count frequency of each element
    int* count = new int[range];
    for (int i = 0; i < range; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        count[arr[i] - minVal]++;
    }

    // Cumulative sum: count[i] = position of last occurrence
    for (int i = 1; i < range; i++) {
        count[i] = count[i] + count[i - 1];
    }

    // Build output array (iterate backwards for stability)
    int* output = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    // Copy back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Counting Sort ===" << endl;
    cout << endl;

    int arr[] = {4, 2, 2, 8, 3, 3, 1, 5, 1};
    int n = 9;

    cout << "Before: ";
    printArray(arr, n);

    countingSort(arr, n);

    cout << "After:  ";
    printArray(arr, n);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Count frequency of each value" << endl;
    cout << "  2. Compute cumulative count (position in output)" << endl;
    cout << "  3. Place elements in output array (backwards for stability)" << endl;
    cout << "  4. Copy output back to original array" << endl;
    cout << endl;

    /*
     * Example: [4, 2, 2, 8, 3, 3, 1, 5, 1]
     * Min = 1, Max = 8, Range = 8
     *
     * Count:  [2, 2, 2, 1, 1, 0, 0, 1]  (for values 1-8)
     * Cumul:  [2, 4, 6, 7, 8, 8, 8, 9]
     * Output: [1, 1, 2, 2, 3, 3, 4, 5, 8]
     */

    cout << "Time: O(n + k) where k = range of values" << endl;
    cout << "Space: O(n + k) for count and output arrays" << endl;
    cout << "Stable: Yes" << endl;
    cout << "Use: When range (k) is small compared to n" << endl;
    cout << "     Example: sorting ages (0-120), grades (0-100)" << endl;
    cout << "Limitation: Only works for integer keys" << endl;

    return 0;
}
