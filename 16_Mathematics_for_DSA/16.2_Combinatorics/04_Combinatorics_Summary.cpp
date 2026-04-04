// 16.2.04 - Combinatorics Summary
// Complete summary: factorial, permutations, combinations, Catalan numbers, derangements.

#include <iostream>
#include <iomanip>

using namespace std;

const int MOD = 1000000007;

// ---- Factorial ----
long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}

long long factorialMod(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) result = (result * i) % MOD;
    return result;
}

// ---- Permutations ----
long long nPr(int n, int r) {
    if (r > n) return 0;
    long long result = 1;
    for (int i = 0; i < r; i++) result *= (n - i);
    return result;
}

// ---- Combinations ----
long long nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    if (r > n - r) r = n - r;
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

// ---- Catalan Numbers (DP) ----
void catalanDP(int n, long long C[]) {
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i] = 0;
        for (int j = 0; j < i; j++) {
            C[i] += C[j] * C[i - 1 - j];
        }
    }
}

// ---- Derangements ----
// !n = (n-1) * (!(n-1) + !(n-2))
// Base: !0 = 1, !1 = 0
long long derangements(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    long long prev2 = 1, prev1 = 0, curr;
    for (int i = 2; i <= n; i++) {
        curr = (i - 1) * (prev1 + prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// ---- Stars and Bars ----
// Distribute n identical items into k distinct bins = C(n+k-1, k-1)
int starsAndBars(int n, int k) {
    return (int)nCr(n + k - 1, k - 1);
}

// ---- Pascal's Triangle ----
void buildPascal(int n, int C[][21]) {
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

int main() {
    cout << "========================================" << endl;
    cout << "  COMBINATORICS - COMPLETE SUMMARY" << endl;
    cout << "========================================" << endl;

    // 1. Factorial
    cout << endl << "1. FACTORIAL (O(n))" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << "   " << i << "! = " << factorial(i) << endl;
    }

    // 2. Permutations
    cout << endl << "2. PERMUTATIONS nPr (O(r))" << endl;
    cout << "   P(5, 2) = " << nPr(5, 2) << " (arranging 2 of 5)" << endl;
    cout << "   P(5, 5) = " << nPr(5, 5) << " (arranging all 5)" << endl;

    // 3. Combinations
    cout << endl << "3. COMBINATIONS nCr (O(r))" << endl;
    cout << "   C(5, 2) = " << nCr(5, 2) << " (choosing 2 of 5)" << endl;
    cout << "   C(52, 5) = " << nCr(52, 5) << " (poker hands)" << endl;

    // Pascal's Triangle
    cout << endl << "   Pascal's Triangle (n=5):" << endl;
    int C[21][21] = {0};
    buildPascal(5, C);
    for (int i = 0; i <= 5; i++) {
        cout << "   ";
        for (int j = 0; j <= i; j++) {
            cout << setw(4) << C[i][j];
        }
        cout << endl;
    }

    // 4. Catalan Numbers
    cout << endl << "4. CATALAN NUMBERS (O(n^2) DP, O(n) direct)" << endl;
    long long cat[15];
    catalanDP(10, cat);
    cout << "   C_0 to C_10: ";
    for (int i = 0; i <= 10; i++) cout << cat[i] << " ";
    cout << endl;
    cout << "   Applications: valid parentheses, BSTs, triangulations" << endl;

    // 5. Derangements
    cout << endl << "5. DERANGEMENTS (O(n))" << endl;
    cout << "   n   !n" << endl;
    for (int i = 0; i <= 8; i++) {
        cout << "   " << setw(2) << i << "  " << setw(5) << derangements(i) << endl;
    }
    cout << "   As n -> infinity, !n/n! -> 1/e ~ 0.3679" << endl;

    // 6. Stars and Bars
    cout << endl << "6. STARS AND BARS" << endl;
    cout << "   Distribute 5 candies to 3 children: " << starsAndBars(5, 3) << " ways" << endl;

    // Complexity summary
    cout << endl << "========================================" << endl;
    cout << "  COMPLEXITY SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "  Factorial:       O(n) time, O(1) space" << endl;
    cout << "  nPr:             O(r) time, O(1) space" << endl;
    cout << "  nCr:             O(r) time, O(1) space" << endl;
    cout << "  Pascal's table:  O(n*r) time, O(n*r) space" << endl;
    cout << "  Catalan (DP):    O(n^2) time, O(n) space" << endl;
    cout << "  Catalan (direct): O(n) time (uses nCr)" << endl;
    cout << "  Derangements:    O(n) time, O(1) space" << endl;

    return 0;
}
