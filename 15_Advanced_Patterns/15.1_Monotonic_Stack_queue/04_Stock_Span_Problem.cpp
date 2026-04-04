// 15.1 - Stock Span Problem
// The stock span is the number of consecutive days (including today)
// where the stock price was less than or equal to today's price.
// This is a variant of the Previous Greater Element problem.
//
// PATTERN:
//   For each day i, find the index of the previous greater element.
//   Span[i] = i - previous_greater_index (or i + 1 if none exists).
//   Use a monotonic decreasing stack to find the previous greater in O(n).
//
// TIME: O(n) - each element pushed/popped at most once.
// SPACE: O(n) - stack storage.

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// ============================================================
// STOCK SPAN - O(n) using monotonic stack
// Returns array of span values for each day.
// ============================================================

vector<int> stockSpan(const int prices[], int n) {
    int span[1000];
    stack<int> st;  // Monotonic decreasing stack of indices

    for (int i = 0; i < n; i++) {
        // Pop elements with price <= current price
        while (!st.empty() && prices[st.top()] <= prices[i]) {
            st.pop();
        }

        // If stack empty, all previous days had lower prices
        if (st.empty()) {
            span[i] = i + 1;
        } else {
            span[i] = i - st.top();
        }

        st.push(i);
    }

    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(span[i]);
    return vec;
}

// ============================================================
// BRUTE FORCE - O(n^2) for comparison
// ============================================================

vector<int> stockSpanBruteForce(const int prices[], int n) {
    int span[1000];

    for (int i = 0; i < n; i++) {
        span[i] = 1;  // Today always counts
        for (int j = i - 1; j >= 0; j--) {
            if (prices[j] <= prices[i]) {
                span[i]++;
            } else {
                break;
            }
        }
    }

    vector<int> vec;
    for (int i = 0; i < n; i++) vec.push_back(span[i]);
    return vec;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoStockSpan() {
    cout << "=== Stock Span Problem ===" << endl;
    int prices[] = {100, 80, 60, 70, 60, 75, 85};
    int n = 7;

    cout << "Prices: ";
    for (int i = 0; i < n; i++) cout << prices[i] << " ";
    cout << endl;

    vector<int> span = stockSpan(prices, n);
    cout << "Span:   ";
    for (int i = 0; i < n; i++) cout << span[i] << " ";
    cout << endl;  // Expected: 1 1 1 2 1 4 6
    cout << endl;
}

void demoStockSpan2() {
    cout << "=== Stock Span - Example 2 ===" << endl;
    int prices[] = {10, 4, 5, 90, 120, 80};
    int n = 6;

    cout << "Prices: ";
    for (int i = 0; i < n; i++) cout << prices[i] << " ";
    cout << endl;

    vector<int> span = stockSpan(prices, n);
    cout << "Span:   ";
    for (int i = 0; i < n; i++) cout << span[i] << " ";
    cout << endl;  // Expected: 1 1 2 4 5 1
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Span for [100, 80, 60, 70, 60, 75, 85] ===" << endl;
    cout << "Day 0 (100): stack empty -> span = 0+1 = 1. Push 0." << endl;
    cout << "Day 1 (80):  80 < 100, stop. span = 1-0 = 1. Push 1." << endl;
    cout << "Day 2 (60):  60 < 80, stop. span = 2-1 = 1. Push 2." << endl;
    cout << "Day 3 (70):  60 <= 70, pop. 70 < 80, stop. span = 3-1 = 2. Push 3." << endl;
    cout << "Day 4 (60):  60 < 70, stop. span = 4-3 = 1. Push 4." << endl;
    cout << "Day 5 (75):  60 <= 75, pop. 70 <= 75, pop. 75 < 80, stop. span = 5-1 = 4. Push 5." << endl;
    cout << "Day 6 (85):  75 <= 85, pop. 60 <= 85, pop. 70 popped... 80 <= 85, pop. 85 < 100. span = 6-0 = 6." << endl;
    cout << "Result: [1, 1, 1, 2, 1, 4, 6]" << endl << endl;
}

void demoCompareBruteVsOptimal() {
    cout << "=== Brute Force vs Optimal ===" << endl;
    int prices[] = {100, 80, 60, 70, 60, 75, 85};
    int n = 7;

    vector<int> brute = stockSpanBruteForce(prices, n);
    vector<int> optimal = stockSpan(prices, n);

    cout << "Brute force: ";
    for (int i = 0; i < n; i++) cout << brute[i] << " ";
    cout << endl;

    cout << "Optimal:     ";
    for (int i = 0; i < n; i++) cout << optimal[i] << " ";
    cout << endl;

    bool match = true;
    for (int i = 0; i < n; i++) {
        if (brute[i] != optimal[i]) match = false;
    }
    cout << "Results match: " << (match ? "Yes" : "No") << endl << endl;
}

int main() {
    demoWalkthrough();
    demoStockSpan();
    demoStockSpan2();
    demoCompareBruteVsOptimal();
    return 0;
}
