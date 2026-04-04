// 13.2 - Fixed Window: First Negative in Every Window of Size K
// Uses a queue to track indices of negative numbers.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

const int MAX = 100;

// Simple queue implementation using array
int q[MAX];
int qFront = 0;
int qRear = 0;

void queuePush(int val) {
    q[qRear] = val;
    qRear++;
}

void queuePop() {
    if (qFront < qRear) qFront++;
}

int queueFront() {
    return q[qFront];
}

int queueEmpty() {
    return (qFront == qRear) ? 1 : 0;
}

void queueClear() {
    qFront = 0;
    qRear = 0;
}

// First negative in every window of size k
int firstNegative(int arr[], int n, int k, int result[]) {
    queueClear();
    int count = 0;

    for (int i = 0; i < n; i++) {
        // Track indices of negative numbers
        if (arr[i] < 0) {
            queuePush(i);
        }

        // When we have a full window of size k
        if (i >= k - 1) {
            // Remove indices outside current window
            while (!queueEmpty() && queueFront() <= i - k) {
                queuePop();
            }

            // First negative in this window
            if (!queueEmpty()) {
                result[count] = arr[queueFront()];
            } else {
                result[count] = 0;  // No negative found
            }
            count++;
        }
    }
    return count;
}

int main() {
    cout << "=== Fixed Window: First Negative in Every Window ===" << endl;
    cout << endl;

    int arr[] = {12, -1, -7, 8, -15, 30, 16, 28};
    int n = 8;
    int k = 3;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Window size k = " << k << endl;
    cout << endl;

    cout << "Windows and their first negatives:" << endl;
    cout << "  [12, -1, -7]        -> -1" << endl;
    cout << "  [-1, -7, 8]         -> -1" << endl;
    cout << "  [-7, 8, -15]        -> -7" << endl;
    cout << "  [8, -15, 30]        -> -15" << endl;
    cout << "  [-15, 30, 16]       -> -15" << endl;
    cout << "  [30, 16, 28]        -> 0 (no negative)" << endl;
    cout << endl;

    int result[MAX];
    int count = firstNegative(arr, n, k, result);

    cout << "Result: ";
    for (int i = 0; i < count; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    cout << "Approach:" << endl;
    cout << "  1. Use a queue to store INDICES of negative numbers" << endl;
    cout << "  2. For each window, front of queue = first negative" << endl;
    cout << "  3. Remove indices that fell out of window (index <= i-k)" << endl;
    cout << "  4. If queue empty, no negative in this window -> 0" << endl;
    cout << "  5. Time: O(n), Space: O(k) for queue" << endl;

    return 0;
}
