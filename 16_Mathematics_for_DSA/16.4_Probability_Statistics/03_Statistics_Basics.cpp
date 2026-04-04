// 16.4.03 - Statistics Basics
// Mean, median, mode calculation.
// Variance and standard deviation.
// Binomial distribution.

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Mean (average)
double mean(double data[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

// Median (middle value after sorting)
// Uses simple bubble sort for small arrays
void sortArray(double arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

double median(double data[], int n) {
    // Make a copy to avoid modifying original
    double* sorted = new double[n];
    for (int i = 0; i < n; i++) {
        sorted[i] = data[i];
    }
    sortArray(sorted, n);

    double result;
    if (n % 2 == 1) {
        result = sorted[n / 2];
    } else {
        result = (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    }
    delete[] sorted;
    return result;
}

// Mode (most frequent value)
// Returns the mode and its frequency
double mode(double data[], int n, int& frequency) {
    double modeVal = data[0];
    frequency = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            double diff = data[i] - data[j];
            if (diff < 0) diff = -diff;
            if (diff < 1e-9) count++;
        }
        if (count > frequency) {
            frequency = count;
            modeVal = data[i];
        }
    }
    return modeVal;
}

// Variance: Var(X) = E[X^2] - (E[X])^2
double variance(double data[], int n) {
    double m = mean(data, n);
    double var = 0;
    for (int i = 0; i < n; i++) {
        double diff = data[i] - m;
        var += diff * diff;
    }
    return var / n;
}

// Standard Deviation = sqrt(Variance)
double stdDev(double data[], int n) {
    return sqrt(variance(data, n));
}

// Binomial distribution: P(k successes in n trials) = C(n,k) * p^k * (1-p)^(n-k)
double binomialProb(int n, int k, double p) {
    // C(n, k)
    long long nCr = 1;
    int r = k;
    if (r > n - r) r = n - r;
    for (int i = 0; i < r; i++) {
        nCr = nCr * (n - i) / (i + 1);
    }
    // p^k * (1-p)^(n-k)
    double pk = 1.0;
    double qk = 1.0;
    for (int i = 0; i < k; i++) pk *= p;
    for (int i = 0; i < n - k; i++) qk *= (1.0 - p);
    return (double)nCr * pk * qk;
}

// Birthday Paradox: P(at least 2 share birthday in n people)
double birthdayParadox(int n) {
    double pNoShared = 1.0;
    for (int i = 0; i < n; i++) {
        pNoShared *= (365.0 - (double)i) / 365.0;
    }
    return 1.0 - pNoShared;
}

int main() {
    cout << fixed << setprecision(4);
    cout << "=== Statistics Basics ===" << endl;

    double data[] = {2, 4, 4, 4, 5, 5, 7, 9};
    int n = 8;

    cout << "Data: ";
    for (int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    // Mean
    cout << endl << "Mean = " << mean(data, n) << endl;  // 5.0

    // Median
    cout << "Median = " << median(data, n) << endl;  // 4.5

    // Mode
    int freq;
    double modeVal = mode(data, n, freq);
    cout << "Mode = " << modeVal << " (appears " << freq << " times)" << endl;  // 4

    // Variance and Std Dev
    cout << endl << "Variance = " << variance(data, n) << endl;  // 4.0
    cout << "Std Dev = " << stdDev(data, n) << endl;  // 2.0

    // Another example
    cout << endl << "=== Another Dataset ===" << endl;
    double data2[] = {10, 20, 30, 40, 50};
    int n2 = 5;
    cout << "Data: ";
    for (int i = 0; i < n2; i++) cout << data2[i] << " ";
    cout << endl;
    cout << "Mean = " << mean(data2, n2) << endl;  // 30
    cout << "Median = " << median(data2, n2) << endl;  // 30
    cout << "Variance = " << variance(data2, n2) << endl;  // 200
    cout << "Std Dev = " << stdDev(data2, n2) << endl;  // ~14.14

    // Binomial Distribution
    cout << endl << "=== Binomial Distribution ===" << endl;
    cout << "n=10 coin flips, P(exactly k heads), p=0.5:" << endl;
    int ks[] = {0, 3, 5, 7, 10};
    int numKs = 5;
    for (int i = 0; i < numKs; i++) {
        cout << "  k=" << ks[i] << ": P = " << binomialProb(10, ks[i], 0.5) << endl;
    }
    cout << "E[X] = np = " << 10 * 0.5 << ", Var = np(1-p) = " << 10 * 0.5 * 0.5 << endl;

    // Birthday Paradox
    cout << endl << "=== Birthday Paradox ===" << endl;
    int people[] = {5, 10, 15, 20, 23, 30, 50};
    int numPeople = 7;
    for (int i = 0; i < numPeople; i++) {
        cout << "  n=" << people[i] << ": P(shared birthday) = "
             << birthdayParadox(people[i]) << endl;
    }

    cout << endl << "Time: O(n) for mean/variance, O(n^2) for mode (unsorted)" << endl;
    cout << "Space: O(n) for median (copy), O(1) for mean/variance" << endl;

    return 0;
}
