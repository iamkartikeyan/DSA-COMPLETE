// 15.1 - Next Greater Element (NGE)
// For each element, find the next element to the right that is greater.
// Uses a monotonic decreasing stack. Time: O(n), Space: O(n).
//
// PATTERN:
//   Store indices in a stack. For each element, pop all indices whose
//   value is smaller than current - current is their next greater.
//   Remaining elements in stack have no next greater element (use -1).

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// ============================================================
// NEXT GREATER ELEMENT
// Returns array where result[i] = next greater element of arr[i], or -1.
// ============================================================

vector<int> nextGreaterElement(const int arr[], int n) {
    int result[1000];
    for (int i = 0; i < n; i++) result[i] = -1;

    stack<int> st;  // Stores indices

    for (int i = 0; i < n; i++) {
        // Pop elements smaller than current (current is their next greater)
        while (!st.empty() && arr[st.top()] < arr[i]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }

    // Copy to vector for return
    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(result[i]);
    return vec;
}

// ============================================================
// NEXT SMALLER ELEMENT
// Same pattern, reverse comparison.
// ============================================================

vector<int> nextSmallerElement(const int arr[], int n) {
    int result[1000];
    for (int i = 0; i < n; i++) result[i] = -1;

    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }

    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(result[i]);
    return vec;
}

// ============================================================
// CIRCULAR NEXT GREATER ELEMENT
// Array is circular - last element wraps to first.
// Use modulo to simulate two passes through the array.
// ============================================================

vector<int> nextGreaterElementCircular(const int arr[], int n) {
    int result[1000];
    for (int i = 0; i < n; i++) result[i] = -1;

    stack<int> st;

    // Two passes: i from 0 to 2n-1, use i % n for array access
    for (int i = 0; i < 2 * n; i++) {
        int idx = i % n;
        while (!st.empty() && arr[st.top()] < arr[idx]) {
            result[st.top()] = arr[idx];
            st.pop();
        }
        if (i < n) st.push(i);  // Only push indices in first pass
    }

    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(result[i]);
    return vec;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoNextGreater() {
    cout << "=== Next Greater Element ===" << endl;
    int arr[] = {4, 5, 2, 10, 8};
    int n = 5;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    vector<int> nge = nextGreaterElement(arr, n);
    cout << "NGE:   ";
    for (int i = 0; i < n; i++) cout << nge[i] << " ";
    cout << endl;  // Expected: 5 10 10 -1 -1
    cout << endl;
}

void demoNextSmaller() {
    cout << "=== Next Smaller Element ===" << endl;
    int arr[] = {4, 5, 2, 10, 8};
    int n = 5;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    vector<int> nse = nextSmallerElement(arr, n);
    cout << "NSE:   ";
    for (int i = 0; i < n; i++) cout << nse[i] << " ";
    cout << endl;  // Expected: 2 2 -1 8 -1
    cout << endl;
}

void demoCircular() {
    cout << "=== Circular Next Greater Element ===" << endl;
    int arr[] = {1, 2, 1};
    int n = 3;

    cout << "Array (circular): ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    vector<int> nge = nextGreaterElementCircular(arr, n);
    cout << "NGE:             ";
    for (int i = 0; i < n; i++) cout << nge[i] << " ";
    cout << endl;  // Expected: 2 -1 2
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: NGE for [4, 5, 2, 10, 8] ===" << endl;
    int arr[] = {4, 5, 2, 10, 8};
    int n = 5;
    (void)arr; (void)n;

    cout << "i=0, val=4:  stack empty, push index 0. Stack: [0(4)]" << endl;
    cout << "i=1, val=5:  5 > 4, pop 0, result[0]=5. Push 1. Stack: [1(5)]" << endl;
    cout << "i=2, val=2:  2 < 5, push 2. Stack: [1(5), 2(2)]" << endl;
    cout << "i=3, val=10: 10 > 2, pop 2, result[2]=10." << endl;
    cout << "             10 > 5, pop 1, result[1]=10. Push 3. Stack: [3(10)]" << endl;
    cout << "i=4, val=8:  8 < 10, push 4. Stack: [3(10), 4(8)]" << endl;
    cout << "End: remaining indices 3,4 have no NGE -> -1" << endl;
    cout << "Result: [5, 10, 10, -1, -1]" << endl << endl;
}

int main() {
    demoWalkthrough();
    demoNextGreater();
    demoNextSmaller();
    demoCircular();
    return 0;
}
