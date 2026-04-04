// 15.2 - DSU with Path Compression
// Path Compression: during find(x), make every node on the path point
// directly to the root. This flattens the tree dramatically.
//
// HOW IT WORKS:
//   find(x) recursively finds the root, then on the way back,
//   sets parent[x] = root for every node on the path.
//
//   Before: 0 -> 1 -> 2 -> 3 (root)
//   After find(0): 0 -> 3, 1 -> 3, 2 -> 3 (all point to root)
//
// TIME: O(log n) amortized per operation with path compression alone.
// Combined with union by rank: O(alpha(n)) ~ O(1).

#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// DSU WITH PATH COMPRESSION
// ============================================================

class DSUPathCompression {
    int parent[1000];
    int n;

public:
    DSUPathCompression(int size) : n(size) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find with path compression (recursive)
    // Makes every node on the path point directly to root
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    // Union: connect root of x to root of y
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    // Print parent array for visualization
    void printParent(int size) {
        cout << "  parent = [";
        for (int i = 0; i < size; i++) {
            if (i > 0) cout << ", ";
            cout << parent[i];
        }
        cout << "]" << endl;
    }
};

// ============================================================
// ITERATIVE PATH COMPRESSION
// Two-pass: first find root, then compress path.
// ============================================================

class DSUPathCompressionIterative {
    int parent[1000];
    int n;

public:
    DSUPathCompressionIterative(int size) : n(size) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Iterative find with path compression
    int find(int x) {
        // First pass: find the root
        int root = x;
        while (parent[root] != root) {
            root = parent[root];
        }

        // Second pass: compress path (make all nodes point to root)
        int curr = x;
        while (curr != root) {
            int next = parent[curr];
            parent[curr] = root;
            curr = next;
        }

        return root;
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    void printParent(int size) {
        cout << "  parent = [";
        for (int i = 0; i < size; i++) {
            if (i > 0) cout << ", ";
            cout << parent[i];
        }
        cout << "]" << endl;
    }
};

// ============================================================
// DEMONSTRATION
// ============================================================

void demoPathCompression() {
    cout << "=== DSU with Path Compression ===" << endl;
    DSUPathCompression dsu(6);

    cout << "Initial:" << endl;
    dsu.printParent(6);
    cout << endl;

    // Build a chain: 0->1->2->3
    dsu.unite(0, 1);
    cout << "unite(0,1):" << endl;
    dsu.printParent(6);

    dsu.unite(1, 2);
    cout << "unite(1,2):" << endl;
    dsu.printParent(6);

    dsu.unite(2, 3);
    cout << "unite(2,3):" << endl;
    dsu.printParent(6);
    cout << endl;

    // Now find(0) will compress the entire path
    cout << "Before find(0): parent[0]=" << dsu.find(0);
    // Reset to show path before compression
    cout << endl;

    cout << "find(0) triggers path compression:" << endl;
    int root = dsu.find(0);
    cout << "  Root of 0 is: " << root << endl;
    cout << "  After compression, parent array:" << endl;
    dsu.printParent(6);
    cout << "  (All nodes on path now point directly to root)" << endl;
    cout << endl;
}

void demoPathCompressionEffect() {
    cout << "=== Path Compression Effect ===" << endl;
    DSUPathCompression dsu(5);

    cout << "Creating chain: unite(0,1), unite(1,2), unite(2,3), unite(3,4)" << endl;
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(2, 3);
    dsu.unite(3, 4);

    cout << "Before compression:" << endl;
    dsu.printParent(5);
    cout << endl;

    cout << "After find(0) (triggers compression):" << endl;
    dsu.find(0);
    dsu.printParent(5);
    cout << "  Note: subsequent find(0) is now O(1)!" << endl;
    cout << endl;
}

void demoIterativeVersion() {
    cout << "=== Iterative Path Compression ===" << endl;
    DSUPathCompressionIterative dsu(5);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(2, 3);
    dsu.unite(3, 4);

    cout << "Before compression:" << endl;
    dsu.printParent(5);

    cout << "After find(0):" << endl;
    dsu.find(0);
    dsu.printParent(5);
    cout << endl;
}

void demoPerformanceComparison() {
    cout << "=== Performance: Basic vs Path Compression ===" << endl;
    cout << endl;
    cout << "Basic DSU (no optimizations):" << endl;
    cout << "  Worst case: tree becomes a linked list, find = O(n)" << endl;
    cout << endl;
    cout << "DSU with Path Compression:" << endl;
    cout << "  First find on a path of length L: O(L)" << endl;
    cout << "  After compression: all nodes on path point to root" << endl;
    cout << "  Subsequent finds: O(1)" << endl;
    cout << "  Amortized: O(log n) per operation" << endl;
    cout << endl;
    cout << "DSU with Path Compression + Union by Rank:" << endl;
    cout << "  Amortized: O(alpha(n)) ~ O(1) per operation" << endl;
    cout << "  alpha(n) = inverse Ackermann function, <= 4 for all practical n" << endl;
    cout << endl;
}

int main() {
    demoPathCompression();
    demoPathCompressionEffect();
    demoIterativeVersion();
    demoPerformanceComparison();
    return 0;
}
