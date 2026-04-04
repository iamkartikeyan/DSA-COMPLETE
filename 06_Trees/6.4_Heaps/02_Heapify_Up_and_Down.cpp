/*
 * File: 02_Heapify_Up_and_Down.cpp
 * Topic: Heapify Up (after insert) and Heapify Down (after delete)
 * Description: The two core heap operations
 */
#include <iostream>
#include <vector>
using namespace std;

// Swap two elements
void swapVal(vector<int>& h, int i, int j) {
    int temp = h[i];
    h[i] = h[j];
    h[j] = temp;
}

// Heapify Up: used after insertion
// Compare with parent, swap if bigger, repeat
void heapifyUp(vector<int>& h, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h[i] <= h[parent]) {
            break; // heap property satisfied
        }
        swapVal(h, i, parent);
        i = parent; // move up
    }
}

// Heapify Down: used after deletion
// Compare with children, swap with larger child, repeat
void heapifyDown(vector<int>& h, int i) {
    int n = h.size();
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && h[left] > h[largest]) {
            largest = left;
        }
        if (right < n && h[right] > h[largest]) {
            largest = right;
        }
        if (largest == i) {
            break; // heap property satisfied
        }
        swapVal(h, i, largest);
        i = largest; // move down
    }
}

void printHeap(vector<int>& h) {
    for (int i = 0; i < h.size(); i++) {
        cout << h[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Heapify Up & Down ===" << endl;
    cout << endl;

    // --- Heapify Up Demo ---
    cout << "--- Heapify Up (after insert) ---" << endl;
    vector<int> heap1;

    cout << "Insert 50: ";
    heap1.push_back(50);
    heapifyUp(heap1, 0);
    printHeap(heap1);

    cout << "Insert 30: ";
    heap1.push_back(30);
    heapifyUp(heap1, 1);
    printHeap(heap1);

    cout << "Insert 70: ";
    heap1.push_back(70);
    heapifyUp(heap1, 2);
    printHeap(heap1);

    cout << "Insert 10: ";
    heap1.push_back(10);
    heapifyUp(heap1, 3);
    printHeap(heap1);

    cout << "Insert 40: ";
    heap1.push_back(40);
    heapifyUp(heap1, 4);
    printHeap(heap1);

    cout << endl;

    // --- Heapify Down Demo ---
    cout << "--- Heapify Down (after delete root) ---" << endl;
    vector<int> heap2;
    heap2.push_back(50);
    heap2.push_back(40);
    heap2.push_back(30);
    heap2.push_back(20);
    heap2.push_back(10);

    cout << "Before: ";
    printHeap(heap2);

    cout << "Extract max (50)..." << endl;
    // Swap root with last
    swapVal(heap2, 0, heap2.size() - 1);
    heap2.pop_back(); // remove old root
    // Heapify down from root
    heapifyDown(heap2, 0);

    cout << "After:  ";
    printHeap(heap2);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "Heapify Up:" << endl;
    cout << "  1. Insert at end of array" << endl;
    cout << "  2. Compare with parent" << endl;
    cout << "  3. If child > parent -> swap" << endl;
    cout << "  4. Repeat until heap property satisfied" << endl;
    cout << endl;
    cout << "Heapify Down:" << endl;
    cout << "  1. Replace root with last element" << endl;
    cout << "  2. Compare with both children" << endl;
    cout << "  3. Swap with LARGER child" << endl;
    cout << "  4. Repeat until heap property satisfied" << endl;
    cout << endl;
    cout << "Time: O(log n) for both operations" << endl;

    return 0;
}
