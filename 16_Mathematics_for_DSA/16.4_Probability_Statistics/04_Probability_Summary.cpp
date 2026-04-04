// 16.4.04 - Probability & Statistics Summary
// Complete summary: basic probability, expected value, statistics.

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ---- Basic Probability ----
double probabilityAnd(double pA, double pB) { return pA * pB; }
double probabilityOr(double pA, double pB, double pA_and_B) { return pA + pB - pA_and_B; }
double probabilityNot(double pA) { return 1.0 - pA; }

double bayesTheorem(double pA, double pB_givenA, double pB_givenNotA) {
    double pB = pB_givenA * pA + pB_givenNotA * (1.0 - pA);
    return (pB_givenA * pA) / pB;
}

// ---- Expected Value ----
double expectedValue(double outcomes[], double probs[], int n) {
    double ev = 0;
    for (int i = 0; i < n; i++) ev += outcomes[i] * probs[i];
    return ev;
}

double harmonicNumber(int n) {
    double h = 0;
    for (int i = 1; i <= n; i++) h += 1.0 / (double)i;
    return h;
}

double couponCollector(int n) { return n * harmonicNumber(n); }

// ---- Statistics ----
double mean(double data[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += data[i];
    return sum / n;
}

double variance(double data[], int n) {
    double m = mean(data, n);
    double var = 0;
    for (int i = 0; i < n; i++) {
        double diff = data[i] - m;
        var += diff * diff;
    }
    return var / n;
}

// ---- Binomial Distribution ----
double binomialProb(int n, int k, double p) {
    long long nCr = 1;
    int r = k;
    if (r > n - r) r = n - r;
    for (int i = 0; i < r; i++) nCr = nCr * (n - i) / (i + 1);
    double pk = 1.0, qk = 1.0;
    for (int i = 0; i < k; i++) pk *= p;
    for (int i = 0; i < n - k; i++) qk *= (1.0 - p);
    return (double)nCr * pk * qk;
}

double birthdayParadox(int n) {
    double pNoShared = 1.0;
    for (int i = 0; i < n; i++) pNoShared *= (365.0 - (double)i) / 365.0;
    return 1.0 - pNoShared;
}

int main() {
    cout << fixed << setprecision(4);
    cout << "========================================" << endl;
    cout << "  PROBABILITY & STATISTICS - SUMMARY" << endl;
    cout << "========================================" << endl;

    // 1. Basic Probability
    cout << endl << "1. BASIC PROBABILITY" << endl;
    cout << "   P(even on die) = " << 3.0 / 6.0 << endl;
    cout << "   P(sum=7 on 2 dice) = " << 6.0 / 36.0 << endl;
    cout << "   P(A and B) independent = " << probabilityAnd(0.5, 0.5) << endl;

    // Bayes
    cout << endl << "   Bayes - Medical test:" << endl;
    cout << "   P(disease|positive) = " << bayesTheorem(0.01, 0.99, 0.05) << endl;

    // 2. Expected Value
    cout << endl << "2. EXPECTED VALUE" << endl;
    double diceOut[] = {1, 2, 3, 4, 5, 6};
    double dicePr[] = {1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/6};
    cout << "   E[dice roll] = " << expectedValue(diceOut, dicePr, 6) << endl;  // 3.5
    double gameOut[] = {10, -5};
    double gamePr[] = {0.5, 0.5};
    cout << "   E[coin game] = " << expectedValue(gameOut, gamePr, 2) << endl;  // 2.5

    // Coupon Collector
    cout << endl << "   Coupon Collector: E = n * H_n" << endl;
    int coupons[] = {5, 10, 50};
    for (int i = 0; i < 3; i++) {
        cout << "   " << coupons[i] << " coupons: " << couponCollector(coupons[i]) << " trials" << endl;
    }

    // 3. Statistics
    cout << endl << "3. STATISTICS (Mean, Variance)" << endl;
    double data[] = {2, 4, 4, 4, 5, 5, 7, 9};
    int n = 8;
    cout << "   Data: ";
    for (int i = 0; i < n; i++) cout << data[i] << " ";
    cout << endl;
    cout << "   Mean = " << mean(data, n) << endl;  // 5
    cout << "   Variance = " << variance(data, n) << endl;  // 4
    cout << "   Std Dev = " << sqrt(variance(data, n)) << endl;  // 2

    // 4. Binomial Distribution
    cout << endl << "4. BINOMIAL DISTRIBUTION" << endl;
    cout << "   n=10, p=0.5:" << endl;
    int ks[] = {0, 3, 5, 7, 10};
    for (int i = 0; i < 5; i++) {
        cout << "   P(X=" << ks[i] << ") = " << binomialProb(10, ks[i], 0.5) << endl;
    }

    // 5. Birthday Paradox
    cout << endl << "5. BIRTHDAY PARADOX" << endl;
    int people[] = {23, 30, 50};
    for (int i = 0; i < 3; i++) {
        cout << "   n=" << people[i] << ": P(shared) = " << birthdayParadox(people[i]) << endl;
    }

    // Complexity summary
    cout << endl << "========================================" << endl;
    cout << "  COMPLEXITY SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "  Basic probability:  O(1) time, O(1) space" << endl;
    cout << "  Bayes' theorem:     O(1) time, O(1) space" << endl;
    cout << "  Expected value:     O(n) time, O(1) space" << endl;
    cout << "  Harmonic number:    O(n) time, O(1) space" << endl;
    cout << "  Coupon collector:   O(n) time, O(1) space" << endl;
    cout << "  Mean/Variance:      O(n) time, O(1) space" << endl;
    cout << "  Binomial prob:      O(k) time, O(1) space" << endl;
    cout << "  Birthday paradox:   O(n) time, O(1) space" << endl;

    return 0;
}
