/*
 * Graph Fundamentals - Terminology, Representations, BFS/DFS Basics
 *
 * Key Terminology:
 *   Vertex/Node    - A point in the graph
 *   Edge           - A connection between two vertices
 *   Directed Graph - Edges have direction (one-way roads)
 *   Undirected     - Edges are bidirectional (two-way roads)
 *   Weighted       - Edges carry weights/costs
 *   Degree         - Number of edges incident to a vertex
 *   Path           - Sequence of vertices connected by edges
 *   Cycle          - A path that starts and ends at the same vertex
 *   Connected      - A path exists between every pair of vertices
 *   DAG            - Directed Acyclic Graph (no cycles)
 *
 * Representations:
 *   Adjacency Matrix  - O(1) edge lookup, O(V^2) space
 *   Adjacency List    - O(degree(v)) neighbor lookup, O(V+E) space
 *   Edge List         - Simple list of (u, v, weight), O(E) space
 *
 * BFS: Level-order traversal using queue. Shortest path in unweighted graphs.
 * DFS: Depth-first traversal using recursion/stack. Good for reachability, cycles.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

// ============================================================
// 1. ADJACENCY MATRIX REPRESENTATION
//    Best for: dense graphs, frequent edge lookups
//    Space: O(V^2), Edge check: O(1)
// ============================================================
class AdjacencyMatrix {
    int V;
    vector<vector<int>> matrix;

public:
    AdjacencyMatrix(int vertices) : V(vertices), matrix(V, vector<int>(V, 0)) {}

    // Add edge (undirected: both directions)
    void addEdge(int u, int v, bool directed = false) {
        matrix[u][v] = 1;
        if (!directed) matrix[v][u] = 1;
    }

    // Add weighted edge
    void addWeightedEdge(int u, int v, int w, bool directed = false) {
        matrix[u][v] = w;
        if (!directed) matrix[v][u] = w;
    }

    // Check if edge exists
    bool hasEdge(int u, int v) const { return matrix[u][v] != 0; }

    void print() const {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j)
                cout << matrix[i][j] << " ";
            cout << "\n";
        }
    }
};

// ============================================================
// 2. ADJACENCY LIST REPRESENTATION
//    Best for: sparse graphs, iterating neighbors
//    Space: O(V+E), Neighbor iteration: O(degree(v))
// ============================================================
class AdjacencyList {
    int V;
    vector<vector<pair<int, int>>> adj;  // {neighbor, weight}

public:
    AdjacencyList(int vertices) : V(vertices), adj(V) {}

    void addEdge(int u, int v, int w = 1, bool directed = false) {
        adj[u].push_back({v, w});
        if (!directed) adj[v].push_back({u, w});
    }

    const vector<pair<int, int>>& getNeighbors(int u) const { return adj[u]; }

    void print() const {
        cout << "Adjacency List:\n";
        for (int i = 0; i < V; ++i) {
            cout << i << " -> ";
            for (auto& [v, w] : adj[i])
                cout << "(" << v << ", w=" << w << ") ";
            cout << "\n";
        }
    }

    int numVertices() const { return V; }
    const vector<vector<pair<int, int>>>& getAdj() const { return adj; }

    // BFS: shortest path in unweighted graph
    vector<int> bfs(int start) const {
        vector<int> result, visited(V, 0);
        queue<int> q;
        q.push(start); visited[start] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            result.push_back(u);
            for (auto& [v, w] : adj[u]) {
                if (!visited[v]) { visited[v] = 1; q.push(v); }
            }
        }
        return result;
    }

    // DFS: recursive version
    void dfsRecursive(int u, vector<int>& result, vector<bool>& visited) const {
        visited[u] = true;
        result.push_back(u);
        for (auto& [v, w] : adj[u]) {
            if (!visited[v]) dfsRecursive(v, result, visited);
        }
    }

    // DFS: iterative version using stack
    vector<int> dfsIterative(int start) const {
        vector<int> result;
        vector<bool> visited(V, false);
        stack<int> st;
        st.push(start);
        while (!st.empty()) {
            int u = st.top(); st.pop();
            if (visited[u]) continue;
            visited[u] = true;
            result.push_back(u);
            // Push in reverse for same order as recursive
            for (int i = adj[u].size() - 1; i >= 0; --i) {
                if (!visited[adj[u][i].first]) st.push(adj[u][i].first);
            }
        }
        return result;
    }
};

// ============================================================
// 3. EDGE LIST REPRESENTATION
//    Best for: Kruskal's MST, algorithms processing all edges
//    Space: O(E), No direct neighbor lookup
// ============================================================
struct Edge {
    int u, v, weight;
    Edge(int _u, int _v, int _w) : u(_u), v(_v), weight(_w) {}
};

class EdgeList {
    int V;
    vector<Edge> edges;

public:
    EdgeList(int vertices) : V(vertices) {}

    void addEdge(int u, int v, int w = 1) { edges.push_back({u, v, w}); }

    const vector<Edge>& getEdges() const { return edges; }
    int numVertices() const { return V; }

    void print() const {
        cout << "Edge List:\n";
        for (auto& e : edges)
            cout << "(" << e.u << " --" << e.weight << "-- " << e.v << ")\n";
    }
};

// ============================================================
// HELPER: Convert adjacency list to adjacency matrix
// ============================================================
vector<vector<int>> toAdjMatrix(const vector<vector<pair<int, int>>>& adj, int V) {
    vector<vector<int>> mat(V, vector<int>(V, 0));
    for (int u = 0; u < V; ++u)
        for (auto& [v, w] : adj[u])
            mat[u][v] = w;
    return mat;
}

// ============================================================
// HELPER: Convert adjacency matrix to adjacency list
// ============================================================
vector<vector<pair<int, int>>> fromAdjMatrix(const vector<vector<int>>& mat) {
    int V = mat.size();
    vector<vector<pair<int, int>>> adj(V);
    for (int u = 0; u < V; ++u)
        for (int v = 0; v < V; ++v)
            if (mat[u][v] != 0) adj[u].push_back({v, mat[u][v]});
    return adj;
}

// ============================================================
// MAIN: Demonstrate all concepts
// ============================================================
int main() {
    cout << "=== GRAPH FUNDAMENTALS ===\n\n";

    // --- Adjacency Matrix ---
    cout << "--- Adjacency Matrix ---\n";
    AdjacencyMatrix am(4);
    am.addEdge(0, 1); am.addEdge(0, 2);
    am.addEdge(1, 2); am.addEdge(2, 3);
    am.print();
    cout << "Edge 0->1 exists: " << am.hasEdge(0, 1) << "\n\n";

    // --- Weighted Adjacency Matrix ---
    cout << "--- Weighted Adjacency Matrix ---\n";
    AdjacencyMatrix wm(3);
    wm.addWeightedEdge(0, 1, 5); wm.addWeightedEdge(1, 2, 10);
    wm.print(); cout << "\n";

    // --- Adjacency List ---
    cout << "--- Adjacency List ---\n";
    AdjacencyList al(4);
    al.addEdge(0, 1, 2); al.addEdge(0, 2, 3);
    al.addEdge(1, 2, 1);  al.addEdge(1, 3, 4);
    al.addEdge(2, 3, 5);
    al.print();

    cout << "BFS from 0: ";
    for (int v : al.bfs(0)) cout << v << " ";
    cout << "\n";

    cout << "DFS (iterative) from 0: ";
    for (int v : al.dfsIterative(0)) cout << v << " ";
    cout << "\n\n";

    // --- Edge List ---
    cout << "--- Edge List ---\n";
    EdgeList el(4);
    el.addEdge(0, 1, 2); el.addEdge(0, 2, 3);
    el.addEdge(1, 2, 1); el.addEdge(1, 3, 4);
    el.addEdge(2, 3, 5);
    el.print(); cout << "\n";

    // --- Representation Comparison ---
    cout << "--- When to Use Each ---\n";
    cout << "Adjacency Matrix: Dense graphs, O(1) edge check, O(V^2) space\n";
    cout << "Adjacency List:   Sparse graphs, iterate neighbors, O(V+E) space\n";
    cout << "Edge List:        Process all edges (Kruskal's), O(E) space\n";

    // --- Graph Types ---
    cout << "\n--- Graph Types ---\n";
    cout << "Undirected: edges are bidirectional\n";
    cout << "Directed:   edges have direction (one-way)\n";
    cout << "Weighted:   edges carry costs/distances\n";
    cout << "Unweighted: all edges treated equally\n";
    cout << "DAG:        Directed Acyclic Graph (no cycles)\n";
    cout << "Connected:  path exists between every pair of vertices\n";
    cout << "Complete:   every pair of vertices has an edge\n";

    // --- BFS vs DFS Summary ---
    cout << "\n--- BFS vs DFS ---\n";
    cout << "BFS: Uses queue, finds shortest path (unweighted), level-by-level\n";
    cout << "DFS: Uses stack/recursion, good for reachability, topological sort\n";

    return 0;
}
