/*
 * File: 03_Heap_Insert_Extract.cpp
 * Topic: Insert and Extract-Max/Min operations
 * Description: Complete heap push and pop operations
 */
#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
    vector<int> h;

    void swapVal(int i, int j) {
        int temp = h[i];
        h[i] = h[j];
        h[j] = temp;
    }

    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (h[i] <= h[parent]) break;
            swapVal(i, parent);
            i = parent;
        }
    }

    void heapifyDown(int i) {
        int n = h.size();
        while (true) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < n && h[left] > h[largest]) largest = left;
            if (right < n && h[right] > h[largest]) largest = right;
            if (largest == i) break;
            swapVal(i, largest);
            i = largest;
        }
    }

public:
    // Insert: add at end, then heapify up
    void push(int val) {
        h.push_back(val);
        heapifyUp(h.size() - 1);
    }

    // Extract max: swap root with last, remove, heapify down
    int pop() {
        if (h.empty()) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        int top = h[0];
        h[0] = h.back();
        h.pop_back();
        if (h.empty() == false) {
            heapifyDown(0);
        }
        return top;
    }

    // Get max without removing
    int top() {
        if (h.empty()) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        return h[0];
    }

    bool empty() {
        return h.empty();
    }

    int size() {
        return h.size();
    }

    void printHeap() {
        for (int i = 0; i < h.size(); i++) {
            cout << h[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Heap Insert & Extract ===" << endl;
    cout << endl;

    MaxHeap mh;

    // Insert elements
    cout << "--- Insert ---" << endl;
    int values[] = {10, 30, 20, 50, 40};
    int n = 5;

    for (int i = 0; i < n; i++) {
        cout << "Push " << values[i] << " -> ";
        mh.push(values[i]);
        mh.printHeap();
    }

    cout << endl;
    cout << "Heap size: " << mh.size() << endl;
    cout << "Heap top (max): " << mh.top() << endl;

    cout << endl;
    cout << "--- Extract Max ---" << endl;

    while (mh.empty() == false) {
        cout << "Pop " << mh.pop() << " -> ";
        mh.printHeap();
    }

    cout << endl;
    cout << "Elements extracted in descending order!" << endl;
    cout << "This is the heap property: largest always on top." << endl;
    cout << endl;
    cout << "Time: Insert = O(log n), Extract = O(log n), Top = O(1)" << endl;

    return 0;
}
