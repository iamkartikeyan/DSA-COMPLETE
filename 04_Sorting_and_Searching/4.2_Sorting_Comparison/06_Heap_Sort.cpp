/*
 * File: 06_Heap_Sort.cpp
 * Topic: Heap Sort - Build max-heap, extract max
 * Description: Guaranteed O(n log n), in-place, not stable
 */
#include <iostream>
using namespace std;

void swapVal(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Heapify subtree rooted at index i
// n = size of heap
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check if left child is larger
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Check if right child is larger
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root, swap and continue
    if (largest != i) {
        swapVal(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Step 1: Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Step 2: Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current max (root) to end
        swapVal(arr[0], arr[i]);

        // Heapify the reduced heap
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Heap Sort ===" << endl;
    cout << endl;

    int arr[] = {64, 25, 12, 22, 11, 90, 15};
    int n = 7;

    cout << "Before: ";
    printArray(arr, n);

    heapSort(arr, n);

    cout << "After:  ";
    printArray(arr, n);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Build max heap from array" << endl;
    cout << "  2. Root (max element) is at index 0" << endl;
    cout << "  3. Swap root with last element" << endl;
    cout << "  4. Reduce heap size by 1" << endl;
    cout << "  5. Heapify the root" << endl;
    cout << "  6. Repeat until heap size = 1" << endl;
    cout << endl;

    /*
     * After build heap: [90 64 15 22 11 12 25]
     * Extract 90: [25 64 15 22 11 12 | 90]
     * Extract 64: [25 22 15 12 11 | 64 90]
     * Extract 25: [22 12 15 11 | 25 64 90]
     * ...
     */

    cout << "Time: O(n log n) ALWAYS" << endl;
    cout << "Space: O(1) - in-place" << endl;
    cout << "Stable: No" << endl;
    cout << "Use: When guaranteed O(n log n) + in-place needed" << endl;
    cout << "     Also basis for priority queues" << endl;

    return 0;
}
