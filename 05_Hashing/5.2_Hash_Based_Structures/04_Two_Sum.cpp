/*
 * File: 04_Two_Sum.cpp
 * Topic: Two Sum - Find two numbers that add up to target
 * Description: O(n) using hash map to store seen values
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Two Sum ===" << endl;
    cout << endl;

    int arr[] = {2, 7, 11, 15};
    int n = 4;
    int target = 9;

    cout << "Array: 2 7 11 15" << endl;
    cout << "Target: 9" << endl;
    cout << endl;

    /*
     * Brute force: O(n^2) - check all pairs
     * Optimal: O(n) - use hash map
     *
     * For each element x, check if (target - x) was seen before.
     * If yes -> found the pair!
     * If no -> store x in map with its index.
     */

    // Using simple arrays to simulate hash map
    int seenKeys[100];
    int seenIdx[100];
    bool exists[100] = {false};

    for (int i = 0; i < n; i++) {
        int complement = target - arr[i];

        // Check if complement was seen
        int idx = (complement + 100) % 100; // handle negative
        if (exists[idx] && seenKeys[idx] == complement) {
            cout << "Found! indices [" << seenIdx[idx] << ", " << i << "]" << endl;
            cout << "Values: " << seenKeys[idx] << " + " << arr[i] << " = " << target << endl;

            delete[] seenKeys;
            delete[] seenIdx;
            delete[] exists;

            return 0;
        }

        // Store current element
        int storeIdx = (arr[i] + 100) % 100;
        seenKeys[storeIdx] = arr[i];
        seenIdx[storeIdx] = i;
        exists[storeIdx] = true;
    }

    cout << "No pair found." << endl;

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. For each element, calculate complement = target - x" << endl;
    cout << "  2. Check if complement is in hash map" << endl;
    cout << "  3. If yes -> return both indices" << endl;
    cout << "  4. If no -> store x -> index in map" << endl;
    cout << endl;
    cout << "Time: O(n) - single pass" << endl;
    cout << "Space: O(n) - hash map stores at most n elements" << endl;
    cout << endl;
    cout << "Variation: Return values instead of indices," << endl;
    cout << "           or count all pairs that sum to target." << endl;

    return 0;
}
