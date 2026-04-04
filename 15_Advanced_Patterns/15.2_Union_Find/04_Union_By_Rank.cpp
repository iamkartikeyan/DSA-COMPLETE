// 15.2 - DSU with Union by Rank + Path Compression
// Union by Rank: always attach the shorter tree under the taller tree.
// Rank approximates tree height. When ranks are equal, increment the new root's rank.
//
// Combined with path compression: O(alpha(n)) ~ O(1) amortized per operation.
// This is the standard, production-quality DSU implementation.
//
// HOW UNION BY RANK WORKS:
//   - Each root has a "rank" (approximate height of its tree)
//   - When uniting trees with roots rx and ry:
//     * If rank[rx] < rank[ry]: attach rx under ry
//     * If rank[rx] > rank[ry]: attach ry under rx
//     * If rank[rx] == rank[ry]: attach either, increment new root's rank

#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// DSU WITH PATH COMPRESSION + UNION BY RANK
// ============================================================

class DSU {
    int parent[1000];
    int rankArr[1000];  // Approximate tree height
    int n;
    int components;     // Number of connected components

public:
    DSU(int size) : n(size), components(size) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rankArr[i] = 0;  // All trees start with rank 0 (single node)
        }
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union by rank: attach shorter tree to taller tree
    // Returns true if a merge happened, false if already same set
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false;  // Already in same set

        // Attach the shorter tree under the taller tree
        if (rankArr[rootX] < rankArr[rootY]) {
            parent[rootX] = rootY;
        } else if (rankArr[rootX] > rankArr[rootY]) {
            parent[rootY] = rootX;
        } else {
            // Same rank: attach either, increment the new root's rank
            parent[rootY] = rootX;
            rankArr[rootX]++;
        }

        components--;
        return true;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int getComponents() const { return components; }

    void printState(int size) {
        cout << "  parent = [";
        for (int i = 0; i < size; i++) {
            if (i > 0) cout << ", ";
            cout << parent[i];
        }
        cout << "]" << endl;

        cout << "  rank   = [";
        for (int i = 0; i < size; i++) {
            if (i > 0) cout << ", ";
            cout << rankArr[i];
        }
        cout << "]" << endl;
    }
};

// ============================================================
// DSU WITH UNION BY SIZE
// Track size of each component. Attach smaller to larger.
// Useful for "largest component" queries.
// ============================================================

class DSUBySize {
    int parent[1000];
    int size[1000];
    int n;

public:
    DSUBySize(int size) : n(size) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            this->size[i] = 1;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false;

        // Attach smaller tree under larger tree
        if (size[rootX] < size[rootY]) {
            int temp = rootX;
            rootX = rootY;
            rootY = temp;
        }
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
        return true;
    }

    int getSize(int x) { return size[find(x)]; }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

// ============================================================
// DEMONSTRATION
// ============================================================

void demoUnionByRank() {
    cout << "=== DSU with Union by Rank + Path Compression ===" << endl;
    DSU dsu(6);

    cout << "Initial:" << endl;
    dsu.printState(6);
    cout << endl;

    cout << "unite(0, 1):" << endl;
    dsu.unite(0, 1);
    dsu.printState(6);
    cout << "  rank[0] becomes 1 (two trees of rank 0 merged)" << endl;
    cout << endl;

    cout << "unite(2, 3):" << endl;
    dsu.unite(2, 3);
    dsu.printState(6);
    cout << "  rank[2] becomes 1" << endl;
    cout << endl;

    cout << "unite(1, 2) - merge two trees of rank 1:" << endl;
    dsu.unite(1, 2);
    dsu.printState(6);
    cout << "  Both had rank 1, so new root gets rank 2" << endl;
    cout << "  Tree height stays logarithmic, not linear" << endl;
    cout << endl;

    cout << "unite(4, 5):" << endl;
    dsu.unite(4, 5);
    dsu.printState(6);
    cout << endl;

    cout << "Components: " << dsu.getComponents() << endl;
    cout << "  {0,1,2,3} and {4,5}" << endl;
    cout << "  0 connected to 3? " << (dsu.connected(0, 3) ? "Yes" : "No") << endl;
    cout << "  0 connected to 4? " << (dsu.connected(0, 4) ? "Yes" : "No") << endl;
    cout << endl;
}

void demoUnionBySize() {
    cout << "=== DSU with Union by Size ===" << endl;
    DSUBySize dsu(5);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    cout << "After unite(0,1), unite(1,2), unite(3,4):" << endl;
    cout << "  Component size of 0: " << dsu.getSize(0) << endl;  // 3
    cout << "  Component size of 3: " << dsu.getSize(3) << endl;  // 2
    cout << "  0 connected to 2? " << (dsu.connected(0, 2) ? "Yes" : "No") << endl;
    cout << "  0 connected to 3? " << (dsu.connected(0, 3) ? "Yes" : "No") << endl;
    cout << endl;
}

void demoRankVsSize() {
    cout << "=== Union by Rank vs Union by Size ===" << endl;
    cout << endl;
    cout << "Union by Rank:" << endl;
    cout << "  - Uses approximate tree height" << endl;
    cout << "  - Good for keeping tree height small" << endl;
    cout << "  - Does NOT track component size" << endl;
    cout << endl;
    cout << "Union by Size:" << endl;
    cout << "  - Uses actual number of nodes in subtree" << endl;
    cout << "  - Also keeps tree height small" << endl;
    cout << "  - CAN answer 'what is the size of x's component?'" << endl;
    cout << endl;
    cout << "Both achieve O(alpha(n)) amortized with path compression." << endl;
    cout << "Choose by size if you need component size queries." << endl;
    cout << endl;
}

void demoCompleteExample() {
    cout << "=== Complete Example: Network Connections ===" << endl;
    cout << "Scenario: 8 computers, some are connected by cables." << endl;
    cout << "Cables: (0-1), (2-3), (1-2), (4-5), (6-7)" << endl;
    cout << endl;

    DSU dsu(8);
    int edges[][2] = {{0, 1}, {2, 3}, {1, 2}, {4, 5}, {6, 7}};
    int numEdges = 5;

    for (int i = 0; i < numEdges; i++) {
        dsu.unite(edges[i][0], edges[i][1]);
    }

    cout << "Components: " << dsu.getComponents() << endl;
    cout << endl;

    cout << "Connectivity check:" << endl;
    cout << "  0-3: " << (dsu.connected(0, 3) ? "Connected" : "Not connected") << endl;
    cout << "  0-4: " << (dsu.connected(0, 4) ? "Connected" : "Not connected") << endl;
    cout << "  6-7: " << (dsu.connected(6, 7) ? "Connected" : "Not connected") << endl;
    cout << endl;
}

int main() {
    demoUnionByRank();
    demoUnionBySize();
    demoRankVsSize();
    demoCompleteExample();
    return 0;
}
