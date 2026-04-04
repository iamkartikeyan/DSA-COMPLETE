// Subarray Sum Equals K
// Count the number of contiguous subarrays whose sum equals k.
// Uses hash map + prefix sum technique.
//
// Key Insight:
//   If prefixSum[j] - prefixSum[i] = k, then subarray arr[i+1..j] has sum k.
//   Rearranged: prefixSum[i] = prefixSum[j] - k
//   So for each position j, we count how many earlier prefix sums equal (prefixSum[j] - k).
//
// Algorithm:
//   1. Maintain running prefixSum and a hash map counting prefix sum frequencies
//   2. Initialize count[0] = 1 (empty prefix)
//   3. For each element: prefixSum += arr[i]
//      - Add count[prefixSum - k] to result
//      - Increment count[prefixSum]
//
// Time Complexity:  O(n)
// Space Complexity: O(n) for hash map

#include <iostream>
using namespace std;

// Maximum possible array size for hash map simulation
const int MAXN = 1000;

// Simple hash map using separate chaining for prefix sum counting
// Keys can be negative, so we use an offset-based approach
struct HashEntry {
    int key;
    int value;
};

// Simple hash map implementation (no STL map to keep it basic)
const int MAP_SIZE = 2003;  // Prime number for hashing
HashEntry entries[MAP_SIZE];
bool occupied[MAP_SIZE];

void initMap() {
    for (int i = 0; i < MAP_SIZE; i++) {
        occupied[i] = false;
    }
}

// Hash function that handles negative keys
int hashFunc(int key) {
    int h = key % MAP_SIZE;
    if (h < 0) h += MAP_SIZE;
    return h;
}

int getVal(int key) {
    int h = hashFunc(key);
    // Linear probing
    for (int i = 0; i < MAP_SIZE; i++) {
        int idx = (h + i) % MAP_SIZE;
        if (!occupied[idx]) return 0;
        if (entries[idx].key == key) return entries[idx].value;
    }
    return 0;
}

void putVal(int key, int val) {
    int h = hashFunc(key);
    for (int i = 0; i < MAP_SIZE; i++) {
        int idx = (h + i) % MAP_SIZE;
        if (!occupied[idx]) {
            entries[idx].key = key;
            entries[idx].value = val;
            occupied[idx] = true;
            return;
        }
        if (entries[idx].key == key) {
            entries[idx].value = val;
            return;
        }
    }
}

int countSubarraysWithSum(const int arr[], int n, int k) {
    initMap();
    putVal(0, 1);  // Empty prefix sum = 0, count = 1

    int prefixSum = 0;
    int result = 0;

    for (int i = 0; i < n; i++) {
        prefixSum += arr[i];

        // Check if (prefixSum - k) exists in map
        int target = prefixSum - k;
        result += getVal(target);

        // Increment count of current prefixSum
        putVal(prefixSum, getVal(prefixSum) + 1);
    }

    return result;
}

int main() {
    cout << "=== Application: Subarray Sum Equals K ===" << endl;
    cout << endl;

    // Example 1
    int arr1[] = {1, 2, 3, -1, 2, 1};
    int n1 = 6;
    int k1 = 5;

    cout << "Array: ";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    cout << "k = " << k1 << endl;
    cout << "Subarrays with sum = " << k1 << " : " << countSubarraysWithSum(arr1, n1, k1) << endl;
    cout << "  [2,3], [3,-1,2,1], [1,2,3,-1]" << endl;
    cout << endl;

    // Example 2
    int arr2[] = {1, 1, 1};
    int n2 = 3;
    int k2 = 2;

    cout << "Array: ";
    for (int i = 0; i < n2; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    cout << "k = " << k2 << endl;
    cout << "Subarrays with sum = " << k2 << " : " << countSubarraysWithSum(arr2, n2, k2) << endl;
    cout << "  [1,1] at index 0-1, [1,1] at index 1-2" << endl;
    cout << endl;

    // Example 3: all zeros
    int arr3[] = {0, 0, 0, 0};
    int n3 = 4;
    int k3 = 0;

    cout << "Array: ";
    for (int i = 0; i < n3; i++) {
        cout << arr3[i] << " ";
    }
    cout << endl;
    cout << "k = " << k3 << endl;
    cout << "Subarrays with sum = " << k3 << " : " << countSubarraysWithSum(arr3, n3, k3) << endl;
    cout << "  Every single element and every pair has sum 0" << endl;
    cout << endl;

    // Show step-by-step trace for Example 1
    cout << "Step-by-step trace for Example 1:" << endl;
    cout << "  i  arr[i]  prefixSum  prefixSum-k  count[target]  result" << endl;
    cout << "  -     -         0           -             -            0  (initial: count[0]=1)" << endl;
    for (int i = 0; i < n1; i++) {
        static int ps = 0;
        ps += arr1[i];
        int target = ps - k1;
        cout << "  " << i << "    " << arr1[i] << "       " << ps << "         " << target;
        cout << "          (lookup)        (accumulated)" << endl;
    }

    return 0;
}
