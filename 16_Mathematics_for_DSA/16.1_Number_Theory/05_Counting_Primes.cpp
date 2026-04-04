// 16.1.05 - Counting Primes
// Count the number of primes up to n using sieve.
// Simply count true values in the isPrime array after sieving.

#include <iostream>
#include <vector>

using namespace std;

// Count primes up to n using Sieve of Eratosthenes
// Returns the count of primes in range [2, n]
int countPrimes(int n) {
    if (n < 2) return 0;

    bool* isPrime = new bool[n + 1];
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = false;
    isPrime[1] = false;

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            count++;
        }
    }

    delete[] isPrime;
    return count;
}

// Count primes and store them for reuse
int getPrimesUpTo(int n, int primes[], int maxPrimes) {
    if (n < 2) return 0;

    bool* isPrime = new bool[n + 1];
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = false;
    isPrime[1] = false;

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    int count = 0;
    for (int i = 2; i <= n && count < maxPrimes; i++) {
        if (isPrime[i]) {
            primes[count] = i;
            count++;
        }
    }

    delete[] isPrime;
    return count;
}

int main() {
    cout << "=== Counting Primes ===" << endl;

    int limits[] = {10, 30, 50, 100, 200};
    int numLimits = 5;

    for (int i = 0; i < numLimits; i++) {
        int limit = limits[i];
        int cnt = countPrimes(limit);
        cout << "Primes up to " << limit << ": " << cnt << endl;
    }

    // List all primes up to 30
    cout << endl << "=== Primes up to 30 ===" << endl;
    int primes[100];
    int count = getPrimesUpTo(30, primes, 100);
    cout << "Found " << count << " primes: ";
    for (int i = 0; i < count; i++) {
        cout << primes[i] << " ";
    }
    cout << endl;

    // Prime number theorem approximation
    cout << endl << "=== Prime Number Theorem ===" << endl;
    cout << "Pi(n) ~ n / ln(n)" << endl;
    for (int i = 0; i < numLimits; i++) {
        int n = limits[i];
        int actual = countPrimes(n);
        cout << "Pi(" << n << ") = " << actual << endl;
    }

    cout << endl << "Time: O(n log log n) for sieve" << endl;
    cout << "Space: O(n) for boolean array" << endl;

    return 0;
}
