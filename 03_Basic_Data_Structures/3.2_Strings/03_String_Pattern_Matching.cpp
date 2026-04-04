/*
 * File: 03_String_Pattern_Matching.cpp
 * Topic: Naive pattern matching in strings
 * Description: Find all occurrences of pattern in text
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Pattern Matching (Naive) ===" << endl;
    cout << endl;

    string text = "AABAACAADAABAABA";
    string pattern = "AABA";
    int n = text.length();
    int m = pattern.length();

    cout << "Text:    " << text << endl;
    cout << "Pattern: " << pattern << endl;
    cout << endl;

    /*
     * Naive approach:
     * Try matching pattern at each position in text.
     * For each position i, compare pattern[0..m-1] with text[i..i+m-1].
     */

    cout << "Matches found:" << endl;
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break; // mismatch at position j
            }
        }
        if (j == m) {
            cout << "  Found at index " << i << endl;
        }
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  Position 0: AABA matches! -> Found at 0" << endl;
    cout << "  Position 1: ABAA != AABA -> no match" << endl;
    cout << "  Position 2: BAAC != AABA -> no match" << endl;
    cout << "  ..." << endl;
    cout << "  Position 9: AABA matches! -> Found at 9" << endl;
    cout << "  Position 10: AABA matches! -> Found at 10" << endl;
    cout << endl;
    cout << "Time: O(n * m) worst case" << endl;
    cout << "Space: O(1)" << endl;
    cout << endl;
    cout << "Better algorithms:" << endl;
    cout << "  KMP: O(n + m) - uses prefix function" << endl;
    cout << "  Rabin-Karp: O(n + m) avg - uses rolling hash" << endl;
    cout << "  (Covered in Advanced Hashing section)" << endl;

    return 0;
}
