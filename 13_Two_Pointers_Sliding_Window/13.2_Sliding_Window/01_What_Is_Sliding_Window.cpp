// 13.2 - What Is Sliding Window?
// Explains fixed vs variable size window, template pattern.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

// Fixed window: max sum of subarray of size k
int maxSumFixedWindow(int arr[], int n, int k) {
    if (n < k) return -1;
    int windowSum = 0;
    for (int i = 0; i < k; i++) windowSum += arr[i];

    int maxSum = windowSum;
    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];
        maxSum = maxVal(maxSum, windowSum);
    }
    return maxSum;
}

// Variable window: longest subarray with sum <= limit
int longestSubarrayWithLimit(int arr[], int n, int limit) {
    int left = 0, sum = 0, maxLen = 0;
    for (int right = 0; right < n; right++) {
        sum += arr[right];           // Expand
        while (sum > limit && left <= right) {  // Shrink
            sum -= arr[left];
            left++;
        }
        maxLen = maxVal(maxLen, right - left + 1);
    }
    return maxLen;
}

int main() {
    cout << "=== Sliding Window Technique ===" << endl;
    cout << endl;

    cout << "WHAT IS IT?" << endl;
    cout << "  Maintain a 'window' that slides over data (array/string)." << endl;
    cout << "  Avoids recomputing from scratch for each position." << endl;
    cout << endl;

    cout << "TYPE 1: Fixed Size Window" << endl;
    cout << "  - Window size k is constant" << endl;
    cout << "  - Slide by one element at a time" << endl;
    cout << "  - Subtract outgoing, add incoming" << endl;
    cout << "  Examples: max sum of k elements, first negative in" << endl;
    cout << "            each window, anagram counting" << endl;
    cout << endl;
    cout << "  Template:" << endl;
    cout << "    int windowSum = 0;" << endl;
    cout << "    for (int i = 0; i < k; i++) windowSum += arr[i];" << endl;
    cout << "    for (int i = k; i < n; i++) {" << endl;
    cout << "        windowSum += arr[i] - arr[i - k];" << endl;
    cout << "        updateAnswer(windowSum);" << endl;
    cout << "    }" << endl;
    cout << endl;

    cout << "TYPE 2: Variable Size Window" << endl;
    cout << "  - Window expands and shrinks based on constraint" << endl;
    cout << "  - Expand right pointer always" << endl;
    cout << "  - Shrink left pointer when constraint violated" << endl;
    cout << "  Examples: longest unique substring, min window" << endl;
    cout << "            substring, longest subarray with sum <= k" << endl;
    cout << endl;
    cout << "  Template:" << endl;
    cout << "    int left = 0;" << endl;
    cout << "    for (int right = 0; right < n; right++) {" << endl;
    cout << "        add(arr[right]);          // Expand" << endl;
    cout << "        while (invalid) {" << endl;
    cout << "            remove(arr[left]);" << endl;
    cout << "            left++;" << endl;
    cout << "        }" << endl;
    cout << "        updateAnswer(right - left + 1);" << endl;
    cout << "    }" << endl;
    cout << endl;

    // Demos
    int arr[] = {1, 4, 2, 10, 2, 3, 1, 0, 20};
    int n = 9;
    int k = 4;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << endl;

    cout << "Fixed Window Demo (k=" << k << "):" << endl;
    cout << "  Max sum of subarray size " << k << ": "
         << maxSumFixedWindow(arr, n, k) << endl;
    cout << endl;

    int arr2[] = {1, 2, 3, 1, 1, 1, 4, 2, 1};
    int n2 = 9;
    int limit = 5;
    cout << "Variable Window Demo (sum <= " << limit << "):" << endl;
    cout << "  Array: ";
    for (int i = 0; i < n2; i++) cout << arr2[i] << " ";
    cout << endl;
    cout << "  Longest subarray with sum <= " << limit << ": length "
         << longestSubarrayWithLimit(arr2, n2, limit) << endl;
    cout << endl;

    cout << "KEY DIFFERENCE:" << endl;
    cout << "  Fixed:    window size is known, just slide" << endl;
    cout << "  Variable: window size unknown, expand/shrink dynamically" << endl;

    return 0;
}
