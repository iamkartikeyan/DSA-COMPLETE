// 16.1.03 - Modular Arithmetic
// Modular exponentiation, modular inverse, Fermat's little theorem.
// Core operations for competitive programming and cryptography.

#include <iostream>

using namespace std;

const int MOD = 1000000007;

// Modular addition: (a + b) % m
int modAdd(int a, int b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}

// Modular multiplication: (a * b) % m using 1LL to prevent overflow
int modMul(int a, int b) {
    return (int)((1LL * (a % MOD) * (b % MOD)) % MOD);
}

// Modular subtraction: (a - b) % m, add m to handle negative
int modSub(int a, int b) {
    return ((a % MOD) - (b % MOD) + MOD) % MOD;
}

// Modular exponentiation - O(log exp)
// Computes (base^exp) % mod using binary exponentiation (square & multiply)
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        // If exponent is odd, multiply result by base
        if (exp & 1) {
            result = (result * base) % mod;
        }
        // Square the base
        base = (base * base) % mod;
        // Divide exponent by 2
        exp >>= 1;
    }
    return result;
}

// Modular inverse using Fermat's Little Theorem (MOD must be prime)
// a^(MOD-2) % MOD = a^(-1) mod MOD
long long modInverseFermat(long long a) {
    return modPow(a, MOD - 2, MOD);
}

// Modular inverse using Extended GCD (works for any coprime a, m)
int extendedGCDForModInverse(int a, int m, int& x, int& y) {
    if (m == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = extendedGCDForModInverse(m, a % m, x1, y1);
    x = y1;
    y = x1 - (a / m) * y1;
    return g;
}

long long modInverseGCD(long long a, long long m) {
    int x, y;
    int g = extendedGCDForModInverse((int)a, (int)m, x, y);
    if (g != 1) return -1;  // No inverse exists
    return ((long long)x % m + m) % m;
}

// Modular division: (a / b) % m = (a * b^(-1)) % m
long long modDiv(long long a, long long b) {
    long long inv = modInverseFermat(b);
    return modMul((int)(a % MOD), (int)inv);
}

int main() {
    cout << "=== Modular Arithmetic ===" << endl;
    cout << "MOD = " << MOD << endl;

    int a = 1000000005, b = 5;
    cout << "(" << a << " + " << b << ") % MOD = " << modAdd(a, b) << endl;
    cout << "(" << a << " * " << b << ") % MOD = " << modMul(a, b) << endl;
    cout << "(" << a << " - " << b << ") % MOD = " << modSub(a, b) << endl;

    // Modular exponentiation
    cout << endl << "=== Modular Exponentiation ===" << endl;
    cout << "2^10 % 1000 = " << modPow(2, 10, 1000) << endl;  // 24
    cout << "2^100 % MOD = " << modPow(2, 100, MOD) << endl;

    // Modular inverse
    cout << endl << "=== Modular Inverse ===" << endl;
    long long inv1 = modInverseFermat(3);
    cout << "3^(-1) mod MOD = " << inv1 << " (Fermat)" << endl;
    cout << "Verify: 3 * " << inv1 << " % MOD = " << modMul(3, (int)inv1) << endl;

    long long inv2 = modInverseGCD(3, MOD);
    cout << "Extended GCD: " << inv2 << endl;

    // Modular division
    cout << endl << "=== Modular Division ===" << endl;
    cout << "(10 / 3) % MOD = " << modDiv(10, 3) << endl;

    cout << endl << "Time: O(log exp) for modPow, O(log MOD) for modInverse" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
