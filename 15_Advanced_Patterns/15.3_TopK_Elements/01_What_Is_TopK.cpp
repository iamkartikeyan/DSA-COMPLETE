// 15.3 - What Is Top K Elements?
// The Top K pattern finds the K largest, smallest, or most frequent elements.
// Three main approaches:
//   1. Heap (Priority Queue): O(n log k), good for streaming
//   2. Quickselect: O(n) average, in-place, modifies array
//   3. Bucket Sort: O(n), frequency-based when range is bounded
//
// HEAP CHOICE:
//   - Top K LARGEST  -> use MIN-heap of size k (pop smallest, keep largest)
//   - Top K SMALLEST -> use MAX-heap of size k (pop largest, keep smallest)
//
// WHY THIS WORKS:
//   A min-heap of size k always contains the k largest elements seen so far.
//   When you push a new element, if heap size exceeds k, you pop the minimum.
//   The minimum of the k largest is the "weakest" of the top k, so removing
//   it ensures we keep only the strongest candidates.

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ============================================================
// MIN-HEAP FOR TOP K LARGEST
// C++ priority_queue is a max-heap by default.
// For min-heap: priority_queue<T, vector<T>, greater<T>>
// ============================================================

void demoMinHeap() {
    cout << "=== Min-Heap for Top K Largest ===" << endl;
    cout << endl;
    cout << "C++ priority_queue default = MAX-heap (largest on top)" << endl;
    cout << "For MIN-heap: priority_queue<int, vector<int>, greater<int>>" << endl;
    cout << endl;

    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;
    int k = 3;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Top " << k << " largest using min-heap of size " << k << ":" << endl;

    // Min-heap
    priority_queue<int, vector<int>, greater<int> > minHeap;

    for (int i = 0; i < n; i++) {
        minHeap.push(arr[i]);
        cout << "  Push " << arr[i] << ". Heap size = " << (int)minHeap.size();
        if ((int)minHeap.size() > k) {
            cout << ", pop " << minHeap.top();
            minHeap.pop();
        }
        cout << endl;
    }

    cout << "  Final heap contents (top k largest): ";
    int result[100];
    int idx = 0;
    while (!minHeap.empty()) {
        result[idx++] = minHeap.top();
        minHeap.pop();
    }
    for (int i = 0; i < idx; i++) cout << result[i] << " ";
    cout << endl;  // 5 6 9
    cout << endl;
}

// ============================================================
// MAX-HEAP FOR TOP K SMALLEST
// ============================================================

void demoMaxHeap() {
    cout << "=== Max-Heap for Top K Smallest ===" << endl;
    cout << endl;

    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;
    int k = 3;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Top " << k << " smallest using max-heap of size " << k << ":" << endl;

    // Max-heap (default)
    priority_queue<int> maxHeap;

    for (int i = 0; i < n; i++) {
        maxHeap.push(arr[i]);
        cout << "  Push " << arr[i] << ". Heap size = " << (int)maxHeap.size();
        if ((int)maxHeap.size() > k) {
            cout << ", pop " << maxHeap.top();
            maxHeap.pop();
        }
        cout << endl;
    }

    cout << "  Final heap contents (top k smallest): ";
    int result[100];
    int idx = 0;
    while (!maxHeap.empty()) {
        result[idx++] = maxHeap.top();
        maxHeap.pop();
    }
    for (int i = 0; i < idx; i++) cout << result[i] << " ";
    cout << endl;  // 3 2 1
    cout << endl;
}

// ============================================================
// QUICKSELECT OVERVIEW
// ============================================================

void demoQuickselectOverview() {
    cout << "=== Quickselect Overview ===" << endl;
    cout << endl;
    cout << "Like quicksort: pick a pivot, partition array into <= pivot and > pivot." << endl;
    cout << "But only recurse into the side containing the k-th element." << endl;
    cout << endl;
    cout << "Time: O(n) average, O(n^2) worst case" << endl;
    cout << "Space: O(1) - in-place" << endl;
    cout << "Drawback: modifies the array" << endl;
    cout << endl;
}

// ============================================================
// BUCKET SORT OVERVIEW
// ============================================================

void demoBucketSortOverview() {
    cout << "=== Bucket Sort Overview ===" << endl;
    cout << endl;
    cout << "For top K FREQUENT elements:" << endl;
    cout << "1. Count frequencies with a hash map" << endl;
    cout << "2. Create buckets: bucket[frequency] = list of elements" << endl;
    cout << "3. Collect from highest frequency bucket down to get top K" << endl;
    cout << endl;
    cout << "Time: O(n)" << endl;
    cout << "Space: O(n)" << endl;
    cout << "Best when frequency range is bounded (1 to n)" << endl;
    cout << endl;
}

// ============================================================
// APPROACH SELECTION GUIDE
// ============================================================

void demoApproachSelection() {
    cout << "=== Approach Selection Guide ===" << endl;
    cout << endl;
    cout << "Problem Type                  | Best Approach" << endl;
    cout << "------------------------------|---------------------------" << endl;
    cout << "Top K largest/smallest        | Min/Max heap O(n log k)" << endl;
    cout << "K-th largest/smallest         | Quickselect O(n) avg" << endl;
    cout << "Top K frequent (unbounded)    | Heap O(n log k)" << endl;
    cout << "Top K frequent (bounded freq) | Bucket sort O(n)" << endl;
    cout << "Streaming data                | Heap (online algorithm)" << endl;
    cout << "Cannot modify array           | Heap" << endl;
    cout << "k << n                        | Heap O(n log k)" << endl;
    cout << "k ~ n                         | Quickselect or sort" << endl;
    cout << endl;
}

int main() {
    demoMinHeap();
    demoMaxHeap();
    demoQuickselectOverview();
    demoBucketSortOverview();
    demoApproachSelection();
    return 0;
}
