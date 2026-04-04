/*
 * Graph Traversals - BFS, DFS, Connected Components, Cycle Detection
 *
 * BFS (Breadth-First Search):
 *   - Uses a queue, explores level by level
 *   - Time: O(V + E), Space: O(V)
 *   - Finds shortest path in unweighted graphs
 *
 * DFS (Depth-First Search):
 *   - Uses recursion/stack, explores deep first
 *   - Time: O(V + E), Space: O(V) for recursion stack
 *   - Good for reachability, cycle detection, topological sort
 *
 * Connected Components:
 *   - Run BFS/DFS from each unvisited node
 *   - Count how many separate "islands" exist
 *
 * Cycle Detection:
 *   Undirected: Track parent node, if visited neighbor != parent => cycle
 *   Directed:   Track recursion stack, if revisited node in stack => cycle
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// ============================================================
// 1. BFS: Breadth-First Search
// ============================================================
vector<int> bfs(const vector<vector<int>>& adj, int start) {
    int V = adj.size();
    vector<int> result;
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(start); visited[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        result.push_back(u);
        for (int v : adj[u])
            if (!visited[v]) { visited[v] = true; q.push(v); }
    }
    return result;
}

// BFS: Shortest path distances in unweighted graph
vector<int> bfsDistances(const vector<vector<int>>& adj, int start) {
    int V = adj.size();
    vector<int> dist(V, -1);
    queue<int> q;
    q.push(start); dist[start] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u])
            if (dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }
    }
    return dist;
}

// ============================================================
// 2. DFS: Depth-First Search
// ============================================================
void dfsRecursive(const vector<vector<int>>& adj, int u,
                  vector<int>& result, vector<bool>& visited) {
    visited[u] = true;
    result.push_back(u);
    for (int v : adj[u])
        if (!visited[v]) dfsRecursive(adj, v, result, visited);
}

vector<int> dfs(const vector<vector<int>>& adj, int start) {
    vector<int> result;
    vector<bool> visited(adj.size(), false);
    dfsRecursive(adj, start, result, visited);
    return result;
}

// DFS iterative
vector<int> dfsIterative(const vector<vector<int>>& adj, int start) {
    vector<int> result;
    vector<bool> visited(adj.size(), false);
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (visited[u]) continue;
        visited[u] = true;
        result.push_back(u);
        for (int i = adj[u].size() - 1; i >= 0; --i)
            if (!visited[adj[u][i]]) st.push(adj[u][i]);
    }
    return result;
}

// ============================================================
// 3. CONNECTED COMPONENTS
// ============================================================
vector<vector<int>> connectedComponents(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    vector<vector<int>> components;

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            vector<int> comp;
            dfsRecursive(adj, i, comp, visited);
            components.push_back(comp);
        }
    }
    return components;
}

int countComponents(const vector<vector<int>>& adj) {
    int V = adj.size(), count = 0;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; ++i)
        if (!visited[i]) { count++; dfsRecursive(adj, i, vector<int>(), visited); }
    // Fix: need to pass a proper result vector
    count = 0;
    fill(visited.begin(), visited.end(), false);
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            count++;
            vector<int> dummy;
            dfsRecursive(adj, i, dummy, visited);
        }
    }
    return count;
}

// ============================================================
// 4. CYCLE DETECTION - Undirected Graph
//    If we see a visited node that isn't our parent => cycle
// ============================================================
bool hasCycleUndirected(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);

    for (int start = 0; start < V; ++start) {
        if (visited[start]) continue;
        queue<pair<int, int>> q;  // {node, parent}
        q.push({start, -1}); visited[start] = true;
        while (!q.empty()) {
            auto [u, parent] = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!visited[v]) { visited[v] = true; q.push({v, u}); }
                else if (v != parent) return true;  // back edge => cycle
            }
        }
    }
    return false;
}

// ============================================================
// 5. CYCLE DETECTION - Directed Graph
//    Use recursion stack tracking: visited + inCurrentPath
// ============================================================
bool dfsDetectCycle(const vector<vector<int>>& adj, int u,
                    vector<bool>& visited, vector<bool>& inStack) {
    visited[u] = true;
    inStack[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfsDetectCycle(adj, v, visited, inStack)) return true;
        } else if (inStack[v]) {
            return true;  // back edge in current path => cycle
        }
    }
    inStack[u] = false;  // backtrack
    return false;
}

bool hasCycleDirected(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false), inStack(V, false);
    for (int i = 0; i < V; ++i)
        if (!visited[i] && dfsDetectCycle(adj, i, visited, inStack))
            return true;
    return false;
}

// ============================================================
// MAIN: Demonstrate all concepts
// ============================================================
int main() {
    cout << "=== GRAPH TRAVERSALS ===\n\n";

    // --- Sample Graph ---
    //   0 -- 1 -- 2
    //   |         |
    //   3 -- 4    5   (6 is isolated)
    int V = 7;
    vector<vector<int>> adj(V);
    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };
    addEdge(0, 1); addEdge(0, 3);
    addEdge(1, 2); addEdge(2, 5);
    addEdge(3, 4);

    // --- BFS ---
    cout << "--- BFS ---\n";
    cout << "BFS from 0: ";
    for (int v : bfs(adj, 0)) cout << v << " ";
    cout << "\n";

    vector<int> dists = bfsDistances(adj, 0);
    cout << "Distances from 0: ";
    for (int i = 0; i < V; ++i) cout << dists[i] << " ";
    cout << "\n\n";

    // --- DFS ---
    cout << "--- DFS ---\n";
    cout << "DFS from 0: ";
    for (int v : dfs(adj, 0)) cout << v << " ";
    cout << "\n";

    cout << "DFS (iterative) from 0: ";
    for (int v : dfsIterative(adj, 0)) cout << v << " ";
    cout << "\n\n";

    // --- Connected Components ---
    cout << "--- Connected Components ---\n";
    auto comps = connectedComponents(adj);
    cout << "Number of components: " << comps.size() << "\n";
    for (int i = 0; i < comps.size(); ++i) {
        cout << "Component " << i << ": ";
        for (int v : comps[i]) cout << v << " ";
        cout << "\n";
    }
    cout << "Count: " << countComponents(adj) << "\n\n";

    // --- Cycle Detection: Undirected ---
    cout << "--- Cycle Detection (Undirected) ---\n";
    cout << "Graph has cycle (undirected): " << hasCycleUndirected(adj) << "\n";
    // 0-1-2 tree has no cycle
    vector<vector<int>> tree = {{1, 2}, {0}, {0}};
    cout << "Tree has cycle (undirected): " << hasCycleUndirected(tree) << "\n\n";

    // --- Cycle Detection: Directed ---
    cout << "--- Cycle Detection (Directed) ---\n";
    // Directed cycle: 0->1->2->0
    vector<vector<int>> dirCycle = {{1}, {2}, {0}};
    cout << "Graph 0->1->2->0 has cycle: " << hasCycleDirected(dirCycle) << "\n";

    // Directed DAG: 0->1->2
    vector<vector<int>> dag = {{1}, {2}, {}};
    cout << "DAG 0->1->2 has cycle: " << hasCycleDirected(dag) << "\n";

    return 0;
}
