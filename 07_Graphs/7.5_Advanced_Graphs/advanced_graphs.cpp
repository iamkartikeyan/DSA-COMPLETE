/*
 * Advanced Graph Algorithms
 *
 * Topological Sort:
 *   - Linear ordering of DAG vertices where edges go forward
 *   - Kahn's Algorithm: BFS with in-degree tracking
 *   - DFS: post-order + reverse
 *   - Applications: build systems, task scheduling, course prerequisites
 *
 * Strongly Connected Components (Kosaraju's):
 *   - Maximal subgraph where every vertex reaches every other
 *   - Step 1: DFS on G, record finish order
 *   - Step 2: Reverse all edges (G^T)
 *   - Step 3: DFS on G^T in reverse finish order
 *   - Each DFS tree = one SCC
 *
 * Articulation Points & Bridges:
 *   - Articulation Point: removing it disconnects the graph
 *   - Bridge: removing it disconnects the graph
 *   - Uses DFS with discovery time + low-link values
 *   - low[u] = earliest discovery reachable via back edges
 *
 * Bipartite Check:
 *   - Graph can be 2-colored (no two adjacent same color)
 *   - No odd-length cycles
 *   - BFS/DFS coloring approach
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// ============================================================
// 1. TOPOLOGICAL SORT - Kahn's Algorithm (BFS)
// ============================================================
vector<int> topologicalSortKahn(int V, const vector<vector<int>>& adj) {
    vector<int> inDegree(V, 0);
    for (int u = 0; u < V; ++u)
        for (int v : adj[u]) inDegree[v]++;

    queue<int> q;
    for (int i = 0; i < V; ++i)
        if (inDegree[i] == 0) q.push(i);

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) q.push(v);
        }
    }
    return topo;  // size < V means graph has a cycle
}

// Topological Sort - DFS approach
void topoDFS(int u, const vector<vector<int>>& adj, vector<bool>& visited,
             vector<int>& order) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) topoDFS(v, adj, visited, order);
    order.push_back(u);  // post-order
}

vector<int> topologicalSortDFS(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    vector<int> order;
    for (int i = 0; i < V; ++i)
        if (!visited[i]) topoDFS(i, adj, visited, order);
    reverse(order.begin(), order.end());  // reverse post-order
    return order;
}

// ============================================================
// 2. STRONGLY CONNECTED COMPONENTS (Kosaraju's)
// ============================================================
void fillOrder(int u, const vector<vector<int>>& adj,
               vector<bool>& visited, vector<int>& order) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) fillOrder(v, adj, visited, order);
    order.push_back(u);
}

void dfsSCC(int u, const vector<vector<int>>& adj,
            vector<bool>& visited, vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    for (int v : adj[u])
        if (!visited[v]) dfsSCC(v, adj, visited, component);
}

// Reverse the graph
vector<vector<int>> reverseGraph(int V, const vector<vector<int>>& adj) {
    vector<vector<int>> rev(V);
    for (int u = 0; u < V; ++u)
        for (int v : adj[u]) rev[v].push_back(u);
    return rev;
}

vector<vector<int>> kosarajuSCC(int V, const vector<vector<int>>& adj) {
    // Step 1: Fill order by finish time
    vector<bool> visited(V, false);
    vector<int> order;
    for (int i = 0; i < V; ++i)
        if (!visited[i]) fillOrder(i, adj, visited, order);

    // Step 2: Reverse graph
    auto rev = reverseGraph(V, adj);

    // Step 3: DFS on reversed graph in reverse finish order
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> sccs;
    for (int i = V - 1; i >= 0; --i) {
        if (!visited[order[i]]) {
            vector<int> comp;
            dfsSCC(order[i], rev, visited, comp);
            sccs.push_back(comp);
        }
    }
    return sccs;
}

// ============================================================
// 3. ARTICULATION POINTS & BRIDGES (Tarjan's)
// ============================================================
void findArticulationBridges(int u, int p, const vector<vector<int>>& adj,
                             vector<int>& disc, vector<int>& low,
                             vector<bool>& isAP, vector<pair<int, int>>& bridges,
                             int& timer) {
    disc[u] = low[u] = timer++;
    int children = 0;

    for (int v : adj[u]) {
        if (v == p) continue;
        if (disc[v] != -1) {
            // Back edge
            low[u] = min(low[u], disc[v]);
        } else {
            // Tree edge
            children++;
            findArticulationBridges(v, u, adj, disc, low, isAP, bridges, timer);
            low[u] = min(low[u], low[v]);

            // Bridge: low[v] > disc[u]
            if (low[v] > disc[u]) bridges.push_back({u, v});

            // Articulation point: low[v] >= disc[u] (not root)
            if (p != -1 && low[v] >= disc[u]) isAP[u] = true;
        }
    }
    // Root is AP if it has > 1 child in DFS tree
    if (p == -1 && children > 1) isAP[u] = true;
}

pair<vector<int>, vector<pair<int, int>>> findAPAndBridges(
        int V, const vector<vector<int>>& adj) {
    vector<int> disc(V, -1), low(V, -1);
    vector<bool> isAP(V, false);
    vector<pair<int, int>> bridges;
    int timer = 0;

    for (int i = 0; i < V; ++i)
        if (disc[i] == -1)
            findArticulationBridges(i, -1, adj, disc, low, isAP, bridges, timer);

    vector<int> aps;
    for (int i = 0; i < V; ++i)
        if (isAP[i]) aps.push_back(i);
    return {aps, bridges};
}

// ============================================================
// 4. BIPARTITE CHECK
// ============================================================
bool isBipartite(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<int> color(V, -1);  // -1 = uncolored

    for (int start = 0; start < V; ++start) {
        if (color[start] != -1) continue;
        // BFS coloring
        queue<int> q;
        q.push(start); color[start] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];  // opposite color
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;  // conflict => not bipartite
                }
            }
        }
    }
    return true;
}

// ============================================================
// MAIN: Demonstrate all algorithms
// ============================================================
int main() {
    cout << "=== ADVANCED GRAPH ALGORITHMS ===\n\n";

    // --- Topological Sort ---
    cout << "--- Topological Sort ---\n";
    // DAG: 0->1, 0->2, 1->3, 2->3, 3->4
    int V = 5;
    vector<vector<int>> dag(V);
    dag[0] = {1, 2}; dag[1] = {3}; dag[2] = {3}; dag[3] = {4};

    cout << "Kahn's:    ";
    for (int v : topologicalSortKahn(V, dag)) cout << v << " ";
    cout << "\n";

    cout << "DFS-based: ";
    for (int v : topologicalSortDFS(V, dag)) cout << v << " ";
    cout << "\n\n";

    // --- Strongly Connected Components ---
    cout << "--- Strongly Connected Components (Kosaraju) ---\n";
    // Graph with SCCs: {0,1,2} and {3} and {4,5,6,7}
    V = 8;
    vector<vector<int>> g(V);
    // SCC 1: 0->1->2->0
    g[0] = {1}; g[1] = {2}; g[2] = {0, 3};
    // SCC 2: 3 (single node, no back edge)
    g[3] = {4};
    // SCC 3: 4->5->6->7->4
    g[4] = {5}; g[5] = {6}; g[6] = {7}; g[7] = {4};

    auto sccs = kosarajuSCC(V, g);
    cout << "Found " << sccs.size() << " SCCs:\n";
    for (int i = 0; i < sccs.size(); ++i) {
        cout << "  SCC " << i << ": ";
        for (int v : sccs[i]) cout << v << " ";
        cout << "\n";
    }
    cout << "\n";

    // --- Articulation Points & Bridges ---
    cout << "--- Articulation Points & Bridges ---\n";
    // Graph: 0-1-2-3 (line), plus 2-4, 4-5 (2 is AP)
    V = 6;
    vector<vector<int>> undir(V);
    auto addEdge = [&](int u, int v) {
        undir[u].push_back(v); undir[v].push_back(u);
    };
    addEdge(0, 1); addEdge(1, 2); addEdge(2, 3);
    addEdge(2, 4); addEdge(4, 5);

    auto [aps, bridges] = findAPAndBridges(V, undir);
    cout << "Articulation points: ";
    for (int v : aps) cout << v << " ";
    cout << "\n";
    cout << "Bridges: ";
    for (auto& [u, v] : bridges) cout << "(" << u << "," << v << ") ";
    cout << "\n\n";

    // --- Bipartite Check ---
    cout << "--- Bipartite Check ---\n";
    // Bipartite: 0-1-2-3 (even cycle)
    vector<vector<int>> bipartite = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    cout << "Square cycle is bipartite: " << isBipartite(bipartite) << "\n";

    // Not bipartite: triangle 0-1-2-0 (odd cycle)
    vector<vector<int>> notBipartite = {{1, 2}, {0, 2}, {0, 1}};
    cout << "Triangle is bipartite: " << isBipartite(notBipartite) << "\n\n";

    // --- Summary ---
    cout << "--- Algorithm Summary ---\n";
    cout << "Topological Sort:  Kahn's (BFS) or DFS, O(V+E), DAGs only\n";
    cout << "Kosaraju's SCC:    2 DFS passes, O(V+E), finds strongly connected subgraphs\n";
    cout << "Articulation Pt:   DFS + low-link, O(V+E), critical nodes\n";
    cout << "Bridges:           DFS + low-link, O(V+E), critical edges\n";
    cout << "Bipartite:         2-coloring BFS/DFS, O(V+E), no odd cycles\n";

    return 0;
}
