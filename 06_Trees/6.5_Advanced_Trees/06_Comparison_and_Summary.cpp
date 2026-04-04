/*
 * File: 06_Comparison_and_Summary.cpp
 * Topic: Trie vs Segment Tree vs Fenwick Tree comparison
 * Description: When to use each, complexity table
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Advanced Trees - Comparison & Summary ===" << endl;
    cout << endl;

    cout << "--- Trie ---" << endl;
    cout << "Purpose: Store and search strings/prefixes" << endl;
    cout << "Use for: Autocomplete, spell check, IP routing" << endl;
    cout << "Time: Insert = O(L), Search = O(L), Prefix = O(L)" << endl;
    cout << "Space: O(26 * N * L) worst case" << endl;
    cout << endl;

    cout << "--- Segment Tree ---" << endl;
    cout << "Purpose: Range queries (sum, min, max, etc.)" << endl;
    cout << "Use for: Any associative operation on a range" << endl;
    cout << "Time: Build = O(n), Query = O(log n), Update = O(log n)" << endl;
    cout << "Space: O(n) for tree array (4n)" << endl;
    cout << endl;

    cout << "--- Fenwick Tree (BIT) ---" << endl;
    cout << "Purpose: Prefix sums and range sums" << endl;
    cout << "Use for: Sum/XOR queries, counting inversions" << endl;
    cout << "Time: Build = O(n), Query = O(log n), Update = O(log n)" << endl;
    cout << "Space: O(n) for BIT array (n+1)" << endl;
    cout << endl;

    cout << "--- Segment Tree vs Fenwick Tree ---" << endl;
    cout << endl;
    cout << "Feature     | Segment Tree    | Fenwick Tree" << endl;
    cout << "------------|-----------------|------------------" << endl;
    cout << "Operations  | Any associative | Invertible only" << endl;
    cout << "            | (min, max, sum) | (sum, xor)" << endl;
    cout << "Code length | Longer          | Shorter" << endl;
    cout << "Space       | 4n              | n" << endl;
    cout << "Flexibility | More flexible   | Limited but fast" << endl;
    cout << "Easier?     | No              | Yes" << endl;
    cout << endl;

    cout << "--- When to Use ---" << endl;
    cout << "Trie:          String problems, prefix search, autocomplete" << endl;
    cout << "Segment Tree:  Range min/max/sum, range updates (with lazy prop)" << endl;
    cout << "Fenwick Tree:  Prefix/range sums, simpler than segment tree" << endl;
    cout << endl;

    cout << "--- Topics Covered ---" << endl;
    cout << "Trie:" << endl;
    cout << "  01. Trie Basics           - Node, Insert, Search" << endl;
    cout << "  02. Trie Autocomplete     - Collect words with prefix" << endl;
    cout << "Segment Tree:" << endl;
    cout << "  03. Segment Tree Basics   - Build, Range Sum" << endl;
    cout << "  04. Segment Tree Update   - Point Update + Query" << endl;
    cout << "Fenwick Tree:" << endl;
    cout << "  05. Fenwick Tree Basics   - Prefix Sum, Range Sum, Update" << endl;
    cout << "  06. Comparison & Summary  - This file" << endl;

    return 0;
}
