// 13.2 - Longest Substring Without Repeating Characters
// Uses lastSeen array to track character positions.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

// Longest substring without repeating characters
int longestUniqueSubstring(const char s[]) {
    int lastSeen[256];
    for (int i = 0; i < 256; i++) lastSeen[i] = -1;

    int maxLen = 0;
    int left = 0;
    int right = 0;

    while (s[right] != '\0') {
        unsigned char ch = s[right];

        // If character was seen in current window, jump left past it
        if (lastSeen[ch] >= left) {
            left = lastSeen[ch] + 1;
        }

        lastSeen[ch] = right;
        maxLen = maxVal(maxLen, right - left + 1);
        right++;
    }
    return maxLen;
}

int main() {
    cout << "=== Longest Substring Without Repeating Characters ===" << endl;
    cout << endl;

    const char s1[] = "abcabcbb";
    cout << "String: " << s1 << endl;
    int ans1 = longestUniqueSubstring(s1);
    cout << "Answer: " << ans1 << " (substring \"abc\")" << endl;
    cout << endl;

    cout << "Step-by-step for \"abcabcbb\":" << endl;
    cout << "  right=0: 'a', lastSeen=-1 -> no conflict, window=[0..0], len=1" << endl;
    cout << "  right=1: 'b', lastSeen=-1 -> no conflict, window=[0..1], len=2" << endl;
    cout << "  right=2: 'c', lastSeen=-1 -> no conflict, window=[0..2], len=3" << endl;
    cout << "  right=3: 'a', lastSeen=0  -> CONFLICT! left=0+1=1, window=[1..3], len=3" << endl;
    cout << "  right=4: 'b', lastSeen=1  -> CONFLICT! left=1+1=2, window=[2..4], len=3" << endl;
    cout << "  right=5: 'c', lastSeen=2  -> CONFLICT! left=2+1=3, window=[3..5], len=3" << endl;
    cout << "  right=6: 'b', lastSeen=4  -> no conflict (4>=3), window=[3..6], len=4" << endl;
    cout << "           Wait: lastSeen['b']=4 >= left=3 -> CONFLICT! left=5, window=[5..6], len=2" << endl;
    cout << "  right=7: 'b', lastSeen=6  -> CONFLICT! left=6+1=7, window=[7..7], len=1" << endl;
    cout << "  Max length = 3" << endl;
    cout << endl;

    const char s2[] = "pwwkew";
    cout << "String: " << s2 << endl;
    int ans2 = longestUniqueSubstring(s2);
    cout << "Answer: " << ans2 << " (substring \"wke\")" << endl;
    cout << endl;

    const char s3[] = "abcde";
    cout << "String: " << s3 << endl;
    int ans3 = longestUniqueSubstring(s3);
    cout << "Answer: " << ans3 << " (all unique, no repeats)" << endl;
    cout << endl;

    const char s4[] = "bbbbb";
    cout << "String: " << s4 << endl;
    int ans4 = longestUniqueSubstring(s4);
    cout << "Answer: " << ans4 << " (all same character)" << endl;
    cout << endl;

    cout << "Approach:" << endl;
    cout << "  1. lastSeen[256] stores the last index of each character" << endl;
    cout << "  2. If char was seen at index >= left, it is in current window" << endl;
    cout << "  3. Jump left to lastSeen[char] + 1 (skip past the repeat)" << endl;
    cout << "  4. Always update lastSeen[char] = right" << endl;
    cout << "  5. Time: O(n), Space: O(1) fixed 256-size array" << endl;

    return 0;
}
