/*
 * File: 06_Kth_Smallest_Largest.cpp
 * Topic: Find K-th smallest and K-th largest element
 * Description: Using heap to find K-th element in O(n log k)
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// K-th smallest using max-heap of size k
// Keep smallest k elements in heap, top is k-th smallest
int kthSmallest(vector<int>& arr, int k) {
    // Max-heap: stores k smallest elements seen so far
    priority_queue<int> pq;

    for (int i = 0; i < arr.size(); i++) {
        pq.push(arr[i]);
        // If heap has more than k elements, remove largest
        if (pq.size() > k) {
            pq.pop();
        }
    }

    // Top of heap = k-th smallest
    return pq.top();
}

// K-th largest using min-heap of size k
// Keep largest k elements in heap, top is k-th largest
int kthLargest(vector<int>& arr, int k) {
    // Min-heap: stores k largest elements seen so far
    priority_queue<int, vector<int>, greater<int> > pq;

    for (int i = 0; i < arr.size(); i++) {
        pq.push(arr[i]);
        // If heap has more than k elements, remove smallest
        if (pq.size() > k) {
            pq.pop();
        }
    }

    // Top of heap = k-th largest
    return pq.top();
}

int main() {
    cout << "=== K-th Smallest / Largest ===" << endl;
    cout << endl;

    vector<int> arr;
    arr.push_back(7);
    arr.push_back(10);
    arr.push_back(4);
    arr.push_back(3);
    arr.push_back(20);
    arr.push_back(15);

    cout << "Array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Sorted: 3, 4, 7, 10, 15, 20

    int k = 3;
    cout << "--- K = " << k << " ---" << endl;
    cout << k << "-th smallest: " << kthSmallest(arr, k) << endl;
    cout << k << "-th largest:  " << kthLargest(arr, k) << endl;

    cout << endl;

    k = 2;
    cout << "--- K = " << k << " ---" << endl;
    cout << k << "-th smallest: " << kthSmallest(arr, k) << endl;
    cout << k << "-th largest:  " << kthLargest(arr, k) << endl;

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "K-th Smallest:" << endl;
    cout << "  1. Use MAX-HEAP of size k" << endl;
    cout << "  2. Push each element" << endl;
    cout << "  3. If size > k, pop (removes LARGEST)" << endl;
    cout << "  4. Heap top = k-th smallest" << endl;
    cout << endl;
    cout << "K-th Largest:" << endl;
    cout << "  1. Use MIN-HEAP of size k" << endl;
    cout << "  2. Push each element" << endl;
    cout << "  3. If size > k, pop (removes SMALLEST)" << endl;
    cout << "  4. Heap top = k-th largest" << endl;
    cout << endl;
    cout << "Time: O(n log k)" << endl;
    cout << "Space: O(k) for heap" << endl;

    return 0;
}
