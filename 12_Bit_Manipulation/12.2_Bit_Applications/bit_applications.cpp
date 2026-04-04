// 12.2 Bit Applications
// Check/set/unset/toggle bits, count set bits, power of two,
// XOR problems (unique element, swap numbers), bitmasking for subsets

#include <bits/stdc++.h>
using namespace std;

void printBinary(int n, int bits = 8) {
    for (int i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// 1. BIT OPERATIONS: check, set, unset, toggle
// ============================================================
bool checkBit(int n, int bit)   { return (n & (1 << bit)) != 0; }
int  setBit(int n, int bit)     { return n | (1 << bit); }
int  unsetBit(int n, int bit)   { return n & ~(1 << bit); }
int  toggleBit(int n, int bit)  { return n ^ (1 << bit); }

void demoBitOps() {
    cout << "=== Bit Operations ===\n";
    int n = 0b00010100;  // 20
    cout << "  n = " << n << " = "; printBinary(n); cout << "\n\n";
    cout << "  Check bit 2: " << checkBit(n, 2) << "\n";
    cout << "  Set bit 0:   "; int r = setBit(n, 0);
    printBinary(r); cout << " (" << r << ")\n";
    cout << "  Unset bit 4: "; r = unsetBit(n, 4);
    printBinary(r); cout << " (" << r << ")\n";
    cout << "  Toggle bit 1:"; r = toggleBit(n, 1);
    printBinary(r); cout << " (" << r << ")\n\n";
}

// ============================================================
// 2. COUNT SET BITS (3 methods)
// ============================================================

// Method 1: Check each bit (O(number of bits))
int countBitsLoop(int n) {
    int cnt = 0;
    while (n) {
        cnt += (n & 1);   // Add LSB
        n >>= 1;          // Shift right
    }
    return cnt;
}

// Method 2: Brian Kernighan's (O(set bits)) - clears lowest set bit each iteration
int countBitsKernighan(int n) {
    int cnt = 0;
    while (n) {
        n &= (n - 1);     // Clear lowest set bit
        cnt++;
    }
    return cnt;
}

// Method 3: GCC builtin (O(1) using CPU instruction)
int countBitsBuiltin(int n) { return __builtin_popcount(n); }

// ============================================================
// 3. POWER OF TWO CHECK
// Power of two has exactly one bit set: n & (n-1) == 0
// ============================================================
bool isPowerOfTwo(int n) { return n > 0 && (n & (n - 1)) == 0; }

// ============================================================
// 4. XOR PROBLEMS
// ============================================================

// 4a. Find the unique element (all others appear twice)
// Key: x ^ x = 0, x ^ 0 = x, XOR is commutative
int findUnique(const vector<int>& arr) {
    int result = 0;
    for (int x : arr) result ^= x;  // Pairs cancel, unique remains
    return result;
}

// 4b. Find two unique elements (all others appear twice)
// XOR all -> gets a^b. Find a set bit in a^b. Split array by that bit.
pair<int, int> findTwoUniques(const vector<int>& arr) {
    int xorAll = 0;
    for (int x : arr) xorAll ^= x;   // xorAll = a ^ b

    // Find rightmost set bit (differs between a and b)
    int setBit = xorAll & (-xorAll);

    int a = 0, b = 0;
    for (int x : arr) {
        if (x & setBit) a ^= x;     // Elements with that bit set
        else b ^= x;                 // Elements without that bit
    }
    return {a, b};
}

// 4c. Find missing number in 0..n array (one number missing)
// XOR all indices 0..n with all array elements; duplicates cancel
int findMissing(const vector<int>& arr) {
    int n = arr.size();
    int xorAll = 0, xorArr = 0;
    for (int i = 0; i <= n; i++) xorAll ^= i;   // XOR 0,1,...,n
    for (int x : arr) xorArr ^= x;               // XOR all array elements
    return xorAll ^ xorArr;                      // Missing number remains
}

// 4d. XOR swap (swap without temporary variable)
void xorSwap(int& a, int& b) {
    if (a == b) return;          // Edge case: same variable
    a ^= b; b ^= a; a ^= b;
}

// ============================================================
// 5. BITMASKING FOR SUBSET REPRESENTATION
// An n-bit mask represents a subset of {0, 1, ..., n-1}
// 2^n possible subsets
// ============================================================

// Generate all subsets using bitmask (iterative)
vector<vector<int>> allSubsetsMask(const vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    for (int mask = 0; mask < (1 << n); mask++) {  // 0 to 2^n - 1
        vector<int> subset;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) subset.push_back(nums[i]);  // Bit i set -> include
        result.push_back(subset);
    }
    return result;
}

// Check if a subset (mask) has property: all elements even
bool allEven(const vector<int>& nums, int mask) {
    for (int i = 0; i < (int)nums.size(); i++)
        if ((mask & (1 << i)) && (nums[i] % 2 != 0)) return false;
    return true;
}

// ============================================================
// 6. ADDITIONAL BIT TRICKS
// ============================================================

// Multiply/divide by power of 2
int multiplyBy4(int x) { return x << 2; }   // x * 4
int divideBy4(int x) { return x >> 2; }     // x / 4

// Absolute value without branching
int absVal(int x) {
    int mask = x >> 31;      // 0 if positive, -1 if negative
    return (x + mask) ^ mask;
}

// Check if two numbers have opposite signs
bool oppositeSigns(int a, int b) { return (a ^ b) < 0; }

// Round up to next power of 2
int nextPowerOfTwo(int n) {
    if (n <= 0) return 1;
    n--;                     // Handle exact power of 2
    n |= n >> 1; n |= n >> 2;
    n |= n >> 4; n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

// Check if number is odd: (n & 1) == 1
bool isOdd(int n) { return (n & 1) == 1; }

int main() {
    cout << "=== 12.2 Bit Applications ===\n\n";

    // --- Bit Operations ---
    demoBitOps();

    // --- Count Set Bits ---
    cout << "=== Count Set Bits ===\n";
    int n = 15;  // 0b1111
    cout << "  n = " << n << " ("; printBinary(n); cout << ")\n";
    cout << "  Loop method:      " << countBitsLoop(n) << "\n";
    cout << "  Kernighan's:      " << countBitsKernighan(n) << "\n";
    cout << "  __builtin_popcount: " << countBitsBuiltin(n) << "\n\n";

    // --- Power of Two ---
    cout << "=== Power of Two ===\n";
    cout << "  Is 8 power of two?  " << isPowerOfTwo(8) << "\n";
    cout << "  Is 6 power of two?  " << isPowerOfTwo(6) << "\n";
    cout << "  Is 1024 power of two? " << isPowerOfTwo(1024) << "\n\n";

    // --- XOR: Unique Element ---
    cout << "=== XOR Problems ===\n";
    vector<int> arr1 = {4, 1, 2, 1, 2};
    cout << "  Find unique in {4,1,2,1,2}: " << findUnique(arr1) << "\n";

    // XOR: Two Uniques
    vector<int> arr2 = {2, 4, 7, 9, 2, 4};
    auto [u1, u2] = findTwoUniques(arr2);
    cout << "  Two uniques in {2,4,7,9,2,4}: " << u1 << " and " << u2 << "\n";

    // XOR: Missing Number
    vector<int> arr3 = {0, 1, 3, 4};  // Missing: 2
    cout << "  Missing in {0,1,3,4}: " << findMissing(arr3) << "\n";

    // XOR: Swap
    int x = 5, y = 10;
    cout << "  Swap x=" << x << ", y=" << y << " (XOR): ";
    xorSwap(x, y);
    cout << "x=" << x << ", y=" << y << "\n\n";

    // --- Bitmasking for Subsets ---
    cout << "=== Bitmasking for Subsets ===\n";
    vector<int> nums = {1, 2, 3};
    cout << "  All subsets of {1, 2, 3}:\n";
    auto subsets = allSubsetsMask(nums);
    for (size_t i = 0; i < subsets.size(); i++) {
        int mask = (int)i;
        cout << "    Mask "; printBinary(mask, 3);
        cout << " (" << mask << "): {";
        for (size_t j = 0; j < subsets[i].size(); j++)
            cout << subsets[i][j] << (j + 1 < subsets[i].size() ? ", " : "");
        cout << "}\n";
    }

    // --- Additional Tricks ---
    cout << "\n=== Bit Tricks ===\n";
    cout << "  5 << 2 = " << multiplyBy4(5) << " (5 * 4)\n";
    cout << "  20 >> 2 = " << divideBy4(20) << " (20 / 4)\n";
    cout << "  abs(-7) = " << absVal(-7) << "\n";
    cout << "  5 and -3 opposite signs? " << oppositeSigns(5, -3) << "\n";
    cout << "  5 and 3 opposite signs? " << oppositeSigns(5, 3) << "\n";
    cout << "  Next power of 2 after 5: " << nextPowerOfTwo(5) << "\n";
    cout << "  Next power of 2 after 13: " << nextPowerOfTwo(13) << "\n";
    cout << "  Is 7 odd? " << isOdd(7) << "\n";

    return 0;
}
