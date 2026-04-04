// 15.3 Top K Elements - Heap, Quickselect, Bucket Sort
// Three approaches to find top K largest/smallest/frequent elements.
// Heap: O(n log k). Quickselect: O(n) avg. Bucket: O(n) when range is bounded.

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

// ============================================================
// APPROACH 1: MIN-HEAP (Priority Queue)
// Keep a heap of size k. Push each element, pop if size > k.
// Time: O(n log k), Space: O(k)
// Best when k << n or for streaming data.
// ============================================================

// Top K largest elements
vector<int> topKLargest(const vector<int>& arr, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;  // Min-heap
    for (int x : arr) {
        minHeap.push(x);
        if ((int)minHeap.size() > k) minHeap.pop();  // Remove smallest
    }
    vector<int> result;
    while (!minHeap.empty()) { result.push_back(minHeap.top()); minHeap.pop(); }
    return result;  // Sorted ascending
}

// Top K smallest elements (use max-heap)
vector<int> topKSmallest(const vector<int>& arr, int k) {
    priority_queue<int> maxHeap;  // Max-heap
    for (int x : arr) {
        maxHeap.push(x);
        if ((int)maxHeap.size() > k) maxHeap.pop();  // Remove largest
    }
    vector<int> result;
    while (!maxHeap.empty()) { result.push_back(maxHeap.top()); maxHeap.pop(); }
    return result;
}

void demoTopKHeap() {
    cout << "=== Top K Using Heap ===" << endl;
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    int k = 3;
    cout << "Array: "; for (int x : arr) cout << x << " "; cout << endl;

    auto largest = topKLargest(arr, k);
    cout << "Top " << k << " largest: "; for (int x : largest) cout << x << " ";  // 5 6 9
    cout << endl;

    auto smallest = topKSmallest(arr, k);
    cout << "Top " << k << " smallest: "; for (int x : smallest) cout << x << " ";  // 3 2 1
    cout << endl << endl;
}

// ============================================================
// APPROACH 2: QUICKSELECT (Hoare's Selection Algorithm)
// Partition like quicksort, recurse only on relevant side.
// Time: O(n) average, O(n^2) worst case. Space: O(1).
// ============================================================

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Lomuto partition
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i++], arr[j]);
        }
    }
    swap(arr[i], arr[high]);
    return i;  // Pivot's final position
}

// Find the k-th smallest element (0-indexed)
int quickselect(vector<int>& arr, int k) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int pivot = partition(arr, low, high);
        if (pivot == k) return arr[pivot];
        else if (pivot < k) low = pivot + 1;
        else high = pivot - 1;
    }
    return -1;
}

// Top K largest using quickselect
vector<int> topKQuickselect(vector<int> arr, int k) {
    int n = arr.size();
    // Find the (n-k)-th smallest => threshold for top k largest
    quickselect(arr, n - k);
    return vector<int>(arr.begin() + n - k, arr.end());
}

void demoQuickselect() {
    cout << "=== Top K Using Quickselect ===" << endl;
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    int k = 3;
    cout << "Array: "; for (int x : arr) cout << x << " "; cout << endl;
    cout << "K-th smallest (k=3): " << quickselect(arr, 2) << endl;  // 2

    arr = {3, 1, 4, 1, 5, 9, 2, 6};
    auto result = topKQuickselect(arr, k);
    cout << "Top " << k << " largest: "; for (int x : result) cout << x << " ";
    cout << " (unsorted)" << endl << endl;
}

// ============================================================
// APPROACH 3: BUCKET SORT (Frequency-based)
// When finding top K frequent elements with bounded frequency range.
// Time: O(n), Space: O(n)
// ============================================================

// Top K frequent elements
vector<int> topKFrequent(const vector<int>& arr, int k) {
    // Count frequencies
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    // Bucket by frequency: bucket[f] = list of elements with freq f
    int n = arr.size();
    vector<vector<int>> buckets(n + 1);
    for (auto& [num, f] : freq)
        buckets[f].push_back(num);

    // Collect from highest frequency bucket down
    vector<int> result;
    for (int f = n; f >= 1 && (int)result.size() < k; f--) {
        for (int num : buckets[f]) {
            result.push_back(num);
            if ((int)result.size() == k) break;
        }
    }
    return result;
}

void demoBucketSort() {
    cout << "=== Top K Frequent (Bucket Sort) ===" << endl;
    vector<int> arr = {1, 1, 1, 2, 2, 3};
    int k = 2;
    cout << "Array: "; for (int x : arr) cout << x << " "; cout << endl;
    auto result = topKFrequent(arr, k);
    cout << "Top " << k << " frequent: "; for (int x : result) cout << x << " ";  // 1 2
    cout << endl << endl;
}

// ============================================================
// COMPARISON: When to use each approach
// ============================================================

void demoComparison() {
    cout << "=== Approach Comparison ===" << endl;
    cout << "Heap (priority_queue):    O(n log k), streaming, any k" << endl;
    cout << "Quickselect:              O(n) avg, in-place, modifies array" << endl;
    cout << "Bucket sort:              O(n), frequency-based, bounded range" << endl;
    cout << endl;

    // Demo with top K frequent words
    cout << "=== Top K Frequent Words ===" << endl;
    vector<string> words = {"the", "day", "is", "sunny", "the", "the", "sunny", "is", "is"};
    unordered_map<string, int> freq;
    for (auto& w : words) freq[w]++;

    // Using min-heap with custom comparator
    auto cmp = [&](const pair<string,int>& a, const pair<string,int>& b) {
        if (a.second != b.second) return a.second > b.second;  // Min-heap by freq
        return a.first < b.first;  // Lexicographic tiebreaker
    };
    priority_queue<pair<string,int>, vector<pair<string,int>>, decltype(cmp)> minHeap(cmp);

    for (auto& [w, f] : freq) {
        minHeap.push({w, f});
        if ((int)minHeap.size() > 2) minHeap.pop();
    }

    cout << "Words: the(3), is(3), sunny(2), day(1)" << endl;
    cout << "Top 2 frequent: ";
    vector<pair<string,int>> result;
    while (!minHeap.empty()) { result.push_back(minHeap.top()); minHeap.pop(); }
    for (auto& [w, f] : result) cout << w << "(" << f << ") ";
    cout << endl;
}

// ============================================================
// FIND K CLOSEST ELEMENTS to X
// Using binary search + two pointers
// ============================================================

vector<int> findClosestElements(const vector<int>& arr, int k, int x) {
    int left = 0, right = arr.size() - k;
    while (left < right) {
        int mid = left + (right - left) / 2;
        // Compare distance: prefer smaller, then smaller index
        if (x - arr[mid] > arr[mid + k] - x)
            left = mid + 1;
        else
            right = mid;
    }
    return vector<int>(arr.begin() + left, arr.begin() + left + k);
}

void demoKClosest() {
    cout << "\n=== K Closest Elements ===" << endl;
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 4, x = 3;
    auto result = findClosestElements(arr, k, x);
    cout << "Array: "; for (int v : arr) cout << v << " "; cout << endl;
    cout << k << " closest to " << x << ": ";
    for (int v : result) cout << v << " ";  // 1 2 3 4
    cout << endl;
}

int main() {
    demoTopKHeap();
    demoQuickselect();
    demoBucketSort();
    demoComparison();
    demoKClosest();
    return 0;
}
