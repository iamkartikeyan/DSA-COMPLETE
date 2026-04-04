// 15.2 - DSU Applications
// Connected components, cycle detection, Kruskal's MST, redundant connection.
// All using the optimized DSU with path compression + union by rank.

#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// DSU CLASS (optimized)
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

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int getComponents() const { return components; }
};

// ============================================================
// APPLICATION 1: Count Connected Components
// Given n nodes and a list of edges, count connected components.
// ============================================================

int countConnectedComponents(int n, const int edges[][2], int numEdges) {
    DSU dsu(n);
    for (int i = 0; i < numEdges; i++) {
        dsu.unite(edges[i][0], edges[i][1]);
    }
    return dsu.getComponents();
}

void demoConnectedComponents() {
    cout << "=== Application 1: Connected Components ===" << endl;

    int edges1[][2] = {{0, 1}, {1, 2}, {3, 4}};
    int n1 = 5;
    cout << "Graph 1: " << n1 << " nodes, edges: (0-1), (1-2), (3-4)" << endl;
    cout << "Components: " << countConnectedComponents(n1, edges1, 3) << endl;
    cout << "Expected: 2 ({0,1,2} and {3,4})" << endl;
    cout << endl;

    int edges2[][2] = {{0, 1}, {2, 3}, {4, 5}};
    int n2 = 6;
    cout << "Graph 2: " << n2 << " nodes, edges: (0-1), (2-3), (4-5)" << endl;
    cout << "Components: " << countConnectedComponents(n2, edges2, 3) << endl;
    cout << "Expected: 3" << endl;
    cout << endl;
}

// ============================================================
// APPLICATION 2: Cycle Detection in Undirected Graph
// If unite(x, y) returns false, x and y are already connected => cycle.
// ============================================================

bool hasCycle(int n, const int edges[][2], int numEdges) {
    DSU dsu(n);
    for (int i = 0; i < numEdges; i++) {
        if (!dsu.unite(edges[i][0], edges[i][1])) {
            return true;  // Edge connects two nodes already in same component
        }
    }
    return false;
}

void demoCycleDetection() {
    cout << "=== Application 2: Cycle Detection ===" << endl;

    // Triangle: 0-1-2-0 => cycle
    int triangle[][2] = {{0, 1}, {1, 2}, {2, 0}};
    cout << "Triangle (0-1, 1-2, 2-0): has cycle? "
         << (hasCycle(3, triangle, 3) ? "Yes" : "No") << endl;

    // Tree: 0-1, 1-2 => no cycle
    int tree[][2] = {{0, 1}, {1, 2}};
    cout << "Tree (0-1, 1-2): has cycle? "
         << (hasCycle(3, tree, 2) ? "Yes" : "No") << endl;

    // Square with diagonal: 0-1-3-2-0, plus 1-2 => cycle
    int square[][2] = {{0, 1}, {1, 3}, {3, 2}, {2, 0}, {1, 2}};
    cout << "Square+diagonal: has cycle? "
         << (hasCycle(4, square, 5) ? "Yes" : "No") << endl;
    cout << endl;
}

// ============================================================
// APPLICATION 3: Kruskal's Minimum Spanning Tree
// Sort edges by weight. Add edge if it connects two different components.
// Stop when we have n-1 edges (MST property).
// ============================================================

struct Edge {
    int u, v, w;
};

// Simple bubble sort for edges by weight
void sortEdges(Edge edges[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int kruskalMST(int n, Edge edges[], int numEdges) {
    sortEdges(edges, numEdges);

    DSU dsu(n);
    int mstWeight = 0;
    int edgeCount = 0;

    cout << "  Sorted edges by weight:" << endl;
    for (int i = 0; i < numEdges; i++) {
        cout << "    (" << edges[i].u << "," << edges[i].v << ") w=" << edges[i].w << endl;
    }

    for (int i = 0; i < numEdges; i++) {
        if (dsu.unite(edges[i].u, edges[i].v)) {
            mstWeight += edges[i].w;
            edgeCount++;
            cout << "  Added (" << edges[i].u << "," << edges[i].v << ") w=" << edges[i].w << endl;
            if (edgeCount == n - 1) break;
        } else {
            cout << "  Skipped (" << edges[i].u << "," << edges[i].v << ") - would create cycle" << endl;
        }
    }

    return mstWeight;
}

void demoKruskalMST() {
    cout << "=== Application 3: Kruskal's MST ===" << endl;
    int n = 4;
    Edge edges[] = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
        {1, 3, 15}, {2, 3, 4}
    };
    int numEdges = 5;

    cout << "Graph: " << n << " nodes, " << numEdges << " edges" << endl;
    int mstWeight = kruskalMST(n, edges, numEdges);
    cout << "  MST Weight: " << mstWeight << endl;  // 19
    cout << endl;
}

// ============================================================
// APPLICATION 4: Redundant Connection (LeetCode 684)
// Find the edge that causes a cycle in a tree + 1 edge.
// Returns the edge as a pair.
// ============================================================

void findRedundantConnection(int n, const int edges[][2], int numEdges, int &resultU, int &resultV) {
    DSU dsu(n);
    resultU = -1;
    resultV = -1;

    for (int i = 0; i < numEdges; i++) {
        if (!dsu.unite(edges[i][0], edges[i][1])) {
            resultU = edges[i][0];
            resultV = edges[i][1];
            return;
        }
    }
}

void demoRedundantConnection() {
    cout << "=== Application 4: Redundant Connection ===" << endl;

    int edges1[][2] = {{1, 2}, {1, 3}, {2, 3}};
    int u, v;
    findRedundantConnection(4, edges1, 3, u, v);
    cout << "Edges: (1,2), (1,3), (2,3). Redundant: (" << u << "," << v << ")" << endl;
    cout << "Expected: (2,3)" << endl;
    cout << endl;

    int edges2[][2] = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    findRedundantConnection(6, edges2, 5, u, v);
    cout << "Edges: (1,2), (2,3), (3,4), (1,4), (1,5). Redundant: (" << u << "," << v << ")" << endl;
    cout << "Expected: (1,4)" << endl;
    cout << endl;
}

// ============================================================
// APPLICATION 5: Number of Provinces (LeetCode 547)
// Given adjacency matrix, count connected components.
// ============================================================

int countProvinces(const int matrix[][3], int n) {
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] == 1) {
                dsu.unite(i, j);
            }
        }
    }
    return dsu.getComponents();
}

void demoProvinces() {
    cout << "=== Application 5: Number of Provinces ===" << endl;
    int matrix[][3] = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    int n = 3;

    cout << "Adjacency matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << " " << matrix[i][j];
        }
        cout << endl;
    }
    cout << "Provinces: " << countProvinces(matrix, n) << endl;  // 2
    cout << endl;
}

int main() {
    demoConnectedComponents();
    demoCycleDetection();
    demoKruskalMST();
    demoRedundantConnection();
    demoProvinces();
    return 0;
}
