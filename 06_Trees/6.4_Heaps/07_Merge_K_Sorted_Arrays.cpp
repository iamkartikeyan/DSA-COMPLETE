/*
 * File: 07_Merge_K_Sorted_Arrays.cpp
 * Topic: Merge K sorted arrays using Min-Heap
 * Description: Efficient O(N log k) merge where N = total elements
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Merge K sorted arrays
// Each element stored as {value, array_index, element_index}
vector<int> mergeKSorted(vector<vector<int> >& arrays) {
    vector<int> result;

    // Min-heap: {value, array_index, element_index}
    // We use a trick: store negative value for min-heap with priority_queue
    // Or use greater<> comparator
    priority_queue<pair<int, pair<int, int> >,
                   vector<pair<int, pair<int, int> > >,
                   greater<pair<int, pair<int, int> > > > pq;

    // Step 1: Push first element of each array into heap
    for (int i = 0; i < arrays.size(); i++) {
        if (arrays[i].empty() == false) {
            pair<int, int> indices;
            indices.first = i;   // array index
            indices.second = 0;  // element index
            pair<int, pair<int, int> > entry;
            entry.first = arrays[i][0]; // value
            entry.second = indices;
            pq.push(entry);
        }
    }

    // Step 2: Extract min and push next element from same array
    while (pq.empty() == false) {
        pair<int, pair<int, int> > top = pq.top();
        pq.pop();

        int val = top.first;
        int arrIdx = top.second.first;
        int elemIdx = top.second.second;

        result.push_back(val);

        // Push next element from same array
        if (elemIdx + 1 < arrays[arrIdx].size()) {
            pair<int, int> indices;
            indices.first = arrIdx;
            indices.second = elemIdx + 1;
            pair<int, pair<int, int> > entry;
            entry.first = arrays[arrIdx][elemIdx + 1];
            entry.second = indices;
            pq.push(entry);
        }
    }

    return result;
}

int main() {
    cout << "=== Merge K Sorted Arrays ===" << endl;
    cout << endl;

    vector<vector<int> > arrays;

    vector<int> arr1;
    arr1.push_back(1); arr1.push_back(4); arr1.push_back(7);
    arrays.push_back(arr1);

    vector<int> arr2;
    arr2.push_back(2); arr2.push_back(5); arr2.push_back(8);
    arrays.push_back(arr2);

    vector<int> arr3;
    arr3.push_back(3); arr3.push_back(6); arr3.push_back(9); arr3.push_back(12);
    arrays.push_back(arr3);

    cout << "Input arrays:" << endl;
    cout << "  Array 1: 1 4 7" << endl;
    cout << "  Array 2: 2 5 8" << endl;
    cout << "  Array 3: 3 6 9 12" << endl;
    cout << endl;

    vector<int> merged = mergeKSorted(arrays);

    cout << "Merged:  ";
    for (int i = 0; i < merged.size(); i++) {
        cout << merged[i] << " ";
    }
    cout << endl;

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Put first element of each array into MIN-HEAP" << endl;
    cout << "  2. Extract smallest element, add to result" << endl;
    cout << "  3. Push NEXT element from same array into heap" << endl;
    cout << "  4. Repeat until heap is empty" << endl;
    cout << endl;
    cout << "Time: O(N log k) where N = total elements, k = number of arrays" << endl;
    cout << "Space: O(k) for heap" << endl;
    cout << endl;
    cout << "Same approach used in: Merge K Sorted Linked Lists" << endl;

    return 0;
}
