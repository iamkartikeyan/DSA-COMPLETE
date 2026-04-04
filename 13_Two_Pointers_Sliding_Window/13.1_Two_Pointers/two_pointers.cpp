// 13.1 Two Pointers Technique
// Opposite ends, same direction, pair sum, remove duplicates, merge sorted arrays

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// CONCEPT: Use two indices to traverse array in one pass
// Common patterns:
//   1. Opposite ends (left++, right--) - for sorted arrays
//   2. Same direction (fast, slow) - for partitioning, removing
// ============================================================

// ============================================================
// 1. PAIR SUM in sorted array (Opposite Ends)
// Time: O(n), Space: O(1)
// ============================================================
pair<int, int> pairSumSorted(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) return {left, right};  // Found
        if (sum < target) left++;                  // Need larger sum
        else right--;                              // Need smaller sum
    }
    return {-1, -1};  // Not found
}

// Pair sum for unsorted array: use hash set instead (O(n) space)
pair<int, int> pairSumUnsorted(const vector<int>& arr, int target) {
    unordered_set<int> seen;
    for (int i = 0; i < (int)arr.size(); i++) {
        int complement = target - arr[i];
        if (seen.count(complement)) return {i, (int)find(arr.begin(), arr.end(), complement) - arr.begin()};
        seen.insert(arr[i]);
    }
    return {-1, -1};
}

// ============================================================
// 2. THREE SUM (fix one, two-pointer for remaining)
// Find all unique triplets summing to 0
// Time: O(n^2), Space: O(1) excluding output
// ============================================================
vector<vector<int>> threeSum(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    vector<vector<int>> result;
    for (int i = 0; i < (int)arr.size() - 2; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) continue;  // Skip duplicates
        int left = i + 1, right = arr.size() - 1;
        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];
            if (sum == 0) {
                result.push_back({arr[i], arr[left], arr[right]});
                while (left < right && arr[left] == arr[left + 1]) left++;   // Skip dupes
                while (left < right && arr[right] == arr[right - 1]) right--;
                left++; right--;
            } else if (sum < 0) left++;
            else right--;
        }
    }
    return result;
}

// ============================================================
// 3. REMOVE DUPLICATES from sorted array (Same Direction)
// Slow pointer = write position, Fast pointer = read position
// Time: O(n), Space: O(1)
// ============================================================
int removeDuplicates(vector<int>& arr) {
    if (arr.empty()) return 0;
    int slow = 1;  // Write position (first element always kept)
    for (int fast = 1; fast < (int)arr.size(); fast++) {
        if (arr[fast] != arr[fast - 1]) {  // New unique element
            arr[slow++] = arr[fast];       // Write and advance
        }
    }
    return slow;  // New length
}

// ============================================================
// 4. MOVE ZEROES to end
// Slow tracks position for non-zero, fast scans
// Time: O(n), Space: O(1)
// ============================================================
void moveZeroes(vector<int>& arr) {
    int slow = 0;
    for (int fast = 0; fast < (int)arr.size(); fast++) {
        if (arr[fast] != 0) swap(arr[slow++], arr[fast]);
    }
}

// ============================================================
// 5. CONTAINER WITH MOST WATER
// Maximize area = min(height[left], height[right]) * (right - left)
// Move the shorter pointer inward (may find taller wall)
// Time: O(n)
// ============================================================
int maxArea(const vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;
    while (left < right) {
        int area = min(height[left], height[right]) * (right - left);
        maxWater = max(maxWater, area);
        if (height[left] < height[right]) left++;   // Shorter limits area
        else right--;
    }
    return maxWater;
}

// ============================================================
// 6. REVERSE ARRAY (Classic two pointers)
// Swap from ends moving inward
// ============================================================
void reverseArray(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) swap(arr[left++], arr[right--]);
}

// ============================================================
// 7. CHECK IF ARRAY IS PALINDROME
// ============================================================
bool isPalindrome(const vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right)
        if (arr[left++] != arr[right--]) return false;
    return true;
}

// ============================================================
// 8. MERGE TWO SORTED ARRAYS
// Use two pointers, pick smaller element each step
// Time: O(n + m)
// ============================================================
vector<int> mergeSorted(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i] <= b[j]) result.push_back(a[i++]);
        else result.push_back(b[j++]);
    }
    while (i < (int)a.size()) result.push_back(a[i++]);
    while (j < (int)b.size()) result.push_back(b[j++]);
    return result;
}

// ============================================================
// 9. MERGE SORTED IN-PLACE (nums1 has extra space at end)
// Start from the END to avoid overwriting
// ============================================================
void mergeInPlace(vector<int>& nums1, int m, const vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
    while (j >= 0) nums1[k--] = nums2[j--];  // Copy remaining from nums2
}

// ============================================================
// 10. FIND INTERSECTION OF TWO SORTED ARRAYS
// ============================================================
vector<int> intersection(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i] == b[j]) {
            if (result.empty() || result.back() != a[i])  // Avoid duplicates
                result.push_back(a[i]);
            i++; j++;
        } else if (a[i] < b[j]) i++;
        else j++;
    }
    return result;
}

// Print helper
void printVec(const string& label, const vector<int>& v) {
    cout << label;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    cout << "=== 13.1 Two Pointers ===\n\n";

    // --- Pair Sum (sorted) ---
    vector<int> sorted = {1, 3, 5, 7, 9, 11};
    printVec("Sorted array: ", sorted);
    auto [l, r] = pairSumSorted(sorted, 12);
    cout << "  Pair summing to 12: indices (" << l << ", " << r
         << ") -> (" << (l != -1 ? to_string(sorted[l]) : "none")
         << ", " << (r != -1 ? to_string(sorted[r]) : "none") << ")\n\n";

    // --- Three Sum ---
    vector<int> ts = {-1, 0, 1, 2, -1, -4};
    printVec("Three Sum input: ", ts);
    auto triplets = threeSum(ts);
    cout << "  Triplets summing to 0:\n";
    for (auto& t : triplets)
        cout << "    [" << t[0] << ", " << t[1] << ", " << t[2] << "]\n";
    cout << "\n";

    // --- Remove Duplicates ---
    vector<int> dups = {1, 1, 2, 2, 3, 4, 4, 5};
    printVec("Before dedup: ", dups);
    int newLen = removeDuplicates(dups);
    cout << "  New length: " << newLen << ", Array: ";
    for (int i = 0; i < newLen; i++) cout << dups[i] << " ";
    cout << "\n\n";

    // --- Move Zeroes ---
    vector<int> zeros = {0, 1, 0, 3, 12};
    printVec("Before move zeroes: ", zeros);
    moveZeroes(zeros);
    printVec("After move zeroes:  ", zeros);

    // --- Container with Most Water ---
    vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    printVec("Heights: ", heights);
    cout << "  Max water: " << maxArea(heights) << "\n\n";

    // --- Reverse Array ---
    vector<int> rev = {1, 2, 3, 4, 5};
    printVec("Before reverse: ", rev);
    reverseArray(rev);
    printVec("After reverse:  ", rev);

    // --- Palindrome Check ---
    vector<int> pal = {1, 2, 3, 2, 1};
    printVec("Array: ", pal);
    cout << "  Is palindrome? " << (isPalindrome(pal) ? "Yes" : "No") << "\n\n";

    // --- Merge Sorted Arrays ---
    vector<int> a = {1, 4, 7}, b = {2, 3, 6, 8};
    printVec("Array A: ", a);
    printVec("Array B: ", b);
    printVec("Merged:  ", mergeSorted(a, b));

    // --- Merge In-Place ---
    vector<int> nums1 = {1, 3, 5, 0, 0, 0};
    vector<int> nums2 = {2, 4, 6};
    cout << "\n  Merge in-place: {1,3,5,_,_,_} + {2,4,6} -> ";
    mergeInPlace(nums1, 3, nums2, 3);
    for (int x : nums1) cout << x << " ";
    cout << "\n";

    // --- Intersection ---
    vector<int> arr1 = {1, 2, 2, 3, 5}, arr2 = {2, 2, 5, 7};
    printVec("A: ", arr1);
    printVec("B: ", arr2);
    printVec("Intersection: ", intersection(arr1, arr2));

    cout << "\n--- Two Pointers Summary ---\n";
    cout << "Opposite ends: pair sum, container, palindrome, reverse\n";
    cout << "Same direction: remove dupes, move zeroes, sliding window\n";
    cout << "Key: sort first when array is unsorted, then apply two pointers\n";

    return 0;
}
