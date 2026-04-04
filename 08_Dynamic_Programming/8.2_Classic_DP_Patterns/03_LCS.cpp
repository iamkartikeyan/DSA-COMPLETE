// Longest Common Subsequence (LCS)
// Given two strings s1 and s2, find the length of their longest common subsequence
// A subsequence is formed by deleting zero or more characters (order must be preserved)
// dp[i][j] = LCS length of s1[0..i-1] and s2[0..j-1]
// If characters match: dp[i][j] = 1 + dp[i-1][j-1]
// If characters don't match: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
// Base case: empty string has LCS = 0

#include <iostream>
#include <string>

using namespace std;

int longestCommonSubsequence(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    int dp[1001][1001];

    // Base case: empty string has LCS = 0
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                // Characters match: extend the LCS
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                // Characters don't match: take max of excluding one char
                int skipS1 = dp[i - 1][j];
                int skipS2 = dp[i][j - 1];
                if (skipS1 > skipS2) {
                    dp[i][j] = skipS1;
                } else {
                    dp[i][j] = skipS2;
                }
            }
        }
    }

    return dp[m][n];
}

// Helper function to find and print the actual LCS string
string printLCS(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    int dp[1001][1001];

    // Build the DP table first
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                int skipS1 = dp[i - 1][j];
                int skipS2 = dp[i][j - 1];
                if (skipS1 > skipS2) {
                    dp[i][j] = skipS1;
                } else {
                    dp[i][j] = skipS2;
                }
            }
        }
    }

    // Backtrack to find the actual LCS string
    string result = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            // This character is part of LCS
            result = s1[i - 1] + result;
            i--;
            j--;
        } else {
            // Move in the direction of larger value
            if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
    }

    return result;
}

int main() {
    cout << "=== Longest Common Subsequence ===" << endl;

    // Example 1
    string s1 = "ABCBDAB";
    string s2 = "BDCAB";
    cout << "\nString 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    cout << "LCS length: " << longestCommonSubsequence(s1, s2) << endl;
    cout << "LCS string: " << printLCS(s1, s2) << endl;
    cout << "Explanation: 'BCAB' or 'BDAB' are common subsequences of length 4" << endl;

    // Example 2
    string s3 = "AGGTAB";
    string s4 = "GXTXAYB";
    cout << "\nString 1: " << s3 << endl;
    cout << "String 2: " << s4 << endl;
    cout << "LCS length: " << longestCommonSubsequence(s3, s4) << endl;
    cout << "LCS string: " << printLCS(s3, s4) << endl;
    cout << "Explanation: 'GTAB' is the LCS of length 4" << endl;

    // Example 3: No common subsequence
    string s5 = "ABC";
    string s6 = "DEF";
    cout << "\nString 1: " << s5 << endl;
    cout << "String 2: " << s6 << endl;
    cout << "LCS length: " << longestCommonSubsequence(s5, s6) << endl;
    cout << "LCS string: '" << printLCS(s5, s6) << "'" << endl;
    cout << "Explanation: No common characters, LCS = 0" << endl;

    // Example 4: One string is subsequence of another
    string s7 = "ACE";
    string s8 = "ABCDE";
    cout << "\nString 1: " << s7 << endl;
    cout << "String 2: " << s8 << endl;
    cout << "LCS length: " << longestCommonSubsequence(s7, s8) << endl;
    cout << "LCS string: " << printLCS(s7, s8) << endl;
    cout << "Explanation: 'ACE' is fully contained in 'ABCDE'" << endl;

    // Example 5: Identical strings
    string s9 = "HELLO";
    string s10 = "HELLO";
    cout << "\nString 1: " << s9 << endl;
    cout << "String 2: " << s10 << endl;
    cout << "LCS length: " << longestCommonSubsequence(s9, s10) << endl;
    cout << "LCS string: " << printLCS(s9, s10) << endl;
    cout << "Explanation: Identical strings, LCS = full string length" << endl;

    return 0;
}
