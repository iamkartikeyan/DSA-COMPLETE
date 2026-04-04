// 15.1 Monotonic Stack & Queue
// Monotonic structures maintain elements in sorted order (increasing/decreasing)
// while processing. Used for next greater element, rain water, sliding window.

#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>

using namespace std;

// ============================================================
// NEXT GREATER ELEMENT (Monotonic Stack)
// For each element, find the next element to the right that is greater.
// Time: O(n) - each element pushed/popped at most once.
// ============================================================

vector<int> nextGreaterElement(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;  // Stores indices

    for (int i = 0; i < n; i++) {
        // Pop elements smaller than current (current is their next greater)
        while (!st.empty() && arr[st.top()] < arr[i]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

// Next Smaller Element (reverse comparison)
vector<int> nextSmallerElement(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

void demoNextGreater() {
    cout << "=== Next Greater Element ===" << endl;
    vector<int> arr = {4, 5, 2, 10, 8};
    auto nge = nextGreaterElement(arr);
    cout << "Array: "; for (int x : arr) cout << x << " "; cout << endl;
    cout << "NGE:   "; for (int x : nge) cout << x << " ";  // 5 10 10 -1 -1
    cout << endl;

    auto nse = nextSmallerElement(arr);
    cout << "NSE:   "; for (int x : nse) cout << x << " ";  // -1 2 -1 8 -1
    cout << endl << endl;
}

// ============================================================
// LARGEST RECTANGLE IN HISTOGRAM
// Uses monotonic stack to find left/right boundaries for each bar.
// Time: O(n)
// ============================================================

int largestRectangleArea(const vector<int>& heights) {
    int n = heights.size(), maxArea = 0;
    stack<int> st;  // Increasing stack of indices

    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];  // Sentinel: 0 at end flushes stack
        while (!st.empty() && heights[st.top()] >= h) {
            int height = heights[st.top()]; st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }
    return maxArea;
}

void demoLargestRectangle() {
    cout << "=== Largest Rectangle in Histogram ===" << endl;
    vector<int> h = {2, 1, 5, 6, 2, 3};
    cout << "Heights: "; for (int x : h) cout << x << " "; cout << endl;
    cout << "Max Area: " << largestRectangleArea(h) << endl;  // 10 (bars 5,6)
    cout << endl;
}

// ============================================================
// TRAPPING RAIN WATER
// Water at index i = min(maxLeft, maxRight) - height[i]
// Solved via two-pass, stack, or two pointers.
// ============================================================

// Two-pointer approach: O(n) time, O(1) space
int trapRainWater(const vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0, water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) leftMax = height[left];
            else water += leftMax - height[left];
            left++;
        } else {
            if (height[right] >= rightMax) rightMax = height[right];
            else water += rightMax - height[right];
            right--;
        }
    }
    return water;
}

// Monotonic stack approach: track boundaries of "valleys"
int trapRainWaterStack(const vector<int>& height) {
    int n = height.size(), water = 0;
    stack<int> st;  // Decreasing stack of indices

    for (int i = 0; i < n; i++) {
        while (!st.empty() && height[i] > height[st.top()]) {
            int bottom = height[st.top()]; st.pop();
            if (st.empty()) break;
            int h = min(height[st.top()], height[i]) - bottom;
            int w = i - st.top() - 1;
            water += h * w;
        }
        st.push(i);
    }
    return water;
}

void demoTrappingRainWater() {
    cout << "=== Trapping Rain Water ===" << endl;
    vector<int> h = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Heights: "; for (int x : h) cout << x << " "; cout << endl;
    cout << "Water trapped (two-pointer): " << trapRainWater(h) << endl;  // 6
    cout << "Water trapped (stack):       " << trapRainWaterStack(h) << endl;  // 6
    cout << endl;
}

// ============================================================
// SLIDING WINDOW MAXIMUM (Monotonic Deque)
// Maintain a deque with decreasing values. Front is always max.
// Time: O(n) - each element enters/leaves deque at most once.
// ============================================================

vector<int> slidingWindowMax(const vector<int>& arr, int k) {
    deque<int> dq;  // Stores indices, values in decreasing order
    vector<int> result;

    for (int i = 0; i < (int)arr.size(); i++) {
        // Remove elements outside window
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        // Remove smaller elements (maintain decreasing order)
        while (!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();
        dq.push_back(i);
        // Window is valid from index k-1 onwards
        if (i >= k - 1) result.push_back(arr[dq.front()]);
    }
    return result;
}

void demoSlidingWindowMax() {
    cout << "=== Sliding Window Maximum ===" << endl;
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    cout << "Array: "; for (int x : arr) cout << x << " "; cout << endl;
    cout << "Window size: " << k << endl;

    auto result = slidingWindowMax(arr, k);
    cout << "Max in each window: ";
    for (int x : result) cout << x << " ";  // 3 3 5 5 6 7
    cout << endl << endl;
}

// ============================================================
// REMOVE K DIGITS - Monotonic Stack Application
// Build smallest number by removing k digits.
// Greedy: remove larger digits when a smaller one follows.
// ============================================================

string removeKDigits(string num, int k) {
    string result;  // Acts as monotonic stack
    for (char c : num) {
        while (k > 0 && !result.empty() && result.back() > c) {
            result.pop_back();
            k--;
        }
        if (!result.empty() || c != '0')  // Skip leading zeros
            result.push_back(c);
    }
    // Remove remaining digits from end
    while (k > 0 && !result.empty()) { result.pop_back(); k--; }
    return result.empty() ? "0" : result;
}

void demoRemoveKDigits() {
    cout << "=== Remove K Digits ===" << endl;
    cout << "\"1432219\", k=3 -> \"" << removeKDigits("1432219", 3) << "\"" << endl;  // "1219"
    cout << "\"10200\", k=1  -> \"" << removeKDigits("10200", 1) << "\"" << endl;       // "200"
    cout << "\"10\", k=2     -> \"" << removeKDigits("10", 2) << "\"" << endl;          // "0"
    cout << endl;
}

int main() {
    demoNextGreater();
    demoLargestRectangle();
    demoTrappingRainWater();
    demoSlidingWindowMax();
    demoRemoveKDigits();
    return 0;
}
