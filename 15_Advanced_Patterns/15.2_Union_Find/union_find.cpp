// 15.2 Union-Find (Disjoint Set Union - DSU)
// Tracks partition of elements into disjoint sets.
// Supports find (which set?) and union (merge sets) in near-O(1) time.
// Optimizations: path compression + union by rank.

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// ============================================================
// UNION-FIND CLASS
// Path compression: flattens tree during find.
// Union by rank: attaches shorter tree to taller tree.
// Time: O(alpha(n)) ~ O(1) amortized per operation.
// ============================================================

class UnionFind {
    vector<int> parent;
    vector<int> rank;
    int components;  // Number of connected components

public:
    UnionFind(int n) : parent(n), rank(n, 0), components(n) {
        iota(parent.begin(), parent.end(), 0);  // parent[i] = i
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // Path compression
        return parent[x];
    }

    // Union by rank
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;  // Already same set

        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
        components--;
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
    int getComponents() const { return components; }
};

void demoBasicUnionFind() {
    cout << "=== Basic Union-Find ===" << endl;
    UnionFind uf(6);

    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(1, 2);
    uf.unite(4, 5);

    cout << "0 connected to 3? " << (uf.connected(0, 3) ? "Yes" : "No") << endl;  // Yes
    cout << "0 connected to 4? " << (uf.connected(0, 4) ? "Yes" : "No") << endl;  // No
    cout << "Components: " << uf.getComponents() << endl;  // 2: {0,1,2,3} and {4,5}
    cout << endl;
}

// ============================================================
// APPLICATION 1: Number of Connected Components
// ============================================================

int countConnectedComponents(int n, const vector<vector<int>>& edges) {
    UnionFind uf(n);
    for (auto& e : edges) uf.unite(e[0], e[1]);
    return uf.getComponents();
}

void demoConnectedComponents() {
    cout << "=== Application: Connected Components ===" << endl;
    int n = 5;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {3, 4}};
    cout << "Nodes: " << n << ", Edges: (0-1), (1-2), (3-4)" << endl;
    cout << "Connected Components: " << countConnectedComponents(n, edges) << endl;  // 2
    cout << endl;
}

// ============================================================
// APPLICATION 2: Kruskal's Minimum Spanning Tree
// Sort edges by weight, add if they connect two different components.
// Time: O(E log E) for sorting + O(E * alpha(V)) for union-find.
// ============================================================

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

int kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    int mstWeight = 0, edgeCount = 0;

    for (auto& e : edges) {
        if (uf.unite(e.u, e.v)) {
            mstWeight += e.w;
            edgeCount++;
            if (edgeCount == n - 1) break;  // MST has n-1 edges
        }
    }
    return mstWeight;
}

void demoKruskalMST() {
    cout << "=== Kruskal's MST ===" << endl;
    int n = 4;
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
        {1, 3, 15}, {2, 3, 4}
    };
    cout << "MST Weight: " << kruskalMST(n, edges) << endl;  // 19 (edges: 2-3, 0-3, 0-1)
    cout << endl;
}

// ============================================================
// APPLICATION 3: Detect Cycle in Undirected Graph
// If two vertices of an edge are already in same set, cycle exists.
// ============================================================

bool hasCycle(int n, const vector<vector<int>>& edges) {
    UnionFind uf(n);
    for (auto& e : edges) {
        if (!uf.unite(e[0], e[1]))
            return true;  // Already connected => cycle
    }
    return false;
}

void demoCycleDetection() {
    cout << "=== Cycle Detection ===" << endl;
    // Triangle: 0-1-2-0 => cycle
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
    cout << "Triangle: has cycle? " << (hasCycle(3, edges1) ? "Yes" : "No") << endl;

    // Tree: 0-1, 1-2 => no cycle
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}};
    cout << "Tree: has cycle? " << (hasCycle(3, edges2) ? "Yes" : "No") << endl;
    cout << endl;
}

// ============================================================
// APPLICATION 4: Redundant Connection (LeetCode 684)
// Find the edge that causes a cycle in a tree + 1 edge.
// ============================================================

vector<int> findRedundantConnection(const vector<vector<int>>& edges) {
    int n = edges.size();  // n edges for n nodes (tree has n-1)
    UnionFind uf(n + 1);
    for (auto& e : edges) {
        if (!uf.unite(e[0], e[1])) return e;  // First cycle-causing edge
    }
    return {};
}

void demoRedundantConnection() {
    cout << "=== Redundant Connection ===" << endl;
    vector<vector<int>> edges = {{1, 2}, {1, 3}, {2, 3}};
    auto result = findRedundantConnection(edges);
    cout << "Edges: (1,2), (1,3), (2,3). Redundant: (" << result[0] << "," << result[1] << ")" << endl;
    cout << endl;
}

// ============================================================
// APPLICATION 5: Accounts Merge (LeetCode 721) - Simplified
// Group accounts sharing emails using union-find.
// ============================================================

void demoAccountsMerge() {
    cout << "=== Accounts Merge (Concept) ===" << endl;
    cout << "Idea: Map each email to an index. Union accounts sharing emails." << endl;
    cout << "Then collect all emails under each root representative." << endl;
    cout << "This avoids O(n^2) pairwise comparison." << endl << endl;
}

// ============================================================
// UNION-FIND WITH SIZE TRACKING
// Track size of each component. Useful for "largest component" queries.
// ============================================================

class UnionFindBySize {
    vector<int> parent, size;
public:
    UnionFindBySize(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (size[px] < size[py]) swap(px, py);  // Attach smaller to larger
        parent[py] = px;
        size[px] += size[py];
        return true;
    }

    int getSize(int x) { return size[find(x)]; }
};

void demoUnionFindBySize() {
    cout << "=== Union-Find by Size ===" << endl;
    UnionFindBySize uf(5);
    uf.unite(0, 1); uf.unite(1, 2); uf.unite(3, 4);
    cout << "Component size of 0: " << uf.getSize(0) << endl;  // 3
    cout << "Component size of 3: " << uf.getSize(3) << endl;  // 2
    cout << endl;
}

int main() {
    demoBasicUnionFind();
    demoConnectedComponents();
    demoKruskalMST();
    demoCycleDetection();
    demoRedundantConnection();
    demoAccountsMerge();
    demoUnionFindBySize();
    return 0;
}
