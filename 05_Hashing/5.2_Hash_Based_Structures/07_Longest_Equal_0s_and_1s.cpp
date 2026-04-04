/*
 * File: 07_Longest_Equal_0s_and_1s.cpp
 * Topic: Longest subarray with equal 0s and 1s
 * Description: Transform 0 -> -1, then find longest subarray with sum 0
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Longest Subarray with Equal 0s and 1s ===" << endl;
    cout << endl;

    int arr[] = {0, 1, 0, 0, 1, 1, 0};
    int n = 7;

    cout << "Array: 0 1 0 0 1 1 0" << endl;
    cout << endl;

    /*
     * Trick: Replace every 0 with -1.
     * Now the problem becomes: find longest subarray with sum = 0.
     *
     * Why this works:
     *   If 0s and 1s are equal, then (-1)s and 1s cancel out -> sum = 0
     *
     * Original: 0  1  0  0  1  1  0
     * Convert: -1  1 -1 -1  1  1 -1
     *
     * Longest subarray with sum 0 = longest equal 0s and 1s
     */

    // Convert 0 to -1
    int converted[7];
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            converted[i] = -1;
        } else {
            converted[i] = 1;
        }
    }

    cout << "After conversion (0 -> -1): ";
    for (int i = 0; i < n; i++) {
        cout << converted[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Now find longest subarray with sum 0
    int OFFSET = 100;
    int firstOccurrence[201];
    bool exists[201] = {false};

    firstOccurrence[0 + OFFSET] = -1;
    exists[0 + OFFSET] = true;

    int prefixSum = 0;
    int maxLen = 0;
    int bestStart = -1;
    int bestEnd = -1;

    for (int i = 0; i < n; i++) {
        prefixSum = prefixSum + converted[i];

        if (prefixSum + OFFSET >= 0 && prefixSum + OFFSET < 201 && exists[prefixSum + OFFSET]) {
            int len = i - firstOccurrence[prefixSum + OFFSET];
            if (len > maxLen) {
                maxLen = len;
                bestStart = firstOccurrence[prefixSum + OFFSET] + 1;
                bestEnd = i;
            }
        }

        if (exists[prefixSum + OFFSET] == false) {
            firstOccurrence[prefixSum + OFFSET] = i;
            exists[prefixSum + OFFSET] = true;
        }
    }

    if (maxLen > 0) {
        cout << "Longest balanced subarray length: " << maxLen << endl;
        cout << "Subarray (original): ";
        for (int i = bestStart; i <= bestEnd; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        // Count 0s and 1s
        int zeros = 0, ones = 0;
        for (int i = bestStart; i <= bestEnd; i++) {
            if (arr[i] == 0) zeros++;
            else ones++;
        }
        cout << "0s: " << zeros << ", 1s: " << ones << endl;
    } else {
        cout << "No balanced subarray found." << endl;
    }

    cout << endl;
    cout << "--- Trick ---" << endl;
    cout << "Replace 0 with -1 -> problem becomes longest subarray with sum 0" << endl;
    cout << "Same prefix sum + hash map technique!" << endl;
    cout << endl;
    cout << "Time: O(n), Space: O(n)" << endl;

    return 0;
}
