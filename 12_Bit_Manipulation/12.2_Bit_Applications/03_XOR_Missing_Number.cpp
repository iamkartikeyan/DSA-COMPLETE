// 03 - XOR Find Missing Number
// Find the missing number in 0..n array using XOR
// One number is missing from the range [0, n]

#include <iostream>

using namespace std;

// ============================================================
// Find the missing number in an array of size n that contains
// numbers from 0 to n with exactly one number missing.
//
// Algorithm:
//   XOR all numbers 0..n with all array elements.
//   Every present number appears twice (once in range, once in array)
//   and cancels out. Only the missing number remains.
// ============================================================
int findMissing(int arr[], int n) {
    // XOR of all numbers 0..n
    int xorRange = 0;
    int i;
    for (i = 0; i <= n; i++)
        xorRange ^= i;

    // XOR of all array elements
    int xorArray = 0;
    for (i = 0; i < n; i++)
        xorArray ^= arr[i];

    // Missing number = xorRange ^ xorArray
    return xorRange ^ xorArray;
}

// ============================================================
// Demo
// ============================================================
void demoFindMissing() {
    cout << "=== Find Missing Number ===" << endl;

    // Example 1: {0, 1, 3, 4}, missing = 2
    int arr1[] = {0, 1, 3, 4};
    int n1 = 4;
    int i;

    cout << "  Array: {0, 1, 3, 4}  (size " << n1 << ", range 0.." << n1 << ")" << endl;
    cout << "  XOR of 0..4: ";
    int xorRange = 0;
    for (i = 0; i <= n1; i++) {
        xorRange ^= i;
        cout << i << "^";
    }
    cout << " = " << xorRange << endl;

    cout << "  XOR of array:  ";
    int xorArray = 0;
    for (i = 0; i < n1; i++) {
        xorArray ^= arr1[i];
        cout << arr1[i] << "^";
    }
    cout << " = " << xorArray << endl;

    int missing = findMissing(arr1, n1);
    cout << "  Missing number: " << xorRange << " ^ " << xorArray << " = " << missing << endl;
    cout << endl;

    // Example 2: {3, 0, 1}, missing = 2
    int arr2[] = {3, 0, 1};
    int n2 = 3;
    cout << "  Array: {3, 0, 1}  (size " << n2 << ", range 0.." << n2 << ")" << endl;
    cout << "  Missing number: " << findMissing(arr2, n2) << endl;
    cout << endl;

    // Example 3: {0}, missing = 1
    int arr3[] = {0};
    int n3 = 1;
    cout << "  Array: {0}  (size " << n3 << ", range 0.." << n3 << ")" << endl;
    cout << "  Missing number: " << findMissing(arr3, n3) << endl;
    cout << endl;

    // Example 4: {1}, missing = 0
    int arr4[] = {1};
    int n4 = 1;
    cout << "  Array: {1}  (size " << n4 << ", range 0.." << n4 << ")" << endl;
    cout << "  Missing number: " << findMissing(arr4, n4) << endl;
    cout << endl;
}

// ============================================================
// Why this works
// ============================================================
void explainWhy() {
    cout << "=== Why This Works ===" << endl;
    cout << "  For {0, 1, 3, 4} (missing 2):" << endl;
    cout << "  XOR 0..4:  0 ^ 1 ^ 2 ^ 3 ^ 4" << endl;
    cout << "  XOR array: 0 ^ 1 ^ 3 ^ 4" << endl;
    cout << "  Combined:  0^0 ^ 1^1 ^ 2 ^ 3^3 ^ 4^4" << endl;
    cout << "             = 0 ^ 0 ^ 2 ^ 0 ^ 0" << endl;
    cout << "             = 2  (the missing number)" << endl;
    cout << endl;

    cout << "  Time:  O(n) - two passes" << endl;
    cout << "  Space: O(1) - no extra storage" << endl;
    cout << "  No overflow risk (unlike sum-based approach)" << endl;
    cout << endl;
}

int main() {
    cout << "=== 03 - XOR Find Missing Number ===" << endl;
    cout << endl;

    demoFindMissing();
    explainWhy();

    cout << "--- Summary ---" << endl;
    cout << "XOR range [0..n] with array -> missing number remains" << endl;
    cout << "Time: O(n), Space: O(1), no overflow issues" << endl;

    return 0;
}
