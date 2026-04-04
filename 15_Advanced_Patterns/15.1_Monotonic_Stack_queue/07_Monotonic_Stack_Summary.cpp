// 15.1 - Monotonic Stack & Queue Summary
// Complete reference for all monotonic stack/queue patterns and problems.

#include <iostream>
#include <stack>
#include <deque>
#include <vector>

using namespace std;

// ============================================================
// PATTERN CHEATSHEET
// ============================================================

void demoPatternSummary() {
    cout << "=== MONOTONIC STACK & QUEUE PATTERN SUMMARY ===" << endl;
    cout << endl;
    cout << "CORE IDEA:" << endl;
    cout << "  Maintain elements in sorted order while processing." << endl;
    cout << "  When a new element violates the order, pop until it doesn't." << endl;
    cout << "  Each element pushed once, popped at most once -> O(n) total." << endl;
    cout << endl;
    cout << "MONOTONIC STACK (using std::stack):" << endl;
    cout << "  - Decreasing stack: pop elements <= current" << endl;
    cout << "  - Increasing-stack: pop elements >= current" << endl;
    cout << "  - Stores INDICES, not values (to compute widths/distances)" << endl;
    cout << endl;
    cout << "MONOTONIC QUEUE/DEQUE (using std::deque):" << endl;
    cout << "  - Pop from BACK to maintain order before inserting" << endl;
    cout << "  - Pop from FRONT to remove elements outside window" << endl;
    cout << "  - Front of deque is the extremum (max or min)" << endl;
    cout << endl;
}

// ============================================================
// PROBLEM CATALOG
// ============================================================

void demoProblemCatalog() {
    cout << "=== PROBLEM CATALOG ===" << endl;
    cout << endl;
    cout << "1. Next Greater Element (NGE)" << endl;
    cout << "   Pattern: Monotonic decreasing stack" << endl;
    cout << "   For each element, find next element to the right that is greater" << endl;
    cout << "   Time: O(n), Space: O(n)" << endl;
    cout << endl;
    cout << "2. Next Smaller Element (NSE)" << endl;
    cout << "   Pattern: Monotonic increasing stack" << endl;
    cout << "   Reverse comparison of NGE" << endl;
    cout << endl;
    cout << "3. Previous Greater Element (PGE)" << endl;
    cout << "   Pattern: Monotonic decreasing stack" << endl;
    cout << "   Scan left to right, stack top after popping is PGE" << endl;
    cout << endl;
    cout << "4. Previous Smaller Element (PSE)" << endl;
    cout << "   Pattern: Monotonic increasing stack" << endl;
    cout << endl;
    cout << "5. Stock Span Problem" << endl;
    cout << "   Pattern: PGE variant" << endl;
    cout << "   Span[i] = i - PGE_index (or i+1 if no PGE)" << endl;
    cout << endl;
    cout << "6. Largest Rectangle in Histogram" << endl;
    cout << "   Pattern: Monotonic increasing stack with sentinel" << endl;
    cout << "   For each bar, find left/right boundaries (nearest smaller)" << endl;
    cout << "   Width = right - left - 1, Area = height * width" << endl;
    cout << endl;
    cout << "7. Trapping Rain Water" << endl;
    cout << "   Pattern: Monotonic decreasing stack (track valleys)" << endl;
    cout << "   OR two-pointer approach: O(n) time, O(1) space" << endl;
    cout << "   Water[i] = min(maxLeft, maxRight) - height[i]" << endl;
    cout << endl;
    cout << "8. Sliding Window Maximum" << endl;
    cout << "   Pattern: Monotonic decreasing deque" << endl;
    cout << "   Remove outside window from front, smaller from back" << endl;
    cout << "   Front is always the window maximum" << endl;
    cout << endl;
    cout << "9. Remove K Digits" << endl;
    cout << "   Pattern: Monotonic increasing (string as stack)" << endl;
    cout << "   Greedy: remove larger digits when smaller follows" << endl;
    cout << endl;
    cout << "10. Circular NGE" << endl;
    cout << "    Pattern: Same as NGE, use modulo for two passes" << endl;
    cout << endl;
}

// ============================================================
// HOW TO CHOOSE THE RIGHT PATTERN
// ============================================================

void demoHowToChoose() {
    cout << "=== HOW TO CHOOSE THE RIGHT PATTERN ===" << endl;
    cout << endl;
    cout << "Ask yourself:" << endl;
    cout << "  Q: Need nearest greater/smaller element?" << endl;
    cout << "  A: Use monotonic stack (decreasing for greater, increasing for smaller)" << endl;
    cout << endl;
    cout << "  Q: Need boundaries where element is min/max in a range?" << endl;
    cout << "  A: Use monotonic increasing stack (for rectangle/histogram problems)" << endl;
    cout << endl;
    cout << "  Q: Sliding window extremum?" << endl;
    cout << "  A: Use monotonic deque (decreasing for max, increasing for min)" << endl;
    cout << endl;
    cout << "  Q: Building smallest/largest number by removing digits?" << endl;
    cout << "  A: Use monotonic stack on string" << endl;
    cout << endl;
    cout << "  Q: Trapping water between bars?" << endl;
    cout << "  A: Two-pointer (simpler) or monotonic stack (same complexity)" << endl;
    cout << endl;
}

// ============================================================
// COMPLEXITY COMPARISON
// ============================================================

void demoComplexityComparison() {
    cout << "=== COMPLEXITY COMPARISON ===" << endl;
    cout << endl;
    cout << "Problem                    | Brute Force | Optimal" << endl;
    cout << "---------------------------|-------------|--------" << endl;
    cout << "Next Greater Element       | O(n^2)      | O(n) stack" << endl;
    cout << "Stock Span                 | O(n^2)      | O(n) stack" << endl;
    cout << "Largest Rectangle          | O(n^2)      | O(n) stack" << endl;
    cout << "Trapping Rain Water        | O(n^2)      | O(n) two-ptr / stack" << endl;
    cout << "Sliding Window Maximum     | O(n*k)      | O(n) deque" << endl;
    cout << "Remove K Digits            | O(n*C(k,n)) | O(n) stack" << endl;
    cout << endl;
}

// ============================================================
// QUICK IMPLEMENTATION REFERENCE
// ============================================================

void demoQuickReference() {
    cout << "=== QUICK IMPLEMENTATION REFERENCE ===" << endl;
    cout << endl;
    cout << "// Next Greater Element:" << endl;
    cout << "stack<int> st;  // decreasing" << endl;
    cout << "for (int i = 0; i < n; i++) {" << endl;
    cout << "    while (!st.empty() && arr[st.top()] < arr[i]) {" << endl;
    cout << "        result[st.top()] = arr[i];" << endl;
    cout << "        st.pop();" << endl;
    cout << "    }" << endl;
    cout << "    st.push(i);" << endl;
    cout << "}" << endl;
    cout << endl;
    cout << "// Sliding Window Maximum:" << endl;
    cout << "deque<int> dq;  // decreasing" << endl;
    cout << "for (int i = 0; i < n; i++) {" << endl;
    cout << "    if (!dq.empty() && dq.front() == i - k) dq.pop_front();" << endl;
    cout << "    while (!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();" << endl;
    cout << "    dq.push_back(i);" << endl;
    cout << "    if (i >= k - 1) result.push_back(arr[dq.front()]);" << endl;
    cout << "}" << endl;
    cout << endl;
}

int main() {
    demoPatternSummary();
    demoProblemCatalog();
    demoHowToChoose();
    demoComplexityComparison();
    demoQuickReference();
    return 0;
}
