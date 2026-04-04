/*
 * File: 04_Common_Space_Complexity_Examples.cpp
 * Topic: Space complexity of common algorithms and data structures
 * Description: Quick reference for space usage
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Space Complexity Examples ===" << endl;
    cout << endl;

    cout << "--- Sorting Algorithms ---" << endl;
    cout << "Bubble Sort:   O(1)       - swaps in place" << endl;
    cout << "Selection Sort: O(1)      - swaps in place" << endl;
    cout << "Insertion Sort: O(1)      - shifts in place" << endl;
    cout << "Quick Sort:    O(log n)   - recursion stack" << endl;
    cout << "Merge Sort:    O(n)       - temporary array" << endl;
    cout << "Heap Sort:     O(1)       - in-place heapify" << endl;
    cout << endl;

    cout << "--- Searching Algorithms ---" << endl;
    cout << "Linear Search: O(1)        - no extra space" << endl;
    cout << "Binary Search (iterative): O(1)  - two pointers" << endl;
    cout << "Binary Search (recursive): O(log n) - stack depth" << endl;
    cout << endl;

    cout << "--- Data Structures ---" << endl;
    cout << "Array:         O(1) extra   - fixed size" << endl;
    cout << "Linked List:   O(n) total   - each node has pointer" << endl;
    cout << "Stack:         O(n) total   - array or linked list" << endl;
    cout << "Queue:         O(n) total   - array or linked list" << endl;
    cout << "Hash Table:    O(n) total   - buckets array" << endl;
    cout << "Binary Tree:   O(n) total   - nodes with pointers" << endl;
    cout << endl;

    cout << "--- Common Patterns ---" << endl;
    cout << "Two Pointers:       O(1)      - just two indices" << endl;
    cout << "Sliding Window:     O(1)      - just window boundaries" << endl;
    cout << "Hash Map:           O(n)      - stores all elements" << endl;
    cout << "Recursion:          O(depth)  - call stack" << endl;
    cout << "DP Array/Table:     O(n) or O(n^2) - stored results" << endl;
    cout << "Adjacency Matrix:   O(n^2)    - graph representation" << endl;
    cout << "Adjacency List:     O(n + e)  - graph (n nodes, e edges)" << endl;
    cout << endl;

    cout << "--- Space-Time Tradeoff ---" << endl;
    cout << "Sometimes we use MORE space to get LESS time:" << endl;
    cout << "  - Hash table: O(n) space -> O(1) search" << endl;
    cout << "  - Memoization: O(n) space -> avoids recomputation" << endl;
    cout << "  - Counting sort: O(k) space -> O(n+k) time" << endl;

    return 0;
}
