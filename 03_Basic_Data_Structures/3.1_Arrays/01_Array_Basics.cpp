/*
 * File: 01_Array_Basics.cpp
 * Topic: What is Array, 1D Array declaration, access, memory
 * Description: Foundation of all data structures
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Array Basics ===" << endl;
    cout << endl;

    // --- Declaration ---
    int arr[5]; // uninitialized array of 5 integers
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    // --- Declaration + Initialization ---
    int arr2[5] = {1, 2, 3, 4, 5};

    // --- Partial initialization (rest = 0) ---
    int arr3[5] = {1, 2}; // arr3[2]=0, arr3[3]=0, arr3[4]=0

    // --- Auto-size ---
    int arr4[] = {10, 20, 30}; // compiler sets size = 3

    cout << "arr[0] = " << arr[0] << endl;
    cout << "arr[4] = " << arr[4] << endl;
    cout << endl;

    // --- Print all elements ---
    cout << "arr2: ";
    for (int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    // --- Array memory layout ---
    cout << endl;
    cout << "--- Memory Layout ---" << endl;
    cout << "Arrays store elements in CONTIGUOUS (consecutive) memory." << endl;
    cout << endl;
    cout << "Address of arr[0]: " << &arr2[0] << endl;
    cout << "Address of arr[1]: " << &arr2[1] << endl;
    cout << "Address of arr[2]: " << &arr2[2] << endl;
    cout << "Each int is 4 bytes apart." << endl;

    cout << endl;
    cout << "--- Key Points ---" << endl;
    cout << "1. Index starts from 0" << endl;
    cout << "2. Size is FIXED at compile time (static array)" << endl;
    cout << "3. O(1) access: arr[i] gives value instantly" << endl;
    cout << "4. O(n) insert/delete: need to shift elements" << endl;
    cout << "5. No bounds checking in C++ (arr[100] won't error)" << endl;

    return 0;
}
