// 15.2 - Basic DSU (Simple Union-Find without optimizations)
// Simple array-based implementation with find and union.
// No path compression, no union by rank.
// Useful for understanding the basic concept before adding optimizations.

#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// BASIC DSU CLASS
// parent[i] = parent of node i. Root has parent[i] == i.
// ============================================================

class BasicDSU {
    int parent[1000];
    int n;

public:
    BasicDSU(int size) : n(size) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // Each element is its own root initially
        }
    }

    // Find: follow parent pointers until we reach the root
    // Returns the representative (root) of the set containing x
    int find(int x) {
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    }

    // Union: merge the sets containing x and y
    // Connects root of x to root of y
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;  // Attach tree of x under tree of y
        }
    }

    // Check if x and y are in the same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

// ============================================================
// COUNT CONNECTED COMPONENTS (naive approach)
// ============================================================

int countComponents(int n, const int edges[][2], int numEdges) {
    BasicDSU dsu(n);
    int components = n;

    for (int i = 0; i < numEdges; i++) {
        int rootX = dsu.find(edges[i][0]);
        int rootY = dsu.find(edges[i][1]);
        if (rootX != rootY) {
            dsu.unite(edges[i][0], edges[i][1]);
            components--;
        }
    }
    return components;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoBasicOperations() {
    cout << "=== Basic DSU Operations ===" << endl;
    BasicDSU dsu(6);

    cout << "Initial state:" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "  parent[" << i << "] = " << dsu.find(i) << endl;
    }
    cout << endl;

    cout << "unite(0, 1)" << endl;
    dsu.unite(0, 1);
    cout << "  find(0) = " << dsu.find(0) << ", find(1) = " << dsu.find(1) << endl;
    cout << "  0 connected to 1? " << (dsu.connected(0, 1) ? "Yes" : "No") << endl;
    cout << endl;

    cout << "unite(2, 3)" << endl;
    dsu.unite(2, 3);
    cout << "  find(2) = " << dsu.find(2) << ", find(3) = " << dsu.find(3) << endl;
    cout << endl;

    cout << "unite(1, 2) - merges {0,1} with {2,3}" << endl;
    dsu.unite(1, 2);
    cout << "  find(0) = " << dsu.find(0) << ", find(3) = " << dsu.find(3) << endl;
    cout << "  0 connected to 3? " << (dsu.connected(0, 3) ? "Yes" : "No") << endl;
    cout << "  0 connected to 4? " << (dsu.connected(0, 4) ? "Yes" : "No") << endl;
    cout << endl;
}

void demoConnectedComponents() {
    cout << "=== Count Connected Components ===" << endl;

    // Graph: 0-1-2, 3-4, 5 (isolated)
    int edges[][2] = {{0, 1}, {1, 2}, {3, 4}};
    int n = 6;
    int numEdges = 3;

    cout << "Graph edges: (0-1), (1-2), (3-4)" << endl;
    cout << "Nodes: " << n << ", Edges: " << numEdges << endl;
    cout << "Connected components: " << countComponents(n, edges, numEdges) << endl;
    cout << "Expected: 3 components: {0,1,2}, {3,4}, {5}" << endl;
    cout << endl;
}

void demoStepByStep() {
    cout << "=== Step-by-Step: unite(0,1), unite(2,3), unite(1,2) ===" << endl;
    BasicDSU dsu(4);

    cout << "Step 0: parent = [0, 1, 2, 3]" << endl;

    dsu.unite(0, 1);
    cout << "Step 1: unite(0,1) -> parent[0] = 1" << endl;
    cout << "        parent = [1, 1, 2, 3]" << endl;

    dsu.unite(2, 3);
    cout << "Step 2: unite(2,3) -> parent[2] = 3" << endl;
    cout << "        parent = [1, 1, 3, 3]" << endl;

    dsu.unite(1, 2);
    cout << "Step 3: unite(1,2) -> find(1)=1, find(2)=3 -> parent[1] = 3" << endl;
    cout << "        parent = [1, 3, 3, 3]" << endl;
    cout << "  Now find(0): 0->1->3 (root=3)" << endl;
    cout << "  All of {0,1,2,3} share root 3" << endl;
    cout << endl;
}

int main() {
    demoStepByStep();
    demoBasicOperations();
    demoConnectedComponents();
    return 0;
}
