// 15.1 - What Is Monotonic Stack & Queue
// Monotonic structures maintain elements in sorted order (increasing or decreasing)
// while processing data. They are used for next greater element, largest rectangle
// in histogram, trapping rain water, and sliding window maximum problems.
//
// A MONOTONIC STACK maintains elements in either:
//   - Monotonically increasing order (bottom to top: smallest to largest)
//   - Monotonically decreasing order (bottom to top: largest to smallest)
//
// WHEN TO USE:
//   - "Next greater/smaller element" for each position
//   - "Previous greater/smaller element" for each position
//   - Finding boundaries where a condition changes (e.g., histogram rectangle)
//   - Problems asking "how far can I extend while maintaining a property"
//
// KEY PATTERN:
//   For each element, pop from stack while condition is violated.
//   The element that stops popping is the boundary.
//   Each element is pushed once and popped at most once -> O(n) total.
//
// MONOTONIC QUEUE (Deque):
//   Similar concept but using a deque (double-ended queue).
//   Maintain decreasing order in the deque. Front is always the maximum.
//   Used for sliding window maximum in O(n) time.

#include <iostream>
#include <stack>
#include <deque>
#include <vector>

using namespace std;

// ============================================================
// MONOTONIC INCREASING STACK EXAMPLE
// Elements in the stack increase from bottom to top.
// When we see a smaller element, we pop larger ones.
// ============================================================

void demoIncreasingStack() {
    cout << "=== Monotonic Increasing Stack ===" << endl;
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    stack<int> st;  // Stores indices, values increase bottom->top
    cout << "Processing with increasing stack:" << endl;

    for (int i = 0; i < n; i++) {
        // Pop elements >= current (maintain strictly increasing)
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            cout << "  Pop " << arr[st.top()] << " (>= " << arr[i] << ")" << endl;
            st.pop();
        }
        st.push(i);
        cout << "  Push " << arr[i] << " at index " << i << endl;
    }

    cout << "Stack contents (bottom to top): ";
    // Note: stack only lets us access top, so we pop to display
    while (!st.empty()) {
        cout << arr[st.top()] << " ";
        st.pop();
    }
    cout << endl << endl;
}

// ============================================================
// MONOTONIC DECREASING STACK EXAMPLE
// Elements in the stack decrease from bottom to top.
// When we see a larger element, we pop smaller ones.
// ============================================================

void demoDecreasingStack() {
    cout << "=== Monotonic Decreasing Stack ===" << endl;
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    stack<int> st;  // Stores indices, values decrease bottom->top
    cout << "Processing with decreasing stack:" << endl;

    for (int i = 0; i < n; i++) {
        // Pop elements <= current (maintain strictly decreasing)
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            cout << "  Pop " << arr[st.top()] << " (<= " << arr[i] << ")" << endl;
            st.pop();
        }
        st.push(i);
        cout << "  Push " << arr[i] << " at index " << i << endl;
    }

    cout << "Stack contents (bottom to top): ";
    while (!st.empty()) {
        cout << arr[st.top()] << " ";
        st.pop();
    }
    cout << endl << endl;
}

// ============================================================
// MONOTONIC QUEUE (DEQUE) EXAMPLE
// Maintain decreasing values in a deque. Front is always max.
// ============================================================

void demoMonotonicQueue() {
    cout << "=== Monotonic Queue (Decreasing Deque) ===" << endl;
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = 8;
    int k = 3;  // Window size

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Window size: " << k << endl;

    deque<int> dq;  // Stores indices, values in decreasing order
    cout << "Sliding window maximums:" << endl;

    for (int i = 0; i < n; i++) {
        // Remove elements outside window
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
            cout << "  Window [" << (i - k + 1) << ".." << i << "] max = " << arr[dq.front()] << endl;
        }
    }
    cout << endl;
}

// ============================================================
// SUMMARY: Common Monotonic Stack/Queue Problems
// ============================================================

void demoSummary() {
    cout << "=== Summary: Monotonic Stack & Queue Problems ===" << endl;
    cout << "1. Next Greater Element   - monotonic decreasing stack" << endl;
    cout << "2. Next Smaller Element   - monotonic increasing stack" << endl;
    cout << "3. Previous Greater/Smaller - same, scan left to right" << endl;
    cout << "4. Stock Span Problem     - previous greater element variant" << endl;
    cout << "5. Largest Rectangle      - monotonic increasing stack (boundaries)" << endl;
    cout << "6. Trapping Rain Water    - monotonic decreasing stack (valleys)" << endl;
    cout << "7. Sliding Window Maximum - monotonic decreasing deque" << endl;
    cout << "8. Remove K Digits        - monotonic increasing (string as stack)" << endl;
    cout << endl;
    cout << "Time complexity: O(n) - each element pushed/popped at most once." << endl;
    cout << "Space complexity: O(n) - stack/deque storage." << endl;
}

int main() {
    demoIncreasingStack();
    demoDecreasingStack();
    demoMonotonicQueue();
    demoSummary();
    return 0;
}
