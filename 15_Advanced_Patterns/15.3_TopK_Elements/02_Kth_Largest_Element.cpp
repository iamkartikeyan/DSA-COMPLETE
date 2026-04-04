// 15.3 - Kth Largest Element
// Find the Kth largest element in an unsorted array.
// Approach 1: Min-heap of size k -> O(n log k)
// Approach 2: Quickselect -> O(n) average
//
// MIN-HEAP APPROACH:
//   Keep a min-heap of size k. After processing all elements,
//   the top of the heap is the Kth largest (smallest of the top k).

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ============================================================
// KTH LARGEST - Min-Heap O(n log k)
// ============================================================

int kthLargest(const int arr[], int n, int k) {
    priority_queue<int, vector<int>, greater<int> > minHeap;

    for (int i = 0; i < n; i++) {
        minHeap.push(arr[i]);
        if ((int)minHeap.size() > k) {
            minHeap.pop();  // Remove smallest, keep k largest
        }
    }
    return minHeap.top();  // Top is the Kth largest
}

// ============================================================
// KTH LARGEST - Quickselect O(n) average
// ============================================================

int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high];  // Lomuto partition scheme
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;
    return i;
}

int kthLargestQuickselect(vector<int> arr, int k) {
    // Kth largest = (n-k)th smallest (0-indexed)
    int n = (int)arr.size();
    int target = n - k;
    int low = 0, high = n - 1;

    while (low <= high) {
        int pivot = partition(arr, low, high);
        if (pivot == target) return arr[pivot];
        else if (pivot < target) low = pivot + 1;
        else high = pivot - 1;
    }
    return -1;
}

// ============================================================
// TOP K LARGEST ELEMENTS (all of them, sorted)
// ============================================================

vector<int> topKLargest(const int arr[], int n, int k) {
    priority_queue<int, vector<int>, greater<int> > minHeap;

    for (int i = 0; i < n; i++) {
        minHeap.push(arr[i]);
        if ((int)minHeap.size() > k) {
            minHeap.pop();
        }
    }

    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    return result;  // Sorted ascending
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoKthLargestHeap() {
    cout << "=== Kth Largest Element - Min-Heap ===" << endl;
    int arr[] = {3, 2, 1, 5, 6, 4};
    int n = 6;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int k = 2;
    cout << k << "th largest: " << kthLargest(arr, n, k) << endl;  // 5

    k = 4;
    cout << k << "th largest: " << kthLargest(arr, n, k) << endl;  // 3
    cout << endl;
}

void demoKthLargestQuickselect() {
    cout << "=== Kth Largest Element - Quickselect ===" << endl;
    int arr[] = {3, 2, 1, 5, 6, 4};
    int n = 6;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(arr[i]);

    int k = 2;
    cout << k << "th largest: " << kthLargestQuickselect(vec, k) << endl;  // 5

    // Reset array for next call
    vec.clear();
    for (int i = 0; i < n; i++) vec.push_back(arr[i]);

    k = 4;
    cout << k << "th largest: " << kthLargestQuickselect(vec, k) << endl;  // 3
    cout << endl;
}

void demoTopKLargest() {
    cout << "=== Top K Largest Elements ===" << endl;
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int k = 3;
    vector<int> result = topKLargest(arr, n, k);

    cout << "Top " << k << " largest: ";
    for (int i = 0; i < (int)result.size(); i++) cout << result[i] << " ";
    cout << endl;  // 5 6 9 (sorted ascending)
    cout << endl;
}

void demoCompareMethods() {
    cout << "=== Compare: Heap vs Quickselect ===" << endl;
    int arr[] = {3, 2, 1, 5, 6, 4};
    int n = 6;
    int k = 2;

    int heapResult = kthLargest(arr, n, k);

    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(arr[i]);
    int qsResult = kthLargestQuickselect(vec, k);

    cout << "Heap: " << heapResult << endl;
    cout << "Quickselect: " << qsResult << endl;
    cout << "Match: " << (heapResult == qsResult ? "Yes" : "No") << endl;
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: 2nd largest in [3, 2, 1, 5, 6, 4] ===" << endl;
    cout << "Min-heap of size 2:" << endl;
    cout << "  Push 3: heap=[3]" << endl;
    cout << "  Push 2: heap=[2,3]" << endl;
    cout << "  Push 1: heap=[1,2,3], size>2, pop 1 -> heap=[2,3]" << endl;
    cout << "  Push 5: heap=[2,3,5], size>2, pop 2 -> heap=[3,5]" << endl;
    cout << "  Push 6: heap=[3,5,6], size>2, pop 3 -> heap=[5,6]" << endl;
    cout << "  Push 4: heap=[4,5,6], size>2, pop 4 -> heap=[5,6]" << endl;
    cout << "  Top of heap = 5 = 2nd largest" << endl;
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoKthLargestHeap();
    demoKthLargestQuickselect();
    demoTopKLargest();
    demoCompareMethods();
    return 0;
}
