/*
 * File: 02_Radix_Sort.cpp
 * Topic: Radix Sort - Sort digit by digit using counting sort
 * Description: Handles large integer ranges efficiently
 */
#include <iostream>
using namespace std;

int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > mx) {
            mx = arr[i];
        }
    }
    return mx;
}

// Counting sort based on a specific digit
// exp = 1 (ones), 10 (tens), 100 (hundreds), ...
void countingSortByDigit(int arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0}; // digits 0-9

    // Count occurrences of each digit
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Cumulative count
    for (int i = 1; i < 10; i++) {
        count[i] = count[i] + count[i - 1];
    }

    // Build output (backwards for stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy back
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] output;
}

void radixSort(int arr[], int n) {
    if (n <= 0) return;

    int mx = getMax(arr, n);

    // Apply counting sort for each digit position
    for (int exp = 1; mx / exp > 0; exp = exp * 10) {
        countingSortByDigit(arr, n, exp);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Radix Sort ===" << endl;
    cout << endl;

    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = 8;

    cout << "Before: ";
    printArray(arr, n);

    radixSort(arr, n);

    cout << "After:  ";
    printArray(arr, n);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Find maximum number (to know number of digits)" << endl;
    cout << "  2. Sort by ones digit using counting sort" << endl;
    cout << "  3. Sort by tens digit using counting sort" << endl;
    cout << "  4. Sort by hundreds digit using counting sort" << endl;
    cout << "  5. Continue until all digits processed" << endl;
    cout << endl;

    /*
     * After ones digit:   [170, 90, 802, 2, 24, 45, 75, 66]
     * After tens digit:   [802, 2, 24, 45, 66, 170, 75, 90]
     * After hundreds:     [2, 24, 45, 66, 75, 90, 170, 802]
     */

    cout << "Time: O(d * (n + b)) where d = digits, b = base (10)" << endl;
    cout << "Space: O(n + b) for counting sort" << endl;
    cout << "Stable: Yes (counting sort is stable)" << endl;
    cout << "Use: Large integer range where counting sort uses too much memory" << endl;
    cout << "     Example: phone numbers, large IDs" << endl;

    return 0;
}
