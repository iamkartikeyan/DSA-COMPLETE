/*
 * File: 02_Hash_Map_Demo.cpp
 * Topic: unordered_map - Key-value pairs
 * Description: Insert, update, search in hash map
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Hash Map (unordered_map) ===" << endl;
    cout << endl;

    /*
     * Hash Map stores KEY -> VALUE pairs.
     * O(1) average for insert, search, update.
     */

    // Simple demo: store name -> age using parallel arrays
    // (In practice, use STL unordered_map)

    string keys[10];
    int values[10];
    bool exists[10] = {false};
    int capacity = 10;

    // Insert entries
    string names[] = {"Alice", "Bob", "Carol"};
    int ages[] = {25, 30, 28};
    int n = 3;

    for (int i = 0; i < n; i++) {
        // Simple hash: first char % capacity
        int idx = names[i][0] % capacity;

        // Linear probing if collision
        while (exists[idx] == true) {
            idx = (idx + 1) % capacity;
        }

        keys[idx] = names[i];
        values[idx] = ages[i];
        exists[idx] = true;
    }

    cout << "Inserted:" << endl;
    cout << "  Alice -> 25" << endl;
    cout << "  Bob   -> 30" << endl;
    cout << "  Carol -> 28" << endl;
    cout << endl;

    // Search
    cout << "--- Search ---" << endl;
    string searchKey = "Bob";
    int idx = searchKey[0] % capacity;
    int steps = 0;
    bool found = false;

    while (steps < capacity) {
        if (exists[idx] == true && keys[idx] == searchKey) {
            cout << searchKey << "'s age: " << values[idx] << endl;
            found = true;
            break;
        }
        if (exists[idx] == false) {
            break; // not found
        }
        idx = (idx + 1) % capacity;
        steps = steps + 1;
    }

    if (found == false) {
        cout << searchKey << " not found" << endl;
    }

    // Update
    cout << endl;
    cout << "--- Update Bob to 31 ---" << endl;
    idx = searchKey[0] % capacity;
    steps = 0;
    while (steps < capacity) {
        if (exists[idx] == true && keys[idx] == searchKey) {
            values[idx] = 31;
            cout << searchKey << "'s updated age: " << values[idx] << endl;
            break;
        }
        idx = (idx + 1) % capacity;
        steps = steps + 1;
    }

    cout << endl;
    cout << "--- Common Patterns ---" << endl;
    cout << "Frequency counting: freq[x]++" << endl;
    cout << "Grouping: map<key, vector<value>>" << endl;
    cout << "Index tracking: map<value, index>" << endl;
    cout << endl;
    cout << "unordered_map: O(1) avg, no ordering" << endl;
    cout << "map:           O(log n), sorted order (BST-based)" << endl;

    return 0;
}
