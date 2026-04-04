// 13.2 - Count All Anagrams of Pattern in Text
// Fixed window frequency comparison. Count occurrences where
// the window has the same character frequencies as the pattern.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

// Compare two frequency arrays
bool freqMatch(int freq1[], int freq2[]) {
    for (int i = 0; i < 26; i++) {
        if (freq1[i] != freq2[i]) return false;
    }
    return true;
}

// Count anagrams of pattern in text
int countAnagrams(const char text[], const char pattern[]) {
    int patternFreq[26];
    int windowFreq[26];
    for (int i = 0; i < 26; i++) {
        patternFreq[i] = 0;
        windowFreq[i] = 0;
    }

    // Calculate pattern length and frequency
    int k = 0;
    while (pattern[k] != '\0') {
        patternFreq[pattern[k] - 'a']++;
        k++;
    }

    int textLen = 0;
    while (text[textLen] != '\0') textLen++;

    if (textLen < k) return 0;

    int count = 0;

    // Build first window
    for (int i = 0; i < k; i++) {
        windowFreq[text[i] - 'a']++;
    }

    // Check first window
    if (freqMatch(windowFreq, patternFreq)) count++;

    // Slide window
    for (int i = k; i < textLen; i++) {
        // Add new character
        windowFreq[text[i] - 'a']++;
        // Remove old character
        windowFreq[text[i - k] - 'a']--;

        // Check if frequencies match
        if (freqMatch(windowFreq, patternFreq)) count++;
    }

    return count;
}

int main() {
    cout << "=== Count All Anagrams of Pattern in Text ===" << endl;
    cout << endl;

    const char text1[] = "cbaebabacd";
    const char pat1[] = "abc";

    cout << "Text:    " << text1 << endl;
    cout << "Pattern: " << pat1 << endl;
    cout << "Window size k = " << 3 << endl;
    cout << endl;

    cout << "Pattern frequencies: a=1, b=1, c=1" << endl;
    cout << endl;

    cout << "Windows and their frequencies:" << endl;
    cout << "  \"cba\" -> a=1,b=1,c=1 -> MATCH (anagram of \"abc\")" << endl;
    cout << "  \"bae\" -> a=1,b=1,e=1 -> no match" << endl;
    cout << "  \"aeb\" -> a=1,b=1,e=1 -> no match" << endl;
    cout << "  \"eba\" -> a=1,b=1,e=1 -> no match" << endl;
    cout << "  \"bab\" -> a=0,b=2,a=0 -> no match" << endl;
    cout << "  \"aba\" -> a=2,b=1,a=0 -> no match" << endl;
    cout << "  \"bac\" -> a=1,b=1,c=1 -> MATCH (anagram of \"abc\")" << endl;
    cout << "  \"acd\" -> a=1,c=1,d=1 -> no match" << endl;
    cout << endl;

    int ans1 = countAnagrams(text1, pat1);
    cout << "Total anagrams found: " << ans1 << endl;
    cout << endl;

    // Second example
    const char text2[] = "aabaabaa";
    const char pat2[] = "aab";
    cout << "Text:    " << text2 << endl;
    cout << "Pattern: " << pat2 << endl;
    int ans2 = countAnagrams(text2, pat2);
    cout << "Total anagrams found: " << ans2 << endl;
    cout << endl;

    cout << "Approach:" << endl;
    cout << "  1. Build frequency array for pattern (size 26 for a-z)" << endl;
    cout << "  2. Build frequency array for first window of size k" << endl;
    cout << "  3. Compare: if equal, found an anagram" << endl;
    cout << "  4. Slide: add new char freq, remove old char freq" << endl;
    cout << "  5. Compare again at each position" << endl;
    cout << "  6. Time: O(n * 26), Space: O(26) = O(1)" << endl;

    return 0;
}
