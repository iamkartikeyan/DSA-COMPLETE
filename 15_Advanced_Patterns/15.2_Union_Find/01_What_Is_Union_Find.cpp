// 15.2 - What Is Union-Find (Disjoint Set Union - DSU)
// Tracks partition of elements into disjoint sets.
// Supports two operations:
//   - find(x): which set does element x belong to?
//   - union(x, y): merge the sets containing x and y
//
// APPLICATIONS:
//   - Connected components in graphs
//   - Cycle detection in undirected graphs
//   - Kruskal's Minimum Spanning Tree
//   - Redundant connection detection
//   - Dynamic connectivity queries
//   - Image processing (connected pixel regions)
//
// OPTIMIZATIONS:
//   - Path Compression: flatten tree during find -> near O(1)
//   - Union by Rank: attach shorter tree to taller tree
//   - Union by Size: attach smaller tree to larger tree
//
// With both optimizations: O(alpha(n)) ~ O(1) amortized per operation.

#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// NAIVE UNION-FIND (no optimizations)
// Simple array-based implementation for understanding.
// parent[i] = parent of node i. Root has parent[i] == i.
// ============================================================

class NaiveUnionFind {
    int parent[1000];
    int n;

public:
    NaiveUnionFind(int size) : n(size) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // Each element is its own root initially
        }
    }

    // Find: follow parent pointers to root (no path compression)
    int find(int x) {
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    }

    // Union: connect root of x to root of y (no rank optimization)
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;  // Make rootY the parent of rootX
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

void demoNaiveUnionFind() {
    cout << "=== Naive Union-Find (No Optimizations) ===" << endl;
    NaiveUnionFind uf(6);

    cout << "Initially: each element is its own set" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "  find(" << i << ") = " << uf.find(i) << endl;
    }
    cout << endl;

    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(1, 2);

    cout << "After unite(0,1), unite(2,3), unite(1,2):" << endl;
    cout << "  0 connected to 3? " << (uf.connected(0, 3) ? "Yes" : "No") << endl;
    cout << "  0 connected to 4? " << (uf.connected(0, 4) ? "Yes" : "No") << endl;
    cout << endl;
}

// ============================================================
// VISUALIZING THE TREE STRUCTURE
// ============================================================

void demoTreeVisualization() {
    cout << "=== Union-Find Tree Structure ===" << endl;
    cout << endl;
    cout << "Initial state (each element is its own root):" << endl;
    cout << "  0  1  2  3  4  5   <- elements" << endl;
    cout << "  0  1  2  3  4  5   <- parent[i]" << endl;
    cout << endl;
    cout << "After unite(0, 1): parent[0] = 1" << endl;
    cout << "  0->1  2  3  4  5   (0 is child of 1)" << endl;
    cout << endl;
    cout << "After unite(2, 3): parent[2] = 3" << endl;
    cout << "  0->1  2->3  4  5" << endl;
    cout << endl;
    cout << "After unite(1, 2): parent[1] = 3 (or parent[3] = 1)" << endl;
    cout << "  0->1->3  2->3  4  5   => all of {0,1,2,3} have root 3" << endl;
    cout << endl;
    cout << "find(0): 0 -> 1 -> 3 (root)" << endl;
    cout << "find(2): 2 -> 3 (root)" << endl;
    cout << "find(0) == find(2) => connected!" << endl;
    cout << endl;
}

// ============================================================
// WHY OPTIMIZATIONS MATTER
// ============================================================

void demoWhyOptimizationsMatter() {
    cout << "=== Why Optimizations Matter ===" << endl;
    cout << endl;
    cout << "Without optimizations, the tree can become a linked list (O(n) find)." << endl;
    cout << "Example: unite(0,1), unite(1,2), unite(2,3), ... creates a chain." << endl;
    cout << endl;
    cout << "Path Compression: During find(x), make all nodes point directly to root." << endl;
    cout << "  Before: 0 -> 1 -> 2 -> 3 (root)" << endl;
    cout << "  After find(0): 0 -> 3, 1 -> 3, 2 -> 3 (flattened)" << endl;
    cout << endl;
    cout << "Union by Rank: Always attach the shorter tree under the taller tree." << endl;
    cout << "  This keeps the tree height logarithmic." << endl;
    cout << endl;
    cout << "With BOTH: amortized time per operation is O(alpha(n)) ~ O(1)." << endl;
    cout << "  alpha(n) is the inverse Ackermann function, <= 4 for all practical n." << endl;
    cout << endl;
}

int main() {
    demoNaiveUnionFind();
    demoTreeVisualization();
    demoWhyOptimizationsMatter();
    return 0;
}
