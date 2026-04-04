/*
 * File: 06_Complexity_Comparison.cpp
 * Topic: All Balanced Trees Complexity Summary
 * Description: Time complexity table and when to use each
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Balanced Trees - Complexity Summary ===" << endl;
    cout << endl;

    cout << "--- Time Complexity ---" << endl;
    cout << endl;
    cout << "Tree     | Search    | Insert    | Delete    | Rebalancing" << endl;
    cout << "---------|-----------|-----------|-----------|---------------------" << endl;
    cout << "BST      | O(h)      | O(h)      | O(h)      | None (h can be O(n))" << endl;
    cout << "AVL      | O(log n)  | O(log n)  | O(log n)  | Rotations (1-2)" << endl;
    cout << "RedBlack | O(log n)  | O(log n)  | O(log n)  | Recolor + Rotations" << endl;
    cout << "B-Tree   | O(log n)  | O(log n)  | O(log n)  | Split/Merge nodes" << endl;
    cout << endl;

    cout << "--- Space Complexity ---" << endl;
    cout << "All: O(n) for n nodes" << endl;
    cout << endl;

    cout << "--- When to Use ---" << endl;
    cout << "BST:        Learning, small datasets" << endl;
    cout << "AVL:        Fast lookups, read-heavy workloads" << endl;
    cout << "Red-Black:  General purpose (C++ map/set, Java TreeMap)" << endl;
    cout << "B-Tree:     Databases, file systems (disk-based storage)" << endl;
    cout << "B+ Tree:    Range queries in databases" << endl;
    cout << endl;

    cout << "--- AVL Topics Covered ---" << endl;
    cout << "01. AVL Node Structure + Height + Balance Factor" << endl;
    cout << "02. Four Rotations (LL, RR, LR, RL)" << endl;
    cout << "03. AVL Insert with Rebalancing" << endl;
    cout << "04. Red-Black Trees (Conceptual)" << endl;
    cout << "05. B-Trees (Conceptual)" << endl;
    cout << "06. Complexity Comparison (this file)" << endl;

    return 0;
}
