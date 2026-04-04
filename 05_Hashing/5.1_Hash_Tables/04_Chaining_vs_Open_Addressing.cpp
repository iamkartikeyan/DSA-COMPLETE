/*
 * File: 04_Chaining_vs_Open_Addressing.cpp
 * Topic: Comparison of collision resolution methods
 * Description: When to use chaining vs open addressing
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Chaining vs Open Addressing ===" << endl;
    cout << endl;

    cout << "--- Chaining ---" << endl;
    cout << "Method:      Each bucket = linked list" << endl;
    cout << "Pros:        Handles any number of collisions" << endl;
    cout << "             Delete is easy" << endl;
    cout << "             Higher load factor OK (0.75)" << endl;
    cout << "Cons:        Extra memory for pointers" << endl;
    cout << "             Cache unfriendly (linked list traversal)" << endl;
    cout << endl;

    cout << "--- Open Addressing ---" << endl;
    cout << "Method:      All in array, probe for next slot" << endl;
    cout << "Pros:        No pointers (less memory)" << endl;
    cout << "             Cache friendly (array traversal)" << endl;
    cout << "Cons:        Delete needs tombstones" << endl;
    cout << "             Lower load factor needed (0.5)" << endl;
    cout << "             Clustering problem (keys group together)" << endl;
    cout << endl;

    cout << "--- Probing Variants ---" << endl;
    cout << "Linear Probing:     Check i+1, i+2, i+3... (simple but clusters)" << endl;
    cout << "Quadratic Probing:  Check i+1^2, i+2^2, i+3^2... (reduces clustering)" << endl;
    cout << "Double Hashing:     Use second hash function for step size (best)" << endl;
    cout << endl;

    cout << "--- When to Use ---" << endl;
    cout << "Chaining:        General purpose, easy to implement" << endl;
    cout << "Open Addressing: Memory-constrained, need cache performance" << endl;
    cout << endl;

    cout << "--- Rehashing ---" << endl;
    cout << "When load factor exceeds threshold:" << endl;
    cout << "  1. Double the capacity" << endl;
    cout << "  2. Re-insert all entries with new hash" << endl;
    cout << "  3. Amortized cost: still O(1) per insert" << endl;
    cout << endl;
    cout << "Complexity (Average): Insert O(1), Search O(1), Delete O(1)" << endl;
    cout << "Complexity (Worst):   Insert O(n), Search O(n), Delete O(n)" << endl;

    return 0;
}
