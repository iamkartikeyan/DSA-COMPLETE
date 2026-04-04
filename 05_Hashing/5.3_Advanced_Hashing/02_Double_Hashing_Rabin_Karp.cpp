/*
 * File: 02_Double_Hashing_Rabin_Karp.cpp
 * Topic: Using two hash functions to eliminate false positives
 * Description: Both hashes must match -> virtually no collisions
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Double Hashing Rabin-Karp ===" << endl;
    cout << endl;

    string text = "ABAAABCDABCABCABAB";
    string pattern = "ABC";
    int n = text.length();
    int m = pattern.length();

    cout << "Text:    " << text << endl;
    cout << "Pattern: " << pattern << endl;
    cout << endl;

    // Two different hash configurations
    int d1 = 256, q1 = 1000000007;
    int d2 = 256, q2 = 1000000009;

    // Compute h1 = d1^(m-1) % q1 and h2 = d2^(m-1) % q2
    int h1 = 1, h2 = 1;
    for (int i = 0; i < m - 1; i++) {
        h1 = (1LL * h1 * d1) % q1;
        h2 = (1LL * h2 * d2) % q2;
    }

    // Compute initial hashes
    int p1 = 0, t1 = 0, p2 = 0, t2 = 0;
    for (int i = 0; i < m; i++) {
        p1 = (1LL * p1 * d1 + pattern[i]) % q1;
        t1 = (1LL * t1 * d1 + text[i]) % q1;
        p2 = (1LL * p2 * d2 + pattern[i]) % q2;
        t2 = (1LL * t2 * d2 + text[i]) % q2;
    }

    cout << "Pattern hashes:  h1=" << p1 << ", h2=" << p2 << endl;
    cout << "First window:    h1=" << t1 << ", h2=" << t2 << endl;
    cout << endl;

    // Slide window
    cout << "Match found? ";
    bool found = false;
    for (int i = 0; i <= n - m; i++) {
        // BOTH hashes must match
        if (p1 == t1 && p2 == t2) {
            // Verify char by char (almost never needed with double hash)
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "YES at index " << i << endl;
                found = true;
            }
        }

        // Compute next window hashes
        if (i < n - m) {
            t1 = (1LL * d1 * (t1 - 1LL * text[i] * h1 % q1) + text[i + m]) % q1;
            t2 = (1LL * d2 * (t2 - 1LL * text[i] * h2 % q2) + text[i + m]) % q2;
            if (t1 < 0) t1 = t1 + q1;
            if (t2 < 0) t2 = t2 + q2;
        }
    }
    if (found == false) {
        cout << "NO match found" << endl;
    }

    cout << endl;
    cout << "--- Why Double Hashing? ---" << endl;
    cout << "Single hash: Can have false positives (collisions)" << endl;
    cout << "Double hash: Two different mods -> collision probability ~ 1/(q1*q2)" << endl;
    cout << "With q1=10^9+7 and q2=10^9+9, collision is nearly impossible" << endl;
    cout << endl;
    cout << "Used in: Competitive programming, large text search" << endl;

    return 0;
}
