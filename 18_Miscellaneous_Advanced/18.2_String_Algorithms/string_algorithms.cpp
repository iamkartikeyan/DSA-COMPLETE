#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ===== KMP ALGORITHM (Knuth-Morris-Pratt) =====
// O(n + m) pattern matching using LPS (Longest Prefix Suffix) array

// Build LPS array
vector<int> computeLPS(string pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;  // Length of previous longest prefix suffix
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0) len = lps[len - 1];  // Fall back
            else lps[i++] = 0;
        }
    }
    return lps;
}

vector<int> kmpSearch(string text, string pattern) {
    vector<int> result;
    vector<int> lps = computeLPS(pattern);
    int n = text.length(), m = pattern.length();
    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) { i++; j++; }
        if (j == m) { result.push_back(i - j); j = lps[j - 1]; }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return result;
}

// ===== Z-ALGORITHM =====
// Z[i] = length of longest common prefix between s and s[i:]
// Used for: pattern matching, string periodicity
vector<int> zFunction(string s) {
    int n = s.length();
    vector<int> z(n, 0);
    int l = 0, r = 0;  // [l, r] is the Z-box
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    z[0] = n;
    return z;
}

vector<int> zSearch(string text, string pattern) {
    vector<int> result;
    string combined = pattern + "$" + text;
    vector<int> z = zFunction(combined);
    int m = pattern.length();
    for (int i = m + 1; i < z.size(); i++) {
        if (z[i] == m) result.push_back(i - m - 1);
    }
    return result;
}

// ===== MANACHER'S ALGORITHM =====
// Finds longest palindromic substring in O(n)
string manacher(string s) {
    if (s.empty()) return "";
    // Transform: "aba" -> "#a#b#a#"
    string t = "#";
    for (char c : s) { t += c; t += '#'; }

    int n = t.length(), center = 0, right = 0;
    vector<int> p(n, 0);  // Radius array

    for (int i = 0; i < n; i++) {
        int mirror = 2 * center - i;
        if (i < right) p[i] = min(right - i, p[mirror]);
        // Expand
        int a = i + p[i] + 1, b = i - p[i] - 1;
        while (a < n && b >= 0 && t[a] == t[b]) { p[i]++; a++; b--; }
        // Update center
        if (i + p[i] > right) { center = i; right = i + p[i]; }
    }

    // Find max
    int maxLen = 0, centerIdx = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] > maxLen) { maxLen = p[i]; centerIdx = i; }
    }

    int start = (centerIdx - maxLen) / 2;
    return s.substr(start, maxLen);
}

// ===== AHO-CORASICK (Concept) =====
// Multi-pattern matching using automaton (Trie + failure links)
// Build Trie of all patterns, add failure links (like KMP's LPS)
// Process text in O(n + m + z) where z = number of matches

struct AhoNode {
    AhoNode* children[26] = {};
    AhoNode* failure = nullptr;
    bool isEnd = false;
    int patternId = -1;
};

void ahoInsert(AhoNode* root, string pattern, int id) {
    AhoNode* curr = root;
    for (char c : pattern) {
        if (!curr->children[c - 'a']) curr->children[c - 'a'] = new AhoNode();
        curr = curr->children[c - 'a'];
    }
    curr->isEnd = true;
    curr->patternId = id;
}

// Build failure links using BFS (similar to KMP LPS construction)
// Then process text through automaton, collecting matches

int main() {
    // KMP
    cout << "=== KMP Algorithm ===\n";
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    auto matches = kmpSearch(text, pattern);
    cout << "Pattern '" << pattern << "' found at: ";
    for (int idx : matches) cout << idx << " ";
    cout << "\n";

    // Z-Algorithm
    cout << "\n=== Z-Algorithm ===\n";
    string s = "aabaacaadaabaaba";
    auto z = zFunction(s);
    cout << "Z-array for '" << s << "': ";
    for (int v : z) cout << v << " ";
    cout << "\n";

    auto zMatches = zSearch(text, pattern);
    cout << "Z-search '" << pattern << "': ";
    for (int idx : zMatches) cout << idx << " ";
    cout << "\n";

    // Manacher's
    cout << "\n=== Manacher's Algorithm ===\n";
    string palin = "abacdfgdcaba";
    cout << "Longest palindrome in '" << palin << "': " << manacher(palin) << "\n";

    vector<string> tests = {"forgeeksskeegfor", "aba", "abacdfgdcaba", "racecar"};
    for (auto &t : tests)
        cout << "Longest palindrome in '" << t << "': " << manacher(t) << "\n";

    // Aho-Corasick Concept
    cout << "\n=== Aho-Corasick Concept ===\n";
    cout << "Multi-pattern matching using Trie + failure links\n";
    cout << "Build Trie of patterns -> Add failure links (BFS) -> Process text\n";
    cout << "O(n + m + z) where z = total matches\n";

    return 0;
}
