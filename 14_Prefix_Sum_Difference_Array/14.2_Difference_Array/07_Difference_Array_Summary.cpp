// Difference Array - Complete Summary
// Summary of all difference array techniques, complexities, and applications.

#include <iostream>
#include <iomanip>
using namespace std;

void printSeparator(int width) {
    for (int i = 0; i < width; i++) cout << "-";
    cout << endl;
}

int main() {
    cout << "=== Difference Array - Complete Summary ===" << endl;
    cout << endl;

    // Core concept
    cout << "Core Concept:" << endl;
    cout << "  diff[0] = arr[0]" << endl;
    cout << "  diff[i] = arr[i] - arr[i-1]    for i >= 1" << endl;
    cout << "  arr[i] = diff[0] + diff[1] + ... + diff[i]  (prefix sum)" << endl;
    cout << endl;

    // 1D Range Update
    cout << "1. 1D Range Update O(1):" << endl;
    cout << "   To add val to arr[l..r]:" << endl;
    cout << "     diff[l]   += val    // start adding val from l" << endl;
    cout << "     diff[r+1] -= val    // stop adding val after r" << endl;
    cout << "   Reconstruct: prefix sum of diff -> O(n)" << endl;
    cout << endl;

    // 2D Range Update
    cout << "2. 2D Range Update O(1):" << endl;
    cout << "   To add val to submatrix [r1..r2][c1..c2]:" << endl;
    cout << "     diff[r1][c1]       += val" << endl;
    cout << "     diff[r2+1][c1]     -= val" << endl;
    cout << "     diff[r1][c2+1]     -= val" << endl;
    cout << "     diff[r2+1][c2+1]   += val" << endl;
    cout << "   Reconstruct: row-wise prefix sum, then column-wise -> O(m*n)" << endl;
    cout << endl;

    // Complexity table
    int width = 65;
    printSeparator(width);
    cout << left << setw(30) << "Operation";
    cout << left << setw(15) << "Per Update";
    cout << left << setw(15) << "Reconstruct" << endl;
    printSeparator(width);
    cout << left << setw(30) << "1D Difference Array";
    cout << left << setw(15) << "O(1)";
    cout << left << setw(15) << "O(n)" << endl;
    cout << left << setw(30) << "2D Difference Array";
    cout << left << setw(15) << "O(1)";
    cout << left << setw(15) << "O(m*n)" << endl;
    cout << left << setw(30) << "Naive range update";
    cout << left << setw(15) << "O(n) or O(m*n)";
    cout << left << setw(15) << "N/A" << endl;
    printSeparator(width);

    cout << endl;
    cout << "Applications Covered:" << endl;
    cout << endl;

    cout << "1. Flight Booking (LeetCode 1109)" << endl;
    cout << "   n flights, m bookings [first, last, seats]" << endl;
    cout << "   Each booking is a range update on flights" << endl;
    cout << "   Reconstruct to get seat count per flight" << endl;
    cout << endl;

    cout << "2. Range Addition (LeetCode 370)" << endl;
    cout << "   Start with zeros, apply range additions" << endl;
    cout << "   Pure difference array demonstration" << endl;
    cout << endl;

    cout << "3. Car Pooling (LeetCode 1094)" << endl;
    cout << "   trips [passengers, from, to]" << endl;
    cout << "   diff[from] += passengers (boarding)" << endl;
    cout << "   diff[to] -= passengers (leaving)" << endl;
    cout << "   Check prefix sum never exceeds capacity" << endl;
    cout << endl;

    cout << "4. 2D Range Updates" << endl;
    cout << "   Batch updates on submatrices" << endl;
    cout << "   4-corner update rule" << endl;
    cout << "   Reconstruct with 2D prefix sum" << endl;
    cout << endl;

    // Relationship with prefix sum
    cout << "Relationship with Prefix Sum:" << endl;
    cout << endl;
    cout << "  Prefix Sum:         Precompute for fast QUERIES (O(1)), no updates" << endl;
    cout << "  Difference Array:   Fast UPDATES (O(1)), reconstruct for final state" << endl;
    cout << "  They are inverse operations:" << endl;
    cout << "    prefix_sum(diff(arr)) = arr" << endl;
    cout << "    diff(prefix_sum(arr)) = arr" << endl;
    cout << endl;

    // When to use what
    cout << "Decision Guide:" << endl;
    cout << endl;
    cout << "  Need many range SUMS, no updates   -> Prefix Sum" << endl;
    cout << "  Need many range UPDATES, query at end -> Difference Array" << endl;
    cout << "  Need both updates AND queries        -> Segment Tree / Fenwick Tree" << endl;
    cout << "  Count subarrays with sum K           -> Hash Map + Prefix Sum" << endl;

    return 0;
}
