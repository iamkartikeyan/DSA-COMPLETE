/*
 * File: 04_Negative_Cycle_Demo.cpp
 * Topic: Negative cycle detection with Bellman-Ford
 * Description: Show how negative cycle makes shortest path undefined
 */
#include <iostream>
using namespace std;

const int INF = 999999999;

struct Edge {
    int u, v, w;
};

int main() {
    cout << "=== Negative Cycle Detection ===" << endl;
    cout << endl;

    // --- Graph WITHOUT negative cycle ---
    cout << "--- Graph Without Negative Cycle ---" << endl;
    int V1 = 3;
    Edge edges1[3];
    edges1[0].u = 0; edges1[0].v = 1; edges1[0].w = 1;
    edges1[1].u = 1; edges1[1].v = 2; edges1[1].w = 2;
    edges1[2].u = 0; edges1[2].v = 2; edges1[2].w = 4;

    int dist1[MAXV];
    for (int i = 0; i < V1; i++) dist1[i] = INF;
    dist1[0] = 0;

    // Relax V-1 times
    for (int i = 0; i < V1 - 1; i++) {
        for (int j = 0; j < 3; j++) {
            if (dist1[edges1[j].u] + edges1[j].w < dist1[edges1[j].v]) {
                dist1[edges1[j].v] = dist1[edges1[j].u] + edges1[j].w;
            }
        }
    }

    bool negCycle1 = false;
    for (int j = 0; j < 3; j++) {
        if (dist1[edges1[j].u] + edges1[j].w < dist1[edges1[j].v]) {
            negCycle1 = true;
        }
    }
    cout << "Negative cycle? " << (negCycle1 ? "YES" : "NO") << endl;

    cout << endl;

    // --- Graph WITH negative cycle ---
    cout << "--- Graph WITH Negative Cycle ---" << endl;
    /*
     * 0 -> 1 (weight 1)
     * 1 -> 2 (weight -1)
     * 2 -> 0 (weight -1)
     *
     * Cycle: 0->1->2->0 has total weight = 1 + (-1) + (-1) = -1
     * Going around the cycle reduces cost each time!
     */

    int V2 = 3;
    Edge edges2[3];
    edges2[0].u = 0; edges2[0].v = 1; edges2[0].w = 1;
    edges2[1].u = 1; edges2[1].v = 2; edges2[1].w = -1;
    edges2[2].u = 2; edges2[2].v = 0; edges2[2].w = -1;

    int dist2[MAXV];
    for (int i = 0; i < V2; i++) dist2[i] = INF;
    dist2[0] = 0;

    // Relax V-1 times
    for (int i = 0; i < V2 - 1; i++) {
        for (int j = 0; j < 3; j++) {
            if (dist2[edges2[j].u] != INF &&
                dist2[edges2[j].u] + edges2[j].w < dist2[edges2[j].v]) {
                dist2[edges2[j].v] = dist2[edges2[j].u] + edges2[j].w;
            }
        }
    }

    bool negCycle2 = false;
    for (int j = 0; j < 3; j++) {
        if (dist2[edges2[j].u] != INF &&
            dist2[edges2[j].u] + edges2[j].w < dist2[edges2[j].v]) {
            negCycle2 = true;
        }
    }
    cout << "Negative cycle? " << (negCycle2 ? "YES" : "NO") << endl;

    cout << endl;
    cout << "--- Why Negative Cycle is Bad ---" << endl;
    cout << "In the second graph, cycle 0->1->2->0 costs -1." << endl;
    cout << "Each lap around the cycle, total cost decreases by 1." << endl;
    cout << "Go around infinite times -> cost = negative infinity!" << endl;
    cout << "So SHORTEST PATH is UNDEFINED." << endl;
    cout << endl;
    cout << "Bellman-Ford DETECTS this situation." << endl;
    cout << "Dijkstra's would give WRONG answer (it assumes no negatives)." << endl;

    return 0;
}
