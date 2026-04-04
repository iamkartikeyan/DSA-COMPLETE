// ============================================================
// 02_Quick_Sort.cpp
// Complete Quick Sort Implementation
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// QUICK SORT
//
// Paradigm: Divide and Conquer
//
// Steps:
//   1. DIVIDE:   Pick a pivot, partition array so that
//                elements < pivot are on the left,
//                elements > pivot are on the right
//   2. CONQUER:  Recursively sort left and right subarrays
//   3. COMBINE:  Not needed! Array is already sorted
//                after the partition step
//
// Average Time: O(n log n)
// Worst Time:   O(n^2)  -- when pivot is always min or max
// Space: O(log n) for recursion stack
// In-place: Yes (sorts within the array, no extra arrays)
// Stable: No (equal elements may change order)
// ============================================================

// -----------------------------------------------------------
// Partition: rearrange arr[low..high] around a pivot
// Returns the final position of the pivot
//
// Uses Lomuto partition scheme (pivot = last element)
// -----------------------------------------------------------

int partition(int arr[], int low, int high)
{
    // Choose last element as pivot
    int pivot = arr[high];

    // Index of smaller element
    int i = low - 1;

    // Move all elements smaller than pivot to the left
    for (int j = low; j < high; j = j + 1)
    {
        if (arr[j] <= pivot)
        {
            i = i + 1;

            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Place pivot in its correct position
    i = i + 1;
    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;

    return i;  // Return pivot's final position
}

// -----------------------------------------------------------
// Quick Sort: recursively sort arr[low..high]
// -----------------------------------------------------------

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        // Partition the array, pi = pivot index
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after pivot
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// -----------------------------------------------------------
// Alternative: Hoare Partition Scheme
// Uses first element as pivot
// Generally does fewer swaps
// -----------------------------------------------------------

int hoarePartition(int arr[], int low, int high)
{
    // Choose first element as pivot
    int pivot = arr[low];

    int i = low - 1;
    int j = high + 1;

    while (1)
    {
        // Find element from left that is >= pivot
        do
        {
            i = i + 1;
        } while (arr[i] < pivot);

        // Find element from right that is <= pivot
        do
        {
            j = j - 1;
        } while (arr[j] > pivot);

        // If pointers crossed, return
        if (i >= j)
        {
            return j;
        }

        // Swap
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void quickSortHoare(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = hoarePartition(arr, low, high);

        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
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
    cout << "  Quick Sort" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- Example 1: Basic sort ---
    int arr1[] = {10, 7, 8, 9, 1, 5};
    int n1 = 6;

    cout << "Example 1:" << endl;
    cout << "  Before: ";
    printArray(arr1, n1);

    quickSort(arr1, 0, n1 - 1);

    cout << "  After:  ";
    printArray(arr1, n1);
    cout << endl;

    // --- Example 2: Already sorted (worst case for Lomuto) ---
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = 5;

    cout << "Example 2 (already sorted - worst case):" << endl;
    cout << "  Before: ";
    printArray(arr2, n2);

    quickSort(arr2, 0, n2 - 1);

    cout << "  After:  ";
    printArray(arr2, n2);
    cout << endl;

    // --- Example 3: With duplicates ---
    int arr3[] = {3, 1, 3, 2, 1, 3, 2};
    int n3 = 7;

    cout << "Example 3 (with duplicates):" << endl;
    cout << "  Before: ";
    printArray(arr3, n3);

    quickSort(arr3, 0, n3 - 1);

    cout << "  After:  ";
    printArray(arr3, n3);
    cout << endl;

    // --- Example 4: Hoare partition ---
    int arr4[] = {15, 3, 2, 1, 9, 5, 8};
    int n4 = 7;

    cout << "Example 4 (Hoare partition):" << endl;
    cout << "  Before: ";
    printArray(arr4, n4);

    quickSortHoare(arr4, 0, n4 - 1);

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
    cout << "  Worst:  O(n^2)  -- already sorted + last element pivot" << endl;
    cout << endl;
    cout << "Space Complexity: O(log n)" << endl;
    cout << "  Recursion stack only, no extra arrays" << endl;
    cout << endl;
    cout << "Stable: No" << endl;
    cout << "  Partitioning can change order of equal elements" << endl;
    cout << endl;
    cout << "In-place: Yes" << endl;
    cout << "  Sorts within the original array" << endl;
    cout << endl;

    // --- Recurrence ---
    cout << "============================================" << endl;
    cout << "  Recurrence" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Average case (balanced partitions):" << endl;
    cout << "  T(n) = 2*T(n/2) + O(n)  => O(n log n)" << endl;
    cout << endl;
    cout << "Worst case (unbalanced, always 1 vs n-1):" << endl;
    cout << "  T(n) = T(n-1) + T(0) + O(n)  => O(n^2)" << endl;
    cout << endl;

    // --- How partition works ---
    cout << "============================================" << endl;
    cout << "  Partition Example (Lomuto, pivot = 5)" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Array: [10, 7, 8, 9, 1, 5]" << endl;
    cout << "Pivot: 5 (last element)" << endl;
    cout << endl;
    cout << "Step 1: 1 < 5, swap with position 0" << endl;
    cout << "  [1, 7, 8, 9, 10, 5]" << endl;
    cout << endl;
    cout << "Step 2: swap pivot into place" << endl;
    cout << "  [1, 5, 8, 9, 10, 7]" << endl;
    cout << endl;
    cout << "Now 5 is in its final sorted position!" << endl;
    cout << "Left of 5: all smaller (just 1)" << endl;
    cout << "Right of 5: all larger (8, 9, 10, 7)" << endl;
    cout << endl;

    // --- Quick Sort vs Merge Sort ---
    cout << "============================================" << endl;
    cout << "  Quick Sort vs Merge Sort" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "              | Quick Sort  | Merge Sort" << endl;
    cout << "--------------|-------------|------------" << endl;
    cout << "Best Time     | O(n log n)  | O(n log n)" << endl;
    cout << "Worst Time    | O(n^2)      | O(n log n)" << endl;
    cout << "Space         | O(log n)    | O(n)" << endl;
    cout << "In-place      | Yes         | No" << endl;
    cout << "Stable        | No          | Yes" << endl;
    cout << "Practical     | Faster      | Slower" << endl;
    cout << "Use when      | In-place    | Stability" << endl;
    cout << "              | needed      | needed" << endl;

    return 0;
}
