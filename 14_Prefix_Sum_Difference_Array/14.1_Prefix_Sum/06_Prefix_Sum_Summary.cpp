// Prefix Sum - Complete Summary
// Summary table of all prefix sum techniques, complexities, and use cases.

#include <iostream>
#include <iomanip>
using namespace std;

void printSeparator(int width) {
    for (int i = 0; i < width; i++) cout << "-";
    cout << endl;
}

int main() {
    cout << "=== Prefix Sum - Complete Summary ===" << endl;
    cout << endl;

    // Summary table
    cout << "Techniques Overview:" << endl;
    cout << endl;

    cout << "1. 1D Prefix Sum" << endl;
    cout << "   Formula:   prefix[i] = prefix[i-1] + arr[i-1]" << endl;
    cout << "   Query:     sum(l,r) = prefix[r+1] - prefix[l]" << endl;
    cout << "   Build:     O(n)" << endl;
    cout << "   Query:     O(1)" << endl;
    cout << "   Updates:   NOT supported (static array)" << endl;
    cout << "   Use when:  Many range sum queries on fixed array" << endl;
    cout << endl;

    cout << "2. 2D Prefix Sum (Summed Area Table)" << endl;
    cout << "   Formula:   prefix[i][j] = mat[i-1][j-1] + prefix[i-1][j]" << endl;
    cout << "              + prefix[i][j-1] - prefix[i-1][j-1]" << endl;
    cout << "   Query:     sum(r1,c1,r2,c2) = prefix[r2+1][c2+1]" << endl;
    cout << "              - prefix[r1][c2+1] - prefix[r2+1][c1]" << endl;
    cout << "              + prefix[r1][c1]" << endl;
    cout << "   Build:     O(m * n)" << endl;
    cout << "   Query:     O(1)" << endl;
    cout << "   Updates:   NOT supported (static matrix)" << endl;
    cout << "   Use when:  Many submatrix sum queries on fixed matrix" << endl;
    cout << endl;

    cout << "3. Hash Map + Prefix Sum (Subarray Sum = K)" << endl;
    cout << "   Formula:   count(prefixSum[j] - prefixSum[i] == k)" << endl;
    cout << "   Time:      O(n)" << endl;
    cout << "   Space:     O(n) for hash map" << endl;
    cout << "   Use when:  Count subarrays with a specific sum" << endl;
    cout << endl;

    cout << "4. Fenwick Tree (Binary Indexed Tree)" << endl;
    cout << "   Update:    add(idx, delta) in O(log n)" << endl;
    cout << "   Query:     prefix sum in O(log n)" << endl;
    cout << "   Range:     sum(l,r) = query(r) - query(l-1)" << endl;
    cout << "   Build:     O(n log n) or O(n) optimized" << endl;
    cout << "   Use when:  Point updates + range sums needed" << endl;
    cout << endl;

    // Comparison table
    int width = 70;
    printSeparator(width);
    cout << left << setw(25) << "Technique";
    cout << left << setw(12) << "Build";
    cout << left << setw(12) << "Query";
    cout << left << setw(12) << "Update" << endl;
    printSeparator(width);
    cout << left << setw(25) << "1D Prefix Sum";
    cout << left << setw(12) << "O(n)";
    cout << left << setw(12) << "O(1)";
    cout << left << setw(12) << "N/A" << endl;
    cout << left << setw(25) << "2D Prefix Sum";
    cout << left << setw(12) << "O(m*n)";
    cout << left << setw(12) << "O(1)";
    cout << left << setw(12) << "N/A" << endl;
    cout << left << setw(25) << "Subarray Sum = K";
    cout << left << setw(12) << "O(n)";
    cout << left << setw(12) << "O(n)";
    cout << left << setw(12) << "N/A" << endl;
    cout << left << setw(25) << "Fenwick Tree";
    cout << left << setw(12) << "O(n log n)";
    cout << left << setw(12) << "O(log n)";
    cout << left << setw(12) << "O(log n)" << endl;
    printSeparator(width);

    cout << endl;
    cout << "When to Use What:" << endl;
    cout << endl;
    cout << "  Fixed array + many range sums  -> 1D Prefix Sum" << endl;
    cout << "  Fixed matrix + many submatrix    -> 2D Prefix Sum" << endl;
    cout << "  Count subarrays with sum K       -> Hash Map + Prefix Sum" << endl;
    cout << "  Dynamic array + range sums       -> Fenwick Tree" << endl;
    cout << "  Range updates + point queries      -> Difference Array (see 14.2)" << endl;
    cout << endl;

    // Quick example: 1D prefix sum
    cout << "Quick Example - 1D Prefix Sum:" << endl;
    int arr[] = {3, 1, 4, 1, 5, 9};
    int n = 6;
    int prefix[7];
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }

    cout << "  arr:    ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "  prefix: ";
    for (int i = 0; i <= n; i++) cout << prefix[i] << " ";
    cout << endl;
    cout << "  sum(1,4) = prefix[5] - prefix[1] = " << prefix[5] << " - " << prefix[1] << " = ";
    cout << prefix[5] - prefix[1] << " (which is 1+4+1+5)" << endl;

    return 0;
}
