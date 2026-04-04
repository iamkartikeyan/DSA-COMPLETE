/*
 * File: 02_Dijkstra_WithPath.cpp
 * Topic: Dijkstra with path reconstruction
 * Description: Track parent pointers to rebuild shortest path
 */
#include <iostream>
using namespace std;

const int INF = 999999999;
const int MAXV = 100;

int adj[MAXV][MAXV];
int edgeWeight[MAXV][MAXV];
int degree[MAXV];
int V;

void addEdge(int u, int v, int w) {
    adj[u][degree[u]] = v;
    edgeWeight[u][degree[u]] = w;
    degree[u]++;
    adj[v][degree[v]] = u;
    edgeWeight[v][degree[v]] = w;
    degree[v]++;
}

void dijkstraWithPath(int src, int dist[], int parent[]) {
    bool visited[MAXV];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }
    dist[src] = 0;

    for (int count = 0; count < V; count++) {
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (visited[i] == false && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (dist[u] == INF) break;
        visited[u] = true;

        for (int i = 0; i < degree[u]; i++) {
            int v = adj[u][i];
            int w = edgeWeight[u][i];
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }
}

void printPath(int target, int parent[]) {
    if (target == -1) return;

    // Recursively print path
    if (parent[target] != -1) {
        printPath(parent[target], parent);
        cout << " -> ";
    }
    cout << target;
}

int main() {
    cout << "=== Dijkstra with Path Reconstruction ===" << endl;
    cout << endl;

    /*
     * Graph:
     *       4
     *   0 ----- 1
     *   | \     |
     *  1|  \2   | 1
     *   |   \   |
     *   2 ----- 3
     *       5
     */

    V = 4;
    for (int i = 0; i < V; i++) {
        degree[i] = 0;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
            edgeWeight[i][j] = 0;
        }
    }

    addEdge(0, 1, 4);
    addEdge(0, 2, 1);
    addEdge(0, 3, 2);
    addEdge(1, 3, 1);
    addEdge(2, 3, 5);

    int dist[MAXV];
    int parent[MAXV];
    dijkstraWithPath(0, dist, parent);

    cout << "--- Shortest Paths from 0 ---" << endl;
    for (int i = 1; i < V; i++) {
        cout << "To " << i << " (cost " << dist[i] << "): ";
        printPath(i, parent);
        cout << endl;
    }

    cout << endl;
    cout << "--- Path Explanation ---" << endl;
    cout << "To vertex 1: 0 -> 3 -> 1 (cost 2+1=3, NOT 0->1 cost 4)" << endl;
    cout << "To vertex 2: 0 -> 2 (cost 1)" << endl;
    cout << "To vertex 3: 0 -> 3 (cost 2)" << endl;
    cout << endl;
    cout << "Parent array tracks 'who got me here'" << endl;
    cout << "Backtrack from target to source using parent[]" << endl;

    return 0;
}
