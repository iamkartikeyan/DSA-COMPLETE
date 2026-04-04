/*
 * File: 02_Aggregate_Method.cpp
 * Topic: Aggregate Method - Total cost divided by n operations
 * Description: Simplest amortized analysis technique
 */
#include <iostream>
using namespace std;

// Simple dynamic array to demonstrate
class DynamicArray {
    int* data;
    int capacity;
    int size;

    void resize() {
        capacity = capacity * 2;
        int* newData = new int[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    DynamicArray(int cap) {
        capacity = cap;
        size = 0;
        data = new int[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    // Push back with resize tracking
    void push(int val) {
        if (size == capacity) {
            resize(); // O(n) occasionally
        }
        data[size] = val;
        size++;
    }

    int getSize() { return size; }
    int getCapacity() { return capacity; }
};

int main() {
    cout << "=== Aggregate Method ===" << endl;
    cout << endl;

    /*
     * Theorem: n insertions into empty dynamic array costs O(n) total.
     *
     * Proof:
     * Resize happens at sizes: 1, 2, 4, 8, ..., n/2
     * Copy cost at each resize: 1 + 2 + 4 + 8 + ... + n/2
     * This is a geometric series = n - 1
     * Plus n insertions (1 each) = n
     * Total = n + (n - 1) = 2n - 1 = O(n)
     * Amortized = O(n) / n = O(1)
     */

    cout << "--- Demonstrating with n=16 inserts ---" << endl;
    cout << endl;

    DynamicArray arr(1);
    int totalOps = 0;

    cout << "Resize happens at: 1, 2, 4, 8" << endl;
    cout << "(powers of 2, where array doubles)" << endl;
    cout << endl;

    // Calculate total copy cost
    int totalCopies = 0;
    int n = 16;
    cout << "Copy cost breakdown:" << endl;
    for (int i = 1; i < n; i = i * 2) {
        cout << "  Resize at " << i << ": copied " << i << " elements" << endl;
        totalCopies = totalCopies + i;
    }

    cout << "Total copies: " << totalCopies << endl;
    cout << "Total inserts: " << n << endl;
    cout << "Total work: " << n << " + " << totalCopies << " = " << (n + totalCopies) << endl;
    cout << "Amortized per insert: " << (n + totalCopies) << " / " << n << " = " << ((double)(n + totalCopies) / n) << endl;

    cout << endl;
    cout << "--- Key Formula ---" << endl;
    cout << "Geometric series: 1 + 2 + 4 + 8 + ... + n/2 = n - 1" << endl;
    cout << "Total = n inserts + (n-1) copies = 2n - 1 = O(n)" << endl;
    cout << "Amortized = O(n) / n = O(1) per operation" << endl;
    cout << endl;
    cout << "This proves push_back is O(1) AMORTIZED," << endl;
    cout << "even though worst case is O(n) for resize." << endl;

    return 0;
}
