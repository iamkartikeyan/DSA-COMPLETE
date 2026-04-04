/*
 * File: 03_Frequency_Counting.cpp
 * Topic: Count occurrences using hash map
 * Description: Most common hash-based pattern
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Frequency Counting ===" << endl;
    cout << endl;

    int arr[] = {1, 2, 2, 3, 3, 3, 4, 1, 2};
    int n = 9;

    cout << "Array: 1 2 2 3 3 3 4 1 2" << endl;
    cout << endl;

    // Simple frequency counting using parallel arrays
    int keys[10];
    int counts[10];
    bool exists[10] = {false};
    int capacity = 10;

    for (int i = 0; i < n; i++) {
        int val = arr[i];
        int idx = val % capacity;

        // Linear probing to find the key
        while (exists[idx] == true && keys[idx] != val) {
            idx = (idx + 1) % capacity;
        }

        if (exists[idx] == false) {
            // New key
            keys[idx] = val;
            counts[idx] = 1;
            exists[idx] = true;
        } else {
            // Key exists, increment count
            counts[idx] = counts[idx] + 1;
        }
    }

    cout << "Frequencies:" << endl;
    for (int i = 0; i < capacity; i++) {
        if (exists[i] == true) {
            cout << "  " << keys[i] << " -> " << counts[i] << " times" << endl;
        }
    }

    cout << endl;
    cout << "--- Pattern ---" << endl;
    cout << "unordered_map<int, int> freq;" << endl;
    cout << "for (int x : arr) freq[x]++;" << endl;
    cout << endl;
    cout << "This auto-initializes to 0, so freq[x]++ works" << endl;
    cout << "even on first occurrence." << endl;
    cout << endl;
    cout << "Used in: Top K frequent, duplicates check," << endl;
    cout << "         anagram check, mode finding" << endl;

    return 0;
}
