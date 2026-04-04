// 13.2 - Longest Substring with at Most K Distinct Characters
// Uses frequency map via array. Variable size window with expand/shrink.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

// Count distinct characters in frequency array
int countDistinct(int freq[]) {
    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) count++;
    }
    return count;
}

// Longest substring with at most k distinct characters
int longestKDistinct(const char s[], int k) {
    int freq[256];
    for (int i = 0; i < 256; i++) freq[i] = 0;

    int maxLen = 0;
    int left = 0;
    int right = 0;
    int distinct = 0;

    while (s[right] != '\0') {
        unsigned char ch = s[right];

        // Expand: add character to window
        if (freq[ch] == 0) distinct++;
        freq[ch]++;

        // Shrink while too many distinct characters
        while (distinct > k) {
            unsigned char leftChar = s[left];
            freq[leftChar]--;
            if (freq[leftChar] == 0) distinct--;
            left++;
        }

        maxLen = maxVal(maxLen, right - left + 1);
        right++;
    }
    return maxLen;
}

int main() {
    cout << "=== Longest Substring with at Most K Distinct ===" << endl;
    cout << endl;

    const char s1[] = "eceba";
    int k1 = 2;
    cout << "String: " << s1 << ", k = " << k1 << endl;

    cout << "Step-by-step:" << endl;
    cout << "  right=0: 'e', distinct=1, window=[0..0], len=1" << endl;
    cout << "  right=1: 'c', distinct=2, window=[0..1], len=2" << endl;
    cout << "  right=2: 'e', distinct=2, window=[0..2], len=3  (\"ece\")" << endl;
    cout << "  right=3: 'b', distinct=3 > 2 -> shrink" << endl;
    cout << "           remove 'e', freq[e]=1, distinct=3 -> shrink more" << endl;
    cout << "           remove 'c', freq[c]=0, distinct=2, left=2" << endl;
    cout << "           window=[2..3], len=2  (\"eb\")" << endl;
    cout << "  right=4: 'a', distinct=3 > 2 -> shrink" << endl;
    cout << "           remove 'e', freq[e]=0, distinct=2, left=3" << endl;
    cout << "           window=[3..4], len=2  (\"ba\")" << endl;
    cout << "  Max length = 3" << endl;
    cout << endl;

    int ans1 = longestKDistinct(s1, k1);
    cout << "Answer: " << ans1 << " (substring \"ece\")" << endl;
    cout << endl;

    const char s2[] = "ccaabbb";
    int k2 = 3;
    cout << "String: " << s2 << ", k = " << k2 << endl;
    int ans2 = longestKDistinct(s2, k2);
    cout << "Answer: " << ans2 << " (entire string has 3 distinct chars)" << endl;
    cout << endl;

    const char s3[] = "aabbcc";
    int k3 = 1;
    cout << "String: " << s3 << ", k = " << k3 << endl;
    int ans3 = longestKDistinct(s3, k3);
    cout << "Answer: " << ans3 << " (at most 1 distinct -> \"aa\" or \"bb\" or \"cc\")" << endl;
    cout << endl;

    cout << "Approach:" << endl;
    cout << "  1. freq[256] tracks character counts in current window" << endl;
    cout << "  2. Expand: add s[right], update distinct count" << endl;
    cout << "  3. While distinct > k: shrink from left, update distinct" << endl;
    cout << "  4. Track max window length at each valid step" << endl;
    cout << "  5. Time: O(n), Space: O(1) fixed 256-size array" << endl;

    return 0;
}
