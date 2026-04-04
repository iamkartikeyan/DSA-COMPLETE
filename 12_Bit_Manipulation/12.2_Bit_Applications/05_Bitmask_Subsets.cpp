// 05 - Bitmask Subsets
// Generate all subsets using bitmask (2^n masks)
// Each bit represents inclusion of an element

#include <iostream>

using namespace std;

// Print binary representation
void printBinary(int n, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--)
        cout << ((n >> i) & 1);
}

// ============================================================
// Print a single subset given the array and a bitmask
// Each bit in mask represents whether nums[i] is included
// ============================================================
void printSubset(int nums[], int n, int mask) {
    int i;
    int first = 1;
    cout << "  {";
    for (i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            if (!first)
                cout << ", ";
            cout << nums[i];
            first = 0;
        }
    }
    cout << "}" << endl;
}

// ============================================================
// Generate and print all subsets using bitmask
// For n elements, there are 2^n subsets (mask 0 to 2^n - 1)
// ============================================================
void generateAllSubsets(int nums[], int n) {
    int total = 1 << n;  // 2^n
    int mask;

    cout << "  Total subsets: " << total << endl;
    cout << endl;

    for (mask = 0; mask < total; mask++) {
        cout << "  Mask ";
        printBinary(mask, n);
        cout << " (" << mask << "): ";
        printSubset(nums, n, mask);
    }
}

// ============================================================
// Demo: subsets of {1, 2, 3}
// ============================================================
void demoSubsets3() {
    cout << "=== Subsets of {1, 2, 3} ===" << endl;

    int nums[] = {1, 2, 3};
    int n = 3;

    generateAllSubsets(nums, n);
    cout << endl;
}

// ============================================================
// Demo: subsets of {10, 20, 30, 40}
// ============================================================
void demoSubsets4() {
    cout << "=== Subsets of {10, 20, 30, 40} ===" << endl;

    int nums[] = {10, 20, 30, 40};
    int n = 4;

    generateAllSubsets(nums, n);
    cout << endl;
}

// ============================================================
// Explain the bitmask-subset correspondence
// ============================================================
void explainBitmaskMapping() {
    cout << "=== How Bitmask Maps to Subsets ===" << endl;
    cout << endl;
    cout << "  For {a, b, c} (indices 0, 1, 2):" << endl;
    cout << "  Bit i = 1 means include element at index i" << endl;
    cout << endl;
    cout << "  Mask  0b000 (0): {}           (empty set)" << endl;
    cout << "  Mask  0b001 (1): {a}          (bit 0 set)" << endl;
    cout << "  Mask  0b010 (2): {b}          (bit 1 set)" << endl;
    cout << "  Mask  0b011 (3): {a, b}       (bits 0,1 set)" << endl;
    cout << "  Mask  0b100 (4): {c}          (bit 2 set)" << endl;
    cout << "  Mask  0b101 (5): {a, c}       (bits 0,2 set)" << endl;
    cout << "  Mask  0b110 (6): {b, c}       (bits 1,2 set)" << endl;
    cout << "  Mask  0b111 (7): {a, b, c}    (all bits set)" << endl;
    cout << endl;
}

// ============================================================
// Practical application: filter subsets by property
// ============================================================
void demoFilterSubsets() {
    cout << "=== Filter: Subsets with Sum >= 5 ===" << endl;

    int nums[] = {1, 2, 3};
    int n = 3;
    int total = 1 << n;  // 2^3 = 8
    int mask;

    for (mask = 0; mask < total; mask++) {
        int sum = 0;
        int i;
        for (i = 0; i < n; i++) {
            if (mask & (1 << i))
                sum += nums[i];
        }

        if (sum >= 5) {
            cout << "  Mask " << mask << ": ";
            printSubset(nums, n, mask);
            cout << "  (sum = " << sum << ")" << endl;
        }
    }
    cout << endl;
}

// ============================================================
// Count subsets of a given size
// ============================================================
void demoSubsetSizes() {
    cout << "=== Subsets by Size ===" << endl;

    int n = 3;
    int total = 1 << n;
    int mask;
    int counts[] = {0, 0, 0, 0};  // counts[0] = empty, counts[1] = size 1, etc.

    for (mask = 0; mask < total; mask++) {
        int size = 0;
        int i;
        for (i = 0; i < n; i++) {
            if (mask & (1 << i))
                size++;
        }
        counts[size]++;
    }

    int k;
    for (k = 0; k <= n; k++) {
        cout << "  Size " << k << ": " << counts[k] << " subsets" << endl;
    }
    cout << "  (C(3,";
    int k2;
    for (k2 = 0; k2 <= n; k2++) {
        if (k2 > 0) cout << "), C(3,";
        cout << k2;
    }
    cout << "))" << endl;
    cout << endl;
}

int main() {
    cout << "=== 05 - Bitmask Subsets ===" << endl;
    cout << endl;

    explainBitmaskMapping();
    demoSubsets3();
    demoFilterSubsets();
    demoSubsetSizes();
    demoSubsets4();

    cout << "--- Summary ---" << endl;
    cout << "Each n-bit mask represents a subset of {0..n-1}" << endl;
    cout << "Bit i set -> include element at index i" << endl;
    cout << "Total subsets: 2^n (from mask 0 to 2^n - 1)" << endl;
    cout << "Useful for: generating subsets, filtering by properties, combinatorial search" << endl;

    return 0;
}
