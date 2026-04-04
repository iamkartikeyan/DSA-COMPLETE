/*
 * File: 02_Common_Complexities.cpp
 * Topic: All common time complexities with examples
 * Description: O(1), O(log n), O(n), O(n log n), O(n^2), O(2^n), O(n!)
 */
#include <iostream>
using namespace std;

// O(1) - Constant time
void constantTime() {
    cout << "O(1): Access arr[0]" << endl;
    int arr[5] = {10, 20, 30, 40, 50};
    cout << "  arr[0] = " << arr[0] << endl;
    cout << "  arr[4] = " << arr[4] << endl;
    cout << "  Both take SAME time regardless of array size" << endl;
}

// O(log n) - Logarithmic time
void logarithmicTime(int n) {
    int count = 0;
    int i = n;
    while (i > 1) {
        i = i / 2;
        count++;
    }
    cout << "O(log n): " << count << " steps to reduce " << n << " to 1" << endl;
    cout << "  Halving each time: n -> n/2 -> n/4 -> ... -> 1" << endl;
}

// O(n) - Linear time
void linearTime(int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count++;
    }
    cout << "O(n): " << count << " iterations for n=" << n << endl;
}

// O(n log n) - Linearithmic time
void linearithmicTime(int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = n; j > 1; j = j / 2) {
            count++;
        }
    }
    cout << "O(n log n): " << count << " iterations for n=" << n << endl;
}

// O(n^2) - Quadratic time
void quadraticTime(int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count++;
        }
    }
    cout << "O(n^2): " << count << " iterations for n=" << n << endl;
}

// O(2^n) - Exponential time
int exponentialTime(int n) {
    if (n <= 1) return 1;
    return exponentialTime(n - 1) + exponentialTime(n - 2);
}

// O(n!) - Factorial time
int factorialTime(int n) {
    if (n <= 1) return 1;
    return n * factorialTime(n - 1);
}

int main() {
    cout << "=== Common Time Complexities ===" << endl;
    cout << endl;

    int n = 10;

    cout << "--- O(1) - Constant ---" << endl;
    constantTime();
    cout << endl;

    cout << "--- O(log n) - Logarithmic ---" << endl;
    logarithmicTime(n);
    cout << "  Example: Binary search" << endl;
    cout << endl;

    cout << "--- O(n) - Linear ---" << endl;
    linearTime(n);
    cout << "  Example: Linear search, finding max" << endl;
    cout << endl;

    cout << "--- O(n log n) - Linearithmic ---" << endl;
    linearithmicTime(n);
    cout << "  Example: Merge sort, Quick sort (avg)" << endl;
    cout << endl;

    cout << "--- O(n^2) - Quadratic ---" << endl;
    quadraticTime(n);
    cout << "  Example: Bubble sort, Selection sort" << endl;
    cout << endl;

    cout << "--- O(2^n) - Exponential ---" << endl;
    cout << "O(2^" << n << ") = " << exponentialTime(n) << " calls" << endl;
    cout << "  Example: Recursive Fibonacci" << endl;
    cout << endl;

    cout << "--- O(n!) - Factorial ---" << endl;
    cout << n << "! = " << factorialTime(n) << endl;
    cout << "  Example: Generating all permutations" << endl;

    cout << endl;
    cout << "--- Hierarchy (Best to Worst) ---" << endl;
    cout << "O(1) < O(log n) < O(n) < O(n log n) < O(n^2) < O(2^n) < O(n!)" << endl;

    return 0;
}
