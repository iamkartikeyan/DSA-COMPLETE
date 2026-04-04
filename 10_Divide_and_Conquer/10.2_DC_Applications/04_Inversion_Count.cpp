// ============================================================
// 04_Inversion_Count.cpp
// Count Inversions using Modified Merge Sort
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// INVERSION COUNT
//
// An inversion is a pair (i, j) such that:
//   i < j  AND  arr[i] > arr[j]
//
// Example: arr = [2, 4, 1, 3, 5]
// Inversions: (2,1), (4,1), (4,3)  =>  3 inversions
//
// Uses:
//   - Measure how "unsorted" an array is
//   - 0 inversions = already sorted
//   - n*(n-1)/2 inversions = reverse sorted
//
// Brute Force: Check all pairs => O(n^2)
// Modified Merge Sort: => O(n log n)
//
// Key idea: During merge step, when we pick an element
// from the RIGHT subarray before elements remaining in
// the LEFT subarray, each remaining left element forms
// an inversion with the right element.
// ============================================================

// -----------------------------------------------------------
// Merge and count inversions
// Merges arr[low..mid] and arr[mid+1..high]
// Returns the number of inversions found during merge
// -----------------------------------------------------------

int mergeAndCount(int arr[], int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[1000];
    int right[1000];

    for (int i = 0; i < n1; i = i + 1)
    {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j = j + 1)
    {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = low;
    int invCount = 0;

    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            // No inversion: left element is smaller or equal
            arr[k] = left[i];
            i = i + 1;
        }
        else
        {
            // INVERSION FOUND!
            // right[j] < left[i], and right[j] should come
            // after left[i] in sorted order.
            // So right[j] forms inversions with ALL remaining
            // elements in left[] (from index i to n1-1).
            arr[k] = right[j];
            j = j + 1;
            invCount = invCount + (n1 - i);
        }
        k = k + 1;
    }

    // Copy remaining elements
    while (i < n1)
    {
        arr[k] = left[i];
        i = i + 1;
        k = k + 1;
    }

    while (j < n2)
    {
        arr[k] = right[j];
        j = j + 1;
        k = k + 1;
    }

    return invCount;
}

// -----------------------------------------------------------
// Count inversions using modified merge sort
// Returns the number of inversions in arr[low..high]
// Also sorts the array as a side effect
// -----------------------------------------------------------

int countInversions(int arr[], int low, int high)
{
    int invCount = 0;

    if (low < high)
    {
        int mid = (low + high) / 2;

        // Count inversions in left half
        invCount = invCount + countInversions(arr, low, mid);

        // Count inversions in right half
        invCount = invCount + countInversions(arr, mid + 1, high);

        // Count inversions during merge
        invCount = invCount + mergeAndCount(arr, low, mid, high);
    }

    return invCount;
}

// -----------------------------------------------------------
// Brute force inversion count (for verification)
// O(n^2) but simple and correct
// -----------------------------------------------------------

int bruteForceCount(int arr[], int n)
{
    int count = 0;

    for (int i = 0; i < n - 1; i = i + 1)
    {
        for (int j = i + 1; j < n; j = j + 1)
        {
            if (arr[i] > arr[j])
            {
                count = count + 1;
            }
        }
    }

    return count;
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
    cout << "  Inversion Count (Modified Merge Sort)" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- Example 1: Basic case ---
    int arr1[] = {2, 4, 1, 3, 5};
    int n1 = 5;

    cout << "Example 1:" << endl;
    cout << "  Array: ";
    printArray(arr1, n1);

    // Brute force for verification
    int bf1 = bruteForceCount(arr1, n1);
    cout << "  Brute Force: " << bf1 << " inversions" << endl;

    // D&C approach
    int arr1Copy[] = {2, 4, 1, 3, 5};
    int dc1 = countInversions(arr1Copy, 0, n1 - 1);
    cout << "  D&C: " << dc1 << " inversions" << endl;
    cout << "  Inversions: (2,1), (4,1), (4,3)" << endl;
    cout << endl;

    // --- Example 2: Already sorted (0 inversions) ---
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = 5;

    cout << "Example 2 (sorted):" << endl;
    cout << "  Array: ";
    printArray(arr2, n2);

    int dc2 = countInversions(arr2, 0, n2 - 1);
    cout << "  Inversions: " << dc2 << endl;
    cout << endl;

    // --- Example 3: Reverse sorted (maximum inversions) ---
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = 5;

    cout << "Example 3 (reverse sorted):" << endl;
    cout << "  Array: ";
    printArray(arr3, n3);

    int bf3 = bruteForceCount(arr3, n3);
    int arr3Copy[] = {5, 4, 3, 2, 1};
    int dc3 = countInversions(arr3Copy, 0, n3 - 1);
    cout << "  Inversions: " << dc3 << endl;
    cout << "  Maximum for n=5: n*(n-1)/2 = " << 5 * 4 / 2 << endl;
    cout << endl;

    // --- Example 4: With duplicates ---
    int arr4[] = {1, 3, 5, 2, 4, 6};
    int n4 = 6;

    cout << "Example 4:" << endl;
    cout << "  Array: ";
    printArray(arr4, n4);

    int bf4 = bruteForceCount(arr4, n4);
    int arr4Copy[] = {1, 3, 5, 2, 4, 6};
    int dc4 = countInversions(arr4Copy, 0, n4 - 1);
    cout << "  Brute Force: " << bf4 << " inversions" << endl;
    cout << "  D&C: " << dc4 << " inversions" << endl;
    cout << endl;

    // --- How counting works during merge ---
    cout << "============================================" << endl;
    cout << "  How Inversions are Counted During Merge" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "When merging [2, 4] and [1, 3, 5]:" << endl;
    cout << endl;
    cout << "  Compare 2 vs 1: 1 < 2, pick 1 from right" << endl;
    cout << "  INVERSIONS! 1 should come before 2 and 4" << endl;
    cout << "  Count += 2 (remaining in left: 2, 4)" << endl;
    cout << endl;
    cout << "  Compare 2 vs 3: 2 < 3, pick 2 from left" << endl;
    cout << "  No inversion" << endl;
    cout << endl;
    cout << "  Compare 4 vs 3: 3 < 4, pick 3 from right" << endl;
    cout << "  INVERSIONS! 3 should come before 4" << endl;
    cout << "  Count += 1 (remaining in left: 4)" << endl;
    cout << endl;
    cout << "  Copy remaining: 4, 5" << endl;
    cout << "  No more inversions" << endl;
    cout << endl;
    cout << "  Total from this merge: 2 + 1 = 3" << endl;
    cout << endl;

    // --- Complexity ---
    cout << "============================================" << endl;
    cout << "  Complexity" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Brute Force:  O(n^2) -- check all pairs" << endl;
    cout << "Modified Merge Sort: O(n log n)" << endl;
    cout << endl;
    cout << "Recurrence: T(n) = 2*T(n/2) + O(n)" << endl;
    cout << "  Same as Merge Sort!" << endl;
    cout << "  T(n) = O(n log n)" << endl;
    cout << endl;

    // --- What inversions tell us ---
    cout << "============================================" << endl;
    cout << "  What Inversions Tell Us" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "0 inversions      => Already sorted" << endl;
    cout << "n*(n-1)/2         => Reverse sorted" << endl;
    cout << "Few inversions    => Nearly sorted" << endl;
    cout << "Many inversions   => Far from sorted" << endl;

    return 0;
}
