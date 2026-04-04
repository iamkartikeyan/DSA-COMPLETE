/*
 * File: 04_Vector_Dynamic_Array.cpp
 * Topic: C++ vector - Dynamic array that grows automatically
 * Description: Insert, delete, resize without manual management
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Vector (Dynamic Array) ===" << endl;
    cout << endl;

    // --- Create vectors ---
    vector<int> v1;                // empty vector
    vector<int> v2(5);             // vector of 5 zeros
    vector<int> v3(5, 10);         // vector of 5 tens
    int arr[] = {1, 2, 3, 4, 5};
    vector<int> v4(arr, arr + 5);  // from array

    cout << "v2 (5 zeros): ";
    for (int i = 0; i < 5; i++) cout << v2[i] << " ";
    cout << endl;

    cout << "v3 (5 tens): ";
    for (int i = 0; i < 5; i++) cout << v3[i] << " ";
    cout << endl;
    cout << endl;

    // --- Push back (add at end) ---
    cout << "--- Push Back ---" << endl;
    vector<int> nums;
    nums.push_back(10);
    nums.push_back(20);
    nums.push_back(30);
    cout << "After push 10, 20, 30: ";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;

    // --- Insert at position ---
    cout << endl;
    cout << "--- Insert at position ---" << endl;
    cout << "Before: ";
    for (int i = 0; i < nums.size(); i++) cout << nums[i] << " ";
    cout << endl;

    nums.insert(nums.begin() + 1, 15); // insert 15 at index 1
    cout << "After insert 15 at index 1: ";
    for (int i = 0; i < nums.size(); i++) cout << nums[i] << " ";
    cout << endl;

    // --- Erase ---
    cout << endl;
    cout << "--- Erase ---" << endl;
    nums.erase(nums.begin() + 2); // erase element at index 2
    cout << "After erase at index 2: ";
    for (int i = 0; i < nums.size(); i++) cout << nums[i] << " ";
    cout << endl;

    // --- Pop back ---
    nums.pop_back();
    cout << "After pop_back: ";
    for (int i = 0; i < nums.size(); i++) cout << nums[i] << " ";
    cout << endl;

    // --- Useful functions ---
    cout << endl;
    cout << "--- Useful Functions ---" << endl;
    cout << "Size: " << nums.size() << endl;
    cout << "Capacity: " << nums.capacity() << endl;
    cout << "Empty? " << (nums.empty() ? "Yes" : "No") << endl;
    cout << "Front: " << nums.front() << endl;
    cout << "Back: " << nums.back() << endl;

    // --- Clear ---
    nums.clear();
    cout << "After clear, size: " << nums.size() << endl;

    cout << endl;
    cout << "--- Vector vs Array ---" << endl;
    cout << "Array:       Fixed size, no auto-resize" << endl;
    cout << "Vector:      Dynamic size, auto-resize, O(1) amortized push" << endl;
    cout << endl;
    cout << "Vector doubles capacity when full -> amortized O(1) push_back" << endl;

    return 0;
}
