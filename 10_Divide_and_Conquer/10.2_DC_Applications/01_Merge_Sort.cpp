// ============================================================
// 01_Merge_Sort.cpp
// Complete Merge Sort Implementation
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// MERGE SORT
//
// Paradigm: Divide and Conquer
//
// Steps:
//   1. DIVIDE:   Split array into two halves
//   2. CONQUER:  Recursively sort each half
//   3. COMBINE:  Merge the two sorted halves
//
// Recurrence: T(n) = 2*T(n/2) + O(n)
//   a = 2, b = 2, d = 1
//   b^d = 2^1 = 2
//   a == b^d  =>  Case 2
//   T(n) = O(n log n)
//
// Properties:
//   - Time:  O(n log n) always (best, avg, worst)
//   - Space: O(n) for temporary arrays
//   - Stable: Yes (equal elements keep their order)
//   - Not in-place (needs extra space)
// ============================================================

// -----------------------------------------------------------
// Merge two sorted subarrays: arr[low..mid] and arr[mid+1..high]
// -----------------------------------------------------------

void merge(int arr[], int low, int mid, int high)
{
    // Sizes of the two subarrays
    int n1 = mid - low + 1;
    int n2 = high - mid;

    // Create temporary arrays
    int left[1000];
    int right[1000];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i = i + 1)
    {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j = j + 1)
    {
        right[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back into arr[low..high]
    int i = 0;  // Index for left subarray
    int j = 0;  // Index for right subarray
    int k = low; // Index for merged array

    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i = i + 1;
        }
        else
        {
            arr[k] = right[j];
            j = j + 1;
        }
        k = k + 1;
    }

    // Copy remaining elements from left (if any)
    while (i < n1)
    {
        arr[k] = left[i];
        i = i + 1;
        k = k + 1;
    }

    // Copy remaining elements from right (if any)
    while (j < n2)
    {
        arr[k] = right[j];
        j = j + 1;
        k = k + 1;
    }
}

// -----------------------------------------------------------
// Merge Sort: recursively sort arr[low..high]
// -----------------------------------------------------------

void mergeSort(int arr[], int low, int high)
{
    // Base case: array of size 1 is already sorted
    if (low >= high)
    {
        return;
    }

    // Divide: find the middle
    int mid = (low + high) / 2;

    // Conquer: recursively sort both halves
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    // Combine: merge the sorted halves
    merge(arr, low, mid, high);
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
    cout << "  Merge Sort" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- Example 1: Basic sort ---
    int arr1[] = {38, 27, 43, 3, 9, 82, 10};
    int n1 = 7;

    cout << "Example 1:" << endl;
    cout << "  Before: ";
    printArray(arr1, n1);

    mergeSort(arr1, 0, n1 - 1);

    cout << "  After:  ";
    printArray(arr1, n1);
    cout << endl;

    // --- Example 2: Already sorted ---
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = 5;

    cout << "Example 2 (already sorted):" << endl;
    cout << "  Before: ";
    printArray(arr2, n2);

    mergeSort(arr2, 0, n2 - 1);

    cout << "  After:  ";
    printArray(arr2, n2);
    cout << endl;

    // --- Example 3: Reverse sorted ---
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = 5;

    cout << "Example 3 (reverse sorted):" << endl;
    cout << "  Before: ";
    printArray(arr3, n3);

    mergeSort(arr3, 0, n3 - 1);

    cout << "  After:  ";
    printArray(arr3, n3);
    cout << endl;

    // --- Example 4: With duplicates ---
    int arr4[] = {4, 2, 4, 1, 3, 2, 1};
    int n4 = 7;

    cout << "Example 4 (with duplicates):" << endl;
    cout << "  Before: ";
    printArray(arr4, n4);

    mergeSort(arr4, 0, n4 - 1);

    cout << "  After:  ";
    printArray(arr4, n4);
    cout << endl;

    // --- Properties ---
    cout << "============================================" << endl;
    cout << "  Properties" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Time Complexity:" << endl;
    cout << "  Best:   O(n log n)" << endl;
    cout << "  Average: O(n log n)" << endl;
    cout << "  Worst:  O(n log n)" << endl;
    cout << "  Always the same, no worst case!" << endl;
    cout << endl;
    cout << "Space Complexity: O(n)" << endl;
    cout << "  Needs temporary arrays for merging" << endl;
    cout << endl;
    cout << "Stable: Yes" << endl;
    cout << "  Equal elements keep their relative order" << endl;
    cout << endl;
    cout << "In-place: No" << endl;
    cout << "  Requires extra space for temporary arrays" << endl;
    cout << endl;

    // --- Recurrence ---
    cout << "============================================" << endl;
    cout << "  Recurrence" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "T(n) = 2*T(n/2) + O(n)" << endl;
    cout << "  a = 2, b = 2, d = 1" << endl;
    cout << "  b^d = 2^1 = 2" << endl;
    cout << "  a == b^d  =>  Master Theorem Case 2" << endl;
    cout << "  T(n) = O(n^1 * log(n)) = O(n log n)" << endl;
    cout << endl;

    // --- Merge step visualization ---
    cout << "============================================" << endl;
    cout << "  How Merge Works (Example)" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Merging [3, 27, 38] and [9, 43, 82]:" << endl;
    cout << "  Compare 3 vs 9  -> pick 3" << endl;
    cout << "  Compare 27 vs 9 -> pick 9" << endl;
    cout << "  Compare 27 vs 43-> pick 27" << endl;
    cout << "  Compare 38 vs 43-> pick 38" << endl;
    cout << "  Right has 43, 82 remaining" << endl;
    cout << "  Result: [3, 9, 27, 38, 43, 82]" << endl;

    return 0;
}
