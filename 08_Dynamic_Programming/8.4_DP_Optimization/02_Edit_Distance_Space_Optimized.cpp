#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

// =============================================
// EDIT DISTANCE WITH SPACE OPTIMIZATION
// =============================================
// Standard Edit Distance uses O(m*n) space for the full DP table.
// But to compute row i, we only need values from row i-1.
// So we can use a "rolling array" with just 2 rows.
//
// ROLLING ARRAY CONCEPT:
// - Instead of dp[m+1][n+1], use dp[2][n+1]
// - Use dp[i%2] for current row and dp[(i-1)%2] for previous row
// - This gives O(min(m,n)) space by choosing the shorter string as columns
//
// =============================================


// =============================================
// STANDARD EDIT DISTANCE: O(m*n) space
// =============================================
int edit_distance_standard(string& s1, string& s2, int m, int n) {
    int dp[101][101];

    // Base cases: converting to/from empty string
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;  // Delete all characters from s1
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;  // Insert all characters into s1
    }

    // Fill the table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  // No operation needed
            } else {
                // Take minimum of three operations
                int insertOp = dp[i][j - 1];      // Insert
                int deleteOp = dp[i - 1][j];      // Delete
                int replaceOp = dp[i - 1][j - 1]; // Replace

                dp[i][j] = 1 + min(insertOp, min(deleteOp, replaceOp));
            }
        }
    }

    return dp[m][n];
}


// =============================================
// SPACE OPTIMIZED EDIT DISTANCE: O(min(m,n)) space
// =============================================
// Uses rolling arrays: only keep previous row and current row.
// We use two 1D arrays and swap them after each row.

int edit_distance_optimized(string& s1, string& s2, int m, int n) {
    // To minimize space, make sure the shorter string determines the array size
    // If s2 is longer than s1, swap them so dp array is smaller
    if (n < m) {
        string temp = s1;
        s1 = s2;
        s2 = temp;
        int tempInt = m;
        m = n;
        n = tempInt;
    }

    // Now n >= m, so we use array of size (m + 1)
    int prev[101];
    int curr[101];

    // Base case: converting empty string to s2[0..j-1] needs j insertions
    for (int j = 0; j <= m; j++) {
        prev[j] = j;
    }

    for (int i = 1; i <= n; i++) {
        curr[0] = i;  // Converting s1[0..i-1] to empty string needs i deletions

        for (int j = 1; j <= m; j++) {
            if (s1[j - 1] == s2[i - 1]) {
                // Characters match, no operation needed
                curr[j] = prev[j - 1];
            } else {
                // Characters don't match, take minimum of three operations
                int insertOp = curr[j - 1];      // Insert into s1 (use current row, left cell)
                int deleteOp = prev[j];          // Delete from s1 (use prev row, same column)
                int replaceOp = prev[j - 1];     // Replace (use prev row, left cell)

                curr[j] = 1 + min(insertOp, min(deleteOp, replaceOp));
            }
        }

        // Current row becomes previous row for next iteration
        for (int j = 0; j <= m; j++) {
            prev[j] = curr[j];
        }
    }

    return prev[m];
}


// =============================================
// EDIT DISTANCE USING MODULO (2-row rolling array)
// =============================================
// Another way: use dp[2][n+1] and access with i%2
// This is the "classic" rolling array pattern

int edit_distance_modulo(string& s1, string& s2, int m, int n) {
    int dp[2][101];

    // Initialize base case (row 0)
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        int curr = i % 2;
        int prev = (i - 1) % 2;

        dp[curr][0] = i;  // Base case: delete i characters

        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[curr][j] = dp[prev][j - 1];
            } else {
                int insertOp = dp[curr][j - 1];
                int deleteOp = dp[prev][j];
                int replaceOp = dp[prev][j - 1];

                dp[curr][j] = 1 + min(insertOp, min(deleteOp, replaceOp));
            }
        }
    }

    return dp[m % 2][n];
}


void print_operations(string& s1, string& s2, int m, int n) {
    cout << "Converting \"" << s1 << "\" to \"" << s2 << "\"" << endl;
    cout << "  Standard O(m*n) space:   " << edit_distance_standard(s1, s2, m, n) << endl;
    cout << "  Optimized O(min) space:  " << edit_distance_optimized(s1, s2, m, n) << endl;
    cout << "  Modulo O(n) space:       " << edit_distance_modulo(s1, s2, m, n) << endl;
    cout << endl;
}

void explain_rolling_array() {
    cout << "=== How Rolling Arrays Work ===" << endl;
    cout << endl;
    cout << "In Edit Distance, dp[i][j] only depends on:" << endl;
    cout << "  - dp[i-1][j-1]  (diagonal - from previous row)" << endl;
    cout << "  - dp[i-1][j]    (above - from previous row)" << endl;
    cout << "  - dp[i][j-1]    (left - from current row)" << endl;
    cout << endl;
    cout << "So we only need TWO rows at any time:" << endl;
    cout << "  - Previous row (i-1)" << endl;
    cout << "  - Current row (i)" << endl;
    cout << endl;
    cout << "Two approaches:" << endl;
    cout << "  1. Two arrays (prev[], curr[]): copy curr to prev after each row" << endl;
    cout << "  2. Modulo 2 array dp[2][n]: use dp[i%2] and dp[(i-1)%2]" << endl;
    cout << endl;
    cout << "Space goes from O(m*n) to O(min(m,n))" << endl;
    cout << "  - Choose the SHORTER string for the array size" << endl;
    cout << "  - If needed, swap strings so the shorter one determines array length" << endl;
    cout << endl;
}


int main() {
    cout << "========================================" << endl;
    cout << "  EDIT DISTANCE: SPACE OPTIMIZATION" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // Explain the concept
    explain_rolling_array();

    // Test case 1: Simple example
    {
        string s1 = "sunday";
        string s2 = "saturday";
        int m = s1.length();
        int n = s2.length();
        print_operations(s1, s2, m, n);
    }

    // Test case 2: Another example
    {
        string s1 = "kitten";
        string s2 = "sitting";
        int m = s1.length();
        int n = s2.length();
        print_operations(s1, s2, m, n);
    }

    // Test case 3: Identical strings
    {
        string s1 = "hello";
        string s2 = "hello";
        int m = s1.length();
        int n = s2.length();
        print_operations(s1, s2, m, n);
    }

    // Test case 4: Completely different
    {
        string s1 = "abc";
        string s2 = "xyz";
        int m = s1.length();
        int n = s2.length();
        print_operations(s1, s2, m, n);
    }

    // Test case 5: One string is empty
    {
        string s1 = "";
        string s2 = "abcd";
        int m = s1.length();
        int n = s2.length();
        print_operations(s1, s2, m, n);
    }

    // Space complexity comparison
    cout << "========================================" << endl;
    cout << "  SPACE COMPLEXITY COMPARISON" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Approach              | Space     | Notes" << endl;
    cout << "----------------------|-----------|----------------------------------" << endl;
    cout << "Full 2D table         | O(m*n)    | Stores entire DP matrix" << endl;
    cout << "Two arrays (prev,cur) | O(min(m,n))| Copy curr to prev each row" << endl;
    cout << "Modulo 2 rows         | O(n)      | dp[2][n], access with i%2" << endl;
    cout << endl;
    cout << "All approaches:       | Time: O(m*n) - time complexity is unchanged!" << endl;
    cout << endl;
    cout << "Key Insight:" << endl;
    cout << "- Time complexity cannot be improved (still O(m*n))" << endl;
    cout << "- Space complexity CAN be reduced (O(m*n) -> O(min(m,n)))" << endl;
    cout << "- Use space optimization when m and n are large" << endl;
    cout << "- Trade-off: Cannot reconstruct the actual edit operations" << endl;
    cout << "  (because we discard previous rows)" << endl;
    cout << endl;

    return 0;
}
