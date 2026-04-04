// 16.1.06 - Number Theory Summary
// Complete summary of all number theory concepts.

#include <iostream>

using namespace std;

const int MOD = 1000000007;

// ---- Primality Test ----
bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// ---- Sieve of Eratosthenes ----
void sieveDemo(int n, bool isPrimeArr[]) {
    for (int i = 0; i <= n; i++) isPrimeArr[i] = true;
    isPrimeArr[0] = false;
    isPrimeArr[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (isPrimeArr[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrimeArr[i] = false;
            }
        }
    }
}

// ---- GCD (Euclidean) ----
int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// ---- Extended GCD ----
int extendedGCD(int a, int b, int& x, int& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int x1, y1;
    int g = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// ---- LCM ----
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

// ---- Modular Exponentiation ----
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

// ---- Modular Inverse (Fermat) ----
long long modInverse(long long a, long long m) {
    return modPow(a, m - 2, m);
}

// ---- Modular Arithmetic ----
int modAdd(int a, int b) { return ((a % MOD) + (b % MOD)) % MOD; }
int modMul(int a, int b) { return (int)((1LL * (a % MOD) * (b % MOD)) % MOD); }
int modSub(int a, int b) { return ((a % MOD) - (b % MOD) + MOD) % MOD; }

int main() {
    cout << "========================================" << endl;
    cout << "  NUMBER THEORY - COMPLETE SUMMARY" << endl;
    cout << "========================================" << endl;

    // 1. Primality Test
    cout << endl << "1. PRIMALITY TEST (O(sqrt(n)))" << endl;
    int tests[] = {1, 2, 7, 15, 17, 97};
    int nTests = 6;
    for (int i = 0; i < nTests; i++) {
        cout << "   " << tests[i] << " is " << (isPrime(tests[i]) ? "prime" : "not prime") << endl;
    }

    // 2. Sieve
    cout << endl << "2. SIEVE OF ERATOSTHENES (O(n log log n))" << endl;
    int n = 30;
    bool isPrimeArr[31];
    sieveDemo(n, isPrimeArr);
    cout << "   Primes up to " << n << ": ";
    for (int i = 2; i <= n; i++) {
        if (isPrimeArr[i]) cout << i << " ";
    }
    cout << endl;

    // 3. GCD and LCM
    cout << endl << "3. GCD & LCM (O(log(min(a,b))))" << endl;
    cout << "   GCD(48, 18) = " << gcd(48, 18) << endl;
    cout << "   LCM(48, 18) = " << lcm(48, 18) << endl;
    int x, y;
    int g = extendedGCD(35, 15, x, y);
    cout << "   35*(" << x << ") + 15*(" << y << ") = " << g << endl;

    // 4. Modular Arithmetic
    cout << endl << "4. MODULAR ARITHMETIC" << endl;
    cout << "   (1e9+5 + 5) % MOD = " << modAdd(1000000005, 5) << endl;
    cout << "   (1e9+5 * 5) % MOD = " << modMul(1000000005, 5) << endl;

    // 5. Modular Exponentiation
    cout << endl << "5. MODULAR EXPONENTIATION (O(log exp))" << endl;
    cout << "   2^10 % 1000 = " << modPow(2, 10, 1000) << endl;
    cout << "   2^100 % MOD = " << modPow(2, 100, MOD) << endl;

    // 6. Modular Inverse
    cout << endl << "6. MODULAR INVERSE (O(log MOD))" << endl;
    long long inv = modInverse(3, MOD);
    cout << "   3^(-1) mod MOD = " << inv << endl;
    cout << "   Verify: 3 * " << inv << " % MOD = " << modMul(3, (int)inv) << endl;

    // Complexity summary
    cout << endl << "========================================" << endl;
    cout << "  COMPLEXITY SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "  Primality test:    O(sqrt(n)) time, O(1) space" << endl;
    cout << "  Sieve:             O(n log log n) time, O(n) space" << endl;
    cout << "  GCD (Euclidean):   O(log(min(a,b))) time, O(1) space" << endl;
    cout << "  Extended GCD:      O(log(min(a,b))) time, O(log(min(a,b))) space (recursive)" << endl;
    cout << "  ModPow:            O(log exp) time, O(1) space" << endl;
    cout << "  ModInverse:        O(log MOD) time, O(1) space" << endl;
    cout << "  Prime fact. (SPF): O(log n) per query after O(n log log n) build" << endl;

    return 0;
}
