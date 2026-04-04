// 04 - Count Set Bits (3 Methods)
// Loop method, Brian Kernighan's algorithm, __builtin_popcount
// Compare efficiency of each approach

#include <iostream>

using namespace std;

// Print binary representation
void printBinary(int n, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// Method 1: Check Each Bit (O(number of bits))
// Check LSB, shift right, repeat until n becomes 0
// Time: O(bits) = O(32) for 32-bit integers
// ============================================================
int countBitsLoop(int n) {
    int count = 0;
    while (n > 0) {
        count += (n & 1);  // Add LSB to count
        n >>= 1;            // Shift right
    }
    return count;
}

void demoLoopMethod() {
    cout << "=== Method 1: Loop (Check Each Bit) ===" << endl;
    cout << "  Approach: check LSB, shift right, repeat" << endl;
    cout << "  Time: O(number of bits) = O(32) for int" << endl;
    cout << endl;

    int n = 13;  // 0b1101
    cout << "  Counting set bits in " << n << ": ";
    printBinary(n, 8);
    cout << endl;

    int temp = n;
    int step = 0;
    while (temp > 0) {
        step++;
        int lsb = temp & 1;
        cout << "    Step " << step << ": LSB=" << lsb;
        temp >>= 1;
        cout << ", remaining: ";
        printBinary(temp, 8);
        cout << endl;
    }
    cout << "  Result: " << countBitsLoop(n) << " set bits" << endl;
    cout << endl;
}

// ============================================================
// Method 2: Brian Kernighan's Algorithm (O(set bits))
// Uses n & (n-1) to clear the lowest set bit each iteration.
// Runs once per SET bit, not per total bit.
// Time: O(number of set bits) - faster when bits are sparse
// ============================================================
int countBitsKernighan(int n) {
    int count = 0;
    while (n > 0) {
        n &= (n - 1);  // Clear lowest set bit
        count++;
    }
    return count;
}

void demoKernighan() {
    cout << "=== Method 2: Brian Kernighan's Algorithm ===" << endl;
    cout << "  Approach: n & (n-1) clears lowest set bit" << endl;
    cout << "  Time: O(number of SET bits) - faster for sparse bits" << endl;
    cout << endl;

    int n = 13;  // 0b1101
    cout << "  Counting set bits in " << n << ": ";
    printBinary(n, 8);
    cout << endl;

    int temp = n;
    int step = 0;
    while (temp > 0) {
        step++;
        int prev = temp;
        temp = temp & (temp - 1);
        cout << "    Step " << step << ": ";
        printBinary(prev, 8);
        cout << " -> ";
        printBinary(temp, 8);
        cout << " (cleared one bit)" << endl;
    }
    cout << "  Result: " << countBitsKernighan(n) << " set bits" << endl;
    cout << endl;
}

// ============================================================
// Method 3: __builtin_popcount (O(1) via CPU instruction)
// GCC/Clang compiler intrinsic that maps to hardware instruction
// ============================================================
int countBitsBuiltin(int n) {
    return __builtin_popcount(n);
}

void demoBuiltin() {
    cout << "=== Method 3: __builtin_popcount (CPU Instruction) ===" << endl;
    cout << "  Approach: uses hardware POPCOUNT instruction" << endl;
    cout << "  Time: O(1) - single CPU instruction" << endl;
    cout << endl;

    int n = 13;
    cout << "  __builtin_popcount(" << n << ") = " << countBitsBuiltin(n) << endl;
    cout << "  Note: GCC/Clang only; use __popcnt for MSVC" << endl;
    cout << endl;
}

// ============================================================
// Compare all three methods on multiple inputs
// ============================================================
void compareMethods() {
    cout << "=== Comparison of All Methods ===" << endl;

    int i;
    int testValues[] = {0, 1, 3, 7, 15, 31, 127, 255, 1023};
    int numTests = 9;

    cout << "  Value  | Binary   | Loop | Kernighan | Builtin" << endl;
    cout << "  -------|----------|------|-----------|--------" << endl;

    for (i = 0; i < numTests; i++) {
        int val = testValues[i];
        int r1 = countBitsLoop(val);
        int r2 = countBitsKernighan(val);
        int r3 = countBitsBuiltin(val);

        cout << "  ";
        if (val < 10) cout << " ";
        cout << val << "    | ";
        printBinary(val, 8);
        cout << "  |  " << r1 << "   |     " << r2 << "       |    " << r3 << endl;
    }
    cout << endl;

    cout << "  Efficiency comparison:" << endl;
    cout << "    Loop:       32 iterations worst case (all bits set)" << endl;
    cout << "    Kernighan:  at most 32, but equals # of set bits" << endl;
    cout << "    Builtin:    1 CPU instruction (fastest)" << endl;
    cout << endl;

    // Show iteration difference
    int sparse = 1 << 30;  // Only 1 bit set in 32-bit number
    cout << "  For " << sparse << " (only 1 bit set in 32 bits):" << endl;
    cout << "    Loop:       32 iterations needed" << endl;
    cout << "    Kernighan:  1 iteration needed (much faster)" << endl;
    cout << "    Builtin:    1 CPU instruction" << endl;
    cout << endl;
}

int main() {
    cout << "=== 04 - Count Set Bits ===" << endl;
    cout << endl;

    demoLoopMethod();
    demoKernighan();
    demoBuiltin();
    compareMethods();

    cout << "--- Summary ---" << endl;
    cout << "Loop:         check LSB, shift, repeat  -> O(32)" << endl;
    cout << "Kernighan's:  n & (n-1) each iteration   -> O(set bits)" << endl;
    cout << "Builtin:      __builtin_popcount(n)      -> O(1)" << endl;
    cout << "Best choice:  __builtin_popcount for speed, Kernighan for portability" << endl;

    return 0;
}
