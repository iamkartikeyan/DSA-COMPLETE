// 16.1.04 - Prime Factorization
// Trial division method: O(sqrt(n)) per number.
// Optimized with SPF (Smallest Prime Factor) sieve for O(log n) queries.

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000;
int spf[MAXN + 1];  // Smallest Prime Factor

// Build SPF sieve: O(n log log n)
void buildSPFSieve(int n) {
    // Initialize SPF[i] = i
    for (int i = 0; i <= n; i++) {
        spf[i] = i;
    }

    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) {  // i is prime
            for (int j = i * i; j <= n; j += i) {
                if (spf[j] == j) {  // Mark SPF if not already set
                    spf[j] = i;
                }
            }
        }
    }
}

// Prime factorization using trial division - O(sqrt(n))
void factorizeTrialDivision(int n, int factors[], int& count) {
    count = 0;
    int temp = n;

    // Check factor 2
    while (temp % 2 == 0) {
        factors[count] = 2;
        count++;
        temp /= 2;
    }

    // Check odd factors from 3
    for (int i = 3; i * i <= temp; i += 2) {
        while (temp % i == 0) {
            factors[count] = i;
            count++;
            temp /= i;
        }
    }

    // Remaining prime > sqrt(n)
    if (temp > 1) {
        factors[count] = temp;
        count++;
    }
}

// Prime factorization using SPF sieve - O(log n)
void factorizeSPF(int n, int factors[], int& count) {
    count = 0;
    while (n > 1) {
        factors[count] = spf[n];
        count++;
        n /= spf[n];
    }
}

// Count number of divisors using prime factorization
// If n = p1^a1 * p2^a2 * ... * pk^ak, then numDivisors = (a1+1)*(a2+1)*...*(ak+1)
int countDivisors(int n) {
    int result = 1;
    int temp = n;

    for (int i = 2; i * i <= temp; i++) {
        if (temp % i == 0) {
            int exponent = 0;
            while (temp % i == 0) {
                exponent++;
                temp /= i;
            }
            result *= (exponent + 1);
        }
    }
    if (temp > 1) {
        result *= 2;  // Remaining prime with exponent 1
    }
    return result;
}

int main() {
    cout << "=== Prime Factorization - Trial Division ===" << endl;
    int testNums[] = {12, 18, 20, 36, 100};
    int numTests = 5;

    for (int i = 0; i < numTests; i++) {
        int num = testNums[i];
        int factors[32];
        int count = 0;
        factorizeTrialDivision(num, factors, count);

        cout << num << " = ";
        for (int j = 0; j < count; j++) {
            cout << factors[j];
            if (j < count - 1) cout << " x ";
        }
        cout << " (" << count << " factors, " << countDivisors(num) << " divisors)" << endl;
    }

    // SPF factorization
    cout << endl << "=== Prime Factorization - SPF Sieve ===" << endl;
    int n = 20;
    buildSPFSieve(n);

    int spfNums[] = {12, 18, 20};
    int spfTests = 3;
    for (int i = 0; i < spfTests; i++) {
        int num = spfNums[i];
        int factors[32];
        int count = 0;
        factorizeSPF(num, factors, count);

        cout << num << " = ";
        for (int j = 0; j < count; j++) {
            cout << factors[j];
            if (j < count - 1) cout << " x ";
        }
        cout << endl;
    }

    cout << endl << "Time: O(sqrt(n)) trial division, O(log n) with SPF" << endl;
    cout << "Space: O(n) for SPF array" << endl;

    return 0;
}
