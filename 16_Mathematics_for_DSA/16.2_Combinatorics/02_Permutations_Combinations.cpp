// 16.2.02 - Permutations and Combinations
// nPr = n! / (n-r)!: ordered arrangements.
// nCr = n! / (r! * (n-r)!): unordered selections.
// Pascal's triangle: C(n,r) = C(n-1,r-1) + C(n-1,r).

#include <iostream>
#include <iomanip>

using namespace std;

const int MOD = 1000000007;

// ---- Permutations: nPr = n! / (n-r)! ----
// Direct computation: n * (n-1) * ... * (n-r+1)
long long nPr(int n, int r) {
    if (r > n) return 0;
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result *= (n - i);
    }
    return result;
}

// ---- Combinations: nCr = n! / (r! * (n-r)!) ----
// Using symmetry: C(n,r) = C(n, n-r) to minimize iterations
long long nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    if (r > n - r) r = n - r;  // Symmetry optimization
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

// ---- Pascal's Triangle (DP approach) ----
// C[i][j] = C[i-1][j-1] + C[i-1][j]
// O(n*r) time and space
void buildPascalTriangle(int n, int C[][21]) {
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;  // C(n, 0) = 1
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

// ---- Modular exponentiation ----
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

// Modular nCr using precomputed factorials
long long nCrMod(int n, int r, long long fact[]) {
    if (r > n) return 0;
    long long num = fact[n];
    long long den = (fact[r] * fact[n - r]) % MOD;
    return (num * modInverse(den, MOD)) % MOD;
}

// ---- Stars and Bars ----
// Distribute n identical items into k distinct bins: C(n+k-1, k-1)
int starsAndBars(int n, int k) {
    return (int)nCr(n + k - 1, k - 1);
}

int main() {
    cout << "=== Permutations (nPr) ===" << endl;
    cout << "P(5, 2) = " << nPr(5, 2) << endl;     // 20
    cout << "P(5, 5) = " << nPr(5, 5) << endl;     // 120
    cout << "P(10, 3) = " << nPr(10, 3) << endl;   // 720

    // Combinations
    cout << endl << "=== Combinations (nCr) ===" << endl;
    cout << "C(5, 2) = " << nCr(5, 2) << endl;     // 10
    cout << "C(10, 3) = " << nCr(10, 3) << endl;   // 120
    cout << "C(52, 5) = " << nCr(52, 5) << endl;   // 2598960

    // Pascal's Triangle
    cout << endl << "=== Pascal's Triangle (n=5) ===" << endl;
    int C[21][21] = {0};
    int n = 5;
    buildPascalTriangle(n, C);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << setw(4) << C[i][j];
        }
        cout << endl;
    }

    // Modular nCr
    cout << endl << "=== Modular nCr ===" << endl;
    long long fact[21];
    fact[0] = 1;
    for (int i = 1; i <= 20; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    cout << "C(20, 10) mod (10^9+7) = " << nCrMod(20, 10, fact) << endl;

    // Stars and Bars
    cout << endl << "=== Stars and Bars ===" << endl;
    int candies = 5, children = 3;
    cout << "Distribute " << candies << " identical candies into " << children << " children:" << endl;
    cout << "Ways = C(" << candies + children - 1 << ", " << children - 1 << ") = "
         << starsAndBars(candies, children) << endl;  // C(7,2) = 21

    cout << endl << "Time: O(r) for nPr/nCr, O(n*r) for Pascal's triangle" << endl;
    cout << "Space: O(n*r) for Pascal's table, O(1) for direct computation" << endl;

    return 0;
}
