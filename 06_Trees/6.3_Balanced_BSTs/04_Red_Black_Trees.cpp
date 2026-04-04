/*
 * File: 04_Red_Black_Trees.cpp
 * Topic: Red-Black Tree Properties (Conceptual)
 * Description: Rules, comparison with AVL, where it is used
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Red-Black Trees ===" << endl;
    cout << endl;

    cout << "--- Properties ---" << endl;
    cout << "Each node is colored RED or BLACK." << endl;
    cout << endl;
    cout << "Rule 1: Root is always BLACK." << endl;
    cout << "Rule 2: No two consecutive RED nodes." << endl;
    cout << "        (RED node's children must be BLACK)" << endl;
    cout << "Rule 3: Every path from root to NULL has" << endl;
    cout << "        the same number of BLACK nodes." << endl;
    cout << "Rule 4: Height <= 2 * log2(n+1)" << endl;
    cout << "        (approximately balanced)" << endl;
    cout << endl;

    cout << "--- Rebalancing ---" << endl;
    cout << "Uses: Recoloring + Rotations (same 4 types as AVL)" << endl;
    cout << endl;

    cout << "--- AVL vs Red-Black ---" << endl;
    cout << endl;
    cout << "Feature        | AVL              | Red-Black" << endl;
    cout << "---------------|------------------|------------------" << endl;
    cout << "Balance        | Strict           | Relaxed" << endl;
    cout << "Search speed   | Faster (shorter) | Slightly slower" << endl;
    cout << "Insert speed   | More rotations   | Fewer rotations" << endl;
    cout << "Delete speed   | More rotations   | Fewer rotations" << endl;
    cout << "Use when       | Read-heavy       | Mixed read/write" << endl;
    cout << endl;

    cout << "--- Where Used ---" << endl;
    cout << "C++ STL: std::map, std::set use Red-Black Trees" << endl;
    cout << "Java: TreeMap, TreeSet use Red-Black Trees" << endl;
    cout << "Linux CPU scheduler uses Red-Black Trees" << endl;

    return 0;
}
