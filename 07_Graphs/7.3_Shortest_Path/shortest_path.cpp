/*
 * Shortest Path Algorithms
 *
 * Dijkstra's Algorithm:
 *   - Works with non-negative edge weights
 *   - Uses priority queue (min-heap)
 *   - Time: O((V+E) log V) with binary heap
 *   - Greedy: always picks closest unvisited node
 *
 * Bellman-Ford Algorithm:
 *   - Works with negative edge weights, detects negative cycles
 *   - Relaxes all edges V-1 times
 *   - Time: O(V * E)
 *   - If any edge relaxes on Vth iteration => negative cycle exists
 *
 * Floyd-Warshall Algorithm:
 *   - All-pairs shortest path
 *   - Dynamic programming approach
 *   - Time: O(V^3), Space: O(V^2)
 *   - dp[k][i][j] = shortest path using intermediate nodes 0..k
 *
 * A* (A-Star) Search:
 *   - Dijkstra + heuristic function h(node)
 *   - Priority = g(node) + h(node) where g = actual cost, h = estimate
 *   - Admissible heuristic: never overestimates (guarantees optimal)
 *   - Used in pathfinding, game AI, robotics
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX;

// ============================================================
// 1. DIJKSTRA'S ALGORITHM
//    Non-negative weights, single-source shortest path
// ============================================================
struct Edge {
    int to, weight;
};

vector<int> dijkstra(int V, const vector<vector<Edge>>& adj, int src) {
    vector<int> dist(V, INF);
    dist[src] = 0;
    // Min-heap: {distance, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;  // skip stale entries

        for (auto& e : adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

// Dijkstra with path reconstruction
vector<int> dijkstraWithPath(int V, const vector<vector<Edge>>& adj,
                             int src, int dst, vector<int>& path) {
    vector<int> dist(V, INF), parent(V, -1);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        if (u == dst) break;  // optimization: early exit

        for (auto& e : adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                parent[e.to] = u;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    // Reconstruct path
    for (int at = dst; at != -1; at = parent[at]) path.push_back(at);
    reverse(path.begin(), path.end());
    return dist;
}

// ============================================================
// 2. BELLMAN-FORD ALGORITHM
//    Handles negative weights, detects negative cycles
// ============================================================
struct BFEdge { int u, v, w; };

// Returns dist array; if negative cycle, fills negCycle=true
vector<int> bellmanFord(int V, const vector<BFEdge>& edges, int src,
                        bool& negCycle) {
    vector<int> dist(V, INF);
    dist[src] = 0;
    negCycle = false;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; ++i)
        for (auto& e : edges)
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
                dist[e.v] = dist[e.u] + e.w;

    // Check for negative cycle: one more relaxation pass
    for (auto& e : edges)
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
            negCycle = true;

    return dist;
}

// ============================================================
// 3. FLOYD-WARSHALL ALGORITHM
//    All-pairs shortest path
// ============================================================
vector<vector<int>> floydWarshall(const vector<vector<int>>& graph) {
    int V = graph.size();
    auto dist = graph;  // copy

    // dp: try each vertex k as intermediate
    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    return dist;
}

// ============================================================
// 4. A* SEARCH (Concept)
//    Dijkstra + heuristic for faster pathfinding
// ============================================================
// Simplified A* on a grid with Manhattan distance heuristic
struct Point {
    int r, c;
    bool operator==(const Point& o) const { return r == o.r && c == o.c; }
    bool operator!=(const Point& o) const { return !(*this == o); }
    bool operator<(const Point& o) const { return r < o.r || (r == o.r && c < o.c); }
};

int manhattan(Point a, Point b) {
    return abs(a.r - b.r) + abs(a.c - b.c);
}

// A* on a 2D grid (0=walkable, 1=blocked)
vector<Point> aStar(const vector<vector<int>>& grid, Point start, Point goal) {
    int R = grid.size(), C = grid[0].size();
    int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};

    // g = actual cost, f = g + heuristic
    auto cmp = [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<2>(a) > get<2>(b);  // min-heap by f-score
    };
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp)> pq(cmp);
    vector<vector<int>> g(R, vector<int>(C, INF));
    vector<vector<Point>> parent(R, vector<Point>(C));

    g[start.r][start.c] = 0;
    pq.push({start.r, start.c, manhattan(start, goal)});
    parent[start.r][start.c] = {-1, -1};

    while (!pq.empty()) {
        auto [r, c, f] = pq.top(); pq.pop();
        Point cur = {r, c};
        if (cur == goal) break;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || grid[nr][nc] == 1) continue;

            int newG = g[r][c] + 1;
            if (newG < g[nr][nc]) {
                g[nr][nc] = newG;
                parent[nr][nc] = cur;
                pq.push({nr, nc, newG + manhattan({nr, nc}, goal)});
            }
        }
    }

    // Reconstruct path
    vector<Point> path;
    for (Point p = goal; !(p == Point{-1, -1}); p = parent[p.r][p.c])
        path.push_back(p);
    reverse(path.begin(), path.end());
    if (g[goal.r][goal.c] == INF) return {};  // no path
    return path;
}

// ============================================================
// HELPER: Print distance array
// ============================================================
void printDist(const vector<int>& dist, const string& label = "") {
    cout << label;
    for (int i = 0; i < dist.size(); ++i)
        if (dist[i] == INF) cout << "inf ";
        else cout << dist[i] << " ";
    cout << "\n";
}

void printMatrix(const vector<vector<int>>& mat) {
    for (auto& row : mat) {
        for (int v : row)
            if (v == INF) cout << " inf";
            else cout << " " << v;
        cout << "\n";
    }
}

// ============================================================
// MAIN: Demonstrate all algorithms
// ============================================================
int main() {
    cout << "=== SHORTEST PATH ALGORITHMS ===\n\n";

    // --- Dijkstra's ---
    cout << "--- Dijkstra's Algorithm ---\n";
    // Graph: 0-1(4), 0-2(1), 2-1(2), 1-3(1), 2-3(5)
    int V = 4;
    vector<vector<Edge>> adj(V);
    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };
    addEdge(0, 1, 4); addEdge(0, 2, 1);
    addEdge(2, 1, 2); addEdge(1, 3, 1);
    addEdge(2, 3, 5);

    vector<int> dist = dijkstra(V, adj, 0);
    printDist(dist, "Distances from 0: ");

    // With path reconstruction
    vector<int> path;
    dijkstraWithPath(V, adj, 0, 3, path);
    cout << "Shortest path 0->3: ";
    for (int v : path) cout << v << " ";
    cout << "(cost=" << dist[3] << ")\n\n";

    // --- Bellman-Ford ---
    cout << "--- Bellman-Ford Algorithm ---\n";
    vector<BFEdge> edges = {{0, 1, 4}, {0, 2, 1}, {2, 1, 2}, {1, 3, 1}, {2, 3, 5}};
    bool negCycle;
    vector<int> bfDist = bellmanFord(V, edges, 0, negCycle);
    printDist(bfDist, "Distances from 0: ");
    cout << "Negative cycle: " << negCycle << "\n";

    // Graph with negative cycle
    vector<BFEdge> negEdges = {{0, 1, 1}, {1, 2, -1}, {2, 0, -1}};
    vector<int> negDist = bellmanFord(3, negEdges, 0, negCycle);
    cout << "Negative cycle in triangle: " << negCycle << "\n\n";

    // --- Floyd-Warshall ---
    cout << "--- Floyd-Warshall Algorithm ---\n";
    vector<vector<int>> graph = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0}
    };
    cout << "All-pairs shortest paths:\n";
    printMatrix(floydWarshall(graph));
    cout << "\n";

    // --- A* Search ---
    cout << "--- A* Search (Grid Pathfinding) ---\n";
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };
    auto pathA = aStar(grid, {0, 0}, {4, 4});
    cout << "A* path from (0,0) to (4,4):\n";
    if (pathA.empty()) cout << "  No path found\n";
    else for (auto& p : pathA) cout << "  (" << p.r << "," << p.c << ")\n";
    cout << "\n";

    // --- Algorithm Comparison ---
    cout << "--- Algorithm Comparison ---\n";
    cout << "Dijkstra:      O((V+E)log V), non-negative weights only\n";
    cout << "Bellman-Ford:  O(V*E), handles negative weights, detects neg cycles\n";
    cout << "Floyd-Warshall:O(V^3), all-pairs, handles negative weights\n";
    cout << "A*:            O(b^d), Dijkstra + heuristic, optimal if h admissible\n";

    return 0;
}
