// 15.3 - Kth Smallest Element
// Find the Kth smallest element in an unsorted array.
// Approach 1: Max-heap of size k -> O(n log k)
// Approach 2: Quickselect -> O(n) average
//
// MAX-HEAP APPROACH:
//   Keep a max-heap of size k. After processing all elements,
//   the top of the heap is the Kth smallest (largest of the bottom k).

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ============================================================
// KTH SMALLEST - Max-Heap O(n log k)
// ============================================================

int kthSmallest(const int arr[], int n, int k) {
    priority_queue<int> maxHeap;  // Default max-heap

    for (int i = 0; i < n; i++) {
        maxHeap.push(arr[i]);
        if ((int)maxHeap.size() > k) {
            maxHeap.pop();  // Remove largest, keep k smallest
        }
    }
    return maxHeap.top();  // Top is the Kth smallest
}

// ============================================================
// KTH SMALLEST - Quickselect O(n) average
// ============================================================

int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high];
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

int kthSmallestQuickselect(vector<int> arr, int k) {
    // k is 1-indexed here, convert to 0-indexed
    int target = k - 1;
    int n = (int)arr.size();
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
// TOP K SMALLEST ELEMENTS (all of them)
// ============================================================

vector<int> topKSmallest(const int arr[], int n, int k) {
    priority_queue<int> maxHeap;

    for (int i = 0; i < n; i++) {
        maxHeap.push(arr[i]);
        if ((int)maxHeap.size() > k) {
            maxHeap.pop();
        }
    }

    vector<int> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return result;  // Sorted descending
}

// ============================================================
// MEDIAN OF TWO SORTED ARRAYS (application of kth smallest)
// Simplified version for equal-length arrays.
// ============================================================

double findMedianSortedArrays(const int nums1[], int n1, const int nums2[], int n2) {
    // Merge both arrays and find median
    int total = n1 + n2;
    int merged[2000];
    for (int i = 0; i < n1; i++) merged[i] = nums1[i];
    for (int i = 0; i < n2; i++) merged[n1 + i] = nums2[i];

    // Simple bubble sort
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (merged[j] > merged[j + 1]) {
                int temp = merged[j];
                merged[j] = merged[j + 1];
                merged[j + 1] = temp;
            }
        }
    }

    if (total % 2 == 1) {
        return (double)merged[total / 2];
    } else {
        return (merged[total / 2 - 1] + merged[total / 2]) / 2.0;
    }
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoKthSmallestHeap() {
    cout << "=== Kth Smallest Element - Max-Heap ===" << endl;
    int arr[] = {7, 10, 4, 3, 20, 15};
    int n = 6;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int k = 3;
    cout << k << "th smallest: " << kthSmallest(arr, n, k) << endl;  // 7

    k = 1;
    cout << k << "st smallest (minimum): " << kthSmallest(arr, n, k) << endl;  // 3

    k = 5;
    cout << k << "th smallest: " << kthSmallest(arr, n, k) << endl;  // 15
    cout << endl;
}

void demoKthSmallestQuickselect() {
    cout << "=== Kth Smallest Element - Quickselect ===" << endl;
    int arr[] = {7, 10, 4, 3, 20, 15};
    int n = 6;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(arr[i]);

    int k = 3;
    cout << k << "th smallest: " << kthSmallestQuickselect(vec, k) << endl;  // 7
    cout << endl;
}

void demoTopKSmallest() {
    cout << "=== Top K Smallest Elements ===" << endl;
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int k = 3;
    vector<int> result = topKSmallest(arr, n, k);

    cout << "Top " << k << " smallest: ";
    for (int i = 0; i < (int)result.size(); i++) cout << result[i] << " ";
    cout << endl;  // 3 2 1 (descending from max-heap)
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: 3rd smallest in [7, 10, 4, 3, 20, 15] ===" << endl;
    cout << "Max-heap of size 3:" << endl;
    cout << "  Push 7: heap=[7]" << endl;
    cout << "  Push 10: heap=[7,10]" << endl;
    cout << "  Push 4: heap=[4,7,10]" << endl;
    cout << "  Push 3: heap=[3,4,7,10], size>3, pop 10 -> heap=[3,4,7]" << endl;
    cout << "  Push 20: heap=[3,4,7,20], size>3, pop 20 -> heap=[3,4,7]" << endl;
    cout << "  Push 15: heap=[3,4,7,15], size>3, pop 15 -> heap=[3,4,7]" << endl;
    cout << "  Top of heap = 7 = 3rd smallest" << endl;
    cout << endl;
}

void demoMedian() {
    cout << "=== Median of Two Sorted Arrays ===" << endl;
    int nums1[] = {1, 3};
    int nums2[] = {2};
    double median = findMedianSortedArrays(nums1, 2, nums2, 1);
    cout << "nums1 = [1, 3], nums2 = [2]" << endl;
    cout << "Median: " << median << endl;  // 2.0
    cout << endl;

    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    median = findMedianSortedArrays(nums3, 2, nums4, 2);
    cout << "nums1 = [1, 2], nums2 = [3, 4]" << endl;
    cout << "Median: " << median << endl;  // 2.5
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoKthSmallestHeap();
    demoKthSmallestQuickselect();
    demoTopKSmallest();
    demoMedian();
    return 0;
}
