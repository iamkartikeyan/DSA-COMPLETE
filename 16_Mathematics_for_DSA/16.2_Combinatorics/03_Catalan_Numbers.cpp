// 16.2.03 - Catalan Numbers
// C_n = (2n)! / ((n+1)! * n!) = C(2n, n) / (n+1)
// Recurrence: C_0 = 1, C_n = sum(C_i * C_{n-1-i}) for i = 0..n-1
// Applications: valid parentheses, BSTs, triangulations, grid paths.

#include <iostream>

using namespace std;

// ---- nCr helper ----
long long nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    if (r > n - r) r = n - r;
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

// ---- Catalan Numbers using DP (recurrence) - O(n^2) ----
// C_0 = 1, C_n = sum(C_i * C_{n-1-i}) for i = 0..n-1
void catalanDP(int n, long long C[]) {
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i] = 0;
        for (int j = 0; j < i; j++) {
            C[i] += C[j] * C[i - 1 - j];
        }
    }
}

// ---- Catalan Number using direct formula - O(n) ----
// C_n = C(2n, n) / (n+1)
long long catalanDirect(int n) {
    return nCr(2 * n, n) / (n + 1);
}

// ---- Generate Valid Parentheses ----
// Uses backtracking to generate all valid parenthesis strings with n pairs.
void generateParentheses(int open, int close, char current[], int pos, char results[][20], int& count) {
    if (open == 0 && close == 0) {
        current[pos] = '\0';
        // Copy to results
        int j = 0;
        while (j <= pos) {
            results[count][j] = current[j];
            j++;
        }
        count++;
        return;
    }
    if (open > 0) {
        current[pos] = '(';
        generateParentheses(open - 1, close, current, pos + 1, results, count);
    }
    if (close > open) {
        current[pos] = ')';
        generateParentheses(open, close - 1, current, pos + 1, results, count);
    }
}

// ---- BST count with n nodes = Catalan(n) ----
int countBSTs(int n) {
    return (int)catalanDirect(n);
}

int main() {
    cout << "=== Catalan Numbers ===" << endl;

    // DP approach
    long long C[15];
    int n = 10;
    catalanDP(n, C);
    cout << "C_0 to C_10 (DP): ";
    for (int i = 0; i <= n; i++) {
        cout << C[i] << " ";
    }
    cout << endl;
    // Expected: 1 1 2 5 14 42 132 429 1430 4862 16796

    // Direct formula
    cout << endl << "Direct formula:" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << "  C_" << i << " = " << catalanDirect(i) << endl;
    }

    // Applications
    cout << endl << "=== Applications of C_3 = 5 ===" << endl;

    // Valid parentheses
    cout << "1. Valid parentheses with 3 pairs:" << endl;
    char results[10][20];
    char current[20];
    int count = 0;
    generateParentheses(3, 3, current, 0, results, count);
    cout << "   Total: " << count << endl;
    for (int i = 0; i < count; i++) {
        cout << "   " << (i + 1) << ". " << results[i] << endl;
    }

    // BSTs
    cout << endl << "2. Number of BSTs with n nodes:" << endl;
    for (int i = 1; i <= 6; i++) {
        cout << "   n=" << i << ": " << countBSTs(i) << " BSTs" << endl;
    }

    // Triangulations
    cout << endl << "3. Triangulations of convex (n+2)-gon:" << endl;
    int sides[] = {3, 4, 5, 6, 7};  // triangle, quadrilateral, pentagon, hexagon, heptagon
    int numSides = 5;
    for (int i = 0; i < numSides; i++) {
        int s = sides[i];
        cout << "   " << s << "-gon: " << catalanDirect(s - 2) << " triangulations" << endl;
    }

    cout << endl << "Time: O(n^2) DP, O(n) direct formula" << endl;
    cout << "Space: O(n) for Catalan array" << endl;

    return 0;
}
