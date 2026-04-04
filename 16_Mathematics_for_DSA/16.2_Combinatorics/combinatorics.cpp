// 16.2 Combinatorics - Permutations, Combinations, Catalan, Derangements
// Counting techniques fundamental to probability and algorithm analysis.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int MOD = 1e9 + 7;

// ============================================================
// FACTORIAL
// n! = n * (n-1) * ... * 1. 0! = 1.
// Precompute for repeated queries.
// ============================================================

long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}

// Factorial modulo MOD
long long factorialMod(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) result = (result * i) % MOD;
    return result;
}

void demoFactorial() {
    cout << "=== Factorial ===" << endl;
    for (int i = 0; i <= 10; i++)
        cout << i << "! = " << factorial(i) << endl;
    cout << endl;
}

// ============================================================
// PERMUTATIONS (nPr)
// nPr = n! / (n-r)! : ordered arrangements of r items from n.
// Example: arranging 3 people in 2 seats from 5 = P(5,2) = 20
// ============================================================

long long nPr(int n, int r) {
    if (r > n) return 0;
    long long result = 1;
    for (int i = 0; i < r; i++) result *= (n - i);
    return result;
}

void demoPermutations() {
    cout << "=== Permutations (nPr) ===" << endl;
    cout << "P(5, 2) = " << nPr(5, 2) << endl;  // 20
    cout << "P(5, 5) = " << nPr(5, 5) << endl;  // 120
    cout << "P(10, 3) = " << nPr(10, 3) << endl;  // 720
    cout << endl;
}

// ============================================================
// COMBINATIONS (nCr)
// nCr = n! / (r! * (n-r)!) : unordered selections of r items from n.
// Pascal's triangle: C(n, r) = C(n-1, r-1) + C(n-1, r)
// ============================================================

// Method 1: Pascal's Triangle DP - O(n*r) space optimization
vector<vector<int>> buildPascalTriangle(int n) {
    vector<vector<int>> C(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;  // C(n, 0) = 1
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    return C;
}

// Method 2: Direct computation using nPr
long long nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    if (r > n - r) r = n - r;  // Symmetry: C(n,r) = C(n, n-r)
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

// Method 3: Modular nCr using precomputed factorials and modular inverse
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long modInverse(long long a, long long m) {
    return modPow(a, m - 2, m);
}

long long nCrMod(int n, int r, const vector<long long>& fact) {
    if (r > n) return 0;
    long long num = fact[n];
    long long den = (fact[r] * fact[n - r]) % MOD;
    return (num * modInverse(den, MOD)) % MOD;
}

void demoCombinations() {
    cout << "=== Combinations (nCr) ===" << endl;
    cout << "C(5, 2) = " << nCr(5, 2) << endl;  // 10
    cout << "C(10, 3) = " << nCr(10, 3) << endl;  // 120
    cout << "C(52, 5) = " << nCr(52, 5) << endl;  // 2598960

    // Pascal's triangle
    cout << "\nPascal's Triangle (n=5):" << endl;
    auto C = buildPascalTriangle(5);
    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= i; j++)
            cout << setw(4) << C[i][j];
        cout << endl;
    }

    // Modular nCr
    cout << "\nC(20, 10) mod (10^9+7) = ";
    vector<long long> fact(21);
    fact[0] = 1;
    for (int i = 1; i <= 20; i++) fact[i] = (fact[i - 1] * i) % MOD;
    cout << nCrMod(20, 10, fact) << endl;
    cout << endl;
}

// ============================================================
// APPLICATION: Stars and Bars
// Number of ways to distribute n identical items into k distinct bins
// = C(n + k - 1, k - 1)
// ============================================================

void demoStarsAndBars() {
    cout << "=== Stars and Bars ===" << endl;
    int n = 5, k = 3;
    cout << "Distribute " << n << " identical candies into " << k << " children:" << endl;
    cout << "Ways = C(" << n + k - 1 << ", " << k - 1 << ") = " << nCr(n + k - 1, k - 1) << endl;
    // C(7, 2) = 21
    cout << endl;
}

// ============================================================
// CATALAN NUMBERS
// C_n = (2n)! / ((n+1)! * n!) = C(2n, n) / (n+1)
// Recurrence: C_0 = 1, C_n = sum(C_i * C_{n-1-i}) for i = 0..n-1
//
// Applications:
// - Valid parenthesis expressions with n pairs
// - Number of BSTs with n nodes
// - Triangulations of convex (n+2)-gon
// - Paths in grid that don't cross diagonal
// ============================================================

// Method 1: Recurrence O(n^2)
vector<long long> catalanDP(int n) {
    vector<long long> C(n + 1, 0);
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++)
            C[i] += C[j] * C[i - 1 - j];
    }
    return C;
}

// Method 2: Direct formula using nCr
long long catalan(int n) {
    return nCr(2 * n, n) / (n + 1);
}

void demoCatalan() {
    cout << "=== Catalan Numbers ===" << endl;
    auto C = catalanDP(10);
    cout << "C_0 to C_10: ";
    for (int i = 0; i <= 10; i++) cout << C[i] << " ";
    // 1 1 2 5 14 42 132 429 1430 4862 16796
    cout << endl;

    cout << "Applications of C_3 = 5:" << endl;
    cout << "  Valid parentheses with 3 pairs: ((())), (()()), (())(), ()(()), ()()()" << endl;
    cout << "  BSTs with 3 nodes = 5" << endl;
    cout << "  Triangulations of pentagon = 5" << endl;
    cout << endl;
}

// ============================================================
// DERANGEMENTS
// A derangement is a permutation where no element is in its original position.
// !n = (n-1) * (!(n-1) + !(n-2))
// Base: !0 = 1, !1 = 0
// Approximation: !n ~ n! / e
// ============================================================

long long derangements(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (n == 2) return 1;

    long long prev2 = 1, prev1 = 0, curr;
    for (int i = 2; i <= n; i++) {
        curr = (i - 1) * (prev1 + prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

void demoDerangements() {
    cout << "=== Derangements ===" << endl;
    cout << "n   !n   !n/n!" << endl;
    for (int i = 0; i <= 8; i++) {
        double ratio = (double)derangements(i) / factorial(max(i, 1));
        cout << i << "   " << setw(5) << derangements(i) << "   "
             << fixed << setprecision(4) << ratio << endl;
    }
    cout << "As n -> infinity, !n/n! -> 1/e ~ 0.3679" << endl;
    cout << endl;
}

// ============================================================
// APPLICATION: Count Valid Parentheses (Catalan)
// Generate all valid parenthesis strings with n pairs.
// ============================================================

void generateParentheses(int open, int close, string current, vector<string>& result) {
    if (open == 0 && close == 0) { result.push_back(current); return; }
    if (open > 0) generateParentheses(open - 1, close, current + "(", result);
    if (close > open) generateParentheses(open, close - 1, current + ")", result);
}

void demoValidParentheses() {
    cout << "=== Valid Parentheses Generation ===" << endl;
    int n = 3;
    vector<string> result;
    generateParentheses(n, n, "", result);
    cout << "Valid parentheses with " << n << " pairs (" << result.size() << " total):" << endl;
    for (auto& s : result) cout << "  " << s << endl;
    cout << endl;
}

// ============================================================
// APPLICATION: Counting BSTs with n nodes (Catalan)
// ============================================================

void demoBSTCount() {
    cout << "=== Number of BSTs with n Nodes ===" << endl;
    for (int n = 1; n <= 6; n++)
        cout << "n=" << n << ": " << catalan(n) << " BSTs" << endl;
    cout << endl;
}

int main() {
    demoFactorial();
    demoPermutations();
    demoCombinations();
    demoStarsAndBars();
    demoCatalan();
    demoDerangements();
    demoValidParentheses();
    demoBSTCount();
    return 0;
}
