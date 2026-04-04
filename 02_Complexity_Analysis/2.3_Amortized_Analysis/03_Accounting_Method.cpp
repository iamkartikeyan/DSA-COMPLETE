/*
 * File: 03_Accounting_Method.cpp
 * Topic: Accounting Method - Assign credits/charges to operations
 * Description: Overcharge cheap ops, save credits for expensive ones
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Accounting Method ===" << endl;
    cout << endl;

    cout << "--- The Idea ---" << endl;
    cout << "Assign an artificial 'charge' to each operation." << endl;
    cout << "Charge MORE than actual cost for cheap operations." << endl;
    cout << "Save the extra as CREDITS." << endl;
    cout << "Use credits to pay for expensive operations." << endl;
    cout << endl;

    cout << "--- Dynamic Array Example ---" << endl;
    cout << endl;

    /*
     * Charge $3 for each push:
     *   $1 = actual insertion cost
     *   $1 = save to copy THIS element later (when it gets moved)
     *   $1 = save to copy an element that was inserted before
     *
     * When resize happens:
     *   Each element has $1 saved = enough to copy it
     *   Total credits = size = enough for all copies
     *   Credits never go negative!
     */

    cout << "Charge $3 per push:" << endl;
    cout << "  $1 for actual insertion" << endl;
    cout << "  $1 saved for copying THIS element during resize" << endl;
    cout << "  $1 saved for copying an OLD element during resize" << endl;
    cout << endl;

    cout << "--- Step by Step ---" << endl;
    cout << endl;
    cout << "Op | Action      | Charge | Actual | Credits After" << endl;
    cout << "---|-------------|--------|--------|--------------" << endl;
    cout << " 1 | Insert + res|   $3   |   $2   |     $2       " << endl;
    cout << " 2 | Insert + res|   $3   |   $3   |     $3       " << endl;
    cout << " 3 | Insert      |   $3   |   $1   |     $5       " << endl;
    cout << " 4 | Insert + res|   $3   |   $5   |     $3       " << endl;
    cout << " 5 | Insert      |   $3   |   $1   |     $5       " << endl;
    cout << " 6 | Insert      |   $3   |   $1   |     $7       " << endl;
    cout << " 7 | Insert      |   $3   |   $1   |     $9       " << endl;
    cout << " 8 | Insert + res|   $3   |   $9   |     $3       " << endl;

    cout << endl;
    cout << "Credits NEVER go negative!" << endl;
    cout << "This proves amortized cost = $3 = O(1) per operation" << endl;
    cout << endl;
    cout << "--- Why This Works ---" << endl;
    cout << "If we can always pay for actual cost using credits," << endl;
    cout << "then the charged amount is an upper bound on amortized cost." << endl;

    return 0;
}
