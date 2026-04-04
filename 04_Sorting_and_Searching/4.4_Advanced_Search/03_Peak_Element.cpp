/*
 * File: 03_Peak_Element.cpp
 * Topic: Find a peak element in array
 * Description: Peak = element strictly greater than neighbors
 */
#include <iostream>
using namespace std;

int findPeakElement(int arr[], int n) {
    int lo = 0;
    int hi = n - 1;

    while (lo < hi) { // note: < not <=
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] > arr[mid + 1]) {
            // We are on a downward slope or at peak
            // Peak is at mid or to the left
            hi = mid;
        } else {
            // We are on an upward slope
            // Peak is to the right
            lo = mid + 1;
        }
    }

    // lo == hi, this is the peak
    return lo;
}

int main() {
    cout << "=== Peak Element ===" << endl;
    cout << endl;

    /*
     * Peak element: arr[i] > arr[i-1] AND arr[i] > arr[i+1]
     * Edge elements: arr[0] only needs arr[0] > arr[1]
     *                arr[n-1] only needs arr[n-1] > arr[n-2]
     */

    // Example 1
    int arr1[] = {1, 2, 3, 1};
    int n1 = 4;
    cout << "Array: 1 2 3 1" << endl;
    int peak1 = findPeakElement(arr1, n1);
    cout << "Peak at index " << peak1 << " (value: " << arr1[peak1] << ")" << endl;
    cout << endl;

    // Example 2: Multiple peaks possible
    int arr2[] = {1, 2, 1, 3, 5, 6, 4};
    int n2 = 7;
    cout << "Array: 1 2 1 3 5 6 4" << endl;
    int peak2 = findPeakElement(arr2, n2);
    cout << "Peak at index " << peak2 << " (value: " << arr2[peak2] << ")" << endl;
    cout << "(Could also be index 1 with value 2)" << endl;
    cout << endl;

    cout << "--- How it works ---" << endl;
    cout << "  1. Find mid point" << endl;
    cout << "  2. Compare arr[mid] with arr[mid+1]" << endl;
    cout << "  3. If arr[mid] > arr[mid+1]:" << endl;
    cout << "     We're going DOWN -> peak is at mid or left" << endl;
    cout << "  4. If arr[mid] < arr[mid+1]:" << endl;
    cout << "     We're going UP -> peak is to the right" << endl;
    cout << "  5. Converge until lo == hi (peak found)" << endl;
    cout << endl;

    cout << "Why binary search works:" << endl;
    cout << "  At least one peak ALWAYS exists." << endl;
    cout << "  Going in the direction of increase guarantees finding one." << endl;
    cout << endl;
    cout << "Time: O(log n)" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
