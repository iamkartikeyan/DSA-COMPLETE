// 15.1 - Previous Greater Element (PGE)
// For each element, find the previous (to the left) element that is greater.
// Uses a monotonic decreasing stack scanned left to right.
// Time: O(n), Space: O(n).
//
// PATTERN:
//   Same as NGE but we process left-to-right and look at elements
//   already in the stack (which are to the left of current).
//   The top of stack after popping is the previous greater element.

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// ============================================================
// PREVIOUS GREATER ELEMENT
// Returns array where result[i] = previous greater element of arr[i], or -1.
// ============================================================

vector<int> previousGreaterElement(const int arr[], int n) {
    int result[1000];
    stack<int> st;  // Monotonic decreasing stack of indices

    for (int i = 0; i < n; i++) {
        // Pop elements smaller than current (they cannot be PGE)
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            st.pop();
        }
        // Top of stack is the previous greater element
        if (st.empty()) {
            result[i] = -1;
        } else {
            result[i] = arr[st.top()];
        }
        st.push(i);
    }

    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(result[i]);
    return vec;
}

// ============================================================
// PREVIOUS SMALLER ELEMENT
// Reverse comparison: maintain increasing stack.
// ============================================================

vector<int> previousSmallerElement(const int arr[], int n) {
    int result[1000];
    stack<int> st;  // Monotonic increasing stack of indices

    for (int i = 0; i < n; i++) {
        // Pop elements >= current
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }
        if (st.empty()) {
            result[i] = -1;
        } else {
            result[i] = arr[st.top()];
        }
        st.push(i);
    }

    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(result[i]);
    return vec;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoPreviousGreater() {
    cout << "=== Previous Greater Element ===" << endl;
    int arr[] = {4, 5, 2, 10, 8};
    int n = 5;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    vector<int> pge = previousGreaterElement(arr, n);
    cout << "PGE:   ";
    for (int i = 0; i < n; i++) cout << pge[i] << " ";
    cout << endl;  // Expected: -1 -1 5 -1 10
    cout << endl;
}

void demoPreviousSmaller() {
    cout << "=== Previous Smaller Element ===" << endl;
    int arr[] = {4, 5, 2, 10, 8};
    int n = 5;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    vector<int> pse = previousSmallerElement(arr, n);
    cout << "PSE:   ";
    for (int i = 0; i < n; i++) cout << pse[i] << " ";
    cout << endl;  // Expected: -1 4 -1 2 2
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: PGE for [4, 5, 2, 10, 8] ===" << endl;
    cout << "i=0, val=4:  stack empty -> PGE=-1. Push 0. Stack: [0(4)]" << endl;
    cout << "i=1, val=5:  4 <= 5, pop 0. Stack empty -> PGE=-1. Push 1. Stack: [1(5)]" << endl;
    cout << "i=2, val=2:  5 > 2, stop. PGE=5. Push 2. Stack: [1(5), 2(2)]" << endl;
    cout << "i=3, val=10: 2 <= 10, pop. 5 <= 10, pop. Empty -> PGE=-1. Push 3." << endl;
    cout << "i=4, val=8:  10 > 8, stop. PGE=10. Push 4." << endl;
    cout << "Result: [-1, -1, 5, -1, 10]" << endl << endl;
}

// ============================================================
// APPLICATION: Distance to Previous Greater
// How many positions back is the previous greater element?
// ============================================================

void demoDistanceToPGE() {
    cout << "=== Distance to Previous Greater Element ===" << endl;
    int arr[] = {4, 5, 2, 10, 8};
    int n = 5;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    vector<int> pge = previousGreaterElement(arr, n);
    cout << "Distance: ";
    for (int i = 0; i < n; i++) {
        if (pge[i] == -1) {
            cout << -1 << " ";  // No previous greater
        } else {
            // Find index of PGE
            int j;
            for (j = i - 1; j >= 0; j--) {
                if (arr[j] == pge[i]) break;
            }
            cout << (i - j) << " ";
        }
    }
    cout << endl << endl;
}

int main() {
    demoWalkthrough();
    demoPreviousGreater();
    demoPreviousSmaller();
    demoDistanceToPGE();
    return 0;
}
