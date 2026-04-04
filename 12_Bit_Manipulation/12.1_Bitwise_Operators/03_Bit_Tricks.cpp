// 03 - Bit Tricks
// n&(n-1) clear lowest bit, n&(-n) isolate lowest bit,
// power of two check, isOdd check

#include <iostream>

using namespace std;

// Print binary representation
void printBinary(int n, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// Trick 1: n & (n-1) clears the lowest set bit
// Why it works: subtracting 1 flips all bits from the lowest
// set bit to the right. AND with original clears that bit.
// ============================================================
void demoClearLowestBit() {
    cout << "=== Trick 1: n & (n-1) Clear Lowest Set Bit ===" << endl;

    int n = 12;  // 0b00001100
    cout << "  n = " << n << " = ";
    printBinary(n, 8);
    cout << endl;

    cout << "  n-1 = " << (n - 1) << " = ";
    printBinary(n - 1, 8);
    cout << endl;

    int result = n & (n - 1);
    cout << "  n & (n-1) = " << result << " = ";
    printBinary(result, 8);
    cout << "  (bit 2 cleared)" << endl;
    cout << endl;

    // Multiple applications to count set bits
    int val = 15;  // 0b1111
    cout << "  Repeated application on " << val << " (0b1111):" << endl;
    int temp = val;
    int step = 0;
    while (temp) {
        step++;
        int prev = temp;
        temp = temp & (temp - 1);
        cout << "    Step " << step << ": ";
        printBinary(prev, 8);
        cout << " -> ";
        printBinary(temp, 8);
        cout << " (" << temp << ")" << endl;
    }
    cout << "  Total " << step << " set bits in " << val << endl;
    cout << endl;
}

// ============================================================
// Trick 2: n & (-n) isolates the lowest set bit
// Why it works: -n = ~n + 1 (two's complement)
// This flips all bits above the lowest set bit, so AND keeps
// only that single bit.
// ============================================================
void demoIsolateLowestBit() {
    cout << "=== Trick 2: n & (-n) Isolate Lowest Set Bit ===" << endl;

    int n = 12;  // 0b00001100
    cout << "  n    = " << n << " = ";
    printBinary(n, 8);
    cout << endl;

    cout << "  -n   = " << (-n) << " = ";
    printBinary(-n, 8);
    cout << endl;

    int result = n & (-n);
    cout << "  n & (-n) = " << result << " = ";
    printBinary(result, 8);
    cout << "  (isolated bit 2, value 4)" << endl;
    cout << endl;

    // More examples
    int i;
    int values[] = {6, 8, 10, 15, 32};
    int numValues = 5;

    cout << "  More examples:" << endl;
    for (i = 0; i < numValues; i++) {
        int val = values[i];
        int isolated = val & (-val);
        cout << "    " << val << " & " << (-val) << " = " << isolated;
        cout << "  (bit position ";
        // Find position: count trailing zeros
        int pos = 0;
        while ((isolated & 1) == 0) {
            pos++;
            isolated >>= 1;
        }
        cout << pos << ")" << endl;
    }
    cout << endl;
}

// ============================================================
// Trick 3: Power of Two Check
// A power of two has exactly one bit set.
// So: n > 0 && (n & (n-1)) == 0
// ============================================================
int isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

void demoPowerOfTwo() {
    cout << "=== Trick 3: Power of Two Check ===" << endl;

    int i;
    int testValues[] = {1, 2, 3, 4, 7, 8, 16, 31, 32, 64, 100, 1024, 0, -4};
    int numTests = 14;

    for (i = 0; i < numTests; i++) {
        int val = testValues[i];
        const char* result = isPowerOfTwo(val) ? "Yes" : "No";
        cout << "  Is " << val << " a power of 2? " << result << endl;
    }
    cout << endl;

    // Why it works
    cout << "  Why it works:" << endl;
    cout << "  8  = 0b00001000 (one bit set)" << endl;
    cout << "  7  = 0b00000111 (n-1 flips all below the set bit)" << endl;
    cout << "  8&7 = 0b00000000 (zero means power of 2)" << endl;
    cout << endl;
}

// ============================================================
// Trick 4: Check if Odd
// An odd number always has bit 0 set: (n & 1) == 1
// ============================================================
int isOdd(int n) {
    return (n & 1) == 1;
}

void demoIsOdd() {
    cout << "=== Trick 4: Check if Odd ===" << endl;

    int i;
    int values[] = {0, 1, 2, 3, 7, 10, 15, 100, -3, -4};
    int numValues = 10;

    for (i = 0; i < numValues; i++) {
        int val = values[i];
        cout << "  Is " << val << " odd? " << (isOdd(val) ? "Yes" : "No") << endl;
    }
    cout << endl;

    cout << "  Why: odd numbers have bit 0 set:" << endl;
    cout << "  3 = 0b00000011  (bit 0 is 1) -> odd" << endl;
    cout << "  4 = 0b00000100  (bit 0 is 0) -> even" << endl;
    cout << endl;
}

int main() {
    cout << "=== 03 - Bit Tricks ===" << endl;
    cout << endl;

    demoClearLowestBit();
    demoIsolateLowestBit();
    demoPowerOfTwo();
    demoIsOdd();

    cout << "--- Summary ---" << endl;
    cout << "n & (n-1)  : clears the lowest set bit" << endl;
    cout << "n & (-n)   : isolates the lowest set bit" << endl;
    cout << "Power of 2 : n > 0 && (n & (n-1)) == 0" << endl;
    cout << "Is odd     : (n & 1) == 1" << endl;

    return 0;
}
