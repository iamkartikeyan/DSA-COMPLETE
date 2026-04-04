// 16.1 Number Theory - Primes, GCD, LCM, Modular Arithmetic
// Fundamental number theory concepts used across competitive programming
// and cryptography.

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

// ============================================================
// PRIMALITY TEST - O(sqrt(n))
// A prime has exactly two divisors: 1 and itself.
// Check divisors only up to sqrt(n) - if n = a*b, one factor <= sqrt(n).
// ============================================================

bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    // Check 6k +/- 1 form
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

void demoPrimality() {
    cout << "=== Primality Test ===" << endl;
    for (int n : {1, 2, 7, 15, 17, 97, 100})
        cout << n << " is " << (isPrime(n) ? "prime" : "not prime") << endl;
    cout << endl;
}

// ============================================================
// SIEVE OF ERATOSTHENES - O(n log log n)
// Precompute all primes up to n. Mark multiples of each prime.
// ============================================================

vector<int> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            // Mark all multiples starting from p*p
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if (isPrime[i]) primes.push_back(i);
    return primes;
}

void demoSieve() {
    cout << "=== Sieve of Eratosthenes ===" << endl;
    int n = 30;
    auto primes = sieve(n);
    cout << "Primes up to " << n << ": ";
    for (int p : primes) cout << p << " ";
    cout << endl;
    cout << "Count: " << primes.size() << endl << endl;
}

// ============================================================
// SIEVE WITH SMALLEST PRIME FACTOR (SPF)
// Store smallest prime factor for each number.
// Useful for prime factorization in O(log n).
// ============================================================

void demoSPFSieve() {
    cout << "=== Smallest Prime Factor Sieve ===" << endl;
    int n = 20;
    vector<int> spf(n + 1);
    for (int i = 0; i <= n; i++) spf[i] = i;

    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) {  // i is prime
            for (int j = i * i; j <= n; j += i)
                if (spf[j] == j) spf[j] = i;  // Mark SPF if not already set
        }
    }

    cout << "Prime factorization using SPF:" << endl;
    for (int num : {12, 18, 20}) {
        cout << num << " = ";
        int temp = num;
        while (temp > 1) {
            cout << spf[temp];
            temp /= spf[temp];
            if (temp > 1) cout << " x ";
        }
        cout << endl;
    }
    cout << endl;
}

// ============================================================
// GCD AND LCM
// GCD(a, b): largest number that divides both.
// LCM(a, b): smallest number divisible by both.
// Formula: GCD(a,b) * LCM(a,b) = a * b
// ============================================================

int gcd(int a, int b) {
    // Euclidean algorithm: GCD(a, b) = GCD(b, a % b)
    // Base case: GCD(a, 0) = a
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;  // Divide first to avoid overflow
}

// GCD of array
int gcdArray(const vector<int>& arr) {
    int result = arr[0];
    for (size_t i = 1; i < arr.size(); i++)
        result = gcd(result, arr[i]);
    return result;
}

void demoGCDLCM() {
    cout << "=== GCD and LCM ===" << endl;
    cout << "GCD(48, 18) = " << gcd(48, 18) << endl;  // 6
    cout << "LCM(48, 18) = " << lcm(48, 18) << endl;  // 144
    cout << "GCD([12, 18, 24]) = " << gcdArray({12, 18, 24}) << endl;  // 6
    cout << "Built-in std::gcd: " << std::gcd(48, 18) << endl;
    cout << endl;
}

// ============================================================
// EXTENDED EUCLIDEAN ALGORITHM
// Finds x, y such that: a*x + b*y = GCD(a, b)
// Foundation for modular inverse, RSA, linear Diophantine equations.
// ============================================================

// Returns {gcd, x, y} where a*x + b*y = gcd
tuple<int, int, int> extendedGCD(int a, int b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x1, y1] = extendedGCD(b, a % b);
    // Back-substitute: x = y1, y = x1 - (a/b)*y1
    return {g, y1, x1 - (a / b) * y1};
}

void demoExtendedGCD() {
    cout << "=== Extended Euclidean Algorithm ===" << endl;
    int a = 35, b = 15;
    auto [g, x, y] = extendedGCD(a, b);
    cout << a << "*(" << x << ") + " << b << "*(" << y << ") = " << g << endl;
    // 35*(1) + 15*(-2) = 5 = GCD(35, 15)
    cout << endl;
}

// ============================================================
// MODULAR ARITHMETIC
// (a + b) % m = ((a % m) + (b % m)) % m
// (a * b) % m = ((a % m) * (b % m)) % m
// (a - b) % m = ((a % m) - (b % m) + m) % m  [add m to handle negative]
// ============================================================

const int MOD = 1e9 + 7;

int modAdd(int a, int b) { return ((a % MOD) + (b % MOD)) % MOD; }
int modMul(int a, int b) { return (1LL * (a % MOD) * (b % MOD)) % MOD; }
int modSub(int a, int b) { return ((a % MOD) - (b % MOD) + MOD) % MOD; }

void demoModularArithmetic() {
    cout << "=== Modular Arithmetic ===" << endl;
    int a = 1e9 + 5, b = 5;
    cout << "MOD = " << MOD << endl;
    cout << "(" << a << " + " << b << ") % MOD = " << modAdd(a, b) << endl;
    cout << "(" << a << " * " << b << ") % MOD = " << modMul(a, b) << endl;
    cout << "(" << a << " - " << b << ") % MOD = " << modSub(a, b) << endl;
    cout << endl;
}

// ============================================================
// MODULAR EXPONENTIATION - O(log b)
// Computes (a^b) % m using binary exponentiation (square & multiply).
// Key idea: a^b = a^(b/2) * a^(b/2) if b is even, a * a^(b-1) if odd.
// ============================================================

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;  // If odd, multiply
        base = (base * base) % mod;  // Square
        exp >>= 1;  // Divide exponent by 2
    }
    return result;
}

void demoModPow() {
    cout << "=== Modular Exponentiation ===" << endl;
    long long base = 2, exp = 10, mod = 1000;
    cout << base << "^" << exp << " % " << mod << " = " << modPow(base, exp, mod) << endl;  // 24
    cout << "2^100 % (10^9+7) = " << modPow(2, 100, MOD) << endl;
    cout << endl;
}

// ============================================================
// MODULAR INVERSE
// a^(-1) mod m: number x such that (a * x) % m = 1
// Exists only when GCD(a, m) = 1 (coprime).
// Method 1: Fermat's Little Theorem (m must be prime): a^(m-2) mod m
// Method 2: Extended GCD (works for any coprime a, m)
// ============================================================

// Method 1: Fermat's Little Theorem (m is prime)
long long modInverseFermat(long long a, long long m) {
    return modPow(a, m - 2, m);
}

// Method 2: Extended GCD (general case)
long long modInverseGCD(long long a, long long m) {
    auto [g, x, y] = extendedGCD(a, m);
    if (g != 1) return -1;  // No inverse exists
    return (x % m + m) % m;  // Ensure positive result
}

void demoModInverse() {
    cout << "=== Modular Inverse ===" << endl;
    long long a = 3, m = MOD;
    long long inv1 = modInverseFermat(a, m);
    long long inv2 = modInverseGCD(a, m);
    cout << "3^(-1) mod (10^9+7) = " << inv1 << " (Fermat)" << endl;
    cout << "Verify: 3 * " << inv1 << " % " << m << " = " << modMul(3, inv1) << endl;
    cout << "Extended GCD: " << inv2 << endl;
    cout << endl;
}

// ============================================================
// MODULAR DIVISION
// (a / b) % m = (a * b^(-1)) % m
// Only works when b and m are coprime (m is prime for Fermat's method).
// ============================================================

long long modDiv(long long a, long long b, long long m) {
    long long inv = modInverseFermat(b, m);
    return modMul(a % m, inv);
}

void demoModDiv() {
    cout << "=== Modular Division ===" << endl;
    long long a = 10, b = 3, m = MOD;
    cout << "(" << a << " / " << b << ") % " << m << " = " << modDiv(a, b, m) << endl;
    cout << endl;
}

int main() {
    demoPrimality();
    demoSieve();
    demoSPFSieve();
    demoGCDLCM();
    demoExtendedGCD();
    demoModularArithmetic();
    demoModPow();
    demoModInverse();
    demoModDiv();
    return 0;
}
