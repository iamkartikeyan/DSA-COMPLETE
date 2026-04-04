// 01 - Bitwise Operators Basics: AND, OR, XOR, NOT
// Demonstrates each operator with truth tables and binary printing

#include <iostream>
#include <vector>

using namespace std;

// Print binary representation of an integer
void printBinary(int n, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// AND (&): Bit is 1 only if BOTH bits are 1
// Use: mask bits, check if bit is set, clear bits
// ============================================================
void demoAnd() {
    cout << "=== AND (&) ===" << endl;

    int a = 0b1011;  // 11
    int b = 0b1100;  // 12

    cout << "  "; printBinary(a, 8); cout << " (" << a << ")" << endl;
    cout << "& "; printBinary(b, 8); cout << " (" << b << ")" << endl;
    cout << "= "; printBinary(a & b, 8); cout << " (" << (a & b) << ")" << endl;
    cout << endl;

    cout << "  Truth table:" << endl;
    cout << "    1 & 1 = " << (1 & 1) << endl;
    cout << "    1 & 0 = " << (1 & 0) << endl;
    cout << "    0 & 0 = " << (0 & 0) << endl;
    cout << endl;

    cout << "  Use: mask = n & 0xFF keeps lowest 8 bits" << endl;
    cout << "  Check even: (n & 1) == 0" << endl;
    cout << "  Example: 12 is even? " << ((12 & 1) == 0 ? "Yes" : "No") << endl;
    cout << endl;
}

// ============================================================
// OR (|): Bit is 1 if EITHER bit is 1
// Use: set bits, combine flags
// ============================================================
void demoOr() {
    cout << "=== OR (|) ===" << endl;

    int a = 0b1011;  // 11
    int b = 0b1100;  // 12

    cout << "  "; printBinary(a, 8); cout << " (" << a << ")" << endl;
    cout << "| "; printBinary(b, 8); cout << " (" << b << ")" << endl;
    cout << "= "; printBinary(a | b, 8); cout << " (" << (a | b) << ")" << endl;
    cout << endl;

    cout << "  Truth table:" << endl;
    cout << "    1 | 1 = " << (1 | 1) << endl;
    cout << "    1 | 0 = " << (1 | 0) << endl;
    cout << "    0 | 0 = " << (0 | 0) << endl;
    cout << endl;

    cout << "  Use: set bit k with  n | (1 << k)" << endl;
    int val = 8;  // 0b00001000
    cout << "  Set bit 0 on 8: ";
    int result = val | (1 << 0);
    printBinary(result, 8);
    cout << " (" << result << ")" << endl;
    cout << endl;
}

// ============================================================
// XOR (^): Bit is 1 if bits DIFFER
// Key properties: x^x=0, x^0=x, x^y = y^x, (x^y)^z = x^(y^z)
// Use: toggle bits, find unique element, swap without temp
// ============================================================
void demoXor() {
    cout << "=== XOR (^) ===" << endl;

    int a = 0b1011;  // 11
    int b = 0b1100;  // 12

    cout << "  "; printBinary(a, 8); cout << " (" << a << ")" << endl;
    cout << "^ "; printBinary(b, 8); cout << " (" << b << ")" << endl;
    cout << "= "; printBinary(a ^ b, 8); cout << " (" << (a ^ b) << ")" << endl;
    cout << endl;

    cout << "  Truth table:" << endl;
    cout << "    1 ^ 1 = " << (1 ^ 1) << endl;
    cout << "    1 ^ 0 = " << (1 ^ 0) << endl;
    cout << "    0 ^ 0 = " << (0 ^ 0) << endl;
    cout << endl;

    cout << "  Key properties:" << endl;
    cout << "    x ^ x = " << (5 ^ 5) << "  (self cancels to 0)" << endl;
    cout << "    x ^ 0 = " << (5 ^ 0) << "  (identity, returns x)" << endl;
    cout << "    a ^ b ^ a = " << (3 ^ 7 ^ 3) << "  = b (commutative, pairs cancel)" << endl;
    cout << endl;
}

// ============================================================
// NOT (~): Flip all bits (one's complement)
// ~x = -(x+1) in two's complement
// ============================================================
void demoNot() {
    cout << "=== NOT (~) ===" << endl;

    int a = 0b00001011;  // 11
    cout << "  ~"; printBinary(a, 8); cout << " (" << a << ") = ";
    printBinary(~a, 8); cout << " (" << ~a << ")" << endl;
    cout << endl;

    cout << "  ~5 = " << ~5 << "  (equals -(5+1) = -6 in two's complement)" << endl;
    cout << "  ~0 = " << ~0 << "  (all 1s = -1)" << endl;
    cout << "  ~(-1) = " << ~(-1) << "  (flips back to 0)" << endl;
    cout << endl;
}

int main() {
    cout << "=== 01 - Bitwise Operators Basics ===" << endl;
    cout << endl;

    demoAnd();
    demoOr();
    demoXor();
    demoNot();

    cout << "--- Summary ---" << endl;
    cout << "&  : both 1 -> 1; masks, checks, clears bits" << endl;
    cout << "|  : either 1 -> 1; sets bits, combines flags" << endl;
    cout << "^  : different -> 1; toggles, unique finding, swap" << endl;
    cout << "~  : flips all bits; one's complement, ~x = -(x+1)" << endl;

    return 0;
}
