// 15.1 - Largest Rectangle in Histogram
// Given bar heights, find the largest rectangular area.
// Uses a monotonic increasing stack to find left/right boundaries for each bar.
// Time: O(n), Space: O(n).
//
// PATTERN:
//   For each bar, we need the nearest smaller bar on the left and right.
//   The rectangle with this bar's height extends between those boundaries.
//   Width = right_boundary - left_boundary - 1
//   Area = height * width
//
//   We use a sentinel (height 0) at the end to flush remaining elements
//   from the stack, ensuring all bars are processed.

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// ============================================================
// LARGEST RECTANGLE - Monotonic Stack O(n)
// ============================================================

int largestRectangleArea(const int heights[], int n) {
    int maxArea = 0;
    stack<int> st;  // Increasing stack of indices

    for (int i = 0; i <= n; i++) {
        // Use 0 as sentinel height at position n to flush stack
        int h = (i == n) ? 0 : heights[i];

        // Pop bars taller than current - we found their right boundary
        while (!st.empty() && heights[st.top()] >= h) {
            int height = heights[st.top()];
            st.pop();
            // Left boundary is the new top (or -1 if empty)
            // Right boundary is i (current position)
            int width = st.empty() ? i : i - st.top() - 1;
            int area = height * width;
            if (area > maxArea) maxArea = area;
        }
        st.push(i);
    }
    return maxArea;
}

// ============================================================
// ALTERNATIVE: Using explicit left/right boundary arrays
// More intuitive but uses extra space.
// ============================================================

int largestRectangleAreaExplicit(const int heights[], int n) {
    int left[1000];   // Nearest smaller element to the left
    int right[1000];  // Nearest smaller element to the right

    stack<int> st;

    // Find left boundaries (previous smaller element)
    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    // Clear stack for right boundaries
    while (!st.empty()) st.pop();

    // Find right boundaries (next smaller element)
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        right[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    // Calculate max area
    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        int width = right[i] - left[i] - 1;
        int area = heights[i] * width;
        if (area > maxArea) maxArea = area;
    }
    return maxArea;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoLargestRectangle() {
    cout << "=== Largest Rectangle in Histogram ===" << endl;
    int h[] = {2, 1, 5, 6, 2, 3};
    int n = 6;

    cout << "Heights: ";
    for (int i = 0; i < n; i++) cout << h[i] << " ";
    cout << endl;

    int area = largestRectangleArea(h, n);
    cout << "Max Area: " << area << endl;  // 10 (bars 5,6 with height 5, width 2)
    cout << endl;
}

void demoLargestRectangle2() {
    cout << "=== Largest Rectangle - Example 2 ===" << endl;
    int h[] = {2, 4};
    int n = 2;

    cout << "Heights: ";
    for (int i = 0; i < n; i++) cout << h[i] << " ";
    cout << endl;

    int area = largestRectangleArea(h, n);
    cout << "Max Area: " << area << endl;  // 4 (single bar of height 4, or width 2 * height 2)
    cout << endl;
}

void demoLargestRectangle3() {
    cout << "=== Largest Rectangle - All Same Height ===" << endl;
    int h[] = {3, 3, 3, 3, 3};
    int n = 5;

    cout << "Heights: ";
    for (int i = 0; i < n; i++) cout << h[i] << " ";
    cout << endl;

    int area = largestRectangleArea(h, n);
    cout << "Max Area: " << area << endl;  // 15 (width 5 * height 3)
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Heights [2, 1, 5, 6, 2, 3] ===" << endl;
    cout << "Processing with monotonic increasing stack:" << endl;
    cout << "  i=0, h=2: push 0. Stack: [0(2)]" << endl;
    cout << "  i=1, h=1: 2>=1, pop 0, area=2*1=2. Push 1. Stack: [1(1)]" << endl;
    cout << "  i=2, h=5: push 2. Stack: [1(1), 2(5)]" << endl;
    cout << "  i=3, h=6: push 3. Stack: [1(1), 2(5), 3(6)]" << endl;
    cout << "  i=4, h=2: 6>=2, pop 3, area=6*1=6. 5>=2, pop 2, area=5*2=10. Push 4." << endl;
    cout << "  i=5, h=3: push 5. Stack: [1(1), 4(2), 5(3)]" << endl;
    cout << "  i=6, h=0(sentinel): pop 5, area=3*1=3. pop 4, area=2*4=8. pop 1, area=1*6=6." << endl;
    cout << "Max area = 10" << endl << endl;
}

void demoCompareMethods() {
    cout << "=== Compare: Stack vs Explicit Boundaries ===" << endl;
    int h[] = {2, 1, 5, 6, 2, 3};
    int n = 6;

    int area1 = largestRectangleArea(h, n);
    int area2 = largestRectangleAreaExplicit(h, n);

    cout << "Single-pass stack method: " << area1 << endl;
    cout << "Explicit boundary method: " << area2 << endl;
    cout << "Results match: " << (area1 == area2 ? "Yes" : "No") << endl << endl;
}

int main() {
    demoWalkthrough();
    demoLargestRectangle();
    demoLargestRectangle2();
    demoLargestRectangle3();
    demoCompareMethods();
    return 0;
}
