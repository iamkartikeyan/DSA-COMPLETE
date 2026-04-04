// 13.2 Sliding Window Technique
// Fixed size window, variable size window, max sum, longest substring, min window

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// CONCEPT: Maintain a "window" that slides over the data
// Two types:
//   1. Fixed size: window size k is constant, slide one element at a time
//   2. Variable size: expand right, shrink left based on constraint
// ============================================================

// ============================================================
// 1. FIXED SIZE WINDOW: Maximum Sum Subarray of Size K
// Time: O(n), Space: O(1)
// ============================================================
int maxSumFixedWindow(const vector<int>& arr, int k) {
    if ((int)arr.size() < k) return -1;
    int windowSum = 0;
    // Compute sum of first window
    for (int i = 0; i < k; i++) windowSum += arr[i];

    int maxSum = windowSum;
    // Slide window: subtract outgoing, add incoming
    for (int i = k; i < (int)arr.size(); i++) {
        windowSum += arr[i] - arr[i - k];  // Slide by 1
        maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}

// ============================================================
// 2. FIXED SIZE: First Negative in Every Window of Size K
// ============================================================
vector<int> firstNegative(const vector<int>& arr, int k) {
    vector<int> result;
    queue<int> negIndices;  // Store indices of negative numbers

    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] < 0) negIndices.push(i);     // Track negatives

        if (i >= k - 1) {                        // Window of size k
            // Remove indices outside current window
            while (!negIndices.empty() && negIndices.front() <= i - k)
                negIndices.pop();
            result.push_back(negIndices.empty() ? 0 : arr[negIndices.front()]);
        }
    }
    return result;
}

// ============================================================
// 3. VARIABLE SIZE WINDOW: Longest Subarray with Sum <= K
// Expand right, shrink left when sum exceeds limit
// Time: O(n), Space: O(1)
// ============================================================
int longestSubarraySumK(const vector<int>& arr, int k) {
    int left = 0, sum = 0, maxLen = 0;
    for (int right = 0; right < (int)arr.size(); right++) {
        sum += arr[right];                       // Expand
        while (sum > k && left <= right) {       // Shink until valid
            sum -= arr[left++];
        }
        if (sum <= k) maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// ============================================================
// 4. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS
// Use hash set / array to track characters in current window
// Time: O(n), Space: O(min(n, charset))
// ============================================================
int longestUniqueSubstring(const string& s) {
    vector<int> lastSeen(256, -1);  // Last seen position of each char
    int maxLen = 0, left = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        // If char already in window, shrink to after its last position
        if (lastSeen[s[right]] >= left)
            left = lastSeen[s[right]] + 1;
        lastSeen[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// ============================================================
// 5. LONGEST SUBSTRING WITH AT MOST K DISTINCT CHARACTERS
// ============================================================
int longestKDistinct(const string& s, int k) {
    unordered_map<char, int> freq;
    int maxLen = 0, left = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        freq[s[right]]++;                        // Expand

        while ((int)freq.size() > k) {           // Shrink if too many distinct
            freq[s[left]]--;
            if (freq[s[left]] == 0) freq.erase(s[left]);
            left++;
        }
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// ============================================================
// 6. MINIMUM WINDOW SUBSTRING
// Find smallest substring of s containing all chars of t
// Time: O(n), Space: O(charset)
// ============================================================
string minWindow(const string& s, const string& t) {
    if (t.empty() || s.size() < t.size()) return "";

    unordered_map<char, int> need;
    for (char c : t) need[c]++;
    int required = need.size();                  // Number of unique chars needed

    int left = 0, formed = 0;                    // formed = chars satisfied
    int minLen = INT_MAX, start = 0;
    unordered_map<char, int> window;

    for (int right = 0; right < (int)s.size(); right++) {
        window[s[right]]++;
        if (need.count(s[right]) && window[s[right]] == need[s[right]])
            formed++;

        // Shrink while all chars are satisfied
        while (formed == required && left <= right) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                start = left;
            }
            window[s[left]]--;
            if (need.count(s[left]) && window[s[left]] < need[s[left]])
                formed--;
            left++;
        }
    }
    return (minLen == INT_MAX) ? "" : s.substr(start, minLen);
}

// ============================================================
// 7. MAXIMUM SUM SUBARRAY (Kadane's - sliding window variant)
// Time: O(n), Space: O(1)
// ============================================================
int kadane(const vector<int>& arr) {
    int maxSoFar = arr[0], currentMax = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        currentMax = max(arr[i], currentMax + arr[i]);  // Extend or restart
        maxSoFar = max(maxSoFar, currentMax);
    }
    return maxSoFar;
}

// ============================================================
// 8. COUNT ANAGRAMS in string
// Fixed window of size |pattern|, compare frequency maps
// ============================================================
int countAnagrams(const string& s, const string& pattern) {
    if (s.size() < pattern.size()) return 0;

    vector<int> patternFreq(26, 0), windowFreq(26, 0);
    for (char c : pattern) patternFreq[c - 'a']++;

    int count = 0, k = pattern.size();
    // Build first window
    for (int i = 0; i < k; i++) windowFreq[s[i] - 'a']++;
    if (windowFreq == patternFreq) count++;

    // Slide window
    for (int i = k; i < (int)s.size(); i++) {
        windowFreq[s[i] - 'a']++;               // Add new char
        windowFreq[s[i - k] - 'a']--;           // Remove old char
        if (windowFreq == patternFreq) count++;
    }
    return count;
}

// ============================================================
// 9. FRUIT INTO BASKETS (at most 2 types)
// Variable window with at most 2 distinct elements
// ============================================================
int fruitIntoBaskets(const vector<int>& fruits) {
    unordered_map<int, int> count;
    int maxFruits = 0, left = 0;

    for (int right = 0; right < (int)fruits.size(); right++) {
        count[fruits[right]]++;
        while (count.size() > 2) {              // Shrink to 2 types
            count[fruits[left]]--;
            if (count[fruits[left]] == 0) count.erase(fruits[left]);
            left++;
        }
        maxFruits = max(maxFruits, right - left + 1);
    }
    return maxFruits;
}

void printVec(const string& label, const vector<int>& v) {
    cout << label;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    cout << "=== 13.2 Sliding Window ===\n\n";

    // --- Fixed Window: Max Sum ---
    vector<int> arr = {1, 4, 2, 10, 2, 3, 1, 0, 20};
    printVec("Array: ", arr);
    int k = 4;
    cout << "  Max sum of subarray size " << k << ": "
         << maxSumFixedWindow(arr, k) << "\n";
    cout << "  Explanation: window [2,3,1,0]=6 -> [3,1,0,20]=24\n\n";

    // --- Fixed Window: First Negative ---
    vector<int> nums = {12, -1, -7, 8, -15, 30, 16, 28};
    k = 3;
    printVec("Array: ", nums);
    cout << "  First negative in each window of size " << k << ": ";
    for (int x : firstNegative(nums, k)) cout << x << " ";
    cout << "\n\n";

    // --- Variable Size: Longest Subarray with Sum <= K ---
    vector<int> vals = {1, 2, 3, 1, 1, 1, 4, 2, 1};
    int limit = 5;
    printVec("Array: ", vals);
    cout << "  Longest subarray with sum <= " << limit << ": length "
         << longestSubarraySumK(vals, limit) << "\n\n";

    // --- Longest Unique Substring ---
    string s = "abcabcbb";
    cout << "Longest unique substring in \"" << s << "\": length "
         << longestUniqueSubstring(s) << " (answer: \"abc\")\n";
    s = "pwwkew";
    cout << "Longest unique substring in \"" << s << "\": length "
         << longestUniqueSubstring(s) << " (answer: \"wke\")\n\n";

    // --- Longest K Distinct ---
    s = "eceba";
    k = 2;
    cout << "Longest substring with at most " << k << " distinct in \"" << s
         << "\": length " << longestKDistinct(s, k) << " (answer: \"ece\")\n\n";

    // --- Minimum Window Substring ---
    string text = "ADOBECODEBANC", pattern = "ABC";
    cout << "Min window in \"" << text << "\" containing \"" << pattern
         << "\": \"" << minWindow(text, pattern) << "\"\n";
    text = "a"; pattern = "a";
    cout << "Min window in \"" << text << "\" containing \"" << pattern
         << "\": \"" << minWindow(text, pattern) << "\"\n\n";

    // --- Kadane's (Max Sum Subarray) ---
    vector<int> kad = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    printVec("Array: ", kad);
    cout << "  Max sum subarray (Kadane's): " << kadane(kad)
         << " (subarray [4,-1,2,1] = 6)\n\n";

    // --- Count Anagrams ---
    string text2 = "cbaebabacd", pat2 = "abc";
    cout << "Anagrams of \"" << pat2 << "\" in \"" << text2 << "\": "
         << countAnagrams(text2, pat2) << " found\n\n";

    // --- Fruit into Baskets ---
    vector<int> fruits = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    printVec("Fruits: ", fruits);
    cout << "  Max fruits in 2 baskets: " << fruitIntoBaskets(fruits) << "\n";

    cout << "\n--- Sliding Window Summary ---\n";
    cout << "Fixed size:    window size k is constant; slide by 1 each step\n";
    cout << "  Examples: max sum of k elements, first negative, anagram count\n";
    cout << "Variable size: expand right, shrink left when constraint violated\n";
    cout << "  Examples: longest unique substring, min window, Kadane's\n";
    cout << "Template: for right in 0..n-1 { add arr[right]; while invalid remove arr[left++]; update answer; }\n";

    return 0;
}
