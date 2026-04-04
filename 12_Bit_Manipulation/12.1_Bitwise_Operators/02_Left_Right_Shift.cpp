// 02 - Left and Right Shift Operators
// Left shift (multiply by 2^k), Right shift (divide by 2^k)

#include <iostream>

using namespace std;

// Print binary representation
void printBinary(int n, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// LEFT SHIFT (<<): Multiply by 2^k
// x << k = x * 2^k
// Bits shifted out are lost, new bits filled with 0
// ============================================================
void demoLeftShift() {
    cout << "=== LEFT SHIFT (<<) ===" << endl;

    int a = 0b00000101;  // 5
    cout << "  "; printBinary(a, 8); cout << " = " << a << endl;
    cout << "  "; printBinary(a << 1, 8); cout << " = " << (a << 1) << " (<< 1, *2)" << endl;
    cout << "  "; printBinary(a << 2, 8); cout << " = " << (a << 2) << " (<< 2, *4)" << endl;
    cout << "  "; printBinary(a << 3, 8); cout << " = " << (a << 3) << " (<< 3, *8)" << endl;
    cout << endl;

    cout << "  Computing powers of 2 with 1 << k:" << endl;
    int k;
    for (k = 0; k <= 10; k++)
        cout << "    1 << " << k << " = " << (1 << k) << "  (2^" << k << ")" << endl;
    cout << endl;

    // Practical example: multiply by 2^k
    int x = 7;
    int kVal = 3;
    cout << "  " << x << " << " << kVal << " = " << (x << kVal);
    cout << "  (which is " << x << " * " << (1 << kVal) << " = " << (x * (1 << kVal)) << ")" << endl;
    cout << endl;
}

// ============================================================
// RIGHT SHIFT (>>): Divide by 2^k (integer division)
// For signed ints: arithmetic shift (sign bit preserved)
// ============================================================
void demoRightShift() {
    cout << "=== RIGHT SHIFT (>>) ===" << endl;

    int a = 40;  // 0b00101000
    cout << "  "; printBinary(a, 8); cout << " = " << a << endl;
    cout << "  "; printBinary(a >> 1, 8); cout << " = " << (a >> 1) << " (>> 1, /2)" << endl;
    cout << "  "; printBinary(a >> 2, 8); cout << " = " << (a >> 2) << " (>> 2, /4)" << endl;
    cout << "  "; printBinary(a >> 3, 8); cout << " = " << (a >> 3) << " (>> 3, /8)" << endl;
    cout << endl;

    // Division examples
    int val = 100;
    cout << "  " << val << " >> 1 = " << (val >> 1) << "  (" << val << " / 2)" << endl;
    cout << "  " << val << " >> 2 = " << (val >> 2) << "  (" << val << " / 4)" << endl;
    cout << "  " << val << " >> 3 = " << (val >> 3) << "  (" << val << " / 8)" << endl;
    cout << endl;

    // Negative number right shift (arithmetic: preserves sign)
    int neg = -16;
    cout << "  Negative number right shift:" << endl;
    cout << "  " << neg << " >> 1 = " << (neg >> 1) << "  (" << neg << " / 2)" << endl;
    cout << "  " << neg << " >> 2 = " << (neg >> 2) << "  (" << neg << " / 4)" << endl;
    cout << endl;
}

// ============================================================
// Important: Shift operations are NOT commutative with overflow
// Shifting by >= width of type is undefined behavior
// ============================================================
void demoShiftCaveats() {
    cout << "=== Shift Caveats ===" << endl;

    // Bits shifted out are permanently lost
    int small = 0b00000011;  // 3
    cout << "  " << small << " in binary: ";
    printBinary(small, 8);
    cout << endl;
    cout << "  " << small << " << 7 = " << (small << 7);
    cout << " (bits lost when shifted out)" << endl;
    cout << "  (" << small << " << 7) >> 7 = " << ((small << 7) >> 7);
    cout << " (original value NOT recovered)" << endl;
    cout << endl;

    // Shift by 0 is identity
    int x = 42;
    cout << "  " << x << " << 0 = " << (x << 0) << " (no change)" << endl;
    cout << endl;
}

int main() {
    cout << "=== 02 - Left and Right Shift Operators ===" << endl;
    cout << endl;

    demoLeftShift();
    demoRightShift();
    demoShiftCaveats();

    cout << "--- Summary ---" << endl;
    cout << "<< : left shift by k = multiply by 2^k" << endl;
    cout << ">> : right shift by k = divide by 2^k (integer division)" << endl;
    cout << "   Left shift fills with 0 on the right" << endl;
    cout << "   Right shift preserves sign bit for negative numbers" << endl;
    cout << "   Shifting by >= type width is undefined behavior" << endl;

    return 0;
}
