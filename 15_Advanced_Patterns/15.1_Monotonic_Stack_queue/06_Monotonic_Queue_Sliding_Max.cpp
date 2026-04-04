// 15.1 - Monotonic Queue / Sliding Window Maximum
// Find the maximum in each sliding window of size k.
// Uses a monotonic decreasing deque. Front is always the maximum.
// Time: O(n), Space: O(k).
//
// PATTERN:
//   Maintain a deque where values are in decreasing order.
//   - Remove elements outside the window from the front.
//   - Remove smaller elements from the back before inserting.
//   - The front of the deque is the maximum of the current window.
//
//   Each element enters the deque once and leaves at most once -> O(n).

#include <iostream>
#include <deque>
#include <vector>

using namespace std;

// ============================================================
// SLIDING WINDOW MAXIMUM - Monotonic Deque O(n)
// Returns array of maximums for each window position.
// ============================================================

vector<int> slidingWindowMax(const int arr[], int n, int k) {
    deque<int> dq;  // Stores indices, values in decreasing order
    vector<int> result;

    for (int i = 0; i < n; i++) {
        // Remove elements outside window from front
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }

        // Remove smaller elements from back (maintain decreasing order)
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Window is valid from index k-1 onwards
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
    return result;
}

// ============================================================
// SLIDING WINDOW MINIMUM - Monotonic Increasing Deque
// Same pattern, reverse comparison.
// ============================================================

vector<int> slidingWindowMin(const int arr[], int n, int k) {
    deque<int> dq;  // Stores indices, values in increasing order
    vector<int> result;

    for (int i = 0; i < n; i++) {
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }

        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
    return result;
}

// ============================================================
// BRUTE FORCE - O(n*k) for comparison
// ============================================================

vector<int> slidingWindowMaxBrute(const int arr[], int n, int k) {
    vector<int> result;
    for (int i = 0; i <= n - k; i++) {
        int maxVal = arr[i];
        for (int j = 1; j < k; j++) {
            if (arr[i + j] > maxVal) maxVal = arr[i + j];
        }
        result.push_back(maxVal);
    }
    return result;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoSlidingWindowMax() {
    cout << "=== Sliding Window Maximum ===" << endl;
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = 8;
    int k = 3;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Window size: " << k << endl;

    vector<int> result = slidingWindowMax(arr, n, k);
    cout << "Maximums: ";
    for (int i = 0; i < (int)result.size(); i++) cout << result[i] << " ";
    cout << endl;  // Expected: 3 3 5 5 6 7
    cout << endl;
}

void demoSlidingWindowMin() {
    cout << "=== Sliding Window Minimum ===" << endl;
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = 8;
    int k = 3;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Window size: " << k << endl;

    vector<int> result = slidingWindowMin(arr, n, k);
    cout << "Minimums: ";
    for (int i = 0; i < (int)result.size(); i++) cout << result[i] << " ";
    cout << endl;  // Expected: -1 -3 -3 -3 3 3
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Max with k=3 for [1, 3, -1, -3, 5, 3, 6, 7] ===" << endl;
    cout << "i=0, val=1:  deque empty, push 0. dq: [0(1)]" << endl;
    cout << "i=1, val=3:  1<=3, pop 0. push 1. dq: [1(3)]" << endl;
    cout << "i=2, val=-1: -1<3, push 2. dq: [1(3), 2(-1)]. Window [0..2] max=3" << endl;
    cout << "i=3, val=-3: -3<-1, push 3. dq: [1(3), 2(-1), 3(-3)]. Window [1..3] max=3" << endl;
    cout << "i=4, val=5:  3<=5 pop, -1<=5 pop, -3<=5 pop. push 4. dq: [4(5)]. Window [2..4] max=5" << endl;
    cout << "i=5, val=3:  3<5, push 5. dq: [4(5), 5(3)]. Window [3..5] max=5" << endl;
    cout << "i=6, val=6:  5<=6 pop, 3<=6 pop. push 6. dq: [6(6)]. Window [4..6] max=6" << endl;
    cout << "i=7, val=7:  6<=7 pop. push 7. dq: [7(7)]. Window [5..7] max=7" << endl;
    cout << "Result: [3, 3, 5, 5, 6, 7]" << endl << endl;
}

void demoCompareMethods() {
    cout << "=== Compare: Deque vs Brute Force ===" << endl;
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = 8;
    int k = 3;

    vector<int> dqResult = slidingWindowMax(arr, n, k);
    vector<int> bruteResult = slidingWindowMaxBrute(arr, n, k);

    cout << "Deque method:  ";
    for (int i = 0; i < (int)dqResult.size(); i++) cout << dqResult[i] << " ";
    cout << endl;

    cout << "Brute force:   ";
    for (int i = 0; i < (int)bruteResult.size(); i++) cout << bruteResult[i] << " ";
    cout << endl;

    bool match = true;
    for (int i = 0; i < (int)dqResult.size(); i++) {
        if (dqResult[i] != bruteResult[i]) match = false;
    }
    cout << "Results match: " << (match ? "Yes" : "No") << endl << endl;
}

int main() {
    demoWalkthrough();
    demoSlidingWindowMax();
    demoSlidingWindowMin();
    demoCompareMethods();
    return 0;
}
