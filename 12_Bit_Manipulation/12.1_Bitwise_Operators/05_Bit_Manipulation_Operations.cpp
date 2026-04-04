// 05 - Bit Manipulation Operations
// checkBit, setBit, clearBit, toggleBit functions with demos

#include <iostream>

using namespace std;

// Print binary representation
void printBinary(int n, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// checkBit: Check if the bit at position 'bit' is set
// Returns 1 if set, 0 if not set
// Uses: (n >> bit) & 1  or  (n & (1 << bit)) != 0
// ============================================================
int checkBit(int n, int bit) {
    return (n & (1 << bit)) != 0;
}

// ============================================================
// setBit: Set the bit at position 'bit' to 1
// Uses OR with shifted 1: n | (1 << bit)
// ============================================================
int setBit(int n, int bit) {
    return n | (1 << bit);
}

// ============================================================
// clearBit: Set the bit at position 'bit' to 0
// Uses AND with complement: n & ~(1 << bit)
// ============================================================
int clearBit(int n, int bit) {
    return n & ~(1 << bit);
}

// ============================================================
// toggleBit: Flip the bit at position 'bit'
// Uses XOR with shifted 1: n ^ (1 << bit)
// If bit was 0 -> becomes 1; if 1 -> becomes 0
// ============================================================
int toggleBit(int n, int bit) {
    return n ^ (1 << bit);
}

// ============================================================
// Demo: checkBit
// ============================================================
void demoCheckBit() {
    cout << "=== checkBit ===" << endl;

    int n = 10;  // 0b00001010
    cout << "  n = " << n << " = ";
    printBinary(n, 8);
    cout << endl;
    cout << endl;

    int bit;
    for (bit = 0; bit < 8; bit++) {
        int result = checkBit(n, bit);
        cout << "  checkBit(" << n << ", " << bit << ") = " << result << endl;
    }
    cout << endl;

    // Practical use: check if number is even or odd
    cout << "  Is 10 even? " << (checkBit(10, 0) == 0 ? "Yes" : "No") << endl;
    cout << "  Is 7  even? " << (checkBit(7, 0) == 0 ? "Yes" : "No") << endl;
    cout << endl;
}

// ============================================================
// Demo: setBit
// ============================================================
void demoSetBit() {
    cout << "=== setBit ===" << endl;

    int n = 8;  // 0b00001000
    cout << "  Original: ";
    printBinary(n, 8);
    cout << " (" << n << ")" << endl;
    cout << endl;

    int bits[] = {0, 1, 3};
    int numBits = 3;
    int i;

    for (i = 0; i < numBits; i++) {
        int bit = bits[i];
        int result = setBit(n, bit);
        cout << "  setBit(" << n << ", " << bit << ") = ";
        printBinary(result, 8);
        cout << " (" << result << ")" << endl;
    }
    cout << endl;

    // Setting an already-set bit is a no-op
    cout << "  setBit(8, 3) = " << setBit(8, 3);
    cout << "  (bit 3 already set, no change)" << endl;
    cout << endl;
}

// ============================================================
// Demo: clearBit
// ============================================================
void demoClearBit() {
    cout << "=== clearBit ===" << endl;

    int n = 15;  // 0b00001111
    cout << "  Original: ";
    printBinary(n, 8);
    cout << " (" << n << ")" << endl;
    cout << endl;

    int bits[] = {0, 2, 3};
    int numBits = 3;
    int i;

    for (i = 0; i < numBits; i++) {
        int bit = bits[i];
        int result = clearBit(n, bit);
        cout << "  clearBit(" << n << ", " << bit << ") = ";
        printBinary(result, 8);
        cout << " (" << result << ")" << endl;
    }
    cout << endl;

    // Clearing an already-clear bit is a no-op
    cout << "  clearBit(8, 0) = " << clearBit(8, 0);
    cout << "  (bit 0 already clear, no change)" << endl;
    cout << endl;
}

// ============================================================
// Demo: toggleBit
// ============================================================
void demoToggleBit() {
    cout << "=== toggleBit ===" << endl;

    int n = 10;  // 0b00001010
    cout << "  Original: ";
    printBinary(n, 8);
    cout << " (" << n << ")" << endl;
    cout << endl;

    int bits[] = {0, 1, 3};
    int numBits = 3;
    int i;

    for (i = 0; i < numBits; i++) {
        int bit = bits[i];
        int result = toggleBit(n, bit);
        cout << "  toggleBit(" << n << ", " << bit << ") = ";
        printBinary(result, 8);
        cout << " (" << result << ")" << endl;
    }
    cout << endl;

    // Toggling twice returns to original
    int val = 42;
    int toggled = toggleBit(val, 2);
    int restored = toggleBit(toggled, 2);
    cout << "  Toggle bit 2 twice: " << val << " -> " << toggled << " -> " << restored;
    cout << " (back to original)" << endl;
    cout << endl;
}

// ============================================================
// Combined demo: apply multiple operations
// ============================================================
void demoCombined() {
    cout << "=== Combined Operations ===" << endl;

    int n = 0;  // Start with 0
    cout << "  Start: ";
    printBinary(n, 8);
    cout << " (" << n << ")" << endl;

    // Set bits 0, 3, 5
    n = setBit(n, 0);
    n = setBit(n, 3);
    n = setBit(n, 5);
    cout << "  After set bits 0,3,5: ";
    printBinary(n, 8);
    cout << " (" << n << ")" << endl;

    // Toggle bit 3
    n = toggleBit(n, 3);
    cout << "  After toggle bit 3:   ";
    printBinary(n, 8);
    cout << " (" << n << ")" << endl;

    // Clear bit 5
    n = clearBit(n, 5);
    cout << "  After clear bit 5:    ";
    printBinary(n, 8);
    cout << " (" << n << ")" << endl;
    cout << endl;
}

int main() {
    cout << "=== 05 - Bit Manipulation Operations ===" << endl;
    cout << endl;

    demoCheckBit();
    demoSetBit();
    demoClearBit();
    demoToggleBit();
    demoCombined();

    cout << "--- Summary ---" << endl;
    cout << "checkBit(n, b) : (n & (1 << b)) != 0  -> check if bit b is 1" << endl;
    cout << "setBit(n, b)   : n | (1 << b)         -> set bit b to 1" << endl;
    cout << "clearBit(n, b) : n & ~(1 << b)        -> set bit b to 0" << endl;
    cout << "toggleBit(n, b): n ^ (1 << b)         -> flip bit b" << endl;

    return 0;
}
