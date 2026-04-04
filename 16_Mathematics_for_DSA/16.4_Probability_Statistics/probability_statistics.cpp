// 16.4 Probability & Statistics - Expected Value, Randomized Algorithms
// Probability theory applications in algorithm design and analysis.
// Includes expected value calculations, Monte Carlo methods, and more.

#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <iomanip>

using namespace std;

// ============================================================
// BASIC PROBABILITY
// P(Event) = favorable outcomes / total outcomes (uniform case)
// P(A or B) = P(A) + P(B) - P(A and B)
// P(A and B) = P(A) * P(B|A)  [chain rule]
// P(A|B) = P(A and B) / P(B)  [Bayes' theorem]
// ============================================================

// P(A|B) = P(B|A) * P(A) / P(B)
double bayesTheorem(double pA, double pB_givenA, double pB_givenNotA) {
    double pB = pB_givenA * pA + pB_givenNotA * (1 - pA);
    return (pB_givenA * pA) / pB;
}

void demoBasicProbability() {
    cout << "=== Basic Probability ===" << endl;
    cout << "Die roll: P(even) = 3/6 = " << 3.0 / 6.0 << endl;
    cout << "Die roll: P(>4) = 2/6 = " << 2.0 / 6.0 << endl;
    cout << "Two dice: P(sum=7) = 6/36 = " << 6.0 / 36.0 << endl;
    cout << endl;
}

void demoBayes() {
    cout << "=== Bayes' Theorem ===" << endl;
    cout << "Medical test example:" << endl;
    cout << "  Disease prevalence: 1%" << endl;
    cout << "  Test sensitivity (true positive rate): 99%" << endl;
    cout << "  False positive rate: 5%" << endl;
    double result = bayesTheorem(0.01, 0.99, 0.05);
    cout << fixed << setprecision(4);
    cout << "  P(disease | positive test) = " << result << " (~" << (result * 100) << "%)" << endl;
    // ~16.7% - counterintuitive but correct due to base rate fallacy
    cout << endl;
}

// ============================================================
// EXPECTED VALUE
// E[X] = sum of (value * probability) for all outcomes.
// Linearity: E[X + Y] = E[X] + E[Y] (even if X, Y are dependent).
// ============================================================

// Expected value of a discrete random variable
// Harmonic number H_n = 1 + 1/2 + ... + 1/n
double H_n(int n) {
    double h = 0;
    for (int i = 1; i <= n; i++) h += 1.0 / i;
    return h;
}

double expectedValue(const vector<pair<double, double>>& outcomes) {
    double ev = 0;
    for (auto& [value, prob] : outcomes)
        ev += value * prob;
    return ev;
}

void demoExpectedValue() {
    cout << "=== Expected Value ===" << endl;

    // Dice roll: E[X] = (1+2+3+4+5+6)/6 = 3.5
    vector<pair<double, double>> dice;
    for (int i = 1; i <= 6; i++) dice.push_back({(double)i, 1.0 / 6.0});
    cout << "Expected value of die roll: " << expectedValue(dice) << endl;  // 3.5

    // Coin toss game: +10 for heads, -5 for tails
    vector<pair<double, double>> game = {{10, 0.5}, {-5, 0.5}};
    cout << "Expected value of coin game: " << expectedValue(game) << endl;  // 2.5

    // Expected number of coin flips to get heads: E = 1/p = 2
    cout << "Expected flips to get heads (p=0.5): " << 1.0 / 0.5 << endl;  // 2
    cout << endl;
}

// ============================================================
// EXPECTED NUMBER OF TRIALS
// Geometric distribution: expected trials to first success = 1/p
// Expected trials to collect all n coupons (Coupon Collector) = n * H_n
// H_n = 1 + 1/2 + 1/3 + ... + 1/n (harmonic number)
// ============================================================

double couponCollector(int n) {
    double H = 0;
    for (int i = 1; i <= n; i++) H += 1.0 / i;
    return n * H;
}

void demoExpectedTrials() {
    cout << "=== Expected Number of Trials ===" << endl;
    cout << "Geometric: E[trials for p=" << "0.1] = " << 1.0 / 0.1 << endl;  // 10

    cout << "\nCoupon Collector Problem:" << endl;
    for (int n : {5, 10, 50, 100})
        cout << "  Collect " << n << " coupons: E = "
             << fixed << setprecision(1) << couponCollector(n) << " trials" << endl;
    cout << endl;
}

// ============================================================
// MONTE CARLO SIMULATION
// Use random sampling to estimate values (PI, integrals, etc.)
// Accuracy improves with more samples (converges as O(1/sqrt(n))).
// ============================================================

double monteCarloPI(int samples) {
    mt19937 rng(42);
    uniform_real_distribution<double> dist(0.0, 1.0);
    int inside = 0;

    for (int i = 0; i < samples; i++) {
        double x = dist(rng), y = dist(rng);
        if (x * x + y * y <= 1.0) inside++;  // Inside quarter circle
    }
    return 4.0 * inside / samples;  // Area ratio: pi/4
}

void demoMonteCarloPI() {
    cout << "=== Monte Carlo: Estimate PI ===" << endl;
    for (int samples : {1000, 10000, 100000, 1000000}) {
        double pi = monteCarloPI(samples);
        cout << "Samples: " << setw(7) << samples << " => PI ~ "
             << fixed << setprecision(5) << pi << endl;
    }
    cout << "Actual PI: " << acos(-1.0) << endl;
    cout << endl;
}

// ============================================================
// RESERVOIR SAMPLING
// Select k random items from a stream of unknown length.
// Each item has equal probability k/n of being selected.
// ============================================================

vector<int> reservoirSampling(const vector<int>& stream, int k) {
    vector<int> result(stream.begin(), stream.begin() + k);
    mt19937 rng(42);

    for (size_t i = k; i < stream.size(); i++) {
        uniform_int_distribution<int> dist(0, i);
        int j = dist(rng);
        if (j < k) result[j] = stream[i];  // Replace with probability k/(i+1)
    }
    return result;
}

void demoReservoirSampling() {
    cout << "=== Reservoir Sampling ===" << endl;
    vector<int> stream;
    for (int i = 1; i <= 20; i++) stream.push_back(i);
    auto sample = reservoirSampling(stream, 5);
    cout << "Stream: 1..20, Sample of 5: ";
    for (int x : sample) cout << x << " ";
    cout << endl << endl;
}

// ============================================================
// RANDOMIZED QUICKSELECT
// Random pivot avoids worst-case O(n^2) of standard quickselect.
// Expected time: O(n).
// ============================================================

int randomizedPartition(vector<int>& arr, int low, int high) {
    mt19937 rng(42);
    uniform_int_distribution<int> dist(low, high);
    int pivotIdx = dist(rng);
    swap(arr[pivotIdx], arr[high]);

    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= arr[high]) swap(arr[i++], arr[j]);
    }
    swap(arr[i], arr[high]);
    return i;
}

int randomizedQuickselect(vector<int>& arr, int k, int low, int high) {
    while (low <= high) {
        int pivot = randomizedPartition(arr, low, high);
        if (pivot == k) return arr[pivot];
        else if (pivot < k) low = pivot + 1;
        else high = pivot - 1;
    }
    return -1;
}

void demoRandomizedQuickselect() {
    cout << "=== Randomized Quickselect ===" << endl;
    vector<int> arr = {7, 10, 4, 3, 20, 15};
    cout << "Array: "; for (int x : arr) cout << x << " "; cout << endl;
    cout << "3rd smallest: " << randomizedQuickselect(arr, 2, 0, arr.size() - 1) << endl;  // 7
    cout << endl;
}

// ============================================================
// SKIP LIST (Concept)
// Probabilistic data structure for O(log n) search, like balanced BST.
// Each node has random height; higher nodes form "express lanes".
// P(height = k) = (1/2)^k, expected height = 2.
// ============================================================

void demoSkipList() {
    cout << "=== Skip List (Concept) ===" << endl;
    cout << "A skip list is a probabilistic alternative to balanced trees." << endl;
    cout << "Structure: multiple linked lists, each a 'subsample' of the one below." << endl;
    cout << "Search: O(log n) expected, Insert/Delete: O(log n) expected." << endl;
    cout << "Key advantage: simpler to implement than AVL/Red-Black trees." << endl;
    cout << endl;
}

// ============================================================
// BLOOM FILTER (Concept)
// Probabilistic set membership test.
// May return false positives, but NEVER false negatives.
// Space-efficient: O(k * m/k) bits for m elements.
// ============================================================

void demoBloomFilter() {
    cout << "=== Bloom Filter (Concept) ===" << endl;
    cout << "A Bloom filter uses k hash functions to map items to a bit array." << endl;
    cout << "Insert: set k bits. Query: check k bits." << endl;
    cout << "If any bit is 0 => definitely NOT in set." << endl;
    cout << "If all bits are 1 => probably in set (may be false positive)." << endl;
    cout << "Used in: databases, caches, spell checkers, blockchain." << endl;
    cout << endl;
}

// ============================================================
// LINEARITY OF EXPECTATION APPLICATION
// Hat check problem: n people, n hats, random redistribution.
// Expected number of people who get their own hat = 1 (always!).
// ============================================================

void demoHatCheck() {
    cout << "=== Hat Check Problem (Linearity of Expectation) ===" << endl;
    cout << "n people randomly receive n hats. Expected # who get own hat:" << endl;
    for (int n : {1, 2, 5, 10, 100}) {
        // E[X] = sum of E[X_i] = n * (1/n) = 1
        cout << "  n=" << setw(3) << n << ": E[X] = 1.0" << endl;
    }
    cout << endl;
}

// ============================================================
// BIRTHDAY PARADOX
// In a group of 23 people, P(at least 2 share birthday) > 50%.
// P(no shared) = 365/365 * 364/365 * ... * (365-n+1)/365
// ============================================================

double birthdayParadox(int n) {
    double pNoShared = 1.0;
    for (int i = 0; i < n; i++)
        pNoShared *= (365.0 - i) / 365.0;
    return 1.0 - pNoShared;  // P(at least one shared)
}

void demoBirthdayParadox() {
    cout << "=== Birthday Paradox ===" << endl;
    cout << fixed << setprecision(4);
    for (int n : {5, 10, 15, 20, 23, 30, 50})
        cout << "  n=" << setw(2) << n << ": P(shared birthday) = "
             << birthdayParadox(n) << endl;
    cout << endl;
}

// ============================================================
// VARIANCE AND STANDARD DEVIATION
// Var(X) = E[X^2] - (E[X])^2
// StdDev = sqrt(Var)
// ============================================================

double mean(const vector<double>& data) {
    double sum = 0;
    for (double x : data) sum += x;
    return sum / data.size();
}

double variance(const vector<double>& data) {
    double m = mean(data);
    double var = 0;
    for (double x : data) var += (x - m) * (x - m);
    return var / data.size();
}

void demoStatistics() {
    cout << "=== Variance and Standard Deviation ===" << endl;
    vector<double> data = {2, 4, 4, 4, 5, 5, 7, 9};
    cout << "Data: "; for (double x : data) cout << x << " "; cout << endl;
    cout << "Mean = " << mean(data) << endl;           // 5
    cout << "Variance = " << variance(data) << endl;   // 4
    cout << "Std Dev = " << sqrt(variance(data)) << endl;  // 2
    cout << endl;
}

// ============================================================
// PROBABILITY DISTRIBUTION - Binomial
// P(k successes in n trials) = C(n,k) * p^k * (1-p)^(n-k)
// E[X] = np, Var(X) = np(1-p)
// ============================================================

double binomialProb(int n, int k, double p) {
    // C(n, k) * p^k * (1-p)^(n-k)
    long long nCr = 1;
    for (int i = 0; i < k; i++) nCr = nCr * (n - i) / (i + 1);
    return nCr * pow(p, k) * pow(1 - p, n - k);
}

void demoBinomial() {
    cout << "=== Binomial Distribution ===" << endl;
    cout << "n=10 coin flips, P(exactly k heads), p=0.5:" << endl;
    cout << fixed << setprecision(4);
    for (int k : {0, 3, 5, 7, 10})
        cout << "  k=" << setw(2) << k << ": P = " << binomialProb(10, k, 0.5) << endl;
    cout << "E[X] = np = " << 10 * 0.5 << ", Var = np(1-p) = " << 10 * 0.5 * 0.5 << endl;
    cout << endl;
}

int main() {
    demoBasicProbability();
    demoBayes();
    demoExpectedValue();
    demoExpectedTrials();
    demoMonteCarloPI();
    demoReservoirSampling();
    demoRandomizedQuickselect();
    demoSkipList();
    demoBloomFilter();
    demoHatCheck();
    demoBirthdayParadox();
    demoStatistics();
    demoBinomial();
    return 0;
}
