// 13.1 - Two Pointers Summary
// Complete summary of all two pointers patterns and problems.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int minVal(int a, int b) {
    return (a < b) ? a : b;
}

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Pair Sum (opposite ends)
bool pairSum(int arr[], int n, int target, int &outL, int &outR) {
    int left = 0, right = n - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) { outL = left; outR = right; return true; }
        if (sum < target) left++;
        else right--;
    }
    return false;
}

// Remove Duplicates (same direction)
int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    int slow = 1;
    for (int fast = 1; fast < n; fast++) {
        if (arr[fast] != arr[fast - 1]) {
            arr[slow++] = arr[fast];
        }
    }
    return slow;
}

// Move Zeroes (same direction)
void moveZeroes(int arr[], int n) {
    int slow = 0;
    for (int fast = 0; fast < n; fast++) {
        if (arr[fast] != 0) swap(arr[slow++], arr[fast]);
    }
}

// Container With Most Water (opposite ends)
int maxArea(int height[], int n) {
    int left = 0, right = n - 1, maxWater = 0;
    while (left < right) {
        int area = minVal(height[left], height[right]) * (right - left);
        maxWater = maxVal(maxWater, area);
        if (height[left] < height[right]) left++;
        else right--;
    }
    return maxWater;
}

// Reverse Array (opposite ends)
void reverseArray(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) swap(arr[left++], arr[right--]);
}

// Is Palindrome (opposite ends)
bool isPalindrome(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        if (arr[left] != arr[right]) return false;
        left++;
        right--;
    }
    return true;
}

// Merge Sorted Arrays
void mergeSorted(int a[], int n, int b[], int m, int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (a[i] <= b[j]) result[k++] = a[i++];
        else result[k++] = b[j++];
    }
    while (i < n) result[k++] = a[i++];
    while (j < m) result[k++] = b[j++];
}

// Merge In-Place (from end)
void mergeInPlace(int nums1[], int m, int nums2[], int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
    while (j >= 0) nums1[k--] = nums2[j--];
}

// Intersection
int intersection(int a[], int n, int b[], int m, int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            if (k == 0 || result[k - 1] != a[i]) result[k++] = a[i];
            i++; j++;
        } else if (a[i] < b[j]) {
            i++;
        } else {
            j++;
        }
    }
    return k;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    cout << "=== Two Pointers Complete Summary ===" << endl;
    cout << endl;

    cout << "+-------------------+-------------------+-------------------+" << endl;
    cout << "| Problem           | Pattern           | Complexity        |" << endl;
    cout << "+-------------------+-------------------+-------------------+" << endl;
    cout << "| Pair Sum          | Opposite Ends     | O(n) time, O(1)   |" << endl;
    cout << "| Three Sum         | Fix + Opp. Ends   | O(n^2) time, O(1) |" << endl;
    cout << "| Container Water   | Opposite Ends     | O(n) time, O(1)   |" << endl;
    cout << "| Reverse Array     | Opposite Ends     | O(n) time, O(1)   |" << endl;
    cout << "| Palindrome Check  | Opposite Ends     | O(n) time, O(1)   |" << endl;
    cout << "| Remove Duplicates | Same Direction    | O(n) time, O(1)   |" << endl;
    cout << "| Move Zeroes       | Same Direction    | O(n) time, O(1)   |" << endl;
    cout << "| Merge Sorted      | Same Direction    | O(n+m) time, O(n) |" << endl;
    cout << "| Merge In-Place    | Same Dir (reverse)| O(n+m) time, O(1) |" << endl;
    cout << "| Intersection      | Same Direction    | O(n+m) time, O(1) |" << endl;
    cout << "+-------------------+-------------------+-------------------+" << endl;
    cout << endl;

    cout << "PATTERN 1: OPPOSITE ENDS (Converging Pointers)" << endl;
    cout << "  int left = 0, right = n - 1;" << endl;
    cout << "  while (left < right) { ... left++ or right-- ... }" << endl;
    cout << "  Use when: sorted array, symmetry, pair/triplet search" << endl;
    cout << endl;

    // Quick demo
    int arr[] = {1, 3, 5, 7, 9};
    int n = 5;
    cout << "Demo - Pair Sum in {1, 3, 5, 7, 9}:" << endl;
    int l, r;
    if (pairSum(arr, n, 12, l, r)) {
        cout << "  " << arr[l] << " + " << arr[r] << " = 12" << endl;
    }
    cout << endl;

    cout << "PATTERN 2: SAME DIRECTION (Fast/Slow Pointers)" << endl;
    cout << "  int slow = 0;" << endl;
    cout << "  for (int fast = 0; fast < n; fast++) {" << endl;
    cout << "      if (condition) { arr[slow++] = arr[fast]; }" << endl;
    cout << "  }" << endl;
    cout << "  Use when: in-place modification, partitioning, dedup" << endl;
    cout << endl;

    // Quick demo
    int arr2[] = {1, 1, 2, 2, 3};
    int n2 = 5;
    cout << "Demo - Remove Duplicates from {1, 1, 2, 2, 3}:" << endl;
    int len = removeDuplicates(arr2, n2);
    cout << "  Result: ";
    printArray(arr2, len);
    cout << endl;

    cout << "KEY RULES:" << endl;
    cout << "  1. Sort first if array is unsorted and you need opposite ends" << endl;
    cout << "  2. Opposite ends: move pointer based on comparison with target" << endl;
    cout << "  3. Same direction: slow = write, fast = read" << endl;
    cout << "  4. Skip duplicates to avoid repeated results" << endl;
    cout << "  5. For in-place merge, work from the END to avoid overwrites" << endl;

    return 0;
}
