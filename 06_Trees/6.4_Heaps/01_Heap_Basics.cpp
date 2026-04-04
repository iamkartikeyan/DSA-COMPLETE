/*
 * File: 01_Heap_Basics.cpp
 * Topic: What is Heap, Array representation, Max-Heap property
 * Description: Parent/Child index, heap property explanation
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "=== Heap Basics ===" << endl;
    cout << endl;

    cout << "--- What is a Heap? ---" << endl;
    cout << "A heap is a COMPLETE binary tree." << endl;
    cout << "It can be stored in an ARRAY (no need for pointers)." << endl;
    cout << endl;

    cout << "--- Array Index Formulas ---" << endl;
    cout << "Parent(i)  = (i - 1) / 2" << endl;
    cout << "Left(i)    = 2 * i + 1" << endl;
    cout << "Right(i)   = 2 * i + 2" << endl;
    cout << endl;

    cout << "--- Max-Heap Property ---" << endl;
    cout << "Parent >= Left child AND Parent >= Right child" << endl;
    cout << "Root is always the MAXIMUM element." << endl;
    cout << endl;

    cout << "--- Min-Heap Property ---" << endl;
    cout << "Parent <= Left child AND Parent <= Right child" << endl;
    cout << "Root is always the MINIMUM element." << endl;
    cout << endl;

    /*
     * Example Max-Heap as array: [50, 30, 40, 10, 20]
     *
     * Tree form:
     *        50
     *      /    \
     *    30      40
     *   /  \
     *  10   20
     *
     * Check: 50 >= 30, 50 >= 40, 30 >= 10, 30 >= 20
     */

    cout << "--- Example Max-Heap ---" << endl;
    int arr[] = {50, 30, 40, 10, 20};
    int n = 5;

    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << endl;

    cout << "Tree form:" << endl;
    cout << "        50" << endl;
    cout << "      /    \\" << endl;
    cout << "    30      40" << endl;
    cout << "   /  \\" << endl;
    cout << "  10   20" << endl;
    cout << endl;

    // Verify heap property
    bool isMaxHeap = true;
    for (int i = 0; i < n / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && arr[i] < arr[left]) isMaxHeap = false;
        if (right < n && arr[i] < arr[right]) isMaxHeap = false;
    }

    if (isMaxHeap) {
        cout << "This IS a valid Max-Heap." << endl;
    } else {
        cout << "This is NOT a valid Max-Heap." << endl;
    }

    cout << endl;
    cout << "--- STL Priority Queue ---" << endl;
    cout << "priority_queue<int>                 = Max-Heap (default)" << endl;
    cout << "priority_queue<int, vector<int>,    = Min-Heap" << endl;
    cout << "         greater<int>>" << endl;
    cout << endl;
    cout << "Operations:" << endl;
    cout << "  push()  - Insert element" << endl;
    cout << "  pop()   - Remove top element" << endl;
    cout << "  top()   - Get top element (O(1))" << endl;
    cout << "  size()  - Get size" << endl;
    cout << "  empty() - Check if empty" << endl;

    return 0;
}
