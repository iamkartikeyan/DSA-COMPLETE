/*
 * File: 01_Dijkstra_Algorithm.cpp
 * Topic: Dijkstra's Algorithm - Shortest path with non-negative weights
 * Description: Uses min-heap/priority queue for efficiency
 */
#include <iostream>
using namespace std;

const int INF = 999999999;
const int MAXV = 100;

// Adjacency list
int adj[MAXV][MAXV]; // adj[u][i] stores neighbor, weight[MAXV][MAXV] stores weight
int weight[MAXV][MAXV];
int degree[MAXV];
int V;

void addEdge(int u, int v, int w) {
    adj[u][degree[u]] = v;
    weight[u][degree[u]] = w;
    degree[u]++;

    adj[v][degree[v]] = u;
    weight[v][degree[v]] = w;
    degree[v]++;
}

// Simple Dijkstra without priority queue (O(V^2))
void dijkstra(int src, int dist[]) {
    bool visited[MAXV];

    // Initialize
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[src] = 0;

    // Process V vertices
    for (int count = 0; count < V; count++) {
        // Find minimum distance unvisited vertex
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (visited[i] == false && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (dist[u] == INF) break; // unreachable
        visited[u] = true;

        // Relax all neighbors
        for (int i = 0; i < degree[u]; i++) {
            int v = adj[u][i];
            int w = weight[u][i];
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    cout << "=== Dijkstra's Algorithm ===" << endl;
    cout << endl;

    /*
     * Weighted Graph:
     *       4
     *   0 ----- 1
     *   | \     |
     *  1|  \2   | 1
     *   |   \   |
     *   2 ----- 3
     *       5
     *
     * Edges: (0,1,4), (0,2,1), (0,3,2), (1,3,1), (2,3,5)
     */

    V = 4;
    for (int i = 0; i < V; i++) {
        degree[i] = 0;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
            weight[i][j] = 0;
        }
    }

    addEdge(0, 1, 4);
    addEdge(0, 2, 1);
    addEdge(0, 3, 2);
    addEdge(1, 3, 1);
    addEdge(2, 3, 5);

    int dist[MAXV];
    dijkstra(0, dist);

    cout << "--- Shortest Distances from 0 ---" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            cout << "Distance to " << i << ": unreachable" << endl;
        } else {
            cout << "Distance to " << i << ": " << dist[i] << endl;
        }
    }

    cout << endl;
    cout << "--- How Dijkstra Works ---" << endl;
    cout << "  1. Set all distances to infinity, source to 0" << endl;
    cout << "  2. Pick unvisited vertex with minimum distance" << endl;
    cout << "  3. Relax all its neighbors (update if shorter path found)" << endl;
    cout << "  4. Mark as visited" << endl;
    cout << "  5. Repeat until all vertices processed" << endl;
    cout << endl;
    cout << "GREEDY: Always picks closest unvisited vertex." << endl;
    cout << endl;
    cout << "Time: O(V^2) without heap, O((V+E)log V) with heap" << endl;
    cout << "Works ONLY with non-negative edge weights!" << endl;
    cout << "For negative weights: Use Bellman-Ford" << endl;

    return 0;
}
