/*
 * File: 05_Amortized_Analysis_Summary.cpp
 * Topic: Complete amortized analysis summary
 * Description: All methods, examples, and when to use each
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Amortized Analysis - Summary ===" << endl;
    cout << endl;

    cout << "--- Key Concept ---" << endl;
    cout << "Amortized analysis looks at AVERAGE cost per operation" << endl;
    cout << "over a SEQUENCE of operations, not worst case per operation." << endl;
    cout << endl;

    cout << "--- Three Methods ---" << endl;
    cout << endl;
    cout << "1. Aggregate Method" << endl;
    cout << "   Formula: Total cost / n operations" << endl;
    cout << "   Easiest to understand" << endl;
    cout << "   Example: n push_backs = O(n) total -> O(1) each" << endl;
    cout << endl;
    cout << "2. Accounting Method" << endl;
    cout << "   Assign 'credits' to operations" << endl;
    cout << "   Overcharge cheap ops, save for expensive ones" << endl;
    cout << "   Example: Charge $3 per push, use credits for resize" << endl;
    cout << endl;
    cout << "3. Potential Method" << endl;
    cout << "   Define Phi(state) = energy of data structure" << endl;
    cout << "   Amortized = Actual + Delta_Phi" << endl;
    cout << "   Most general and powerful method" << endl;
    cout << endl;

    cout << "--- Common Examples ---" << endl;
    cout << endl;
    cout << "Dynamic Array push_back: O(1) amortized" << endl;
    cout << "  - Most: O(1), Resize: O(n), but rare" << endl;
    cout << endl;
    cout << "Stack push/pop: O(1) amortized" << endl;
    cout << "  - Even with multipop (pop k at once)" << endl;
    cout << endl;
    cout << "Binary counter increment: O(1) amortized" << endl;
    cout << "  - Each bit flips half as often as previous" << endl;
    cout << endl;
    cout << "Union-Find with path compression: O(alpha(n)) amortized" << endl;
    cout << "  - Nearly constant (alpha(n) <= 4 for all practical n)" << endl;
    cout << endl;

    cout << "--- Worst Case vs Amortized ---" << endl;
    cout << "Worst case:  'This ONE operation could be O(n)'" << endl;
    cout << "Amortized:   'But over n operations, average is O(1)'" << endl;
    cout << endl;
    cout << "Use amortized when operations are SEQUENTIAL and" << endl;
    cout << "expensive operations are RARE or PREPAID." << endl;

    return 0;
}
