/*
 * File: 08_Top_K_Frequent_Elements.cpp
 * Topic: Find top K most frequent elements
 * Description: Use hash map for frequency + min-heap for top K
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Find top K frequent elements
vector<int> topKFrequent(vector<int>& nums, int k) {
    // Step 1: Count frequency of each element
    // Using simple arrays since we don't know the range
    // In practice, use unordered_map
    int freq[100] = {0}; // assuming values 0-99
    vector<int> uniqueVals;

    for (int i = 0; i < nums.size(); i++) {
        if (freq[nums[i]] == 0) {
            uniqueVals.push_back(nums[i]);
        }
        freq[nums[i]]++;
    }

    // Step 2: Min-heap of size k: {frequency, value}
    // Store pairs: first = frequency, second = value
    priority_queue<pair<int, int>,
                   vector<pair<int, int> >,
                   greater<pair<int, int> > > pq;

    for (int i = 0; i < uniqueVals.size(); i++) {
        int val = uniqueVals[i];
        int count = freq[val];

        pair<int, int> entry;
        entry.first = count;
        entry.second = val;
        pq.push(entry);

        // If heap size > k, remove element with lowest frequency
        if (pq.size() > k) {
            pq.pop();
        }
    }

    // Step 3: Extract results
    vector<int> result;
    while (pq.empty() == false) {
        result.push_back(pq.top().second);
        pq.pop();
    }

    return result;
}

int main() {
    cout << "=== Top K Frequent Elements ===" << endl;
    cout << endl;

    vector<int> nums;
    nums.push_back(1); nums.push_back(1); nums.push_back(1);
    nums.push_back(2); nums.push_back(2);
    nums.push_back(3); nums.push_back(3); nums.push_back(3); nums.push_back(3);
    nums.push_back(4);

    cout << "Array: 1 1 1 2 2 3 3 3 3 4" << endl;
    cout << endl;

    cout << "Frequencies:" << endl;
    cout << "  1 -> 3 times" << endl;
    cout << "  2 -> 2 times" << endl;
    cout << "  3 -> 4 times" << endl;
    cout << "  4 -> 1 time" << endl;
    cout << endl;

    int k = 2;
    cout << "Top " << k << " frequent elements:" << endl;
    vector<int> result = topKFrequent(nums, k);
    for (int i = 0; i < result.size(); i++) {
        cout << "  " << result[i] << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Count frequency of each element (hash map)" << endl;
    cout << "  2. Use MIN-HEAP of size k to track top k frequent" << endl;
    cout << "  3. Push {frequency, value} into heap" << endl;
    cout << "  4. If size > k, pop (removes least frequent)" << endl;
    cout << "  5. Heap contains top k frequent elements" << endl;
    cout << endl;
    cout << "Time: O(n log k)" << endl;
    cout << "Space: O(n) for frequency map + O(k) for heap" << endl;

    return 0;
}
