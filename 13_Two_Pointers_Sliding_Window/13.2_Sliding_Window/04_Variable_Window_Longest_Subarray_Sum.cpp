// 13.2 - Variable Window: Longest Subarray with Sum <= K
// Expand right, shrink left when sum exceeds limit.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

// Longest subarray with sum <= k
int longestSubarrayWithSumK(int arr[], int n, int k) {
    int left = 0;
    int sum = 0;
    int maxLen = 0;

    for (int right = 0; right < n; right++) {
        sum += arr[right];  // Expand window

        // Shrink window while sum exceeds limit
        while (sum > k && left <= right) {
            sum -= arr[left];
            left++;
        }

        // Update max length if window is valid
        if (sum <= k) {
            maxLen = maxVal(maxLen, right - left + 1);
        }
    }
    return maxLen;
}

int main() {
    cout << "=== Variable Window: Longest Subarray with Sum <= K ===" << endl;
    cout << endl;

    int arr[] = {1, 2, 3, 1, 1, 1, 4, 2, 1};
    int n = 9;
    int k = 5;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Maximum allowed sum: " << k << endl;
    cout << endl;

    cout << "Approach: Expand/Shrink" << endl;
    cout << "  - Always expand: right++, add arr[right] to sum" << endl;
    cout << "  - If sum > k: shrink from left until valid" << endl;
    cout << "  - Track maximum valid window length" << endl;
    cout << endl;

    cout << "Step-by-step (sum <= 5):" << endl;
    cout << "  right=0: add 1,  sum=1,  window=[0..0], len=1" << endl;
    cout << "  right=1: add 2,  sum=3,  window=[0..1], len=2" << endl;
    cout << "  right=2: add 3,  sum=6 > 5 -> shrink" << endl;
    cout << "           remove 1, sum=5,  window=[1..2], len=2" << endl;
    cout << "  right=3: add 1,  sum=6 > 5 -> shrink" << endl;
    cout << "           remove 2, sum=4,  window=[2..3], len=2" << endl;
    cout << "  right=4: add 1,  sum=5,  window=[2..4], len=3" << endl;
    cout << "  right=5: add 1,  sum=6 > 5 -> shrink" << endl;
    cout << "           remove 3, sum=3,  window=[3..5], len=3" << endl;
    cout << "  right=6: add 4,  sum=7 > 5 -> shrink" << endl;
    cout << "           remove 1, sum=6 > 5 -> shrink" << endl;
    cout << "           remove 1, sum=5,  window=[5..6], len=2" << endl;
    cout << "  right=7: add 2,  sum=7 > 5 -> shrink" << endl;
    cout << "           remove 1, sum=6 > 5 -> shrink" << endl;
    cout << "           remove 4, sum=2,  window=[7..7], len=1" << endl;
    cout << "  right=8: add 1,  sum=3,  window=[7..8], len=2" << endl;
    cout << endl;

    int answer = longestSubarrayWithSumK(arr, n, k);
    cout << "Answer: longest subarray with sum <= " << k << " has length "
         << answer << endl;
    cout << endl;

    // Second example
    int arr2[] = {2, 5, 1, 7, 10};
    int n2 = 5;
    int k2 = 15;
    cout << "Array: ";
    for (int i = 0; i < n2; i++) cout << arr2[i] << " ";
    cout << " (k=" << k2 << ")" << endl;
    cout << "  Longest subarray with sum <= " << k2 << ": length "
         << longestSubarrayWithSumK(arr2, n2, k2) << endl;
    cout << "  ([5,1,7] = 13, length 3)" << endl;

    return 0;
}
