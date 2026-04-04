/*
 * File: 05_Subarray_Sum_Divisible_by_K.cpp
 * Topic: Check if subarray sum is multiple of K
 * Description: Using prefix sum % K + hash map
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Subarray Sum Divisible by K ===" << endl;
    cout << endl;

    int arr[] = {23, 2, 4, 6, 7};
    int n = 5;
    int k = 6;

    cout << "Array: 23 2 4 6 7" << endl;
    cout << "K = " << k << endl;
    cout << endl;

    /*
     * Key idea:
     * If prefixSum[i] % k == prefixSum[j] % k (where i < j),
     * then the subarray from i+1 to j has sum divisible by k.
     *
     * Why?
     *   subarray_sum = prefixSum[j] - prefixSum[i]
     *   If both have same remainder mod k, their difference is divisible by k.
     *
     * We also need subarray size >= 2, so j - i >= 2.
     */

    // Track first occurrence of each remainder
    int firstOccurrence[100];
    bool exists[100] = {false};

    // Initialize: remainder 0 at index -1
    firstOccurrence[0] = -1;
    exists[0] = true;

    int prefixSum = 0;
    bool found = false;

    for (int i = 0; i < n; i++) {
        prefixSum = prefixSum + arr[i];
        int mod = prefixSum % k;

        if (exists[mod]) {
            if (i - firstOccurrence[mod] >= 2) {
                cout << "Found! Subarray from index " << (firstOccurrence[mod] + 1) << " to " << i << endl;

                // Print the subarray
                cout << "Subarray: ";
                for (int j = firstOccurrence[mod] + 1; j <= i; j++) {
                    cout << arr[j] << " ";
                }
                cout << endl;

                int sum = 0;
                for (int j = firstOccurrence[mod] + 1; j <= i; j++) {
                    sum = sum + arr[j];
                }
                cout << "Sum = " << sum << " (divisible by " << k << "? " << (sum % k == 0 ? "Yes" : "No") << ")" << endl;

                found = true;
                break;
            }
        } else {
            firstOccurrence[mod] = i;
            exists[mod] = true;
        }
    }

    if (found == false) {
        cout << "No subarray found with sum divisible by " << k << endl;
    }

    cout << endl;
    cout << "--- Key Insight ---" << endl;
    cout << "Same remainder mod k => subarray between them is divisible by k" << endl;
    cout << "Store FIRST occurrence only (we want longest subarray)" << endl;
    cout << endl;
    cout << "Time: O(n)" << endl;
    cout << "Space: O(min(n, k)) for remainder map" << endl;

    return 0;
}
