// 13.1 - Pair Sum in Sorted Array
// Opposite ends pattern: find two elements that sum to target.
// O(n) vs O(n^2) brute force comparison.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

// Brute force: O(n^2) - check every pair
void pairSumBruteForce(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target) {
                cout << "  Found: arr[" << i << "]=" << arr[i]
                     << " + arr[" << j << "]=" << arr[j]
                     << " = " << target << endl;
                return;
            }
        }
    }
    cout << "  No pair found." << endl;
}

// Two pointers: O(n) - works on sorted array only
bool pairSumSorted(int arr[], int n, int target, int &outLeft, int &outRight) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) {
            outLeft = left;
            outRight = right;
            return true;
        }
        if (sum < target) {
            left++;   // Need larger sum
        } else {
            right--;  // Need smaller sum
        }
    }
    return false;
}

int main() {
    cout << "=== Pair Sum in Sorted Array ===" << endl;
    cout << endl;

    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = 6;
    int target = 12;

    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Target sum: " << target << endl;
    cout << endl;

    cout << "Brute Force O(n^2):" << endl;
    pairSumBruteForce(arr, n, target);
    cout << endl;

    cout << "Two Pointers O(n):" << endl;
    int leftIdx = -1, rightIdx = -1;
    if (pairSumSorted(arr, n, target, leftIdx, rightIdx)) {
        cout << "  Found: arr[" << leftIdx << "]=" << arr[leftIdx]
             << " + arr[" << rightIdx << "]=" << arr[rightIdx]
             << " = " << target << endl;
    } else {
        cout << "  No pair found." << endl;
    }
    cout << endl;

    cout << "Why O(n) works:" << endl;
    cout << "  - Array is sorted, so we know direction to move" << endl;
    cout << "  - If sum < target, left++ gives larger values" << endl;
    cout << "  - If sum > target, right-- gives smaller values" << endl;
    cout << "  - Each step eliminates one element from consideration" << endl;
    cout << endl;

    // Second example: no pair exists
    int target2 = 100;
    cout << "Target sum: " << target2 << endl;
    cout << "Two Pointers O(n):" << endl;
    leftIdx = -1;
    rightIdx = -1;
    if (pairSumSorted(arr, n, target2, leftIdx, rightIdx)) {
        cout << "  Found: indices (" << leftIdx << ", " << rightIdx << ")" << endl;
    } else {
        cout << "  No pair sums to " << target2 << endl;
    }

    return 0;
}
