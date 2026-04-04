/*
 * File: 04_Potential_Method.cpp
 * Topic: Potential Method - Define energy function on state
 * Description: Amortized cost = actual cost + change in potential
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Potential Method ===" << endl;
    cout << endl;

    cout << "--- The Idea ---" << endl;
    cout << "Define a POTENTIAL FUNCTION Phi(state) that measures" << endl;
    cout << "the 'stored energy' or 'prepaid work' in the data structure." << endl;
    cout << endl;

    cout << "--- Formula ---" << endl;
    cout << "  Amortized Cost = Actual Cost + (Phi_after - Phi_before)" << endl;
    cout << "                 = Actual Cost + Delta_Phi" << endl;
    cout << endl;

    cout << "--- Dynamic Array: Phi = 2 * size - capacity ---" << endl;
    cout << "When array is half full: Phi = 2*(n/2) - n = 0" << endl;
    cout << "When array is full:      Phi = 2*n - n = n" << endl;
    cout << endl;

    /*
     * For dynamic array where capacity doubles:
     * Phi = 2 * size - capacity
     *
     * Case 1: No resize (most inserts)
     *   Actual = 1
     *   Phi_before = 2*size - capacity
     *   Phi_after = 2*(size+1) - capacity = Phi_before + 2
     *   Delta_Phi = 2
     *   Amortized = 1 + 2 = 3 = O(1)
     *
     * Case 2: Resize (occasional)
     *   Actual = size + 1 (copy all + insert)
     *   Before: size = capacity, Phi = 2*size - capacity = capacity
     *   After: capacity doubled, Phi = 2 - new_capacity = 2 - 2*capacity = -capacity + 2
     *   Delta_Phi = -capacity + 2
     *   Amortized = (capacity + 1) + (-capacity + 2) = 3 = O(1)
     */

    cout << "--- Step by Step ---" << endl;
    cout << endl;
    cout << "Op | size | cap | Phi  | Actual | Delta_Phi | Amortized" << endl;
    cout << "---|------|-----|------|--------|-----------|----------" << endl;
    cout << " 1 |   1  |  2  |   0  |   2    |    +2     |    3" << endl;
    cout << " 2 |   2  |  4  |   0  |   3    |    +2     |    3" << endl;
    cout << " 3 |   3  |  4  |   2  |   1    |    +2     |    3" << endl;
    cout << " 4 |   4  |  8  |   0  |   5    |    -2     |    3" << endl;
    cout << " 5 |   5  |  8  |   2  |   1    |    +2     |    3" << endl;
    cout << " 6 |   6  |  8  |   4  |   1    |    +2     |    3" << endl;
    cout << " 7 |   7  |  8  |   6  |   1    |    +2     |    3" << endl;
    cout << " 8 |   8  | 16  |   0  |   9    |    -6     |    3" << endl;

    cout << endl;
    cout << "Amortized cost is ALWAYS 3 = O(1)!" << endl;
    cout << endl;
    cout << "--- Three Methods Compared ---" << endl;
    cout << "Aggregate:     Simplest, just divide total by n" << endl;
    cout << "Accounting:    Intuitive, assign credits to ops" << endl;
    cout << "Potential:     Most general, energy function" << endl;
    cout << "All give same result: O(1) amortized for push_back" << endl;

    return 0;
}
