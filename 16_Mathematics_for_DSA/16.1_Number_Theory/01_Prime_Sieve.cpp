// 16.1.01 - Sieve of Eratosthenes
// Precompute all primes up to n in O(n log log n).
// Mark multiples of each prime starting from p*p.

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100000;
bool isPrimeArr[MAXN + 1];

void sieveOfEratosthenes(int n) {
    // Initialize all as prime
    for (int i = 0; i <= n; i++) {
        isPrimeArr[i] = true;
    }
    isPrimeArr[0] = false;
    isPrimeArr[1] = false;

    // Mark composites
    for (int p = 2; p * p <= n; p++) {
        if (isPrimeArr[p]) {
            // Mark all multiples of p starting from p*p
            for (int i = p * p; i <= n; i += p) {
                isPrimeArr[i] = false;
            }
        }
    }
}

void collectPrimes(int n, int primes[], int& count) {
    count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrimeArr[i]) {
            primes[count] = i;
            count++;
        }
    }
}

// Primality test in O(sqrt(n))
bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    // Check 6k +/- 1 form
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    cout << "=== Sieve of Eratosthenes ===" << endl;

    // Sieve up to 30
    int n = 30;
    sieveOfEratosthenes(n);

    int primes[MAXN];
    int count = 0;
    collectPrimes(n, primes, count);

    cout << "Primes up to " << n << ": ";
    for (int i = 0; i < count; i++) {
        cout << primes[i] << " ";
    }
    cout << endl;
    cout << "Count: " << count << endl;

    // Primality test
    cout << endl << "=== Primality Test ===" << endl;
    int testVals[] = {1, 2, 7, 15, 17, 97, 100};
    int numTests = 7;
    for (int i = 0; i < numTests; i++) {
        int val = testVals[i];
        cout << val << " is " << (isPrime(val) ? "prime" : "not prime") << endl;
    }

    // Complexity note
    cout << endl << "Time: O(n log log n) for sieve, O(sqrt(n)) for single primality test" << endl;
    cout << "Space: O(n) for boolean array" << endl;

    return 0;
}
