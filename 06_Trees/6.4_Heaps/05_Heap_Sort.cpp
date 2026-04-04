/*
 * File: 05_Heap_Sort.cpp
 * Topic: Heap Sort Algorithm
 * Description: Sort using max-heap, O(n log n) time, O(1) space
 */
#include <iostream>
#include <vector>
using namespace std;

void swapVal(vector<int>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Heapify a subtree rooted at index i
// n = size of heap (not array size)
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swapVal(arr, i, largest);
        heapify(arr, n, largest); // recursive call
    }
}

// Heap Sort
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Step 1: Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Step 2: Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current max to end
        swapVal(arr, 0, i);
        // Heapify the reduced heap (size = i)
        heapify(arr, i, 0);
    }
}

void printArray(vector<int>& arr, string label) {
    cout << label;
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Heap Sort ===" << endl;
    cout << endl;

    vector<int> arr;
    arr.push_back(64);
    arr.push_back(25);
    arr.push_back(12);
    arr.push_back(22);
    arr.push_back(11);
    arr.push_back(90);

    printArray(arr, "Original:  ");

    heapSort(arr);

    printArray(arr, "Sorted:    ");

    cout << endl;
    cout << "--- How Heap Sort Works ---" << endl;
    cout << "Step 1: Build max heap from array" << endl;
    cout << "Step 2: Swap root (max) with last element" << endl;
    cout << "Step 3: Reduce heap size by 1" << endl;
    cout << "Step 4: Heapify the root" << endl;
    cout << "Step 5: Repeat until heap size = 1" << endl;
    cout << endl;

    cout << "--- Complexity ---" << endl;
    cout << "Time:  O(n log n) - always (best, average, worst)" << endl;
    cout << "Space: O(1) - in-place sorting" << endl;
    cout << "Stable: No - order of equal elements may change" << endl;
    cout << endl;
    cout << "Note: Not used much in practice (Quick Sort is faster on average)" << endl;
    cout << "But guaranteed O(n log n) unlike Quick Sort's O(n^2) worst case" << endl;

    return 0;
}
