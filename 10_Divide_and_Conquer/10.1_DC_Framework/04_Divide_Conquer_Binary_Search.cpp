// ============================================================
// 04_Divide_Conquer_Binary_Search.cpp
// Recursive Binary Search as a Divide and Conquer Example
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// BINARY SEARCH AS DIVIDE AND CONQUER
// ============================================================
//
// Divide:   Compare target with middle element
// Conquer:  Search in the left half OR right half
// Combine:  Not needed (just return the result)
//
// Precondition: Array must be SORTED
//
// Recurrence: T(n) = T(n/2) + O(1)
//   a = 1  (one sub-problem)
//   b = 2  (half the size)
//   d = 0  (comparison is O(1))
//   b^d = 2^0 = 1
//   a == b^d  =>  Case 2
//   T(n) = O(log n)
//
// Space: O(log n) for recursion stack
// ============================================================

// -----------------------------------------------------------
// Recursive Binary Search
// Returns the index of key if found, -1 otherwise
// -----------------------------------------------------------

int binarySearch(int arr[], int low, int high, int key)
{
    // Base case: key not found
    if (low > high)
    {
        return -1;
    }

    // Divide: find the middle
    int mid = (low + high) / 2;

    // Check middle element
    if (arr[mid] == key)
    {
        return mid;  // Found!
    }

    // Conquer: search in the appropriate half
    if (key < arr[mid])
    {
        // Key is smaller, search left half
        return binarySearch(arr, low, mid - 1, key);
    }
    else
    {
        // Key is larger, search right half
        return binarySearch(arr, mid + 1, high, key);
    }
}

// -----------------------------------------------------------
// Iterative Binary Search (for comparison)
// Same O(log n) time but O(1) space
// -----------------------------------------------------------

int binarySearchIterative(int arr[], int low, int high, int key)
{
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
        {
            return mid;
        }
        else if (key < arr[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return -1;
}

// -----------------------------------------------------------
// Helper to print array
// -----------------------------------------------------------

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i = i + 1)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ============================================================

int main()
{
    cout << "============================================" << endl;
    cout << "  Binary Search as Divide and Conquer" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // Sorted array (required for binary search)
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int n = 11;

    cout << "Sorted Array: ";
    printArray(arr, n);
    cout << endl;

    // --- Search for existing element ---
    int key1 = 23;
    cout << "--- Searching for " << key1 << " ---" << endl;

    int idx1 = binarySearch(arr, 0, n - 1, key1);
    cout << "  Recursive: ";
    if (idx1 == -1)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << "Found at index " << idx1 << endl;
    }

    int idx2 = binarySearchIterative(arr, 0, n - 1, key1);
    cout << "  Iterative: ";
    if (idx2 == -1)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << "Found at index " << idx2 << endl;
    }
    cout << endl;

    // --- Search for element not in array ---
    int key2 = 50;
    cout << "--- Searching for " << key2 << " ---" << endl;

    int idx3 = binarySearch(arr, 0, n - 1, key2);
    cout << "  Recursive: ";
    if (idx3 == -1)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << "Found at index " << idx3 << endl;
    }

    int idx4 = binarySearchIterative(arr, 0, n - 1, key2);
    cout << "  Iterative: ";
    if (idx4 == -1)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << "Found at index " << idx4 << endl;
    }
    cout << endl;

    // --- Search for first and last elements ---
    int key3 = 2;
    cout << "--- Searching for " << key3 << " (first element) ---" << endl;
    int idx5 = binarySearch(arr, 0, n - 1, key3);
    cout << "  Found at index " << idx5 << endl;
    cout << endl;

    int key4 = 78;
    cout << "--- Searching for " << key4 << " (last element) ---" << endl;
    int idx6 = binarySearch(arr, 0, n - 1, key4);
    cout << "  Found at index " << idx6 << endl;
    cout << endl;

    // --- How D&C applies to Binary Search ---
    cout << "============================================" << endl;
    cout << "  How Binary Search is Divide and Conquer" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "DIVIDE:   Compare key with middle element." << endl;
    cout << "          This splits the problem in half." << endl;
    cout << endl;
    cout << "CONQUER:  Recursively search only ONE half." << endl;
    cout << "          The other half is discarded." << endl;
    cout << endl;
    cout << "COMBINE:  Not needed. The recursive call" << endl;
    cout << "          directly returns the answer." << endl;
    cout << endl;

    // --- Recurrence ---
    cout << "============================================" << endl;
    cout << "  Recurrence" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "T(n) = T(n/2) + O(1)" << endl;
    cout << "  a = 1, b = 2, d = 0" << endl;
    cout << "  b^d = 1" << endl;
    cout << "  a == b^d  =>  Master Theorem Case 2" << endl;
    cout << "  T(n) = O(log n)" << endl;
    cout << endl;

    // --- Visualizing the search ---
    cout << "============================================" << endl;
    cout << "  Visualizing Search for 23" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Step 1: [2 5 8 12 16 23 38 45 56 67 78]" << endl;
    cout << "         ^             ^             ^" << endl;
    cout << "        low          mid            high" << endl;
    cout << "         arr[mid]=23 == key. Found!" << endl;
    cout << endl;
    cout << "Searching for 5:" << endl;
    cout << "Step 1: [2 5 8 12 16 23 38 45 56 67 78]" << endl;
    cout << "         ^             ^             ^" << endl;
    cout << "        arr[mid]=23 > 5, go LEFT" << endl;
    cout << endl;
    cout << "Step 2: [2 5 8 12 16]" << endl;
    cout << "         ^  ^     ^" << endl;
    cout << "      arr[mid]=8 > 5, go LEFT" << endl;
    cout << endl;
    cout << "Step 3: [2 5]" << endl;
    cout << "         ^^" << endl;
    cout << "      arr[mid]=5 == key. Found!" << endl;

    return 0;
}
