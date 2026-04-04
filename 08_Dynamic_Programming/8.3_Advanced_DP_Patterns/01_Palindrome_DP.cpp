#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// ============================================================
// 1. Longest Palindromic Subsequence (LPS)
// dp[i][j] = LPS length in s[i..j]
// Match: 2 + dp[i+1][j-1]
// Mismatch: max(dp[i+1][j], dp[i][j-1])
// ============================================================

int longestPalindromicSubsequence(const char* s) {
    int n = strlen(s);
    int dp[1000][1000];

    // Initialize dp table
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    // Every single character is a palindrome of length 1
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    // Fill for lengths 2 to n
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = 2 + dp[i + 1][j - 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1];
}

// ============================================================
// 2. Count Palindromic Substrings
// Expand around center approach
// ============================================================

int countPalindromicSubstrings(const char* s) {
    int n = strlen(s);
    int count = 0;

    for (int center = 0; center < n; center++) {
        // Odd length palindromes (single center)
        int left = center;
        int right = center;
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }

        // Even length palindromes (pair center)
        left = center;
        right = center + 1;
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    }

    return count;
}

// ============================================================
// 3. Minimum Cuts for Palindrome Partitioning
// dp[i] = min cuts for s[0..i]
// isPal[i][j] = true if s[i..j] is palindrome
// ============================================================

int minCutsForPalindromePartition(const char* s) {
    int n = strlen(s);
    if (n == 0) return 0;

    int dp[1000];
    bool isPal[1000][1000];

    // Initialize
    for (int i = 0; i < n; i++) {
        dp[i] = i;  // worst case: cut after each character
        for (int j = 0; j < n; j++) {
            isPal[i][j] = false;
        }
    }

    // Fill isPal table and dp together
    for (int j = 0; j < n; j++) {
        for (int i = 0; i <= j; i++) {
            if (s[i] == s[j] && (j - i <= 1 || isPal[i + 1][j - 1])) {
                isPal[i][j] = true;
                if (i == 0) {
                    dp[j] = 0;  // s[0..j] is already a palindrome
                } else {
                    if (dp[i - 1] + 1 < dp[j]) {
                        dp[j] = dp[i - 1] + 1;
                    }
                }
            }
        }
    }

    return dp[n - 1];
}

// ============================================================
// Main - Test all functions
// ============================================================

int main() {
    cout << "=== Palindrome DP Patterns ===" << endl;
    cout << endl;

    // Test 1: Longest Palindromic Subsequence
    cout << "--- 1. Longest Palindromic Subsequence ---" << endl;
    char s1[] = "bbbab";
    cout << "String: " << s1 << endl;
    cout << "LPS length: " << longestPalindromicSubsequence(s1) << endl;
    cout << "Expected: 4 (bbbb)" << endl;
    cout << endl;

    char s2[] = "cbbd";
    cout << "String: " << s2 << endl;
    cout << "LPS length: " << longestPalindromicSubsequence(s2) << endl;
    cout << "Expected: 2 (bb)" << endl;
    cout << endl;

    // Test 2: Count Palindromic Substrings
    cout << "--- 2. Count Palindromic Substrings ---" << endl;
    char s3[] = "abc";
    cout << "String: " << s3 << endl;
    cout << "Count: " << countPalindromicSubstrings(s3) << endl;
    cout << "Expected: 3 (a, b, c)" << endl;
    cout << endl;

    char s4[] = "aaa";
    cout << "String: " << s4 << endl;
    cout << "Count: " << countPalindromicSubstrings(s4) << endl;
    cout << "Expected: 6 (a, a, a, aa, aa, aaa)" << endl;
    cout << endl;

    // Test 3: Min Cuts for Palindrome Partitioning
    cout << "--- 3. Min Cuts for Palindrome Partitioning ---" << endl;
    char s5[] = "aab";
    cout << "String: " << s5 << endl;
    cout << "Min cuts: " << minCutsForPalindromePartition(s5) << endl;
    cout << "Expected: 1 (aa|b)" << endl;
    cout << endl;

    char s6[] = "ababbbabbababa";
    cout << "String: " << s6 << endl;
    cout << "Min cuts: " << minCutsForPalindromePartition(s6) << endl;
    cout << "Expected: 3" << endl;
    cout << endl;

    return 0;
}
