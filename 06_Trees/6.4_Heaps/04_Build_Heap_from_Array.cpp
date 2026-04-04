/*
 * File: 04_Build_Heap_from_Array.cpp
 * Topic: Build a heap from an unsorted array in O(n)
 * Description: Bottom-up heapify starting from last non-leaf node
 */
#include <iostream>
#include <vector>
using namespace std;

void swapVal(vector<int>& h, int i, int j) {
    int temp = h[i];
    h[i] = h[j];
    h[j] = temp;
}

// Heapify down
void heapifyDown(vector<int>& h, int i, int n) {
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && h[left] > h[largest]) largest = left;
        if (right < n && h[right] > h[largest]) largest = right;
        if (largest == i) break;
        swapVal(h, i, largest);
        i = largest;
    }
}

// Build Max-Heap from array in O(n)
void buildHeap(vector<int>& arr) {
    int n = arr.size();
    // Start from last non-leaf node and go up to root
    // Last non-leaf node is at index (n/2 - 1)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(arr, i, n);
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
    cout << "=== Build Heap from Array ===" << endl;
    cout << endl;

    vector<int> arr;
    arr.push_back(3);
    arr.push_back(1);
    arr.push_back(4);
    arr.push_back(1);
    arr.push_back(5);
    arr.push_back(9);
    arr.push_back(2);
    arr.push_back(6);

    printArray(arr, "Original array: ");

    buildHeap(arr);

    printArray(arr, "After buildHeap:  ");

    cout << endl;

    /*
     * The buildHeap process:
     * Start from index n/2-1 (last non-leaf node)
     * Heapify each node going backwards to root
     *
     * Time = O(n) (not O(n log n)!)
     * Why? Most nodes are near leaves and need few swaps
     */

    cout << "How it works:" << endl;
    cout << "  1. Find last non-leaf node at index (n/2 - 1)" << endl;
    cout << "  2. Heapify that node (push it down if needed)" << endl;
    cout << "  3. Move to previous node, repeat" << endl;
    cout << "  4. Continue until root is heapified" << endl;
    cout << endl;
    cout << "Time: O(n) - faster than inserting one by one O(n log n)" << endl;
    cout << "Why? Bottom nodes need very few swaps to fix" << endl;

    return 0;
}
