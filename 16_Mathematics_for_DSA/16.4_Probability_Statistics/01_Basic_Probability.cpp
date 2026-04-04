// 16.4.01 - Basic Probability
// P(Event) = favorable outcomes / total outcomes.
// Bayes' theorem: P(A|B) = P(B|A) * P(A) / P(B).
// Examples: coin flips, dice rolls, cards.

#include <iostream>
#include <iomanip>

using namespace std;

// Bayes' Theorem
// Given: P(A), P(B|A), P(B|not A)
// Compute: P(A|B) = P(B|A) * P(A) / P(B)
// where P(B) = P(B|A) * P(A) + P(B|not A) * P(not A)
double bayesTheorem(double pA, double pB_givenA, double pB_givenNotA) {
    double pB = pB_givenA * pA + pB_givenNotA * (1.0 - pA);
    return (pB_givenA * pA) / pB;
}

// P(A or B) = P(A) + P(B) - P(A and B)
double probabilityOr(double pA, double pB, double pA_and_B) {
    return pA + pB - pA_and_B;
}

// P(A and B) for independent events = P(A) * P(B)
double probabilityAnd(double pA, double pB) {
    return pA * pB;
}

// P(not A) = 1 - P(A)
double probabilityNot(double pA) {
    return 1.0 - pA;
}

int main() {
    cout << fixed << setprecision(4);
    cout << "=== Basic Probability ===" << endl;

    // Die roll examples
    cout << endl << "Die Roll (6-sided):" << endl;
    cout << "  P(even) = P({2,4,6}) = 3/6 = " << 3.0 / 6.0 << endl;
    cout << "  P(>4) = P({5,6}) = 2/6 = " << 2.0 / 6.0 << endl;
    cout << "  P(prime) = P({2,3,5}) = 3/6 = " << 3.0 / 6.0 << endl;

    // Two dice
    cout << endl << "Two Dice:" << endl;
    cout << "  P(sum=7) = 6/36 = " << 6.0 / 36.0 << endl;  // (1,6),(2,5),(3,4),(4,3),(5,2),(6,1)
    cout << "  P(sum=2) = 1/36 = " << 1.0 / 36.0 << endl;  // (1,1)
    cout << "  P(sum=12) = 1/36 = " << 1.0 / 36.0 << endl; // (6,6)

    // Coin flips
    cout << endl << "Coin Flips (fair coin):" << endl;
    cout << "  P(heads) = 0.5" << endl;
    cout << "  P(2 heads in 2 flips) = 0.5 * 0.5 = " << probabilityAnd(0.5, 0.5) << endl;
    cout << "  P(at least 1 head in 2 flips) = 1 - 0.25 = " << probabilityNot(0.25) << endl;

    // P(A or B)
    cout << endl << "P(A or B) = P(A) + P(B) - P(A and B):" << endl;
    cout << "  P(hearts or king) from deck = 13/52 + 4/52 - 1/52 = "
         << probabilityOr(13.0 / 52.0, 4.0 / 52.0, 1.0 / 52.0) << endl;

    // Bayes' Theorem
    cout << endl << "=== Bayes' Theorem ===" << endl;
    cout << "Medical test example:" << endl;
    cout << "  Disease prevalence: 1%" << endl;
    cout << "  Test sensitivity (true positive): 99%" << endl;
    cout << "  False positive rate: 5%" << endl;

    double result = bayesTheorem(0.01, 0.99, 0.05);
    cout << "  P(disease | positive test) = " << result << " (~" << (result * 100) << "%)" << endl;
    cout << "  (Counterintuitive due to base rate fallacy)" << endl;

    // Another Bayes example
    cout << endl << "Spam filter example:" << endl;
    cout << "  P(spam) = 30%" << endl;
    cout << "  P(word 'free' | spam) = 80%" << endl;
    cout << "  P(word 'free' | not spam) = 10%" << endl;
    double spamProb = bayesTheorem(0.30, 0.80, 0.10);
    cout << "  P(spam | contains 'free') = " << spamProb << " (~" << (spamProb * 100) << "%)" << endl;

    cout << endl << "Time: O(1) for all formulas" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
