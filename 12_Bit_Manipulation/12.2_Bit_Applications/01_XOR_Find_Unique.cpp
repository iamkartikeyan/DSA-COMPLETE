// 01 - XOR Find Unique Element
// Find the unique element when all others appear twice
// XOR properties: x^x=0, x^0=x, XOR is commutative

#include <iostream>

using namespace std;

// ============================================================
// Find the unique element in an array where every other
// element appears exactly twice.
//
// Key insight: XOR all elements together.
//   - Pairs cancel out: x ^ x = 0
//   - Identity: x ^ 0 = x
//   - Commutative: order doesn't matter
// Result: only the unique element remains.
// ============================================================
int findUnique(int arr[], int n) {
    int result = 0;
    int i;
    for (i = 0; i < n; i++)
        result ^= arr[i];
    return result;
}

// ============================================================
// Demonstrate XOR properties
// ============================================================
void demoXorProperties() {
    cout << "=== XOR Properties ===" << endl;

    cout << "  x ^ x = 0  (self-cancel):" << endl;
    cout << "    5 ^ 5 = " << (5 ^ 5) << endl;
    cout << "    42 ^ 42 = " << (42 ^ 42) << endl;
    cout << endl;

    cout << "  x ^ 0 = x  (identity):" << endl;
    cout << "    5 ^ 0 = " << (5 ^ 0) << endl;
    cout << "    0 ^ 7 = " << (0 ^ 7) << endl;
    cout << endl;

    cout << "  Commutative: a ^ b = b ^ a" << endl;
    cout << "    3 ^ 7 = " << (3 ^ 7) << "  and  7 ^ 3 = " << (7 ^ 3) << endl;
    cout << endl;

    cout << "  Associative: (a ^ b) ^ c = a ^ (b ^ c)" << endl;
    cout << "    (3 ^ 7) ^ 5 = " << ((3 ^ 7) ^ 5) << endl;
    cout << "    3 ^ (7 ^ 5) = " << (3 ^ (7 ^ 5)) << endl;
    cout << endl;
}

// ============================================================
// Demo: find unique element
// ============================================================
void demoFindUnique() {
    cout << "=== Find Unique Element ===" << endl;

    // Example 1
    int arr1[] = {4, 1, 2, 1, 2};
    int n1 = 5;
    int i;

    cout << "  Array: {";
    for (i = 0; i < n1; i++)
        cout << arr1[i] << (i + 1 < n1 ? ", " : "");
    cout << "}" << endl;

    int unique = findUnique(arr1, n1);
    cout << "  Unique element: " << unique << endl;
    cout << endl;

    // Walk through XOR accumulation
    cout << "  Step-by-step XOR accumulation:" << endl;
    int acc = 0;
    for (i = 0; i < n1; i++) {
        acc ^= arr1[i];
        cout << "    XOR " << arr1[i] << " -> accumulator = " << acc << endl;
    }
    cout << endl;

    // Example 2
    int arr2[] = {10, 20, 30, 20, 10};
    int n2 = 5;
    cout << "  Array: {10, 20, 30, 20, 10}" << endl;
    cout << "  Unique element: " << findUnique(arr2, n2) << endl;
    cout << endl;

    // Example 3: single element
    int arr3[] = {7};
    cout << "  Array: {7}" << endl;
    cout << "  Unique element: " << findUnique(arr3, 1) << endl;
    cout << endl;
}

// ============================================================
// Why this works: detailed explanation
// ============================================================
void explainWhy() {
    cout << "=== Why This Works ===" << endl;
    cout << "  For {4, 1, 2, 1, 2}:" << endl;
    cout << "  4 ^ 1 ^ 2 ^ 1 ^ 2" << endl;
    cout << "  = 4 ^ (1 ^ 1) ^ (2 ^ 2)    (reorder)" << endl;
    cout << "  = 4 ^ 0 ^ 0                (pairs cancel)" << endl;
    cout << "  = 4                        (identity)" << endl;
    cout << endl;

    cout << "  Time:  O(n) - single pass" << endl;
    cout << "  Space: O(1) - only one variable" << endl;
    cout << endl;
}

int main() {
    cout << "=== 01 - XOR Find Unique Element ===" << endl;
    cout << endl;

    demoXorProperties();
    demoFindUnique();
    explainWhy();

    cout << "--- Summary ---" << endl;
    cout << "XOR all elements: pairs cancel (x^x=0), unique remains (x^0=x)" << endl;
    cout << "Time: O(n), Space: O(1)" << endl;

    return 0;
}
