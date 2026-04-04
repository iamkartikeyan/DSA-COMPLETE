// 13.2 - Minimum Window Substring
// Find smallest substring of s containing all characters of target t.
// Variable size window with character frequency tracking.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int minVal(int a, int b) {
    return (a < b) ? a : b;
}

// Find minimum window substring containing all chars of target
// Returns start index and length via reference params
// Returns 0 if not found
int minWindow(const char s[], const char t[], int &outStart, int &outLen) {
    // Build need frequency map for target
    int need[256];
    for (int i = 0; i < 256; i++) need[i] = 0;

    int tLen = 0;
    for (int i = 0; t[i] != '\0'; i++) {
        need[(unsigned char)t[i]]++;
        tLen++;
    }

    int required = 0;
    for (int i = 0; i < 256; i++) {
        if (need[i] > 0) required++;
    }

    int window[256];
    for (int i = 0; i < 256; i++) window[i] = 0;

    int left = 0;
    int formed = 0;  // Number of chars with sufficient count
    int minLen = 1000000;
    int start = 0;
    int right = 0;

    while (s[right] != '\0') {
        unsigned char ch = s[right];
        window[ch]++;

        // Check if this char satisfies the need
        if (need[ch] > 0 && window[ch] == need[ch]) {
            formed++;
        }

        // Shrink while all required chars are satisfied
        while (formed == required && left <= right) {
            int currentLen = right - left + 1;
            if (currentLen < minLen) {
                minLen = currentLen;
                start = left;
            }

            unsigned char leftChar = s[left];
            window[leftChar]--;
            if (need[leftChar] > 0 && window[leftChar] < need[leftChar]) {
                formed--;
            }
            left++;
        }

        right++;
    }

    if (minLen == 1000000) {
        outStart = 0;
        outLen = 0;
        return 0;
    }

    outStart = start;
    outLen = minLen;
    return 1;
}

int main() {
    cout << "=== Minimum Window Substring ===" << endl;
    cout << endl;

    const char s1[] = "ADOBECODEBANC";
    const char t1[] = "ABC";

    cout << "String: " << s1 << endl;
    cout << "Target: " << t1 << endl;
    cout << endl;

    cout << "Need: A=1, B=1, C=1 (required = 3 distinct chars)" << endl;
    cout << endl;

    cout << "Key windows that satisfy requirement:" << endl;
    cout << "  \"ADOBEC\" (indices 0-5, len 6) - first valid window" << endl;
    cout << "  \"BANC\"     (indices 9-12, len 4) - smallest!  " << endl;
    cout << endl;

    int outStart = 0, outLen = 0;
    int found = minWindow(s1, t1, outStart, outLen);

    if (found) {
        cout << "Result: \"";
        for (int i = outStart; i < outStart + outLen; i++) {
            cout << s1[i];
        }
        cout << "\" (start=" << outStart << ", length=" << outLen << ")" << endl;
    } else {
        cout << "No valid window found." << endl;
    }
    cout << endl;

    // Second example
    const char s2[] = "a";
    const char t2[] = "a";
    cout << "String: " << s2 << ", Target: " << t2 << endl;
    int start2 = 0, len2 = 0;
    found = minWindow(s2, t2, start2, len2);
    if (found) {
        cout << "Result: \"";
        for (int i = start2; i < start2 + len2; i++) cout << s2[i];
        cout << "\"" << endl;
    }
    cout << endl;

    // Third example: not possible
    const char s3[] = "a";
    const char t3[] = "aa";
    cout << "String: " << s3 << ", Target: " << t3 << endl;
    int start3 = 0, len3 = 0;
    found = minWindow(s3, t3, start3, len3);
    if (found) {
        cout << "Result: found, length=" << len3 << endl;
    } else {
        cout << "Result: not found (need 2 A's, only have 1)" << endl;
    }
    cout << endl;

    cout << "Approach:" << endl;
    cout << "  1. Build need[] frequency map for target chars" << endl;
    cout << "  2. Expand right, add chars to window[]" << endl;
    cout << "  3. Track 'formed' = how many chars meet their need count" << endl;
    cout << "  4. When formed == required: try to shrink for minimum" << endl;
    cout << "  5. While shrinking, update answer if current window is smaller" << endl;
    cout << "  6. Time: O(n), Space: O(1) fixed 256-size arrays" << endl;

    return 0;
}
