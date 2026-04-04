/*
 * File: 06_Longest_Subarray_Sum_K.cpp
 * Topic: Longest subarray with sum = K
 * Description: Using prefix sum + hash map
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Longest Subarray with Sum K ===" << endl;
    cout << endl;

    int arr[] = {1, -1, 5, -2, 3};
    int n = 5;
    int k = 3;

    cout << "Array: 1 -1 5 -2 3" << endl;
    cout << "K = " << k << endl;
    cout << endl;

    /*
     * Key idea:
     * If prefixSum - k was seen before at some index,
     * then subarray from that index+1 to current has sum = k.
     *
     * Why?
     *   prefixSum[current] - prefixSum[previous] = subarray_sum
     *   So if prefixSum[previous] = prefixSum[current] - k,
     *   then subarray_sum = k.
     */

    // Track first occurrence of each prefix sum
    // Using offset to handle negative prefix sums
    int OFFSET = 100;
    int firstOccurrence[201];
    bool exists[201] = {false};

    // Initialize: prefix sum 0 at index -1
    firstOccurrence[0 + OFFSET] = -1;
    exists[0 + OFFSET] = true;

    int prefixSum = 0;
    int maxLen = 0;
    int bestStart = -1;
    int bestEnd = -1;

    for (int i = 0; i < n; i++) {
        prefixSum = prefixSum + arr[i];

        // Check if (prefixSum - k) was seen
        int target = prefixSum - k;
        if (target + OFFSET >= 0 && target + OFFSET < 201 && exists[target + OFFSET]) {
            int len = i - firstOccurrence[target + OFFSET];
            if (len > maxLen) {
                maxLen = len;
                bestStart = firstOccurrence[target + OFFSET] + 1;
                bestEnd = i;
            }
        }

        // Store first occurrence of this prefix sum
        if (exists[prefixSum + OFFSET] == false) {
            firstOccurrence[prefixSum + OFFSET] = i;
            exists[prefixSum + OFFSET] = true;
        }
    }

    if (maxLen > 0) {
        cout << "Longest subarray with sum " << k << " has length: " << maxLen << endl;
        cout << "Subarray: ";
        for (int i = bestStart; i <= bestEnd; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No subarray found with sum " << k << endl;
    }

    cout << endl;
    cout << "--- Pattern ---" << endl;
    cout << "1. Keep running prefix sum" << endl;
    cout << "2. If (prefixSum - k) seen before -> subarray found" << endl;
    cout << "3. Store FIRST occurrence only (longest subarray)" << endl;
    cout << endl;
    cout << "Time: O(n), Space: O(n)" << endl;

    return 0;
}
