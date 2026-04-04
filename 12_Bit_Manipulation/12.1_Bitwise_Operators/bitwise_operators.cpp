// 12.1 Bitwise Operators
// AND (&), OR (|), XOR (^), NOT (~), Left Shift (<<), Right Shift (>>)
// Properties: x^x=0, x^0=x, n&(n-1) clears lowest set bit

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// PRINT BINARY REPRESENTATION (for demonstration)
// ============================================================
void printBinary(int n, int bits = 8) {
    for (int i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// 1. AND (&): Bit is 1 only if BOTH bits are 1
// Use: mask bits, check if bit is set, clear bits
// ============================================================
void demoAnd() {
    cout << "=== AND (&) ===\n";
    int a = 0b1011, b = 0b1100;
    cout << "  "; printBinary(a); cout << " (" << a << ")\n";
    cout << "& "; printBinary(b); cout << " (" << b << ")\n";
    cout << "= "; printBinary(a & b); cout << " (" << (a & b) << ")\n";
    cout << "  1&1=" << (1&1) << "  1&0=" << (1&0) << "  0&0=" << (0&0) << "\n";
    cout << "  Use: mask = n & 0xFF keeps lowest 8 bits\n";
    cout << "  Check even: (n & 1) == 0\n\n";
}

// ============================================================
// 2. OR (|): Bit is 1 if EITHER bit is 1
// Use: set bits, combine flags
// ============================================================
void demoOr() {
    cout << "=== OR (|) ===\n";
    int a = 0b1011, b = 0b1100;
    cout << "  "; printBinary(a); cout << " (" << a << ")\n";
    cout << "| "; printBinary(b); cout << " (" << b << ")\n";
    cout << "= "; printBinary(a | b); cout << " (" << (a | b) << ")\n";
    cout << "  1|1=" << (1|1) << "  1|0=" << (1|0) << "  0|0=" << (0|0) << "\n";
    cout << "  Use: set bit k: n | (1 << k)\n\n";
}

// ============================================================
// 3. XOR (^): Bit is 1 if bits DIFFER
// Key properties: x^x=0, x^0=x, x^y = y^x, (x^y)^z = x^(y^z)
// Use: toggle bits, find unique element, swap without temp
// ============================================================
void demoXor() {
    cout << "=== XOR (^) ===\n";
    int a = 0b1011, b = 0b1100;
    cout << "  "; printBinary(a); cout << " (" << a << ")\n";
    cout << "^ "; printBinary(b); cout << " (" << b << ")\n";
    cout << "= "; printBinary(a ^ b); cout << " (" << (a ^ b) << ")\n";
    cout << "  1^1=" << (1^1) << "  1^0=" << (1|0) << "  0^0=" << (0^0) << "\n";
    cout << "  Properties:\n";
    cout << "    x ^ x = " << (5 ^ 5) << " (self cancel)\n";
    cout << "    x ^ 0 = " << (5 ^ 0) << " (identity)\n";
    cout << "    a ^ b ^ a = " << (3 ^ 7 ^ 3) << " = b (commutative)\n\n";
}

// ============================================================
// 4. NOT (~): Flip all bits (one's complement)
// ~x = -(x+1) in two's complement
// ============================================================
void demoNot() {
    cout << "=== NOT (~) ===\n";
    int a = 0b00001011;  // 11
    cout << "  ~"; printBinary(a); cout << " (" << a << ") = ";
    printBinary(~a); cout << " (" << ~a << ")\n";
    cout << "  ~5 = " << ~5 << " (equals -(5+1) = -6 in two's complement)\n";
    cout << "  ~0 = " << ~0 << " (all 1s = -1)\n\n";
}

// ============================================================
// 5. LEFT SHIFT (<<): Multiply by 2^k
// x << k = x * 2^k
// Bits shifted out are lost, new bits filled with 0
// ============================================================
void demoLeftShift() {
    cout << "=== LEFT SHIFT (<<) ===\n";
    int a = 0b00000101;  // 5
    cout << "  "; printBinary(a); cout << " = " << a << "\n";
    cout << "  "; printBinary(a << 1); cout << " = " << (a << 1) << " (<<1, *2)\n";
    cout << "  "; printBinary(a << 2); cout << " = " << (a << 2) << " (<<2, *4)\n";
    cout << "  "; printBinary(a << 3); cout << " = " << (a << 3) << " (<<3, *8)\n";
    cout << "  1 << 10 = " << (1 << 10) << " (2^10)\n\n";
}

// ============================================================
// 6. RIGHT SHIFT (>>): Divide by 2^k (integer division)
// For signed ints: arithmetic (sign bit preserved)
// ============================================================
void demoRightShift() {
    cout << "=== RIGHT SHIFT (>>) ===\n";
    int a = 40;  // 0b00101000
    cout << "  "; printBinary(a); cout << " = " << a << "\n";
    cout << "  "; printBinary(a >> 1); cout << " = " << (a >> 1) << " (>>1, /2)\n";
    cout << "  "; printBinary(a >> 2); cout << " = " << (a >> 2) << " (>>2, /4)\n";
    cout << "  "; printBinary(a >> 3); cout << " = " << (a >> 3) << " (>>3, /8)\n\n";
}

// ============================================================
// 7. KEY TRICKS & PROPERTIES
// ============================================================

// n & (n-1): Clear the lowest set bit
int clearLowestBit(int n) { return n & (n - 1); }

// Isolate lowest set bit: n & (-n)
int lowestSetBit(int n) { return n & (-n); }

// Check if power of two: n > 0 && (n & (n-1)) == 0
bool isPowerOfTwo(int n) { return n > 0 && (n & (n - 1)) == 0; }

// Swap without temp using XOR
void xorSwap(int& a, int& b) {
    a ^= b; b ^= a; a ^= b;
}

// Count set bits: Brian Kernighan's algorithm
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  // Clear lowest set bit
        count++;
    }
    return count;
}

// Check if nth bit is set
bool isBitSet(int n, int bit) { return (n & (1 << bit)) != 0; }

// Set nth bit
int setBit(int n, int bit) { return n | (1 << bit); }

// Clear nth bit
int clearBit(int n, int bit) { return n & ~(1 << bit); }

// Toggle nth bit
int toggleBit(int n, int bit) { return n ^ (1 << bit); }

int main() {
    cout << "=== 12.1 Bitwise Operators ===\n\n";

    // --- All operators ---
    demoAnd();
    demoOr();
    demoXor();
    demoNot();
    demoLeftShift();
    demoRightShift();

    // --- Tricks ---
    cout << "=== Key Tricks ===\n";

    int n = 12;  // 0b00001100
    cout << "\nn = " << n << " = "; printBinary(n); cout << "\n";

    cout << "  n & (n-1) = " << clearLowestBit(n)
         << " (clears lowest set bit)\n";
    cout << "    "; printBinary(n); cout << " & "; printBinary(n-1);
    cout << " = "; printBinary(clearLowestBit(n)); cout << "\n";

    cout << "  n & (-n) = " << lowestSetBit(n)
         << " (isolates lowest set bit)\n";
    cout << "  Is power of two? " << (isPowerOfTwo(n) ? "Yes" : "No") << "\n";
    cout << "  Is power of two? " << (isPowerOfTwo(16) ? "Yes" : "No") << " (16)\n";

    // XOR swap
    int x = 5, y = 10;
    cout << "\n  XOR swap: x=" << x << ", y=" << y;
    xorSwap(x, y);
    cout << " -> x=" << x << ", y=" << y << "\n";

    // Count set bits
    cout << "\n  Set bits in 15 ("; printBinary(15); cout << "): "
         << countSetBits(15) << "\n";
    cout << "  Set bits in 7  ("; printBinary(7);  cout << "): "
         << countSetBits(7) << "\n";

    // Bit manipulation
    int val = 10;  // 0b1010
    cout << "\n  val = " << val << " ("; printBinary(val); cout << ")\n";
    cout << "  Bit 1 set? " << isBitSet(val, 1) << "\n";
    cout << "  Set bit 2: "; printBinary(setBit(val, 2)); cout << " (" << setBit(val, 2) << ")\n";
    cout << "  Clear bit 3: "; printBinary(clearBit(val, 3));
    cout << " (" << clearBit(val, 3) << ")\n";
    cout << "  Toggle bit 0: "; printBinary(toggleBit(val, 0));
    cout << " (" << toggleBit(val, 0) << ")\n";

    cout << "\n--- Summary ---\n";
    cout << "&  : both 1 -> 1; masks, checks, clears bits\n";
    cout << "|  : either 1 -> 1; sets bits, combines flags\n";
    cout << "^  : different -> 1; toggles, unique finding, swap\n";
    cout << "~  : flips all bits; one's complement\n";
    cout << "<< : left shift = multiply by 2^k\n";
    cout << ">> : right shift = divide by 2^k\n";
    cout << "n&(n-1) : clear lowest set bit\n";
    cout << "n&(-n)  : isolate lowest set bit\n";

    return 0;
}
