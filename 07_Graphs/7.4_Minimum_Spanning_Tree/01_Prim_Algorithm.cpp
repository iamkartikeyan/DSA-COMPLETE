/*
 * File: 01_Prim_Algorithm.cpp
 * Topic: Prim's Algorithm - MST using greedy vertex expansion
 * Description: Grow MST one vertex at a time using min-heap
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

struct EdgeInfo {
    int to;
    int weight;
    int from;
};

int main() {
    cout << "=== Prim's Algorithm ===" << endl;
    cout << endl;

    /*
     * Graph:
     *       1
     *   0 ----- 1
     *   | \     |
     *  4|  \6   | 2
     *   |   \   |
     *   3 --5-- 2
     */

    V = 4;
    for (int i = 0; i < V; i++) {
        degree[i] = 0;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
            edgeWeight[i][j] = 0;
        }
    }

    addEdge(0, 1, 1);
    addEdge(0, 3, 4);
    addEdge(0, 2, 6);
    addEdge(1, 2, 2);
    addEdge(2, 3, 5);

    /*
     * Prim's Algorithm (without priority queue - O(V^2)):
     * 1. Start from vertex 0
     * 2. Find minimum weight edge from MST to non-MST vertex
     * 3. Add that vertex to MST
     * 4. Repeat until all vertices included
     */

    bool inMST[MAXV];
    int key[MAXV];    // minimum weight to connect to MST
    int parent[MAXV]; // parent in MST

    for (int i = 0; i < V; i++) {
        inMST[i] = false;
        key[i] = INF;
        parent[i] = -1;
    }

    key[0] = 0; // start from vertex 0

    int totalWeight = 0;
    int mstEdges = 0;

    cout << "--- Building MST ---" << endl;

    for (int count = 0; count < V; count++) {
        // Find minimum key vertex not in MST
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (inMST[i] == false && (u == -1 || key[i] < key[u])) {
                u = i;
            }
        }

        inMST[u] = true;
        totalWeight += key[u];

        if (parent[u] != -1) {
            cout << "  Add edge: " << parent[u] << " --" << key[u] << "-- " << u << endl;
            mstEdges++;
        }

        // Update keys of neighbors
        for (int i = 0; i < degree[u]; i++) {
            int v = adj[u][i];
            int w = edgeWeight[u][i];
            if (inMST[v] == false && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
        }
    }

    cout << endl;
    cout << "Total MST weight: " << totalWeight << endl;
    cout << "MST edges: " << mstEdges << endl;

    cout << endl;
    cout << "--- How Prim's Works ---" << endl;
    cout << "  1. Start from any vertex" << endl;
    cout << "  2. Find cheapest edge from MST to non-MST vertex" << endl;
    cout << "  3. Add that vertex to MST" << endl;
    cout << "  4. Repeat until all vertices in MST" << endl;
    cout << endl;
    cout << "GREEDY: Always picks cheapest available edge." << endl;
    cout << endl;
    cout << "Time: O(V^2) without heap, O((V+E)log V) with heap" << endl;
    cout << "Best for: DENSE graphs" << endl;

    return 0;
}
