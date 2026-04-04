// 06 - Advanced Bit Tricks
// Multiply/divide by power of 2, abs without branching,
// opposite signs check, next power of 2, round up

#include <iostream>

using namespace std;

// Print binary representation
void printBinary(int n, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// Trick 1: Multiply by power of 2 using left shift
// x * 2^k = x << k
// ============================================================
int multiplyByPowerOf2(int x, int k) {
    return x << k;
}

void demoMultiplyByPowerOf2() {
    cout << "=== Trick 1: Multiply by Power of 2 ===" << endl;

    int x = 7;
    int k;
    for (k = 0; k <= 4; k++) {
        int shifted = multiplyByPowerOf2(x, k);
        int regular = x * (1 << k);
        cout << "  " << x << " << " << k << " = " << shifted;
        cout << "  (" << x << " * " << (1 << k) << " = " << regular << ")" << endl;
    }
    cout << endl;
}

// ============================================================
// Trick 2: Divide by power of 2 using right shift
// x / 2^k = x >> k  (integer division, truncates toward negative)
// ============================================================
int divideByPowerOf2(int x, int k) {
    return x >> k;
}

void demoDivideByPowerOf2() {
    cout << "=== Trick 2: Divide by Power of 2 ===" << endl;

    int x = 100;
    int k;
    for (k = 0; k <= 3; k++) {
        int shifted = divideByPowerOf2(x, k);
        int regular = x / (1 << k);
        cout << "  " << x << " >> " << k << " = " << shifted;
        cout << "  (" << x << " / " << (1 << k) << " = " << regular << ")" << endl;
    }
    cout << endl;

    // Note: truncation behavior
    int odd = 15;
    cout << "  Odd number division: " << odd << " >> 1 = " << (odd >> 1);
    cout << "  (truncates, " << odd << " / 2 = " << (odd / 2) << ")" << endl;
    cout << endl;
}

// ============================================================
// Trick 3: Absolute value without branching
// Uses the sign bit as a mask.
// For 32-bit int: mask = x >> 31
//   If x >= 0: mask = 0, result = x ^ 0 - 0 = x
//   If x < 0:  mask = -1 (all 1s), result = (x + -1) ^ -1 = ~ (x - 1) = -x
// ============================================================
int absVal(int x) {
    int mask = x >> 31;      // 0 if positive, -1 if negative
    return (x + mask) ^ mask;
}

void demoAbsVal() {
    cout << "=== Trick 3: Absolute Value Without Branching ===" << endl;

    int values[] = {7, -7, 0, 42, -42};
    int numValues = 5;
    int i;

    for (i = 0; i < numValues; i++) {
        int val = values[i];
        cout << "  absVal(" << val << ") = " << absVal(val);

        // Show the steps for negative numbers
        if (val < 0) {
            int mask = val >> 31;
            cout << "  (mask=" << mask << ", (x+mask)=" << (val + mask);
            cout << ", result=" << ((val + mask) ^ mask) << ")";
        }
        cout << endl;
    }
    cout << endl;
}

// ============================================================
// Trick 4: Check if two numbers have opposite signs
// XOR of two numbers with different signs is negative
// (because the sign bits differ, making the result's sign bit 1)
// ============================================================
int oppositeSigns(int a, int b) {
    return (a ^ b) < 0;
}

void demoOppositeSigns() {
    cout << "=== Trick 4: Opposite Signs Check ===" << endl;

    int aVals[] = {5, -3, 0, -10, 7};
    int bVals[] = {-3, 7, 5, -5, 0};
    int numTests = 5;
    int i;

    for (i = 0; i < numTests; i++) {
        int a = aVals[i];
        int b = bVals[i];
        int result = oppositeSigns(a, b);
        const char* desc = result ? "Yes" : "No";
        cout << "  oppositeSigns(" << a << ", " << b << ") = " << desc;
        cout << "  (a^b = " << (a ^ b) << ")" << endl;
    }
    cout << endl;
}

// ============================================================
// Trick 5: Next power of 2
// Round up to the smallest power of 2 >= n.
// Uses bit propagation: fill all bits below the highest set bit,
// then add 1.
// ============================================================
int nextPowerOfTwo(int n) {
    if (n <= 0) return 1;
    if (n == 1) return 2;

    n--;  // Handle exact power of 2 case
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

void demoNextPowerOfTwo() {
    cout << "=== Trick 5: Next Power of 2 ===" << endl;

    int values[] = {3, 5, 7, 8, 13, 16, 17, 31, 32, 100};
    int numValues = 10;
    int i;

    for (i = 0; i < numValues; i++) {
        int val = values[i];
        int result = nextPowerOfTwo(val);
        cout << "  nextPowerOfTwo(" << val << ") = " << result << endl;
    }
    cout << endl;

    // Show how it works for 5
    cout << "  How it works for 5:" << endl;
    int n = 5;
    cout << "    n = "; printBinary(n, 8); cout << " (" << n << ")" << endl;
    n--;
    cout << "    n-1 = "; printBinary(n, 8); cout << " (" << n << ")" << endl;
    n |= n >> 1;
    cout << "    | >>1 = "; printBinary(n, 8); cout << " (" << n << ")" << endl;
    n |= n >> 2;
    cout << "    | >>2 = "; printBinary(n, 8); cout << " (" << n << ")" << endl;
    // Further shifts don't change it for small numbers
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    cout << "    + 1   = "; printBinary(n, 8); cout << " (" << n << ")" << endl;
    cout << endl;
}

// ============================================================
// Trick 6: Check if number is odd
// (n & 1) == 1  -> odd
// ============================================================
int isOdd(int n) {
    return (n & 1) == 1;
}

void demoIsOdd() {
    cout << "=== Trick 6: Check if Odd ===" << endl;

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int numValues = 8;
    int i;

    for (i = 0; i < numValues; i++) {
        int val = values[i];
        cout << "  " << val << " is odd? " << (isOdd(val) ? "Yes" : "No") << endl;
    }
    cout << endl;
}

// ============================================================
// Trick 7: Round up to multiple of a power of 2
// To round n up to the next multiple of 2^k:
//   (n + (2^k - 1)) & ~(2^k - 1)
// ============================================================
int roundUpToPowerOf2(int n, int k) {
    int multiple = 1 << k;
    return (n + multiple - 1) & ~(multiple - 1);
}

void demoRoundUp() {
    cout << "=== Trick 7: Round Up to Multiple of Power of 2 ===" << endl;

    int k = 4;  // Round up to multiple of 16
    int values[] = {1, 15, 16, 17, 31, 32, 33};
    int numValues = 7;
    int i;

    for (i = 0; i < numValues; i++) {
        int val = values[i];
        int result = roundUpToPowerOf2(val, k);
        cout << "  roundUp(" << val << ", multiple of " << (1 << k) << ") = " << result << endl;
    }
    cout << endl;
}

int main() {
    cout << "=== 06 - Advanced Bit Tricks ===" << endl;
    cout << endl;

    demoMultiplyByPowerOf2();
    demoDivideByPowerOf2();
    demoAbsVal();
    demoOppositeSigns();
    demoNextPowerOfTwo();
    demoIsOdd();
    demoRoundUp();

    cout << "--- Summary ---" << endl;
    cout << "Multiply by 2^k : x << k" << endl;
    cout << "Divide by 2^k   : x >> k (integer division)" << endl;
    cout << "Absolute value  : (x + mask) ^ mask, mask = x >> 31" << endl;
    cout << "Opposite signs  : (a ^ b) < 0" << endl;
    cout << "Next power of 2 : propagate bits, then + 1" << endl;
    cout << "Is odd          : (n & 1) == 1" << endl;
    cout << "Round up to 2^k : (n + 2^k - 1) & ~(2^k - 1)" << endl;

    return 0;
}
