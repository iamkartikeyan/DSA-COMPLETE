// 15.3 - Top K Elements Summary
// Complete reference for all Top K patterns.

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ============================================================
// PATTERN SUMMARY
// ============================================================

void demoPatternSummary() {
    cout << "=== TOP K ELEMENTS PATTERN SUMMARY ===" << endl;
    cout << endl;
    cout << "THREE MAIN APPROACHES:" << endl;
    cout << "  1. Heap (Priority Queue)    - O(n log k), versatile, streaming" << endl;
    cout << "  2. Quickselect              - O(n) average, in-place, modifies" << endl;
    cout << "  3. Bucket Sort              - O(n), frequency-based, bounded" << endl;
    cout << endl;
}

// ============================================================
// HEAP APPROACH - THE CORE IDEA
// ============================================================

void demoHeapApproach() {
    cout << "=== HEAP APPROACH ===" << endl;
    cout << endl;
    cout << "TOP K LARGEST -> MIN-HEAP of size k" << endl;
    cout << "  priority_queue<int, vector<int>, greater<int> > minHeap;" << endl;
    cout << "  Push each element, pop if size > k." << endl;
    cout << "  Final heap top = Kth largest." << endl;
    cout << "  All heap contents = top K largest (sorted ascending)." << endl;
    cout << endl;
    cout << "TOP K SMALLEST -> MAX-HEAP of size k" << endl;
    cout << "  priority_queue<int> maxHeap;  // default" << endl;
    cout << "  Push each element, pop if size > k." << endl;
    cout << "  Final heap top = Kth smallest." << endl;
    cout << endl;
    cout << "TOP K FREQUENT -> MIN-HEAP keyed by frequency" << endl;
    cout << "  1. Count frequencies with unordered_map" << endl;
    cout << "  2. Push (frequency, element) to min-heap of size k" << endl;
    cout << "  3. Heap contains top K frequent elements" << endl;
    cout << endl;
    cout << "WHY IT WORKS:" << endl;
    cout << "  Min-heap of size k always holds the k largest seen so far." << endl;
    cout << "  Popping the minimum removes the weakest of the top k." << endl;
    cout << "  After processing all, the minimum of top k = Kth largest." << endl;
    cout << endl;
}

// ============================================================
// QUICKSELECT APPROACH
// ============================================================

void demoQuickselectApproach() {
    cout << "=== QUICKSELECT APPROACH ===" << endl;
    cout << endl;
    cout << "KTH SMALLEST (0-indexed k):" << endl;
    cout << "  1. Partition around pivot (like quicksort)" << endl;
    cout << "  2. If pivot == k, return arr[pivot]" << endl;
    cout << "  3. If pivot < k, search right half" << endl;
    cout << "  4. If pivot > k, search left half" << endl;
    cout << endl;
    cout << "KTH LARGEST:" << endl;
    cout << "  Convert to (n-k)th smallest, then quickselect" << endl;
    cout << endl;
    cout << "TOP K LARGEST:" << endl;
    cout << "  Quickselect to find (n-k)th smallest." << endl;
    cout << "  All elements from index (n-k) to end are top K largest." << endl;
    cout << endl;
    cout << "PARTITION (Lomuto):" << endl;
    cout << "  pivot = arr[high]" << endl;
    cout << "  i = low" << endl;
    cout << "  for j = low to high-1:" << endl;
    cout << "    if arr[j] <= pivot: swap(arr[i], arr[j]), i++" << endl;
    cout << "  swap(arr[i], arr[high])" << endl;
    cout << "  return i" << endl;
    cout << endl;
}

// ============================================================
// BUCKET SORT APPROACH
// ============================================================

void demoBucketSortApproach() {
    cout << "=== BUCKET SORT APPROACH ===" << endl;
    cout << endl;
    cout << "For TOP K FREQUENT elements:" << endl;
    cout << endl;
    cout << "  1. Count frequencies: unordered_map<num, count>" << endl;
    cout << "  2. Create buckets: bucket[freq] = list of nums with that freq" << endl;
    cout << "     bucket[i] contains all numbers that appear i times" << endl;
    cout << "  3. Collect from bucket[n] down to bucket[1] until we have K" << endl;
    cout << endl;
    cout << "Why O(n):" << endl;
    cout << "  - Counting: O(n)" << endl;
    cout << "  - Filling buckets: O(m) where m = unique elements" << endl;
    cout << "  - Collecting: O(n) worst case" << endl;
    cout << "  Total: O(n)" << endl;
    cout << endl;
}

// ============================================================
// PROBLEM CATALOG
// ============================================================

void demoProblemCatalog() {
    cout << "=== PROBLEM CATALOG ===" << endl;
    cout << endl;
    cout << "Problem                      | Best Approach    | Time" << endl;
    cout << "-----------------------------|------------------|----------" << endl;
    cout << "Kth Largest Element          | Quickselect      | O(n) avg" << endl;
    cout << "Kth Smallest Element         | Quickselect      | O(n) avg" << endl;
    cout << "Top K Largest              | Min-heap         | O(n log k)" << endl;
    cout << "Top K Smallest             | Max-heap         | O(n log k)" << endl;
    cout << "Top K Frequent Elements      | Bucket sort      | O(n)" << endl;
    cout << "Top K Frequent Words         | Min-heap         | O(n log k)" << endl;
    cout << "K Closest Elements to X      | Binary search    | O(log n + k)" << endl;
    cout << "K Closest Points to Origin   | Min-heap         | O(n log k)" << endl;
    cout << "Merge K Sorted Lists         | Min-heap         | O(n log k)" << endl;
    cout << "Find Median from Data Stream | Two heaps        | O(log n)" << endl;
    cout << endl;
}

// ============================================================
// APPROACH SELECTION GUIDE
// ============================================================

void demoSelectionGuide() {
    cout << "=== HOW TO CHOOSE ===" << endl;
    cout << endl;
    cout << "Ask yourself:" << endl;
    cout << endl;
    cout << "Q: Finding Kth element (single value)?" << endl;
    cout << "A: Quickselect (O(n) average)" << endl;
    cout << endl;
    cout << "Q: Finding all Top K elements?" << endl;
    cout << "A: Heap (O(n log k)) - works for streaming too" << endl;
    cout << endl;
    cout << "Q: Top K by frequency?" << endl;
    cout << "A: Bucket sort if range is bounded, otherwise heap" << endl;
    cout << endl;
    cout << "Q: k is very small compared to n?" << endl;
    cout << "A: Heap - O(n log k) is much better than O(n log n) sort" << endl;
    cout << endl;
    cout << "Q: k is close to n?" << endl;
    cout << "A: Just sort the array: O(n log n)" << endl;
    cout << endl;
    cout << "Q: Cannot modify the array?" << endl;
    cout << "A: Heap (Quickselect modifies in-place)" << endl;
    cout << endl;
    cout << "Q: Data is streaming?" << endl;
    cout << "A: Heap (online algorithm)" << endl;
    cout << endl;
}

// ============================================================
// COMPLEXITY COMPARISON
// ============================================================

void demoComplexityComparison() {
    cout << "=== COMPLEXITY COMPARISON ===" << endl;
    cout << endl;
    cout << "Approach    | Time        | Space   | Modifies? | Streaming?" << endl;
    cout << "------------|-------------|---------|-----------|-------------" << endl;
    cout << "Sort        | O(n log n)  | O(1)    | Yes       | No" << endl;
    cout << "Heap        | O(n log k)  | O(k)    | No        | Yes" << endl;
    cout << "Quickselect | O(n) avg    | O(1)    | Yes       | No" << endl;
    cout << "Bucket sort | O(n)        | O(n)    | No        | No" << endl;
    cout << endl;
}

// ============================================================
// QUICK CODE TEMPLATES
// ============================================================

void demoCodeTemplates() {
    cout << "=== CODE TEMPLATES ===" << endl;
    cout << endl;
    cout << "// Kth Largest (Min-Heap):" << endl;
    cout << "priority_queue<int, vector<int>, greater<int> > pq;" << endl;
    cout << "for (int i = 0; i < n; i++) {" << endl;
    cout << "    pq.push(arr[i]);" << endl;
    cout << "    if ((int)pq.size() > k) pq.pop();" << endl;
    cout << "}" << endl;
    cout << "return pq.top();" << endl;
    cout << endl;
    cout << "// Kth Smallest (Max-Heap):" << endl;
    cout << "priority_queue<int> pq;" << endl;
    cout << "for (int i = 0; i < n; i++) {" << endl;
    cout << "    pq.push(arr[i]);" << endl;
    cout << "    if ((int)pq.size() > k) pq.pop();" << endl;
    cout << "}" << endl;
    cout << "return pq.top();" << endl;
    cout << endl;
}

// ============================================================
// QUICK DEMO
// ============================================================

void demoQuickDemo() {
    cout << "=== Quick Demo ===" << endl;
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    // Kth largest with min-heap
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int k = 3;
    for (int i = 0; i < n; i++) {
        minHeap.push(arr[i]);
        if ((int)minHeap.size() > k) minHeap.pop();
    }
    cout << k << "th largest: " << minHeap.top() << endl;  // 5

    // Kth smallest with max-heap
    priority_queue<int> maxHeap;
    for (int i = 0; i < n; i++) {
        maxHeap.push(arr[i]);
        if ((int)maxHeap.size() > k) maxHeap.pop();
    }
    cout << k << "th smallest: " << maxHeap.top() << endl;  // 2
    cout << endl;
}

int main() {
    demoPatternSummary();
    demoHeapApproach();
    demoQuickselectApproach();
    demoBucketSortApproach();
    demoProblemCatalog();
    demoSelectionGuide();
    demoComplexityComparison();
    demoCodeTemplates();
    demoQuickDemo();
    return 0;
}
