// 15.2 - Union-Find Summary
// Complete reference for Disjoint Set Union (DSU) patterns and applications.

#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// OPTIMIZED DSU CLASS (reference implementation)
// ============================================================

class DSU {
    int parent[1000];
    int rankArr[1000];
    int n;
    int components;

public:
    DSU(int size) : n(size), components(size) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rankArr[i] = 0;
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
        if (rankArr[rootX] < rankArr[rootY]) {
            parent[rootX] = rootY;
        } else if (rankArr[rootX] > rankArr[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rankArr[rootX]++;
        }
        components--;
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
    int getComponents() const { return components; }
};

// ============================================================
// CORE CONCEPTS
// ============================================================

void demoCoreConcepts() {
    cout << "=== UNION-FIND CORE CONCEPTS ===" << endl;
    cout << endl;
    cout << "WHAT IT DOES:" << endl;
    cout << "  Maintains a partition of elements into disjoint (non-overlapping) sets." << endl;
    cout << "  Supports two operations efficiently:" << endl;
    cout << "    - find(x): return the representative of x's set" << endl;
    cout << "    - unite(x, y): merge the sets containing x and y" << endl;
    cout << endl;
    cout << "DATA STRUCTURE:" << endl;
    cout << "  Each set is represented as a tree." << endl;
    cout << "  parent[i] points to i's parent. Root has parent[i] == i." << endl;
    cout << "  find(x) follows parent pointers to the root." << endl;
    cout << endl;
    cout << "OPTIMIZATIONS:" << endl;
    cout << "  1. Path Compression: during find, make all nodes point to root" << endl;
    cout << "  2. Union by Rank: attach shorter tree under taller tree" << endl;
    cout << "  3. Union by Size: attach smaller tree under larger tree" << endl;
    cout << "  With 1+2 or 1+3: O(alpha(n)) ~ O(1) amortized per operation" << endl;
    cout << endl;
}

// ============================================================
// IMPLEMENTATION COMPARISON
// ============================================================

void demoImplementationComparison() {
    cout << "=== IMPLEMENTATION COMPARISON ===" << endl;
    cout << endl;
    cout << "Approach                  | find Time     | unite Time" << endl;
    cout << "--------------------------|---------------|------------" << endl;
    cout << "Naive (array + chaining)  | O(n) worst    | O(n) worst" << endl;
    cout << "Path compression only     | O(log n) amort| O(log n)" << endl;
    cout << "Union by rank only        | O(log n) worst| O(log n)" << endl;
    cout << "Path compression + rank   | O(alpha(n))   | O(alpha(n))" << endl;
    cout << "Path compression + size   | O(alpha(n))   | O(alpha(n))" << endl;
    cout << endl;
    cout << "alpha(n) = inverse Ackermann function" << endl;
    cout << "  alpha(n) <= 4 for all practical values of n" << endl;
    cout << "  For n = number of atoms in the universe, alpha(n) <= 4" << endl;
    cout << endl;
}

// ============================================================
// APPLICATION CATALOG
// ============================================================

void demoApplicationCatalog() {
    cout << "=== APPLICATION CATALOG ===" << endl;
    cout << endl;
    cout << "1. Connected Components" << endl;
    cout << "   Count disjoint groups in a graph. unite all edges, count components." << endl;
    cout << endl;
    cout << "2. Cycle Detection (Undirected Graph)" << endl;
    cout << "   If unite(u, v) returns false for edge (u,v), a cycle exists." << endl;
    cout << endl;
    cout << "3. Kruskal's Minimum Spanning Tree" << endl;
    cout << "   Sort edges by weight. Add if unite succeeds. Stop at n-1 edges." << endl;
    cout << endl;
    cout << "4. Redundant Connection" << endl;
    cout << "   Find the edge that creates a cycle in tree + 1 edge." << endl;
    cout << endl;
    cout << "5. Number of Provinces" << endl;
    cout << "   Given adjacency matrix, count connected components." << endl;
    cout << endl;
    cout << "6. Dynamic Connectivity" << endl;
    cout << "   Online queries: can x reach y? Support adding edges." << endl;
    cout << endl;
    cout << "7. Accounts Merge" << endl;
    cout << "   Group accounts sharing emails. Map email -> index, unite." << endl;
    cout << endl;
    cout << "8. Image Processing" << endl;
    cout << "   Connected pixel regions. Unite adjacent same-color pixels." << endl;
    cout << endl;
    cout << "9. Percolation" << endl;
    cout << "   Does fluid flow from top to bottom? Use virtual top/bottom nodes." << endl;
    cout << endl;
    cout << "10. Equality Constraints" << endl;
    cout << "    Given a==b, b==c, check if a==c. Unite equal variables." << endl;
    cout << endl;
}

// ============================================================
// CODE TEMPLATE
// ============================================================

void demoCodeTemplate() {
    cout << "=== DSU CODE TEMPLATE ===" << endl;
    cout << endl;
    cout << "class DSU {" << endl;
    cout << "    int parent[1000], rank[1000];" << endl;
    cout << "    int components;" << endl;
    cout << "public:" << endl;
    cout << "    DSU(int n) : components(n) {" << endl;
    cout << "        for (int i = 0; i < n; i++) {" << endl;
    cout << "            parent[i] = i; rank[i] = 0;" << endl;
    cout << "        }" << endl;
    cout << "    }" << endl;
    cout << "    int find(int x) {" << endl;
    cout << "        if (parent[x] != x)" << endl;
    cout << "            parent[x] = find(parent[x]);" << endl;
    cout << "        return parent[x];" << endl;
    cout << "    }" << endl;
    cout << "    bool unite(int x, int y) {" << endl;
    cout << "        int px = find(x), py = find(y);" << endl;
    cout << "        if (px == py) return false;" << endl;
    cout << "        if (rank[px] < rank[py]) swap(px, py);" << endl;
    cout << "        parent[py] = px;" << endl;
    cout << "        if (rank[px] == rank[py]) rank[px]++;" << endl;
    cout << "        components--;" << endl;
    cout << "        return true;" << endl;
    cout << "    }" << endl;
    cout << "};" << endl;
    cout << endl;
}

// ============================================================
// COMMON MISTAKES
// ============================================================

void demoCommonMistakes() {
    cout << "=== COMMON MISTAKES ===" << endl;
    cout << endl;
    cout << "1. Forgetting path compression -> O(n) find in worst case" << endl;
    cout << "2. Forgetting union by rank -> tree becomes a chain" << endl;
    cout << "3. Using unite() result: false means ALREADY connected (cycle)" << endl;
    cout << "4. Off-by-one: 1-indexed vs 0-indexed nodes" << endl;
    cout << "5. Not checking if roots are same before uniting" << endl;
    cout << "6. Using find() instead of unite() for merging" << endl;
    cout << endl;
}

// ============================================================
// QUICK DEMO
// ============================================================

void demoQuickDemo() {
    cout << "=== Quick Demo ===" << endl;
    DSU dsu(6);

    dsu.unite(0, 1);
    dsu.unite(2, 3);
    dsu.unite(1, 2);
    dsu.unite(4, 5);

    cout << "After uniting: (0,1), (2,3), (1,2), (4,5)" << endl;
    cout << "Components: " << dsu.getComponents() << endl;
    cout << "0 connected to 3? " << (dsu.connected(0, 3) ? "Yes" : "No") << endl;
    cout << "0 connected to 4? " << (dsu.connected(0, 4) ? "Yes" : "No") << endl;
    cout << endl;
}

int main() {
    demoCoreConcepts();
    demoImplementationComparison();
    demoApplicationCatalog();
    demoCodeTemplate();
    demoCommonMistakes();
    demoQuickDemo();
    return 0;
}
