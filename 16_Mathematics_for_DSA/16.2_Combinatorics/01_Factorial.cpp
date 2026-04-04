// 16.2.01 - Factorial
// n! = n * (n-1) * ... * 1. 0! = 1.
// Iterative and recursive implementations.

#include <iostream>
#include <iomanip>

using namespace std;

const int MOD = 1000000007;

// Iterative factorial
long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Recursive factorial
long long factorialRecursive(int n) {
    if (n <= 1) return 1;
    return n * factorialRecursive(n - 1);
}

// Factorial modulo MOD - prevents overflow
long long factorialMod(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

// Precompute factorials for repeated queries
void precomputeFactorials(int n, long long fact[]) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
    }
}

// Precompute factorials modulo MOD
void precomputeFactorialsMod(int n, long long fact[]) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
}

int main() {
    cout << "=== Factorial ===" << endl;

    // Basic factorials
    cout << endl << "Iterative:" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << "  " << i << "! = " << factorial(i) << endl;
    }

    // Recursive
    cout << endl << "Recursive:" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << "  " << i << "! = " << factorialRecursive(i) << endl;
    }

    // Modulo factorial
    cout << endl << "Modulo (MOD = " << MOD << "):" << endl;
    int mods[] = {10, 20, 50, 100};
    int nMods = 4;
    for (int i = 0; i < nMods; i++) {
        cout << "  " << mods[i] << "! % MOD = " << factorialMod(mods[i]) << endl;
    }

    // Precomputed factorials
    cout << endl << "Precomputed factorials:" << endl;
    long long fact[21];
    precomputeFactorials(20, fact);
    for (int i = 0; i <= 20; i++) {
        cout << "  " << i << "! = " << fact[i] << endl;
    }

    // Overflow note
    cout << endl << "Note: 21! overflows 64-bit integer (max ~9.2e18)" << endl;
    cout << "20! = " << fact[20] << endl;

    cout << endl << "Time: O(n) per factorial, O(n) precompute for O(1) queries" << endl;
    cout << "Space: O(n) for precomputed array" << endl;

    return 0;
}
