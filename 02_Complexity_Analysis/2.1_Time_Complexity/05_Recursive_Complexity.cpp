/*
 * File: 05_Recursive_Complexity.cpp
 * Topic: Time complexity of recursive functions
 * Description: Counting recursive calls, recurrence relations
 */
#include <iostream>
using namespace std;

// O(n) recursion - reduces by 1 each call
int linearRecursion(int n) {
    if (n <= 0) return 0;
    return 1 + linearRecursion(n - 1);
}

// O(log n) recursion - divides by 2 each call
int logarithmicRecursion(int n) {
    if (n <= 0) return 0;
    return 1 + logarithmicRecursion(n / 2);
}

// O(2^n) recursion - branches into 2 calls
int fibonacci(int n) {
    if (n <= 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Count and print recursive calls
int callCount = 0;

int fibWithCount(int n) {
    callCount++;
    if (n <= 1) return 1;
    return fibWithCount(n - 1) + fibWithCount(n - 2);
}

int main() {
    cout << "=== Recursive Time Complexity ===" << endl;
    cout << endl;

    // O(n) - Linear recursion
    cout << "--- O(n) - Linear Recursion ---" << endl;
    cout << "  int f(n) { return 1 + f(n-1); }" << endl;
    cout << "  n calls, each does O(1) work" << endl;
    cout << "  Total: O(n)" << endl;
    cout << "  f(5) = " << linearRecursion(5) << endl;
    cout << endl;

    // O(log n) - Logarithmic recursion
    cout << "--- O(log n) - Logarithmic Recursion ---" << endl;
    cout << "  int f(n) { return 1 + f(n/2); }" << endl;
    cout << "  Halves each time -> log n calls" << endl;
    cout << "  Total: O(log n)" << endl;
    cout << "  f(1000) = " << logarithmicRecursion(1000) << " steps" << endl;
    cout << endl;

    // O(2^n) - Exponential recursion
    cout << "--- O(2^n) - Exponential Recursion ---" << endl;
    cout << "  int fib(n) { return fib(n-1) + fib(n-2); }" << endl;
    cout << "  Each call makes 2 more calls -> 2^n" << endl;

    for (int i = 0; i <= 10; i++) {
        callCount = 0;
        fibWithCount(i);
        cout << "  fib(" << i << ") = " << callCount << " calls" << endl;
    }

    cout << endl;
    cout << "--- How to Analyze Recursion ---" << endl;
    cout << "1. Count number of recursive calls per level" << endl;
    cout << "2. Count depth of recursion tree" << endl;
    cout << "3. Total = (branches)^(depth)" << endl;
    cout << endl;
    cout << "f(n) -> f(n-1)       : 1 branch, depth n  -> O(n)" << endl;
    cout << "f(n) -> f(n/2)       : 1 branch, depth log n -> O(log n)" << endl;
    cout << "f(n) -> f(n-1)+f(n-2): 2 branches, depth n -> O(2^n)" << endl;

    return 0;
}
