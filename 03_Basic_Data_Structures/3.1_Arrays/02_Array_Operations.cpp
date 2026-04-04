/*
 * File: 02_Array_Operations.cpp
 * Topic: Traversal, Insert, Delete, Search in array
 * Description: Basic array operations
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Array Operations ===" << endl;
    cout << endl;

    int arr[10]; // capacity = 10
    int n = 0;   // current number of elements

    // --- Insert ---
    arr[0] = 10; n++;
    arr[1] = 20; n++;
    arr[2] = 30; n++;
    arr[3] = 50; n++;

    cout << "After inserts: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << endl;

    // --- Traversal ---
    cout << "--- Traversal ---" << endl;
    cout << "Elements: ";
    for (int i = 0; i < n; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    // --- Search ---
    cout << endl;
    cout << "--- Search ---" << endl;
    int target = 30;
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            cout << "Found " << target << " at index " << i << endl;
            found = true;
            break;
        }
    }
    if (found == false) {
        cout << target << " not found" << endl;
    }

    // --- Insert at position ---
    cout << endl;
    cout << "--- Insert 40 at position 3 ---" << endl;
    int pos = 3;
    int val = 40;

    // Shift elements to the right
    for (int i = n - 1; i >= pos; i--) {
        arr[i + 1] = arr[i];
    }
    arr[pos] = val;
    n++;

    cout << "After insert: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // --- Delete at position ---
    cout << endl;
    cout << "--- Delete element at position 2 ---" << endl;
    pos = 2;

    // Shift elements to the left
    for (int i = pos; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--;

    cout << "After delete: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << endl;
    cout << "--- Complexity ---" << endl;
    cout << "Access:  O(1)" << endl;
    cout << "Search:  O(n) - may scan all elements" << endl;
    cout << "Insert:  O(n) - need to shift" << endl;
    cout << "Delete:  O(n) - need to shift" << endl;

    return 0;
}
