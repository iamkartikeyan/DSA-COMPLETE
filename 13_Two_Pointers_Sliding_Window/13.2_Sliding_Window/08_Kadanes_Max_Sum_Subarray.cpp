// 13.2 - Kadane's Algorithm: Maximum Sum Subarray
// currentMax = max(a[i], currentMax + a[i]) - extend or restart.
// O(n) time, O(1) space.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

// Kadane's algorithm - returns max subarray sum
int kadane(int arr[], int n, int &outStart, int &outEnd) {
    int maxSoFar = arr[0];
    int currentMax = arr[0];
    int tempStart = 0;
    outStart = 0;
    outEnd = 0;

    for (int i = 1; i < n; i++) {
        // Decide: extend previous subarray OR start new at current element
        if (currentMax + arr[i] < arr[i]) {
            // Start new subarray at i
            currentMax = arr[i];
            tempStart = i;
        } else {
            // Extend previous subarray
            currentMax = currentMax + arr[i];
        }

        // Update global maximum
        if (currentMax > maxSoFar) {
            maxSoFar = currentMax;
            outStart = tempStart;
            outEnd = i;
        }
    }
    return maxSoFar;
}

int main() {
    cout << "=== Kadane's Algorithm: Maximum Sum Subarray ===" << endl;
    cout << endl;

    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = 9;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << endl;

    cout << "Core Idea:" << endl;
    cout << "  At each position, decide: extend previous subarray or restart?" << endl;
    cout << "  currentMax = max(arr[i], currentMax + arr[i])" << endl;
    cout << "  - If currentMax + arr[i] < arr[i]: restart at arr[i]" << endl;
    cout << "  - Otherwise: extend the existing subarray" << endl;
    cout << endl;

    cout << "Step-by-step:" << endl;
    int currentMax = arr[0];
    int maxSoFar = arr[0];
    cout << "  i=0:  arr[0]=-2,   currentMax=-2,  maxSoFar=-2" << endl;
    for (int i = 1; i < n; i++) {
        if (currentMax + arr[i] < arr[i]) {
            currentMax = arr[i];
        } else {
            currentMax = currentMax + arr[i];
        }
        if (currentMax > maxSoFar) maxSoFar = currentMax;
        cout << "  i=" << i << ":  arr[" << i << "]=" << arr[i];
        if (arr[i] < 0) cout << "  ";
        cout << ",   currentMax=" << currentMax;
        if (currentMax > 0 && currentMax < 10) cout << "  ";
        cout << ",  maxSoFar=" << maxSoFar;
        if (currentMax == maxSoFar) cout << "  <-- new max!";
        cout << endl;
    }
    cout << endl;

    int startIdx = 0, endIdx = 0;
    int answer = kadane(arr, n, startIdx, endIdx);

    cout << "Maximum sum subarray: " << answer << endl;
    cout << "Subarray from index " << startIdx << " to " << endIdx << ": [";
    for (int i = startIdx; i <= endIdx; i++) {
        cout << arr[i];
        if (i < endIdx) cout << ", ";
    }
    cout << "]" << endl;
    cout << endl;

    // All negative array
    int arr2[] = {-5, -3, -8, -2, -1};
    int n2 = 5;
    cout << "Array: ";
    for (int i = 0; i < n2; i++) cout << arr2[i] << " ";
    cout << endl;
    int s2 = 0, e2 = 0;
    cout << "Max sum: " << kadane(arr2, n2, s2, e2);
    cout << " (subarray [" << arr2[s2] << "], index " << s2 << ")" << endl;
    cout << endl;

    // All positive
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = 5;
    cout << "Array: ";
    for (int i = 0; i < n3; i++) cout << arr3[i] << " ";
    cout << endl;
    int s3 = 0, e3 = 0;
    cout << "Max sum: " << kadane(arr3, n3, s3, e3);
    cout << " (entire array, sum of all elements)" << endl;
    cout << endl;

    cout << "Time: O(n), Space: O(1)" << endl;
    cout << "Works even when all numbers are negative." << endl;

    return 0;
}
