/*
 * File: 03_Recursion_Stack_Space.cpp
 * Topic: Space complexity of recursive functions
 * Description: Call stack depth = space complexity
 */
#include <iostream>
using namespace std;

// O(n) stack space - depth = n
void linearRecursion(int n) {
    if (n <= 0) {
        cout << "  Base case reached" << endl;
        return;
    }
    cout << "  Call with n=" << n << endl;
    linearRecursion(n - 1);
}

// O(log n) stack space - depth = log n
void logarithmicRecursion(int n) {
    if (n <= 0) {
        cout << "  Base case reached" << endl;
        return;
    }
    cout << "  Call with n=" << n << endl;
    logarithmicRecursion(n / 2);
}

// O(n) stack space - depth = n (even though time = O(2^n))
int fibonacci(int n) {
    if (n <= 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    cout << "=== Recursion Stack Space ===" << endl;
    cout << endl;

    // O(n) stack
    cout << "--- O(n) Stack Space ---" << endl;
    cout << "void f(n) { f(n-1); }" << endl;
    cout << "Each call waits for next to return." << endl;
    cout << "Stack depth = n" << endl;
    linearRecursion(4);
    cout << endl;

    // O(log n) stack
    cout << "--- O(log n) Stack Space ---" << endl;
    cout << "void f(n) { f(n/2); }" << endl;
    cout << "Halves each time -> depth = log n" << endl;
    logarithmicRecursion(16);
    cout << endl;

    cout << "--- Fibonacci Stack ---" << endl;
    cout << "fib(4) calls:" << endl;
    cout << "  fib(4)" << endl;
    cout << "  -> fib(3)" << endl;
    cout << "     -> fib(2)" << endl;
    cout << "        -> fib(1) returns" << endl;
    cout << "        -> fib(0) returns" << endl;
    cout << "     -> fib(1) returns" << endl;
    cout << "  -> fib(2)" << endl;
    cout << "     -> fib(1) returns" << endl;
    cout << "     -> fib(0) returns" << endl;
    cout << endl;
    cout << "Max stack depth = 4 = O(n)" << endl;
    cout << "But total calls = O(2^n) (time complexity)" << endl;
    cout << endl;

    cout << "--- Key Insight ---" << endl;
    cout << "Space complexity = MAX stack depth at any time" << endl;
    cout << "NOT total number of calls" << endl;
    cout << endl;
    cout << "Algorithm   | Time      | Space (stack)" << endl;
    cout << "------------|-----------|---------------" << endl;
    cout << "f(n) = f(n-1)    | O(n)      | O(n)" << endl;
    cout << "f(n) = f(n/2)    | O(log n)  | O(log n)" << endl;
    cout << "f(n) = f(n-1)+f(n-2) | O(2^n) | O(n)" << endl;
    cout << "Merge sort  | O(n log n)| O(log n)" << endl;
    cout << "Quick sort  | O(n^2)    | O(n) worst" << endl;

    return 0;
}
