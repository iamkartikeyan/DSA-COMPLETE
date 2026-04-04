// 07 - Bit Applications Summary
// Complete summary of all bit tricks and applications

#include <iostream>

using namespace std;

// Print binary representation
void printBinary(int n, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// SECTION 1: Bitwise Operators
// ============================================================
void sectionOperators() {
    cout << "=== SECTION 1: Bitwise Operators ===" << endl;
    cout << endl;

    cout << "  Operator  | Symbol | Truth Table                    | Use" << endl;
    cout << "  ----------|--------|--------------------------------|-------------------" << endl;
    cout << "  AND       |   &    | 0&0=0  0&1=0  1&0=0  1&1=1    | Mask, check bits" << endl;
    cout << "  OR        |   |    | 0|0=0  0|1=1  1|0=1  1|1=1    | Set bits" << endl;
    cout << "  XOR       |   ^    | 0^0=0  0^1=1  1^0=1  1^1=0    | Toggle, unique" << endl;
    cout << "  NOT       |   ~    | ~0=1  ~1=0                     | Flip all bits" << endl;
    cout << "  LeftShift |   <<   | x << k = x * 2^k               | Multiply by 2^k" << endl;
    cout << "  RightShift|   >>   | x >> k = x / 2^k               | Divide by 2^k" << endl;
    cout << endl;

    int a = 0b1011, b = 0b1100;
    cout << "  Example: a=0b1011(11), b=0b1100(12)" << endl;
    cout << "    a & b = "; printBinary(a & b, 8); cout << " (" << (a & b) << ")" << endl;
    cout << "    a | b = "; printBinary(a | b, 8); cout << " (" << (a | b) << ")" << endl;
    cout << "    a ^ b = "; printBinary(a ^ b, 8); cout << " (" << (a ^ b) << ")" << endl;
    cout << "    ~a    = "; printBinary(~a, 8); cout << " (" << ~a << ")" << endl;
    cout << "    a << 2 = " << (a << 2) << "  (a * 4)" << endl;
    cout << "    b >> 1 = " << (b >> 1) << "  (b / 2)" << endl;
    cout << endl;
}

// ============================================================
// SECTION 2: XOR Properties
// ============================================================
void sectionXorProperties() {
    cout << "=== SECTION 2: XOR Properties ===" << endl;
    cout << endl;
    cout << "  x ^ x = 0          (self-cancel)" << endl;
    cout << "  x ^ 0 = x          (identity)" << endl;
    cout << "  x ^ y = y ^ x      (commutative)" << endl;
    cout << "  (x ^ y) ^ z = x ^ (y ^ z)  (associative)" << endl;
    cout << endl;
    cout << "  Applications:" << endl;
    cout << "    1. Find unique element (all others appear twice)" << endl;
    cout << "    2. Find two unique elements" << endl;
    cout << "    3. Find missing number in 0..n" << endl;
    cout << "    4. Swap without temp variable" << endl;
    cout << endl;
}

// ============================================================
// SECTION 3: Key Bit Tricks
// ============================================================
void sectionKeyTricks() {
    cout << "=== SECTION 3: Key Bit Tricks ===" << endl;
    cout << endl;

    cout << "  Trick                    | Formula           | Example" << endl;
    cout << "  -------------------------|-------------------|-------------------" << endl;

    // n & (n-1)
    cout << "  Clear lowest set bit     | n & (n-1)         | 12&11 = ";
    printBinary(12 & 11, 8);
    cout << " (4)" << endl;

    // n & (-n)
    cout << "  Isolate lowest set bit   | n & (-n)          | 12&(-12) = ";
    printBinary(12 & (-12), 8);
    cout << " (4)" << endl;

    // Power of two
    cout << "  Is power of two          | n>0 && !(n&(n-1)) | 8: " << (8 > 0 && !(8 & 7) ? "Yes" : "No");
    cout << ", 6: " << (6 > 0 && !(6 & 5) ? "Yes" : "No") << endl;

    // Is odd
    int four = 4;
    cout << "  Is odd                   | (n & 1) == 1      | 7: " << ((7 & 1) == 1 ? "Yes" : "No");
    cout << ", 4: " << ((four & 1) == 1 ? "Yes" : "No") << endl;

    // Abs without branching
    cout << "  Absolute value           | (x+(x>>31))^(x>>31)| abs(-7) = " << ((-7 + (-7 >> 31)) ^ (-7 >> 31)) << endl;

    // Opposite signs
    cout << "  Opposite signs           | (a ^ b) < 0       | 5,-3: " << ((5 ^ -3) < 0 ? "Yes" : "No");
    cout << ", 5,3: " << ((5 ^ 3) < 0 ? "Yes" : "No") << endl;

    // Multiply/divide by 2^k
    cout << "  Multiply by 2^k          | x << k            | 5<<2 = " << (5 << 2) << endl;
    cout << "  Divide by 2^k            | x >> k            | 20>>2 = " << (20 >> 2) << endl;

    cout << endl;
}

// ============================================================
// SECTION 4: Count Set Bits
// ============================================================
void sectionCountBits() {
    cout << "=== SECTION 4: Count Set Bits ===" << endl;
    cout << endl;

    cout << "  Method              | Time         | Code" << endl;
    cout << "  --------------------|--------------|---------------------------" << endl;
    cout << "  Loop                | O(32)        | while(n){ cnt+=n&1; n>>=1; }" << endl;
    cout << "  Brian Kernighan's   | O(set bits)  | while(n){ n&=n-1; cnt++; }" << endl;
    cout << "  __builtin_popcount  | O(1) HW      | __builtin_popcount(n)" << endl;
    cout << endl;

    int n = 15;
    cout << "  For n=" << n << " ("; printBinary(n, 8); cout << "):" << endl;
    cout << "    Loop: ";
    int cnt1 = 0, temp = n;
    while (temp) { cnt1 += temp & 1; temp >>= 1; }
    cout << cnt1 << endl;

    cout << "    Kernighan: ";
    int cnt2 = 0;
    temp = n;
    while (temp) { temp &= temp - 1; cnt2++; }
    cout << cnt2 << endl;

    cout << "    Builtin: " << __builtin_popcount(n) << endl;
    cout << endl;
}

// ============================================================
// SECTION 5: Bit Manipulation Operations
// ============================================================
void sectionBitOps() {
    cout << "=== SECTION 5: Bit Manipulation Operations ===" << endl;
    cout << endl;

    int n = 10;  // 0b1010
    cout << "  n = " << n << " = ";
    printBinary(n, 8);
    cout << endl;
    cout << endl;

    cout << "  Operation        | Formula          | Result" << endl;
    cout << "  -----------------|------------------|-------------------" << endl;

    // Check bit 1
    cout << "  Check bit 1      | (n>>1)&1         | " << ((n >> 1) & 1) << endl;

    // Set bit 0
    int r1 = n | (1 << 0);
    cout << "  Set bit 0        | n | (1<<0)       | ";
    printBinary(r1, 8);
    cout << " (" << r1 << ")" << endl;

    // Clear bit 1
    int r2 = n & ~(1 << 1);
    cout << "  Clear bit 1      | n & ~(1<<1)      | ";
    printBinary(r2, 8);
    cout << " (" << r2 << ")" << endl;

    // Toggle bit 0
    int r3 = n ^ (1 << 0);
    cout << "  Toggle bit 0     | n ^ (1<<0)       | ";
    printBinary(r3, 8);
    cout << " (" << r3 << ")" << endl;

    cout << endl;
}

// ============================================================
// SECTION 6: XOR Problem Patterns
// ============================================================
void sectionXorProblems() {
    cout << "=== SECTION 6: XOR Problem Patterns ===" << endl;
    cout << endl;

    // Find unique
    int arr1[] = {4, 1, 2, 1, 2};
    int n1 = 5;
    int unique = 0;
    int i;
    for (i = 0; i < n1; i++) unique ^= arr1[i];
    cout << "  Find unique in {4,1,2,1,2}:" << endl;
    cout << "    XOR all = " << unique << endl;
    cout << endl;

    // Missing number
    int arr2[] = {0, 1, 3, 4};
    int n2 = 4;
    int xorRange = 0, xorArray = 0;
    for (i = 0; i <= n2; i++) xorRange ^= i;
    for (i = 0; i < n2; i++) xorArray ^= arr2[i];
    cout << "  Missing in {0,1,3,4}:" << endl;
    cout << "    XOR(0..4) ^ XOR(array) = " << xorRange << " ^ " << xorArray << " = " << (xorRange ^ xorArray) << endl;
    cout << endl;

    // XOR Swap
    int x = 5, y = 10;
    cout << "  XOR swap x=" << x << ", y=" << y << ":" << endl;
    x ^= y; y ^= x; x ^= y;
    cout << "    Result: x=" << x << ", y=" << y << endl;
    cout << endl;
}

// ============================================================
// SECTION 7: Bitmask Subsets
// ============================================================
void sectionSubsets() {
    cout << "=== SECTION 7: Bitmask Subsets ===" << endl;
    cout << endl;

    cout << "  For n elements, there are 2^n subsets." << endl;
    cout << "  Each bit in mask represents inclusion of element at that index." << endl;
    cout << endl;

    int nums[] = {1, 2, 3};
    int n = 3;
    int total = 1 << n;
    int mask;
    int i;

    cout << "  Subsets of {1, 2, 3}:" << endl;
    for (mask = 0; mask < total; mask++) {
        cout << "    Mask " << mask << ": {";
        int first = 1;
        for (i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (!first) cout << ", ";
                cout << nums[i];
                first = 0;
            }
        }
        cout << "}" << endl;
    }
    cout << endl;
}

// ============================================================
// SECTION 8: Next Power of 2
// ============================================================
void sectionNextPowerOf2() {
    cout << "=== SECTION 8: Next Power of 2 ===" << endl;
    cout << endl;

    cout << "  Algorithm: propagate highest set bit to all lower positions, then +1" << endl;
    cout << endl;

    int values[] = {3, 5, 7, 8, 13, 16, 17, 100};
    int numValues = 8;
    int i;

    cout << "  Input  | Next Power of 2" << endl;
    cout << "  -------|----------------" << endl;

    for (i = 0; i < numValues; i++) {
        int n = values[i];
        if (n <= 0) {
            cout << "  " << n << "      | 1" << endl;
            continue;
        }
        int temp = n;
        temp--;
        temp |= temp >> 1;
        temp |= temp >> 2;
        temp |= temp >> 4;
        temp |= temp >> 8;
        temp |= temp >> 16;
        temp++;
        cout << "  ";
        if (n < 10) cout << " ";
        cout << n << "      | " << temp << endl;
    }
    cout << endl;
}

int main() {
    cout << "=== 07 - Bit Applications Complete Summary ===" << endl;
    cout << endl;

    sectionOperators();
    sectionXorProperties();
    sectionKeyTricks();
    sectionCountBits();
    sectionBitOps();
    sectionXorProblems();
    sectionSubsets();
    sectionNextPowerOf2();

    cout << "============================================================" << endl;
    cout << "                    CHEAT SHEET" << endl;
    cout << "============================================================" << endl;
    cout << endl;
    cout << "  OPERATORS:    & | ^ ~ << >>" << endl;
    cout << "  XOR LAWS:     x^x=0, x^0=x, commutative, associative" << endl;
    cout << "  CLEAR BIT:    n & (n-1)" << endl;
    cout << "  ISOLATE BIT:  n & (-n)" << endl;
    cout << "  POWER OF 2:   n > 0 && (n & (n-1)) == 0" << endl;
    cout << "  IS ODD:       (n & 1) == 1" << endl;
    cout << "  SET BIT k:    n | (1 << k)" << endl;
    cout << "  CLEAR BIT k:  n & ~(1 << k)" << endl;
    cout << "  TOGGLE BIT k: n ^ (1 << k)" << endl;
    cout << "  CHECK BIT k:  (n >> k) & 1" << endl;
    cout << "  ABS VALUE:    (x + (x>>31)) ^ (x>>31)" << endl;
    cout << "  OPPOSITE SIGNS: (a ^ b) < 0" << endl;
    cout << "  MULTIPLY 2^k: x << k" << endl;
    cout << "  DIVIDE 2^k:   x >> k" << endl;
    cout << "  COUNT BITS:   __builtin_popcount(n) or Kernighan's" << endl;
    cout << "  SUBSETS:      2^n masks, bit i = include element i" << endl;
    cout << "  NEXT POW2:    propagate bits right, then + 1" << endl;
    cout << endl;

    return 0;
}
