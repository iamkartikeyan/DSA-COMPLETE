// 13.2 - Sliding Window Complete Summary
// Fixed vs variable comparison, templates, and all problems.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

int minVal(int a, int b) {
    return (a < b) ? a : b;
}

// Fixed window: max sum of size k
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

// Variable window: longest subarray with sum <= k
int longestSubarrayWithSumK(int arr[], int n, int k) {
    int left = 0, sum = 0, maxLen = 0;
    for (int right = 0; right < n; right++) {
        sum += arr[right];
        while (sum > k && left <= right) {
            sum -= arr[left];
            left++;
        }
        if (sum <= k) maxLen = maxVal(maxLen, right - left + 1);
    }
    return maxLen;
}

// Kadane's algorithm
int kadane(int arr[], int n) {
    int maxSoFar = arr[0];
    int currentMax = arr[0];
    for (int i = 1; i < n; i++) {
        currentMax = maxVal(arr[i], currentMax + arr[i]);
        maxSoFar = maxVal(maxSoFar, currentMax);
    }
    return maxSoFar;
}

// Longest unique substring
int longestUniqueSubstring(const char s[]) {
    int lastSeen[256];
    for (int i = 0; i < 256; i++) lastSeen[i] = -1;
    int maxLen = 0, left = 0, right = 0;
    while (s[right] != '\0') {
        unsigned char ch = s[right];
        if (lastSeen[ch] >= left) left = lastSeen[ch] + 1;
        lastSeen[ch] = right;
        maxLen = maxVal(maxLen, right - left + 1);
        right++;
    }
    return maxLen;
}

int main() {
    cout << "=== Sliding Window Complete Summary ===" << endl;
    cout << endl;

    cout << "+---------------------------+---------------+---------------+" << endl;
    cout << "| Problem                   | Type          | Complexity    |" << endl;
    cout << "+---------------------------+---------------+---------------+" << endl;
    cout << "| Max Sum Subarray (size k) | Fixed         | O(n), O(1)    |" << endl;
    cout << "| First Negative (size k)   | Fixed         | O(n), O(k)    |" << endl;
    cout << "| Count Anagrams            | Fixed         | O(n*26), O(1) |" << endl;
    cout << "| Longest Sum <= K          | Variable      | O(n), O(1)    |" << endl;
    cout << "| Longest Unique Substring  | Variable      | O(n), O(256)  |" << endl;
    cout << "| Longest K Distinct        | Variable      | O(n), O(256)  |" << endl;
    cout << "| Min Window Substring      | Variable      | O(n), O(256)  |" << endl;
    cout << "| Kadane's (Max Subarray)   | Variable-like | O(n), O(1)    |" << endl;
    cout << "+---------------------------+---------------+---------------+" << endl;
    cout << endl;

    cout << "FIXED SIZE WINDOW" << endl;
    cout << "  - Window size k is CONSTANT" << endl;
    cout << "  - Slide one element at a time" << endl;
    cout << "  - Template:" << endl;
    cout << "    int windowSum = 0;" << endl;
    cout << "    for (int i = 0; i < k; i++) windowSum += arr[i];" << endl;
    cout << "    for (int i = k; i < n; i++) {" << endl;
    cout << "        windowSum += arr[i] - arr[i - k];" << endl;
    cout << "        updateAnswer(windowSum);" << endl;
    cout << "    }" << endl;
    cout << endl;

    // Fixed window demo
    int arr[] = {1, 4, 2, 10, 2, 3, 1, 0, 20};
    int n = 9;
    int k = 4;
    cout << "  Demo: max sum of size " << k << " in {1,4,2,10,2,3,1,0,20}" << endl;
    cout << "  Answer: " << maxSumFixedWindow(arr, n, k) << endl;
    cout << endl;

    cout << "VARIABLE SIZE WINDOW" << endl;
    cout << "  - Window size changes dynamically" << endl;
    cout << "  - Expand right, shrink left when constraint violated" << endl;
    cout << "  - Template:" << endl;
    cout << "    int left = 0;" << endl;
    cout << "    for (int right = 0; right < n; right++) {" << endl;
    cout << "        add(arr[right]);           // Expand window" << endl;
    cout << "        while (constraintViolated) {" << endl;
    cout << "            remove(arr[left]);" << endl;
    cout << "            left++;" << endl;
    cout << "        }" << endl;
    cout << "        updateAnswer(right - left + 1);" << endl;
    cout << "    }" << endl;
    cout << endl;

    // Variable window demo
    int arr2[] = {1, 2, 3, 1, 1, 1, 4, 2, 1};
    int n2 = 9;
    int limit = 5;
    cout << "  Demo: longest subarray with sum <= " << limit << endl;
    cout << "  Answer: " << longestSubarrayWithSumK(arr2, n2, limit) << endl;
    cout << endl;

    // Kadane's demo
    int arr3[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n3 = 9;
    cout << "  Kadane's on {-2,1,-3,4,-1,2,1,-5,4}: " << kadane(arr3, n3) << endl;
    cout << endl;

    // Unique substring demo
    const char s[] = "abcabcbb";
    cout << "  Longest unique substring in \"" << s << "\": "
         << longestUniqueSubstring(s) << endl;
    cout << endl;

    cout << "FIXED vs VARIABLE COMPARISON:" << endl;
    cout << "  | Aspect        | Fixed              | Variable            |" << endl;
    cout << "  | Window size   | Known (k)          | Unknown, dynamic    |" << endl;
    cout << "  | Loop          | Two separate loops | One loop + while    |" << endl;
    cout << "  | Shrink?       | Never              | When invalid        |" << endl;
    cout << "  | Data struct   | Queue for tracking | Map/set for state   |" << endl;
    cout << "  | Answer        | Per-window value   | Max/min length      |" << endl;
    cout << endl;

    cout << "COMMON PATTERNS:" << endl;
    cout << "  - Subarray/substring problems: think sliding window" << endl;
    cout << "  - 'Longest' or 'shortest': variable size window" << endl;
    cout << "  - 'Of size k' or 'every window of k': fixed size window" << endl;
    cout << "  - 'Contains all characters': variable window with frequency map" << endl;
    cout << "  - 'Maximum/minimum sum': fixed window or Kadane's" << endl;

    return 0;
}
