/*
 * File: 04_Priority_Queue.cpp
 * Topic: Priority Queue - Elements with priority, highest/lowest comes out first
 * Description: Max-heap and Min-heap based priority queue
 */
#include <iostream>
#include <queue>
using namespace std;

int main() {
    cout << "=== Priority Queue ===" << endl;
    cout << endl;

    // --- Max Priority Queue (default) ---
    cout << "--- Max Priority Queue ---" << endl;
    priority_queue<int> maxPq;

    maxPq.push(10);
    maxPq.push(30);
    maxPq.push(20);
    maxPq.push(50);
    maxPq.push(40);

    cout << "Pushed: 10, 30, 20, 50, 40" << endl;
    cout << "Top (max): " << maxPq.top() << endl;
    cout << endl;

    cout << "Popping all (descending order):" << endl;
    while (maxPq.empty() == false) {
        cout << "  " << maxPq.top();
        maxPq.pop();
    }
    cout << endl;
    cout << endl;

    // --- Min Priority Queue ---
    cout << "--- Min Priority Queue ---" << endl;
    priority_queue<int, vector<int>, greater<int> > minPq;

    minPq.push(10);
    minPq.push(30);
    minPq.push(20);
    minPq.push(50);
    minPq.push(40);

    cout << "Pushed: 10, 30, 20, 50, 40" << endl;
    cout << "Top (min): " << minPq.top() << endl;
    cout << endl;

    cout << "Popping all (ascending order):" << endl;
    while (minPq.empty() == false) {
        cout << "  " << minPq.top();
        minPq.pop();
    }
    cout << endl;

    cout << endl;
    cout << "--- Priority Queue Properties ---" << endl;
    cout << "Elements are ordered by PRIORITY (value)." << endl;
    cout << "Max PQ: largest element always on top." << endl;
    cout << "Min PQ: smallest element always on top." << endl;
    cout << endl;
    cout << "Implemented using HEAP (not linked list)." << endl;
    cout << "Max PQ = Max-Heap, Min PQ = Min-Heap" << endl;
    cout << endl;
    cout << "push(x)    - O(log n)" << endl;
    cout << "pop()      - O(log n)" << endl;
    cout << "top()      - O(1)" << endl;
    cout << "empty()    - O(1)" << endl;
    cout << "size()     - O(1)" << endl;
    cout << endl;
    cout << "Use: Dijkstra's algorithm, Huffman coding," << endl;
    cout << "     K-th largest/smallest, task scheduling" << endl;

    return 0;
}
