// Edit Distance (Levenshtein Distance)
// Given two strings s1 and s2, find minimum operations to convert s1 to s2
// Allowed operations (each costs 1):
//   1. Insert a character
//   2. Delete a character
//   3. Replace a character
// dp[i][j] = minimum edits to convert s1[0..i-1] to s2[0..j-1]
// If characters match: dp[i][j] = dp[i-1][j-1] (no operation needed)
// If characters don't match: dp[i][j] = 1 + min(insert, delete, replace)
//   - Insert: dp[i][j-1] (insert s2[j-1] into s1)
//   - Delete: dp[i-1][j] (delete s1[i-1])
//   - Replace: dp[i-1][j-1] (replace s1[i-1] with s2[j-1])
// Base case: convert to empty string = delete all, convert from empty = insert all

#include <iostream>
#include <string>

using namespace std;

// Helper function to find minimum of three numbers
int minOfThree(int a, int b, int c) {
    int minVal = a;
    if (b < minVal) {
        minVal = b;
    }
    if (c < minVal) {
        minVal = c;
    }
    return minVal;
}

int editDistance(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    int dp[1001][1001];

    // Base case: convert s1[0..i-1] to empty string = delete all i characters
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }

    // Base case: convert empty string to s2[0..j-1] = insert all j characters
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                // Characters match: no operation needed
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // Characters don't match: try all three operations
                int insertOp = dp[i][j - 1];     // Insert s2[j-1]
                int deleteOp = dp[i - 1][j];     // Delete s1[i-1]
                int replaceOp = dp[i - 1][j - 1]; // Replace s1[i-1] with s2[j-1]

                dp[i][j] = 1 + minOfThree(insertOp, deleteOp, replaceOp);
            }
        }
    }

    return dp[m][n];
}

int main() {
    cout << "=== Edit Distance (Levenshtein) ===" << endl;

    // Example 1
    string s1 = "horse";
    string s2 = "ros";
    cout << "\nConvert '" << s1 << "' to '" << s2 << "'" << endl;
    cout << "Edit distance: " << editDistance(s1, s2) << endl;
    cout << "Operations:" << endl;
    cout << "  1. horse -> rorse (replace 'h' with 'r')" << endl;
    cout << "  2. rorse -> rose (delete 'r')" << endl;
    cout << "  3. rose -> ros (delete 'e')" << endl;
    cout << "  Total: 3 operations" << endl;

    // Example 2
    string s3 = "intention";
    string s4 = "execution";
    cout << "\nConvert '" << s3 << "' to '" << s4 << "'" << endl;
    cout << "Edit distance: " << editDistance(s3, s4) << endl;
    cout << "Explanation: 5 operations needed" << endl;

    // Example 3: Identical strings
    string s5 = "hello";
    string s6 = "hello";
    cout << "\nConvert '" << s5 << "' to '" << s6 << "'" << endl;
    cout << "Edit distance: " << editDistance(s5, s6) << endl;
    cout << "Explanation: Strings are same, 0 operations needed" << endl;

    // Example 4: Empty string
    string s7 = "";
    string s8 = "abc";
    cout << "\nConvert '' to '" << s8 << "'" << endl;
    cout << "Edit distance: " << editDistance(s7, s8) << endl;
    cout << "Explanation: Insert all 3 characters" << endl;

    // Example 5: Completely different
    string s9 = "abc";
    string s10 = "def";
    cout << "\nConvert '" << s9 << "' to '" << s10 << "'" << endl;
    cout << "Edit distance: " << editDistance(s9, s10) << endl;
    cout << "Explanation: Replace all 3 characters" << endl;

    // Example 6: One character difference
    string s11 = "cat";
    string s12 = "cut";
    cout << "\nConvert '" << s11 << "' to '" << s12 << "'" << endl;
    cout << "Edit distance: " << editDistance(s11, s12) << endl;
    cout << "Explanation: Replace 'a' with 'u'" << endl;

    return 0;
}
