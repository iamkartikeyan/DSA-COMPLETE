// ============================================================
// 06_DC_Applications_Summary.cpp
// Summary of All Divide and Conquer Applications
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// SUMMARY OF D&C APPLICATIONS
// ============================================================

// -----------------------------------------------------------
// Quick reference implementations
// -----------------------------------------------------------

// Merge (for Merge Sort)
void merge(int arr[], int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int left[100];
    int right[100];

    for (int i = 0; i < n1; i = i + 1)
    {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j = j + 1)
    {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;
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
}

// Quick Sort partition (Lomuto)
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j = j + 1)
    {
        if (arr[j] <= pivot)
        {
            i = i + 1;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    i = i + 1;
    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;

    return i;
}

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
    cout << "  D&C Applications Summary" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- All algorithms and their properties ---
    cout << "============================================" << endl;
    cout << "  Algorithm Properties Table" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Algorithm    | Time       | Space  | Stable | In-place" << endl;
    cout << "-------------|------------|--------|--------|----------" << endl;
    cout << "Merge Sort   | O(n log n) | O(n)   | Yes    | No" << endl;
    cout << "Quick Sort   | O(n log n)*| O(log n)| No    | Yes" << endl;
    cout << "Closest Pair | O(n log n) | O(n)   | N/A    | No" << endl;
    cout << "Inv. Count   | O(n log n) | O(n)   | N/A    | No" << endl;
    cout << "Strassen's   | O(n^2.81)  | O(n^2) | N/A    | No" << endl;
    cout << endl;
    cout << "* Quick Sort worst case: O(n^2)" << endl;
    cout << endl;

    // --- Recurrence relations ---
    cout << "============================================" << endl;
    cout << "  Recurrence Relations" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Algorithm    | Recurrence           | Time" << endl;
    cout << "-------------|----------------------|----------" << endl;
    cout << "Merge Sort   | T(n)=2T(n/2)+O(n)    | O(n log n)" << endl;
    cout << "Quick Sort   | T(n)=T(k)+T(n-k)+O(n)| O(n log n)*" << endl;
    cout << "Closest Pair | T(n)=2T(n/2)+O(n)    | O(n log n)" << endl;
    cout << "Inv. Count   | T(n)=2T(n/2)+O(n)    | O(n log n)" << endl;
    cout << "Strassen's   | T(n)=7T(n/2)+O(n^2)  | O(n^2.81)" << endl;
    cout << endl;
    cout << "* Average case; worst case O(n^2)" << endl;
    cout << endl;

    // --- When to use each algorithm ---
    cout << "============================================" << endl;
    cout << "  When to Use Each Algorithm" << endl;
    cout << "============================================" << endl;
    cout << endl;

    cout << "MERGE SORT:" << endl;
    cout << "  Use when:" << endl;
    cout << "  - You need guaranteed O(n log n) time" << endl;
    cout << "  - Stability is important (equal items stay in order)" << endl;
    cout << "  - Sorting linked lists (O(1) extra space for LL)" << endl;
    cout << "  - External sorting (data on disk)" << endl;
    cout << "  Avoid when:" << endl;
    cout << "  - Memory is limited (needs O(n) extra space)" << endl;
    cout << "  - In-place sorting is required" << endl;
    cout << endl;

    cout << "QUICK SORT:" << endl;
    cout << "  Use when:" << endl;
    cout << "  - In-place sorting is needed" << endl;
    cout << "  - Average-case performance matters most" << endl;
    cout << "  - Memory is limited" << endl;
    cout << "  Avoid when:" << endl;
    cout << "  - Worst-case guarantee is needed" << endl;
    cout << "  - Stability is required" << endl;
    cout << endl;

    cout << "CLOSEST PAIR OF POINTS:" << endl;
    cout << "  Use when:" << endl;
    cout << "  - Finding nearest neighbors in 2D space" << endl;
    cout << "  - Computational geometry problems" << endl;
    cout << "  - Much faster than O(n^2) brute force" << endl;
    cout << endl;

    cout << "INVERSION COUNT:" << endl;
    cout << "  Use when:" << endl;
    cout << "  - Measuring 'sortedness' of an array" << endl;
    cout << "  - Collaborative filtering / ranking" << endl;
    cout << "  - Analyzing permutations" << endl;
    cout << endl;

    cout << "STRASSEN'S MATRIX MULTIPLICATION:" << endl;
    cout << "  Use when:" << endl;
    cout << "  - Very large matrix multiplication (n > ~1000)" << endl;
    cout << "  - Theoretical interest in faster algorithms" << endl;
    cout << "  Avoid when:" << endl;
    cout << "  - Matrices are small (naive is faster)" << endl;
    cout << "  - Numerical precision is critical" << endl;
    cout << endl;

    // --- Files in this folder ---
    cout << "============================================" << endl;
    cout << "  Files in 10.2_DC_Applications" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "01_Merge_Sort.cpp" << endl;
    cout << "  - Complete merge sort implementation" << endl;
    cout << "  - O(n log n) always, stable, O(n) space" << endl;
    cout << endl;
    cout << "02_Quick_Sort.cpp" << endl;
    cout << "  - Complete quick sort with Lomuto and Hoare" << endl;
    cout << "  - Average O(n log n), worst O(n^2), in-place" << endl;
    cout << endl;
    cout << "03_Closest_Pair_Points.cpp" << endl;
    cout << "  - Closest pair in 2D using D&C" << endl;
    cout << "  - O(n log n) vs O(n^2) brute force" << endl;
    cout << endl;
    cout << "04_Inversion_Count.cpp" << endl;
    cout << "  - Count inversions using modified merge sort" << endl;
    cout << "  - O(n log n) vs O(n^2) brute force" << endl;
    cout << endl;
    cout << "05_Strassen_Concept.cpp" << endl;
    cout << "  - Strassen's matrix multiplication concept" << endl;
    cout << "  - 7 multiplications vs 8, O(n^2.81)" << endl;
    cout << endl;
    cout << "06_DC_Applications_Summary.cpp" << endl;
    cout << "  - This file: summary of all applications" << endl;
    cout << endl;

    // --- Quick demo ---
    cout << "============================================" << endl;
    cout << "  Quick Demos" << endl;
    cout << "============================================" << endl;
    cout << endl;

    int arr1[] = {38, 27, 43, 3, 9, 82, 10};
    int n1 = 7;

    cout << "Merge Sort:" << endl;
    cout << "  Before: ";
    printArray(arr1, n1);
    merge(arr1, 0, 3, 6);
    cout << "  After merge: ";
    printArray(arr1, n1);
    cout << endl;

    int arr2[] = {10, 7, 8, 9, 1, 5};
    int n2 = 6;

    cout << "Quick Sort Partition:" << endl;
    cout << "  Before: ";
    printArray(arr2, n2);
    int pi = partition(arr2, 0, n2 - 1);
    cout << "  After partition (pivot at index " << pi << "):" << endl;
    cout << "  ";
    printArray(arr2, n2);
    cout << "  Elements left of pivot: all <= " << arr2[pi] << endl;
    cout << "  Elements right of pivot: all > " << arr2[pi] << endl;
    cout << endl;

    // --- Master Theorem recap ---
    cout << "============================================" << endl;
    cout << "  Master Theorem for All Applications" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Most D&C applications follow:" << endl;
    cout << "  T(n) = 2*T(n/2) + O(n)" << endl;
    cout << "  a = 2, b = 2, d = 1" << endl;
    cout << "  b^d = 2^1 = 2" << endl;
    cout << "  a == b^d  =>  Case 2" << endl;
    cout << "  T(n) = O(n log n)" << endl;
    cout << endl;
    cout << "Exception: Strassen's uses 7 sub-problems:" << endl;
    cout << "  T(n) = 7*T(n/2) + O(n^2)" << endl;
    cout << "  a = 7, b = 2, d = 2" << endl;
    cout << "  b^d = 4" << endl;
    cout << "  a > b^d  =>  Case 1" << endl;
    cout << "  T(n) = O(n^log_2(7)) = O(n^2.81)" << endl;

    return 0;
}
