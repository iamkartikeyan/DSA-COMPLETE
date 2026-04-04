/*
 * File: 01_Hash_Set_Demo.cpp
 * Topic: unordered_set - Store unique elements
 * Description: Insert, search, delete in hash set
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Hash Set (unordered_set) ===" << endl;
    cout << endl;

    /*
     * Hash Set stores UNIQUE elements.
     * Duplicate inserts are ignored.
     * O(1) average for insert, search, delete.
     */

    // Simple manual hash set demo
    // Using an array of buckets (boolean flags for simplicity)

    int seen[10] = {0}; // 0 = not seen, 1 = seen
    int capacity = 10;

    // Insert values
    int values[] = {5, 3, 7, 3, 8}; // 3 is duplicate
    int n = 5;

    cout << "Inserting: 5 3 7 3 8" << endl;
    cout << "(3 is duplicate, will be ignored)" << endl;
    cout << endl;

    int count = 0;
    for (int i = 0; i < n; i++) {
        int val = values[i];
        int idx = val % capacity;

        if (seen[idx] == 0) {
            seen[idx] = 1;
            count = count + 1;
            cout << "Inserted " << val << endl;
        } else {
            cout << val << " already exists (ignored)" << endl;
        }
    }

    cout << endl;
    cout << "Set size: " << count << endl;
    cout << endl;

    // Search
    cout << "--- Search ---" << endl;
    int search1 = 7;
    int idx1 = search1 % capacity;
    if (seen[idx1] == 1) {
        cout << "Contains " << search1 << ": Yes" << endl;
    } else {
        cout << "Contains " << search1 << ": No" << endl;
    }

    int search2 = 9;
    int idx2 = search2 % capacity;
    if (seen[idx2] == 1) {
        cout << "Contains " << search2 << ": Yes" << endl;
    } else {
        cout << "Contains " << search2 << ": No" << endl;
    }

    cout << endl;
    cout << "--- STL unordered_set ---" << endl;
    cout << "Operations: insert(), count() or find(), erase(), size(), empty()" << endl;
    cout << "count(x) returns 1 if exists, 0 if not" << endl;

    return 0;
}
