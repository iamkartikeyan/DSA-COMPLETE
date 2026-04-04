// 16.4.02 - Expected Value
// E[X] = sum of (value * probability) for all outcomes.
// Linearity: E[X + Y] = E[X] + E[Y] (even for dependent variables).
// Geometric distribution: expected trials to first success = 1/p.
// Coupon collector: E = n * H_n where H_n = 1 + 1/2 + ... + 1/n.

#include <iostream>
#include <iomanip>

using namespace std;

// Expected value of a discrete random variable
// outcomes: array of values
// probs: array of probabilities (must sum to 1)
// n: number of outcomes
double expectedValue(double outcomes[], double probs[], int n) {
    double ev = 0;
    for (int i = 0; i < n; i++) {
        ev += outcomes[i] * probs[i];
    }
    return ev;
}

// Harmonic number H_n = 1 + 1/2 + 1/3 + ... + 1/n
double harmonicNumber(int n) {
    double h = 0;
    for (int i = 1; i <= n; i++) {
        h += 1.0 / (double)i;
    }
    return h;
}

// Coupon collector problem: expected trials to collect all n coupons
double couponCollector(int n) {
    return n * harmonicNumber(n);
}

// Expected number of trials for geometric distribution (first success)
double expectedTrialsGeometric(double p) {
    return 1.0 / p;
}

int main() {
    cout << fixed << setprecision(4);
    cout << "=== Expected Value ===" << endl;

    // Dice roll: E[X] = (1+2+3+4+5+6)/6 = 3.5
    cout << endl << "Dice Roll:" << endl;
    double diceOutcomes[] = {1, 2, 3, 4, 5, 6};
    double diceProbs[] = {1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/6};
    cout << "  E[roll] = " << expectedValue(diceOutcomes, diceProbs, 6) << endl;  // 3.5

    // Coin toss game: +10 for heads, -5 for tails
    cout << endl << "Coin Toss Game:" << endl;
    double gameOutcomes[] = {10, -5};
    double gameProbs[] = {0.5, 0.5};
    cout << "  E[game] = " << expectedValue(gameOutcomes, gameProbs, 2) << endl;  // 2.5
    cout << "  (Positive expected value = favorable game)" << endl;

    // Expected flips to get heads
    cout << endl << "Geometric Distribution:" << endl;
    double p = 0.5;
    cout << "  Expected flips to get heads (p=" << p << "): " << expectedTrialsGeometric(p) << endl;
    p = 0.1;
    cout << "  Expected flips for p=" << p << ": " << expectedTrialsGeometric(p) << endl;

    // Coupon Collector
    cout << endl << "=== Coupon Collector Problem ===" << endl;
    cout << "E[trials] = n * H_n where H_n = 1 + 1/2 + ... + 1/n" << endl;
    int coupons[] = {5, 10, 50, 100};
    int numCases = 4;
    for (int i = 0; i < numCases; i++) {
        int n = coupons[i];
        cout << "  Collect " << n << " coupons: E = " << couponCollector(n) << " trials" << endl;
    }

    // Linearity of Expectation: Hat Check Problem
    cout << endl << "=== Hat Check Problem (Linearity of Expectation) ===" << endl;
    cout << "n people randomly receive n hats." << endl;
    cout << "Expected # who get their own hat = 1 (always!)" << endl;
    cout << "Proof: E[X] = sum of E[X_i] = n * (1/n) = 1" << endl;
    int hats[] = {1, 2, 5, 10, 100};
    int numHats = 5;
    for (int i = 0; i < numHats; i++) {
        cout << "  n=" << hats[i] << ": E[X] = 1.0" << endl;
    }

    cout << endl << "Time: O(n) for expected value with n outcomes" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
