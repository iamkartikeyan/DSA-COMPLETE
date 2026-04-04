// 13.1 - Merge Sorted Arrays and Intersection
// Merge two sorted arrays (normal + in-place from end).
// Also: find intersection of two sorted arrays.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

const int MAX = 100;

// --- Merge two sorted arrays into a new array ---
int mergeSorted(int a[], int n, int b[], int m, int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (a[i] <= b[j]) {
            result[k++] = a[i++];
        } else {
            result[k++] = b[j++];
        }
    }
    while (i < n) result[k++] = a[i++];
    while (j < m) result[k++] = b[j++];
    return k;  // Total elements
}

// --- Merge sorted in-place: nums1 has extra space at end ---
// Start from END to avoid overwriting unprocessed elements
void mergeInPlace(int nums1[], int m, int nums2[], int n) {
    int i = m - 1;      // Last element of valid part in nums1
    int j = n - 1;      // Last element of nums2
    int k = m + n - 1;  // Last position in nums1

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
            k--;
        } else {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
    // Copy remaining nums2 elements (if any)
    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
}

// --- Intersection of two sorted arrays ---
int intersection(int a[], int n, int b[], int m, int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            // Avoid duplicates in result
            if (k == 0 || result[k - 1] != a[i]) {
                result[k++] = a[i];
            }
            i++;
            j++;
        } else if (a[i] < b[j]) {
            i++;
        } else {
            j++;
        }
    }
    return k;  // Number of intersection elements
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Merge Sorted Arrays and Intersection ===" << endl;
    cout << endl;

    // --- Part 1: Merge into new array ---
    cout << "--- Merge into New Array ---" << endl;
    int a[] = {1, 4, 7};
    int b[] = {2, 3, 6, 8};
    int n = 3, m = 4;

    cout << "Array A: ";
    printArray(a, n);
    cout << "Array B: ";
    printArray(b, m);

    int result[MAX];
    int total = mergeSorted(a, n, b, m, result);

    cout << "Merged: ";
    printArray(result, total);
    cout << endl;

    cout << "Approach: Two pointers i, j on each array." << endl;
    cout << "  Compare a[i] and b[j], pick the smaller one." << endl;
    cout << "  Time: O(n + m), Space: O(n + m) for result" << endl;
    cout << endl;

    // --- Part 2: Merge in-place from end ---
    cout << "--- Merge In-Place (from end) ---" << endl;
    int nums1[] = {1, 3, 5, 0, 0, 0};  // Last 3 slots are empty
    int nums2[] = {2, 4, 6};
    int m2 = 3, n2b = 3;
    int totalSize = m2 + n2b;

    cout << "Before: nums1 = {1, 3, 5, _, _, _}, nums2 = {2, 4, 6}" << endl;
    mergeInPlace(nums1, m2, nums2, n2b);
    cout << "After:  ";
    printArray(nums1, totalSize);
    cout << endl;

    cout << "Why start from END?" << endl;
    cout << "  - nums1 has empty space at the end" << endl;
    cout << "  - Filling from back avoids overwriting unprocessed elements" << endl;
    cout << "  - Time: O(n + m), Space: O(1)" << endl;
    cout << endl;

    // --- Part 3: Intersection ---
    cout << "--- Intersection of Sorted Arrays ---" << endl;
    int arr1[] = {1, 2, 2, 3, 5};
    int arr2[] = {2, 2, 5, 7};
    int n1 = 5, n2c = 4;

    cout << "Array A: ";
    printArray(arr1, n1);
    cout << "Array B: ";
    printArray(arr2, n2c);

    int inter[MAX];
    int interCount = intersection(arr1, n1, arr2, n2c, inter);

    cout << "Intersection: ";
    printArray(inter, interCount);
    cout << endl;

    cout << "Approach: Two pointers, advance both on match." << endl;
    cout << "  Skip duplicates to get unique intersection." << endl;
    cout << "  Time: O(n + m), Space: O(1) excluding result" << endl;

    return 0;
}
