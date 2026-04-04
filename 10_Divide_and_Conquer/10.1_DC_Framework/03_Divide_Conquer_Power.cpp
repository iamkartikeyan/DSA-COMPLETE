// ============================================================
// 03_Divide_Conquer_Power.cpp
// Compute x^n in O(log n) using Divide and Conquer
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// PROBLEM: Compute x raised to the power n
//
// Naive approach: multiply x by itself n times => O(n)
// D&C approach: divide n by 2 each step => O(log n)
//
// Key idea:
//   x^n = x^(n/2) * x^(n/2)          when n is even
//   x^n = x * x^(n/2) * x^(n/2)      when n is odd
//
// This halves the exponent at each step, giving O(log n) time.
//
// Recurrence: T(n) = T(n/2) + O(1)
// By Master Theorem: T(n) = O(log n)
// ============================================================

// -----------------------------------------------------------
// Compute x^n for positive n (integer result for integer base)
// Works for integer exponents only.
// -----------------------------------------------------------

int power(int x, int n)
{
    // Base case
    if (n == 0)
    {
        return 1;
    }

    // Divide: compute x^(n/2)
    int half = power(x, n / 2);

    // Conquer and Combine
    if (n % 2 == 0)
    {
        // n is even: x^n = x^(n/2) * x^(n/2)
        return half * half;
    }
    else
    {
        // n is odd: x^n = x * x^(n/2) * x^(n/2)
        return x * half * half;
    }
}

// -----------------------------------------------------------
// Compute x^n for negative n (returns double)
// x^(-n) = 1 / x^n
// -----------------------------------------------------------

double powerWithNegative(int x, int n)
{
    // Handle negative exponent
    if (n < 0)
    {
        return 1.0 / (double)power(x, -n);
    }
    return (double)power(x, n);
}

// -----------------------------------------------------------
// Iterative version of D&C power (also O(log n))
// Sometimes called "binary exponentiation" or "exponentiation
// by squaring"
// -----------------------------------------------------------

int powerIterative(int x, int n)
{
    int result = 1;

    while (n > 0)
    {
        // If n is odd, multiply result by x
        if (n % 2 == 1)
        {
            result = result * x;
        }

        // Square the base
        x = x * x;

        // Halve the exponent
        n = n / 2;
    }

    return result;
}

// ============================================================

int main()
{
    cout << "============================================" << endl;
    cout << "  Divide and Conquer Power: x^n in O(log n)" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- Example 1: Basic powers ---
    int base = 2;
    int exp = 10;

    cout << "Example 1: " << base << "^" << exp << endl;
    cout << "  D&C Power: " << power(base, exp) << endl;
    cout << "  Iterative: " << powerIterative(base, exp) << endl;
    cout << "  Expected:  " << 1024 << endl;
    cout << endl;

    // --- Example 2: Another power ---
    base = 3;
    exp = 5;

    cout << "Example 2: " << base << "^" << exp << endl;
    cout << "  D&C Power: " << power(base, exp) << endl;
    cout << "  Iterative: " << powerIterative(base, exp) << endl;
    cout << "  Expected:  " << 243 << endl;
    cout << endl;

    // --- Example 3: Power of 0 ---
    base = 5;
    exp = 0;

    cout << "Example 3: " << base << "^" << exp << endl;
    cout << "  D&C Power: " << power(base, exp) << endl;
    cout << "  Expected:  " << 1 << endl;
    cout << endl;

    // --- Example 4: Negative exponent ---
    base = 2;
    exp = -3;

    cout << "Example 4: " << base << "^(" << exp << ")" << endl;
    cout << "  D&C Power (negative): " << powerWithNegative(base, exp) << endl;
    cout << "  Expected:  " << 0.125 << endl;
    cout << endl;

    // --- Example 5: Negative base with positive exponent ---
    base = -2;
    exp = 4;

    cout << "Example 5: (" << base << ")^" << exp << endl;
    cout << "  D&C Power: " << power(base, exp) << endl;
    cout << "  Expected:  " << 16 << endl;
    cout << endl;

    // --- Comparison of approaches ---
    cout << "============================================" << endl;
    cout << "  Approach Comparison" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Naive:  multiply x, n times        => O(n)" << endl;
    cout << "D&C:    halve exponent each step     => O(log n)" << endl;
    cout << endl;
    cout << "For n = 1024:" << endl;
    cout << "  Naive: 1024 multiplications" << endl;
    cout << "  D&C:   ~10 multiplications (log2(1024) = 10)" << endl;
    cout << endl;

    // --- Recurrence relation ---
    cout << "============================================" << endl;
    cout << "  Recurrence" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "T(n) = T(n/2) + O(1)" << endl;
    cout << "  a = 1, b = 2, d = 0" << endl;
    cout << "  b^d = 2^0 = 1" << endl;
    cout << "  a == b^d  =>  Master Theorem Case 2" << endl;
    cout << "  T(n) = O(n^0 * log(n)) = O(log n)" << endl;

    return 0;
}
