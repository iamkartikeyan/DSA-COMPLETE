/*
 * File: 03_Bellman_Ford.cpp
 * Topic: Bellman-Ford Algorithm - handles negative weights
 * Description: Relaxes all edges V-1 times, detects negative cycles
 */
#include <iostream>
using namespace std;

const int INF = 999999999;

struct Edge {
    int u, v, w;
};

int main() {
    cout << "=== Bellman-Ford Algorithm ===" << endl;
    cout << endl;

    /*
     * Graph with edges:
     * 0->1 weight 4
     * 0->2 weight 1
     * 2->1 weight 2
     * 1->3 weight 1
     * 2->3 weight 5
     */

    int V = 4;
    Edge edges[5];
    int E = 5;

    edges[0].u = 0; edges[0].v = 1; edges[0].w = 4;
    edges[1].u = 0; edges[1].v = 2; edges[1].w = 1;
    edges[2].u = 2; edges[2].v = 1; edges[2].w = 2;
    edges[3].u = 1; edges[3].v = 3; edges[3].w = 1;
    edges[4].u = 2; edges[4].v = 3; edges[4].w = 5;

    int dist[MAXV];
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[0] = 0; // source

    cout << "--- Relaxing Edges ---" << endl;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        bool changed = false;
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        cout << "After iteration " << (i + 1) << ": ";
        for (int k = 0; k < V; k++) {
            if (dist[k] == INF) cout << "inf ";
            else cout << dist[k] << " ";
        }
        cout << endl;

        if (changed == false) {
            cout << "(No changes, early exit)" << endl;
            break;
        }
    }

    cout << endl;
    cout << "--- Final Distances from 0 ---" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) cout << "Distance to " << i << ": unreachable" << endl;
        else cout << "Distance to " << i << ": " << dist[i] << endl;
    }

    // Check for negative cycle
    bool negCycle = false;
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            negCycle = true;
        }
    }

    cout << endl;
    cout << "Negative cycle? " << (negCycle ? "YES" : "NO") << endl;

    cout << endl;
    cout << "--- How Bellman-Ford Works ---" << endl;
    cout << "  1. Set all distances to infinity, source to 0" << endl;
    cout << "  2. Relax ALL edges V-1 times" << endl;
    cout << "  3. If any edge can still relax -> NEGATIVE CYCLE exists" << endl;
    cout << endl;
    cout << "Advantage over Dijkstra:" << endl;
    cout << "  - Works with NEGATIVE edge weights" << endl;
    cout << "  - Detects negative cycles" << endl;
    cout << endl;
    cout << "Disadvantage:" << endl;
    cout << "  - Slower: O(V * E) vs O((V+E) log V)" << endl;
    cout << endl;
    cout << "Negative cycle = you can keep going around and" << endl;
    cout << "reducing total cost forever -> no shortest path exists" << endl;

    return 0;
}
