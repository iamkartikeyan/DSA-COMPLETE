// 02 - XOR Find Two Unique Elements
// Find TWO unique elements when all others appear twice
// Split array by a differing bit position

#include <iostream>

using namespace std;

// Print binary representation
void printBinary(int n, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// Find two unique elements in an array where every other
// element appears exactly twice.
//
// Algorithm:
//   1. XOR all elements -> gets a ^ b (the two uniques XORed)
//   2. Find a bit position where a and b differ (a set bit in a^b)
//   3. Split array into two groups by that bit
//   4. XOR each group separately -> each group yields one unique
// ============================================================
void findTwoUniques(int arr[], int n, int* out1, int* out2) {
    int i;

    // Step 1: XOR all elements = a ^ b
    int xorAll = 0;
    for (i = 0; i < n; i++)
        xorAll ^= arr[i];

    // Step 2: Find rightmost set bit in xorAll
    // This bit differs between the two unique elements
    int setBit = xorAll & (-xorAll);
    // Explanation: -xorAll = ~xorAll + 1
    // This keeps only the rightmost set bit

    cout << "    XOR of all elements = " << xorAll << " = ";
    printBinary(xorAll, 8);
    cout << endl;
    cout << "    Rightmost differing bit = " << setBit << " = ";
    printBinary(setBit, 8);
    cout << endl;

    // Step 3 & 4: Split by that bit and XOR each group
    int a = 0, b = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] & setBit)
            a ^= arr[i];   // Group with that bit set
        else
            b ^= arr[i];   // Group with that bit clear
    }

    *out1 = a;
    *out2 = b;
}

// ============================================================
// Demo
// ============================================================
void demoFindTwoUniques() {
    cout << "=== Find Two Unique Elements ===" << endl;

    int arr[] = {2, 4, 7, 9, 2, 4};
    int n = 6;

    cout << "  Array: {2, 4, 7, 9, 2, 4}" << endl;
    cout << "  (7 and 9 appear once, others appear twice)" << endl;
    cout << endl;

    cout << "  Step-by-step:" << endl;
    int unique1 = 0, unique2 = 0;
    findTwoUniques(arr, n, &unique1, &unique2);

    cout << endl;
    cout << "  Result: " << unique1 << " and " << unique2 << endl;
    cout << endl;

    // Show the split
    cout << "  Group split (by bit 0):" << endl;
    cout << "    Bit 0 set group includes one unique: " << unique1 << endl;
    cout << "    Bit 0 clear group includes the other unique: " << unique2 << endl;
    cout << endl;
}

// ============================================================
// Another example
// ============================================================
void demoAnotherExample() {
    cout << "=== Another Example ===" << endl;

    int arr[] = {1, 2, 1, 3, 2, 5};
    int n = 6;
    int unique1 = 0, unique2 = 0;

    cout << "  Array: {1, 2, 1, 3, 2, 5}" << endl;

    findTwoUniques(arr, n, &unique1, &unique2);
    cout << "  Result: " << unique1 << " and " << unique2 << endl;
    cout << endl;
}

// ============================================================
// Why this works
// ============================================================
void explainWhy() {
    cout << "=== Why This Works ===" << endl;
    cout << "  1. XOR all -> a^b (pairs cancel out)" << endl;
    cout << "  2. a^b has at least one bit set (a != b)" << endl;
    cout << "  3. That bit splits array into two groups:" << endl;
    cout << "     - Group A: elements with that bit set (includes one unique)" << endl;
    cout << "     - Group B: elements with that bit clear (includes the other)" << endl;
    cout << "  4. Pairs stay in the same group and cancel" << endl;
    cout << "  5. Each group XOR yields one unique element" << endl;
    cout << endl;
    cout << "  Time:  O(n) - two passes" << endl;
    cout << "  Space: O(1) - constant extra variables" << endl;
    cout << endl;
}

int main() {
    cout << "=== 02 - XOR Find Two Unique Elements ===" << endl;
    cout << endl;

    demoFindTwoUniques();
    demoAnotherExample();
    explainWhy();

    cout << "--- Summary ---" << endl;
    cout << "XOR all -> a^b, find differing bit, split, XOR each group" << endl;
    cout << "Time: O(n), Space: O(1)" << endl;

    return 0;
}
