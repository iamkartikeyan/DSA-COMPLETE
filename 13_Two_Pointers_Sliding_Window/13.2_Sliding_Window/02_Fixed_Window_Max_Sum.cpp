// 13.2 - Fixed Window: Maximum Sum Subarray of Size K
// O(n) sliding window vs O(n*k) brute force.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

// Brute force: O(n*k) - recompute sum for every window
int maxSumBruteForce(int arr[], int n, int k) {
    int maxSum = -1;
    for (int i = 0; i <= n - k; i++) {
        int currentSum = 0;
        for (int j = i; j < i + k; j++) {
            currentSum += arr[j];
        }
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }
    return maxSum;
}

// Sliding window: O(n) - subtract outgoing, add incoming
int maxSumSlidingWindow(int arr[], int n, int k) {
    if (n < k) return -1;

    // Compute sum of first window
    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }

    int maxSum = windowSum;

    // Slide window one position at a time
    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];  // Add new, remove old
        maxSum = maxVal(maxSum, windowSum);
    }
    return maxSum;
}

int main() {
    cout << "=== Fixed Window: Maximum Sum Subarray of Size K ===" << endl;
    cout << endl;

    int arr[] = {1, 4, 2, 10, 2, 3, 1, 0, 20};
    int n = 9;
    int k = 4;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Window size k = " << k << endl;
    cout << endl;

    cout << "Brute Force O(n*k):" << endl;
    cout << "  Window [0..3]:   1+4+2+10   = 17" << endl;
    cout << "  Window [1..4]:   4+2+10+2   = 18" << endl;
    cout << "  Window [2..5]:   2+10+2+3   = 17" << endl;
    cout << "  Window [3..6]:   10+2+3+1   = 16" << endl;
    cout << "  Window [4..7]:   2+3+1+0    = 6" << endl;
    cout << "  Window [5..8]:   3+1+0+20   = 24  <-- MAX" << endl;
    cout << "  Answer: " << maxSumBruteForce(arr, n, k) << endl;
    cout << endl;

    cout << "Sliding Window O(n):" << endl;
    cout << "  Start with windowSum = 1+4+2+10 = 17" << endl;
    cout << "  Slide: windowSum += arr[4] - arr[0] = 17 + 2 - 1 = 18" << endl;
    cout << "  Slide: windowSum += arr[5] - arr[1] = 18 + 3 - 4 = 17" << endl;
    cout << "  Slide: windowSum += arr[6] - arr[2] = 17 + 1 - 2 = 16" << endl;
    cout << "  Slide: windowSum += arr[7] - arr[3] = 16 + 0 - 10 = 6" << endl;
    cout << "  Slide: windowSum += arr[8] - arr[4] = 6 + 20 - 2 = 24" << endl;
    cout << "  Answer: " << maxSumSlidingWindow(arr, n, k) << endl;
    cout << endl;

    cout << "Why O(n) works:" << endl;
    cout << "  - Each element is added once and subtracted once" << endl;
    cout << "  - No recomputation of overlapping portions" << endl;
    cout << "  - windowSum = previousSum - outgoing + incoming" << endl;

    return 0;
}
