/*
 * File: 01_Rolling_Hash_Basics.cpp
 * Topic: What is Rolling Hash, Rabin-Karp concept
 * Description: Hash of sliding window computed in O(1)
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Rolling Hash Basics ===" << endl;
    cout << endl;

    cout << "--- What is Rolling Hash? ---" << endl;
    cout << "A rolling hash lets you compute hash of a window" << endl;
    cout << "in O(1) time as the window slides across the text." << endl;
    cout << endl;

    cout << "--- Formula ---" << endl;
    cout << "Remove leading char:  hash = hash - leading_char * power" << endl;
    cout << "Shift left:           hash = hash * alphabet_size" << endl;
    cout << "Add trailing char:    hash = hash + trailing_char" << endl;
    cout << endl;

    /*
     * Example with small numbers:
     * Text: "ABCDE", Pattern: "BCD"
     * Alphabet size = 26, Modulus = 101 (prime)
     *
     * Hash("ABC") = (A*26^2 + B*26 + C) % 101
     * Hash("BCD") = ((Hash("ABC") - A*26^2) * 26 + D) % 101
     */

    string text = "ABAAABCDABCABCABAB";
    string pattern = "ABC";
    int n = text.length();
    int m = pattern.length();

    cout << "Text:    " << text << endl;
    cout << "Pattern: " << pattern << endl;
    cout << endl;

    int d = 256;  // alphabet size
    int q = 101;  // prime modulus

    // Compute h = d^(m-1) % q
    int h = 1;
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Compute initial hash values
    int pHash = 0;
    int tHash = 0;
    for (int i = 0; i < m; i++) {
        pHash = (pHash * d + pattern[i]) % q;
        tHash = (tHash * d + text[i]) % q;
    }

    cout << "Pattern hash: " << pHash << endl;
    cout << "First window hash: " << tHash << endl;
    cout << endl;

    // Slide window
    cout << "Matches found at indices: ";
    for (int i = 0; i <= n - m; i++) {
        // Check if hashes match
        if (pHash == tHash) {
            // Verify character by character
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << i << " ";
            }
        }

        // Compute next window hash
        if (i < n - m) {
            tHash = (d * (tHash - text[i] * h) + text[i + m]) % q;
            if (tHash < 0) {
                tHash = tHash + q; // handle negative
            }
        }
    }
    cout << endl;

    cout << endl;
    cout << "--- Rabin-Karp ---" << endl;
    cout << "1. Compute hash of pattern" << endl;
    cout << "2. Compute hash of first window" << endl;
    cout << "3. If hashes match, verify char by char" << endl;
    cout << "4. Slide window: compute next hash in O(1)" << endl;
    cout << "5. Repeat" << endl;
    cout << endl;
    cout << "Time: O(n+m) average, O(n*m) worst (many collisions)" << endl;
    cout << "Use: Multiple pattern search, plagiarism detection" << endl;

    return 0;
}
