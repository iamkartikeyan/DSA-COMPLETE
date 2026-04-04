/*
 * Minimum Spanning Tree (MST)
 *
 * MST: Connects all vertices with minimum total edge weight, no cycles.
 * A tree with V vertices has exactly V-1 edges.
 *
 * Prim's Algorithm:
 *   - Greedy: grow MST one vertex at a time
 *   - Uses priority queue (min-heap)
 *   - Time: O((V+E) log V)
 *   - Works well for dense graphs
 *   - Similar to Dijkstra but tracks edge weight to MST, not total distance
 *
 * Kruskal's Algorithm:
 *   - Greedy: sort edges, add smallest that doesn't create cycle
 *   - Uses Union-Find (Disjoint Set Union) for cycle detection
 *   - Time: O(E log E) for sorting
 *   - Works well for sparse graphs
 *
 * Union-Find (DSU):
 *   - find(x): return representative of x's set
 *   - union(a, b): merge sets containing a and b
 *   - Path compression: flatten tree during find
 *   - Union by rank: attach shorter tree under taller tree
 *   - Amortized: nearly O(1) per operation, O(alpha(n))
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

// ============================================================
// UNION-FIND (Disjoint Set Union) with Path Compression & Rank
// ============================================================
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);  // parent[i] = i
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }

    bool unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;  // already same set
        // union by rank
        if (rank[ra] < rank[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) rank[ra]++;
        return true;
    }

    bool connected(int a, int b) { return find(a) == find(b); }
};

// ============================================================
// Edge structure for MST algorithms
// ============================================================
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& o) const { return weight < o.weight; }
};

// ============================================================
// 1. PRIM'S ALGORITHM
//    Greedy vertex-by-vertex expansion
// ============================================================
struct PrimEdge {
    int to, weight, from;
    bool operator>(const PrimEdge& o) const { return weight > o.weight; }
};

pair<int, vector<Edge>> primsMST(int V, const vector<vector<pair<int, int>>>& adj) {
    priority_queue<PrimEdge, vector<PrimEdge>, greater<PrimEdge>> pq;
    vector<bool> inMST(V, false);
    vector<Edge> mst;
    int totalWeight = 0;

    // Start from vertex 0
    pq.push({0, 0, -1});

    while (!pq.empty() && mst.size() < V - 1) {
        auto [w, u, from] = pq.top(); pq.pop();
        if (inMST[u]) continue;

        inMST[u] = true;
        totalWeight += w;
        if (from != -1) mst.push_back({from, u, w});

        for (auto& [v, wt] : adj[u])
            if (!inMST[v]) pq.push({v, wt, u});
    }
    return {totalWeight, mst};
}

// ============================================================
// 2. KRUSKAL'S ALGORITHM
//    Sort edges, add if no cycle (using DSU)
// ============================================================
pair<int, vector<Edge>> kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());  // sort by weight
    DSU dsu(V);
    vector<Edge> mst;
    int totalWeight = 0;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.weight;
            if (mst.size() == V - 1) break;  // MST complete
        }
    }
    return {totalWeight, mst};
}

// ============================================================
// HELPER: Print MST edges and total weight
// ============================================================
void printMST(const string& algo, int totalWeight, const vector<Edge>& mst) {
    cout << algo << " MST (weight=" << totalWeight << "):\n";
    for (auto& e : mst)
        cout << "  " << e.u << " --" << e.weight << "-- " << e.v << "\n";
}

// ============================================================
// MAIN: Demonstrate both MST algorithms
// ============================================================
int main() {
    cout << "=== MINIMUM SPANNING TREE ===\n\n";

    // Sample graph
    //     1
    //   0---1
    //  /|   |\
    // 4 |   | 2
    //  \|   |/
    //   3---2
    //     3
    // Plus edge 0-2 with weight 6
    int V = 4;
    vector<vector<pair<int, int>>> adj(V);
    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };
    addEdge(0, 1, 1); addEdge(0, 3, 4);
    addEdge(1, 2, 2); addEdge(1, 3, 5);
    addEdge(2, 3, 3); addEdge(0, 2, 6);

    // --- Prim's Algorithm ---
    cout << "--- Prim's Algorithm ---\n";
    auto [primWeight, primMST] = primsMST(V, adj);
    printMST("Prim's", primWeight, primMST);
    cout << "\n";

    // --- Kruskal's Algorithm ---
    cout << "--- Kruskal's Algorithm ---\n";
    vector<Edge> edges = {
        {0, 1, 1}, {0, 3, 4}, {1, 2, 2},
        {1, 3, 5}, {2, 3, 3}, {0, 2, 6}
    };
    auto [kruskalWeight, kruskalMST] = kruskalMST(V, edges);
    printMST("Kruskal's", krusalWeight, kruskalMST);
    cout << "\n";

    // --- Union-Find Demo ---
    cout << "--- Union-Find (DSU) Demo ---\n";
    DSU dsu(6);
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    dsu.unite(1, 2);
    cout << "find(0) == find(3)? " << dsu.connected(0, 3) << "\n";  // true (0-1-2-3)
    cout << "find(0) == find(5)? " << dsu.connected(0, 5) << "\n";  // false
    dsu.unite(3, 5);
    cout << "After unite(3,5): find(0) == find(5)? " << dsu.connected(0, 5) << "\n\n";

    // --- Comparison ---
    cout << "--- Algorithm Comparison ---\n";
    cout << "Prim's:    O((V+E)log V), grows from a vertex, good for dense\n";
    cout << "Kruskal's: O(E log E), sorts edges, good for sparse\n";
    cout << "Both produce same total weight (MST is unique if all weights distinct)\n";

    // --- Key Properties ---
    cout << "\n--- MST Properties ---\n";
    cout << "MST connects all V vertices with exactly V-1 edges\n";
    cout << "Total weight is minimum possible among all spanning trees\n";
    cout << "If all edge weights are distinct, MST is unique\n";
    cout << "Cut property: lightest edge crossing any cut is in MST\n";
    cout << "Cycle property: heaviest edge in any cycle is NOT in MST\n";

    return 0;
}
