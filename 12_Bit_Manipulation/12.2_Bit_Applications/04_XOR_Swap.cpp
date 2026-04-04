// 04 - XOR Swap
// Swap two values without a temporary variable using XOR
// Includes edge cases and demonstration

#include <iostream>

using namespace std;

// ============================================================
// XOR Swap: exchange two integers without a temp variable
// Three XOR operations:
//   a ^= b   -> a now holds a^b
//   b ^= a   -> b = b^(a^b) = a (original a)
//   a ^= b   -> a = (a^b)^a = b (original b)
// ============================================================
void xorSwap(int* a, int* b) {
    // Edge case: same memory location - skip to avoid zeroing
    if (a == b)
        return;

    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

// ============================================================
// Demo: basic swap
// ============================================================
void demoBasicSwap() {
    cout << "=== Basic XOR Swap ===" << endl;

    int x = 5, y = 10;
    cout << "  Before: x = " << x << ", y = " << y << endl;

    xorSwap(&x, &y);

    cout << "  After:  x = " << x << ", y = " << y << endl;
    cout << endl;

    // Step by step
    int a = 5, b = 10;
    cout << "  Step by step for a=" << a << ", b=" << b << ":" << endl;
    cout << "    Initial:     a = " << a << ", b = " << b << endl;

    a ^= b;
    cout << "    a ^= b:      a = " << a << " (which is 5^10=" << (5 ^ 10) << ")" << endl;

    b ^= a;
    cout << "    b ^= a:      b = " << b << " (which is 10^15=5 = original a)" << endl;

    a ^= b;
    cout << "    a ^= b:      a = " << a << " (which is 15^5=" << (15 ^ 5) << " = original b)" << endl;
    cout << endl;
}

// ============================================================
// Demo: swap with same values (not same memory)
// ============================================================
void demoSameValues() {
    cout << "=== Swap with Same Values ===" << endl;

    int x = 7, y = 7;
    cout << "  Before: x = " << x << ", y = " << y << endl;

    xorSwap(&x, &y);

    cout << "  After:  x = " << x << ", y = " << y << endl;
    cout << "  (Both still 7 - swap of equal values works correctly)" << endl;
    cout << endl;
}

// ============================================================
// Demo: edge case - same memory location
// ============================================================
void demoSameLocation() {
    cout << "=== Edge Case: Same Memory Location ===" << endl;

    int arr[] = {5, 3, 8};

    cout << "  Array before: {" << arr[0] << ", " << arr[1] << ", " << arr[2] << "}" << endl;

    // Try to swap arr[0] with arr[0] (same address)
    xorSwap(&arr[0], &arr[0]);

    cout << "  After xorSwap(&arr[0], &arr[0]):" << endl;
    cout << "  Array: {" << arr[0] << ", " << arr[1] << ", " << arr[2] << "}" << endl;
    cout << "  arr[0] is still " << arr[0] << " (not zeroed, thanks to same-location check)" << endl;
    cout << endl;

    // What happens WITHOUT the guard:
    cout << "  WITHOUT the guard (a == a):" << endl;
    int val = 5;
    val ^= val;   // a = 0
    val ^= val;   // b = 0
    val ^= val;   // a = 0
    cout << "  Value becomes: " << val << " (BUG! self-XOR zeroes the value)" << endl;
    cout << endl;
}

// ============================================================
// Demo: swap with negative numbers
// ============================================================
void demoNegativeSwap() {
    cout << "=== Swap with Negative Numbers ===" << endl;

    int x = -3, y = 7;
    cout << "  Before: x = " << x << ", y = " << y << endl;

    xorSwap(&x, &y);

    cout << "  After:  x = " << x << ", y = " << y << endl;
    cout << endl;
}

// ============================================================
// Comparison with traditional swap
// ============================================================
void compareSwapMethods() {
    cout << "=== Comparison of Swap Methods ===" << endl;

    int a1 = 10, b1 = 20;
    // Traditional swap with temp
    int temp = a1;
    a1 = b1;
    b1 = temp;
    cout << "  Traditional (with temp): 10, 20 -> " << a1 << ", " << b1 << endl;

    int a2 = 10, b2 = 20;
    // XOR swap (no temp)
    xorSwap(&a2, &b2);
    cout << "  XOR swap (no temp):      10, 20 -> " << a2 << ", " << b2 << endl;
    cout << endl;

    cout << "  Pros of XOR swap:" << endl;
    cout << "    - No extra variable needed" << endl;
    cout << "    - Looks clever" << endl;
    cout << endl;
    cout << "  Cons of XOR swap:" << endl;
    cout << "    - Fails if both pointers are the same (needs guard)" << endl;
    cout << "    - Harder to read" << endl;
    cout << "    - Compilers optimize traditional swap anyway" << endl;
    cout << "    - No performance benefit in practice" << endl;
    cout << endl;
}

int main() {
    cout << "=== 04 - XOR Swap ===" << endl;
    cout << endl;

    demoBasicSwap();
    demoSameValues();
    demoSameLocation();
    demoNegativeSwap();
    compareSwapMethods();

    cout << "--- Summary ---" << endl;
    cout << "a ^= b; b ^= a; a ^= b;  swaps without temp variable" << endl;
    cout << "ALWAYS check a != b first to avoid zeroing same-location swap" << endl;

    return 0;
}
