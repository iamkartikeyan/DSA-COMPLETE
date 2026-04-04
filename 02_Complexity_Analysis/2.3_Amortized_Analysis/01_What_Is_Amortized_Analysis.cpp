/*
 * File: 01_What_Is_Amortized_Analysis.cpp
 * Topic: What is Amortized Analysis, why it matters
 * Description: Average cost per operation over a sequence
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== What is Amortized Analysis? ===" << endl;
    cout << endl;

    cout << "--- The Problem ---" << endl;
    cout << "Some operations are usually fast, but occasionally slow." << endl;
    cout << "Worst case says they're always slow, which is misleading." << endl;
    cout << endl;

    cout << "--- Example: Dynamic Array (vector) ---" << endl;
    cout << "push_back() is:" << endl;
    cout << "  - O(1) most of the time (just add element)" << endl;
    cout << "  - O(n) sometimes (need to resize + copy)" << endl;
    cout << endl;
    cout << "If we do n push_backs:" << endl;
    cout << "  - Worst case: each is O(n) -> O(n^2) total" << endl;
    cout << "  - ACTUAL: only O(n) total because resize is rare!" << endl;
    cout << endl;

    cout << "--- Amortized Analysis ---" << endl;
    cout << "Instead of worst case PER operation," << endl;
    cout << "we look at AVERAGE cost over a SEQUENCE of operations." << endl;
    cout << endl;

    cout << "  Amortized Cost = Total cost / Number of operations" << endl;
    cout << endl;

    /*
     * Dynamic Array Resize Pattern:
     * Capacity: 1, 2, 4, 8, 16, ...
     * Resize at: 1, 2, 4, 8, 16, ...
     * Copy cost: 1 + 2 + 4 + 8 + ... + n/2 = n - 1
     * Insert cost: n (one per element)
     * Total: n + (n - 1) = 2n - 1 = O(n)
     * Amortized: O(n) / n = O(1) per operation!
     */

    cout << "--- Dynamic Array Example ---" << endl;
    cout << "Inserting 8 elements into array (starts capacity 1):" << endl;
    cout << endl;

    cout << "Op # | Action        | Cost  | Cumulative" << endl;
    cout << "-----|---------------|-------|------------" << endl;
    cout << "  1  | Insert + resize| 2     | 2          " << endl;
    cout << "  2  | Insert + resize| 3     | 5          " << endl;
    cout << "  3  | Insert         | 1     | 6          " << endl;
    cout << "  4  | Insert + resize| 5     | 11         " << endl;
    cout << "  5  | Insert         | 1     | 12         " << endl;
    cout << "  6  | Insert         | 1     | 13         " << endl;
    cout << "  7  | Insert         | 1     | 14         " << endl;
    cout << "  8  | Insert + resize| 9     | 23         " << endl;

    cout << endl;
    cout << "Total cost for 8 inserts: 23" << endl;
    cout << "Amortized cost: 23 / 8 = ~3 per operation = O(1)" << endl;
    cout << endl;

    cout << "--- Three Methods ---" << endl;
    cout << "1. Aggregate Method: Total cost / n" << endl;
    cout << "2. Accounting Method: Assign credits to operations" << endl;
    cout << "3. Potential Method: Energy function on state" << endl;

    return 0;
}
