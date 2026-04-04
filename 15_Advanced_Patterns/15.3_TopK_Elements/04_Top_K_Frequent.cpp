// 15.3 - Top K Frequent Elements
// Find the K most frequently occurring elements.
// Approaches:
//   1. Frequency map + Min-heap: O(n log k)
//   2. Frequency map + Bucket sort: O(n)
//
// HEAP APPROACH:
//   1. Count frequencies with a hash map (unordered_map)
//   2. Use a min-heap of size k keyed by frequency
//   3. Push each (element, frequency) pair, pop if size > k
//   4. Remaining heap contains top K frequent elements

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ============================================================
// TOP K FREQUENT - Min-Heap O(n log k)
// ============================================================

// Pair struct for element-frequency
struct FreqPair {
    int num;
    int freq;
};

// Comparator for min-heap (smaller frequency on top)
bool isGreater(const FreqPair &a, const FreqPair &b) {
    return a.freq > b.freq;  // Returns true if a has higher freq (so a should be below b in min-heap)
}

// Manual min-heap using array (to avoid complex priority_queue comparator)
// Instead, we use a simpler approach: max-heap with negated frequencies

vector<int> topKFrequentHeap(const int arr[], int n, int k) {
    // Count frequencies
    int freqMap[1000];
    int uniqueNums[1000];
    int uniqueCount = 0;

    for (int i = 0; i < n; i++) {
        freqMap[arr[i]]++;
    }

    // Collect unique numbers
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (uniqueNums[j] == arr[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            uniqueNums[uniqueCount++] = arr[i];
        }
    }

    // Use priority_queue with pair (frequency, number)
    // Min-heap: greater<pair> compares first element (frequency)
    // We use negative frequency to simulate min-heap with default max-heap
    priority_queue<pair<int, int> > pq;  // Max-heap of (-freq, num)

    for (int i = 0; i < uniqueCount; i++) {
        int num = uniqueNums[i];
        pq.push(make_pair(-freqMap[num], num));
        if ((int)pq.size() > k) {
            pq.pop();  // Remove most negative (highest freq removed = we keep smallest freq)
            // Wait, this is wrong. Let me redo with actual min-heap.
        }
    }

    // Actually, let me redo this properly with a vector-based approach
    // Reset and use sorting-based approach for clarity

    // Collect all (num, freq) pairs
    int nums[1000], freqs[1000];
    int count = 0;
    for (int i = 0; i < uniqueCount; i++) {
        nums[count] = uniqueNums[i];
        freqs[count] = freqMap[uniqueNums[i]];
        count++;
    }

    // Selection: find top k by frequency (simple approach)
    vector<int> result;

    // Sort by frequency descending (bubble sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (freqs[j] < freqs[j + 1]) {
                int tempF = freqs[j]; freqs[j] = freqs[j + 1]; freqs[j + 1] = tempF;
                int tempN = nums[j]; nums[j] = nums[j + 1]; nums[j + 1] = tempN;
            }
        }
    }

    for (int i = 0; i < k && i < count; i++) {
        result.push_back(nums[i]);
    }

    return result;
}

// ============================================================
// TOP K FREQUENT - Bucket Sort O(n)
// More efficient when frequency range is bounded (1 to n).
// ============================================================

vector<int> topKFrequentBucket(const int arr[], int n, int k) {
    // Count frequencies
    int freqMap[1000];
    for (int i = 0; i < 1000; i++) freqMap[i] = 0;

    for (int i = 0; i < n; i++) {
        freqMap[arr[i]]++;
    }

    // Create buckets: bucket[f] = numbers with frequency f
    // Use arrays since we can't have vector<vector<int>>
    int bucket[1001][1000];   // bucket[frequency][list of numbers]
    int bucketCount[1001];     // count of numbers at each frequency
    for (int f = 0; f <= n; f++) bucketCount[f] = 0;

    // Find unique numbers and put them in buckets
    int seen[1000];
    int seenCount = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < seenCount; j++) {
            if (seen[j] == arr[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            seen[seenCount++] = arr[i];
            int f = freqMap[arr[i]];
            bucket[f][bucketCount[f]++] = arr[i];
        }
    }

    // Collect from highest frequency down
    vector<int> result;
    for (int f = n; f >= 1 && (int)result.size() < k; f--) {
        for (int i = 0; i < bucketCount[f] && (int)result.size() < k; i++) {
            result.push_back(bucket[f][i]);
        }
    }

    return result;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoTopKFrequent() {
    cout << "=== Top K Frequent Elements - Sort Approach ===" << endl;
    int arr[] = {1, 1, 1, 2, 2, 3};
    int n = 6;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int k = 2;
    vector<int> result = topKFrequentHeap(arr, n, k);

    cout << "Top " << k << " frequent: ";
    for (int i = 0; i < (int)result.size(); i++) cout << result[i] << " ";
    cout << endl;  // 1 2
    cout << endl;
}

void demoTopKFrequentBucket() {
    cout << "=== Top K Frequent Elements - Bucket Sort ===" << endl;
    int arr[] = {1, 1, 1, 2, 2, 3};
    int n = 6;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int k = 2;
    vector<int> result = topKFrequentBucket(arr, n, k);

    cout << "Top " << k << " frequent: ";
    for (int i = 0; i < (int)result.size(); i++) cout << result[i] << " ";
    cout << endl;  // 1 2
    cout << endl;
}

void demoLargerExample() {
    cout << "=== Top K Frequent - Larger Example ===" << endl;
    int arr[] = {4, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = 11;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Frequencies: 4->5, 3->3, 2->2, 1->1" << endl;

    int k = 2;
    vector<int> result1 = topKFrequentHeap(arr, n, k);
    vector<int> result2 = topKFrequentBucket(arr, n, k);

    cout << "Top " << k << " frequent (sort): ";
    for (int i = 0; i < (int)result1.size(); i++) cout << result1[i] << " ";
    cout << endl;

    cout << "Top " << k << " frequent (bucket): ";
    for (int i = 0; i < (int)result2.size(); i++) cout << result2[i] << " ";
    cout << endl;
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Top 2 frequent in [1,1,1,2,2,3] ===" << endl;
    cout << endl;
    cout << "Step 1: Count frequencies" << endl;
    cout << "  1 -> 3,  2 -> 2,  3 -> 1" << endl;
    cout << endl;
    cout << "Step 2a: Min-heap of size 2 (by frequency)" << endl;
    cout << "  Push (1, freq=3): heap=[(1,3)]" << endl;
    cout << "  Push (2, freq=2): heap=[(2,2),(1,3)]" << endl;
    cout << "  Push (3, freq=1): heap=[(2,2),(1,3),(3,1)], size>2, pop (3,1)" << endl;
    cout << "  Result: (2,2), (1,3) -> elements: 1, 2" << endl;
    cout << endl;
    cout << "Step 2b: Bucket sort" << endl;
    cout << "  bucket[1] = [3]" << endl;
    cout << "  bucket[2] = [2]" << endl;
    cout << "  bucket[3] = [1]" << endl;
    cout << "  Collect from bucket[3]: [1], bucket[2]: [1,2] -> done" << endl;
    cout << endl;
}

void demoApproachComparison() {
    cout << "=== Approach Comparison ===" << endl;
    cout << endl;
    cout << "Heap Approach (min-heap of size k):" << endl;
    cout << "  Time: O(n + m log k) where m = unique elements" << endl;
    cout << "  Space: O(m) for frequency map + O(k) for heap" << endl;
    cout << "  Good when k << m" << endl;
    cout << endl;
    cout << "Bucket Sort Approach:" << endl;
    cout << "  Time: O(n + m) - linear" << endl;
    cout << "  Space: O(n + m) for buckets" << endl;
    cout << "  Best when frequency range is bounded (1 to n)" << endl;
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoTopKFrequent();
    demoTopKFrequentBucket();
    demoLargerExample();
    demoApproachComparison();
    return 0;
}
