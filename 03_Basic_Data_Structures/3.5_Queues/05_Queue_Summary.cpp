/*
 * File: 05_Queue_Summary.cpp
 * Topic: All queue types comparison
 * Description: Simple, Circular, Deque, Priority Queue summary
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Queues - Summary ===" << endl;
    cout << endl;

    cout << "--- Simple Queue ---" << endl;
    cout << "Principle:  FIFO (First In, First Out)" << endl;
    cout << "Structure:  Enqueue at rear, dequeue from front" << endl;
    cout << "Problem:    Wasted space at front after dequeues" << endl;
    cout << "Use:        BFS, buffering, task scheduling" << endl;
    cout << endl;

    cout << "--- Circular Queue ---" << endl;
    cout << "Fixes:     Wasted space by wrapping around" << endl;
    cout << "Formula:   index = (index + 1) % capacity" << endl;
    cout << "Use:       Circular buffers, fixed-size queues" << endl;
    cout << endl;

    cout << "--- Deque (Double-Ended Queue) ---" << endl;
    cout << "Feature:   Insert/delete at BOTH ends" << endl;
    cout << "Flexibility: More than normal queue" << endl;
    cout << "Use:       Sliding window, palindrome check" << endl;
    cout << endl;

    cout << "--- Priority Queue ---" << endl;
    cout << "Feature:   Elements come out by PRIORITY, not order" << endl;
    cout << "Max PQ:    Largest element on top (max-heap)" << endl;
    cout << "Min PQ:    Smallest element on top (min-heap)" << endl;
    cout << "Use:       Dijkstra, K-th element, scheduling" << endl;
    cout << endl;

    cout << "--- Complexity ---" << endl;
    cout << "Type         | Enqueue  | Dequeue  | Front/Rear" << endl;
    cout << "-------------|----------|----------|------------" << endl;
    cout << "Simple Queue | O(1)     | O(1)*    | O(1)" << endl;
    cout << "Circular Q   | O(1)     | O(1)     | O(1)" << endl;
    cout << "Deque        | O(1)     | O(1)     | O(1)" << endl;
    cout << "Priority Q   | O(log n) | O(log n) | O(1)" << endl;
    cout << endl;
    cout << "*O(n) with naive array shift, O(1) with two-pointer" << endl;
    cout << endl;

    cout << "--- Queue vs Stack ---" << endl;
    cout << "Stack:  LIFO - push/pop same end" << endl;
    cout << "Queue:  FIFO - enqueue rear, dequeue front" << endl;
    cout << endl;

    cout << "--- Topics Covered in 3.5 ---" << endl;
    cout << "01. Queue Basics           - Simple FIFO queue" << endl;
    cout << "02. Circular Queue         - Wrap-around, reuse space" << endl;
    cout << "03. Deque                  - Double-ended queue" << endl;
    cout << "04. Priority Queue         - Max-heap and Min-heap" << endl;
    cout << "05. Queue Summary          - This file" << endl;

    return 0;
}
