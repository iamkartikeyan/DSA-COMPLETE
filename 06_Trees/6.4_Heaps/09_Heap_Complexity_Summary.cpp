/*
 * File: 09_Heap_Complexity_Summary.cpp
 * Topic: Heap Complexity table and summary
 * Description: All heap operations and when to use
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Heap - Complexity & Summary ===" << endl;
    cout << endl;

    cout << "--- Heap Operations Complexity ---" << endl;
    cout << endl;
    cout << "Operation       | Max-Heap  | Min-Heap" << endl;
    cout << "----------------|-----------|----------" << endl;
    cout << "Insert (push)   | O(log n)  | O(log n)" << endl;
    cout << "Extract (pop)   | O(log n)  | O(log n)" << endl;
    cout << "Get top         | O(1)      | O(1)" << endl;
    cout << "Build heap      | O(n)      | O(n)" << endl;
    cout << "Heap sort       | O(n log n) time, O(1) space" << endl;
    cout << endl;

    cout << "--- STL Priority Queue ---" << endl;
    cout << "priority_queue<int>                   = Max-Heap (default)" << endl;
    cout << "priority_queue<int, vector<int>, greater<int>> = Min-Heap" << endl;
    cout << "Operations: push(), pop(), top(), size(), empty()" << endl;
    cout << endl;

    cout << "--- Common Heap Problems ---" << endl;
    cout << "1.  K-th Smallest/Largest Element" << endl;
    cout << "2.  Merge K Sorted Arrays / Linked Lists" << endl;
    cout << "3.  Top K Frequent Elements" << endl;
    cout << "4.  Median of a Stream" << endl;
    cout << "5.  Running Median" << endl;
    cout << "6.  Sliding Window Maximum" << endl;
    cout << "7.  Task Scheduling with Priority" << endl;
    cout << "8.  Dijkstra's Shortest Path (uses min-heap)" << endl;
    cout << endl;

    cout << "--- Heap Topics Covered ---" << endl;
    cout << "01. Heap Basics               - Structure, array representation" << endl;
    cout << "02. Heapify Up and Down        - Core operations" << endl;
    cout << "03. Heap Insert & Extract      - Push and Pop" << endl;
    cout << "04. Build Heap from Array      - O(n) bottom-up" << endl;
    cout << "05. Heap Sort                  - O(n log n) in-place sort" << endl;
    cout << "06. K-th Smallest/Largest      - Using heap of size k" << endl;
    cout << "07. Merge K Sorted Arrays      - Min-heap merge" << endl;
    cout << "08. Top K Frequent Elements    - Frequency map + min-heap" << endl;
    cout << "09. Complexity Summary         - This file" << endl;

    return 0;
}
