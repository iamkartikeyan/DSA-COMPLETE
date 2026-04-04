/*
 * File: 05_Bridges.cpp
 * Topic: Find bridges (critical edges) in graph
 * Description: Removing a bridge disconnects the graph
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV];
int degree[MAXV];
int V;

int disc[MAXV];
int low[MAXV];
bool visited[MAXV];
int timer;

struct Bridge {
    int u, v;
};

Bridge bridges[MAXV];
int bridgeCount;

void addEdge(int u, int v) {
    adj[u][degree[u]] = v;
    degree[u]++;
    adj[v][degree[v]] = u;
    degree[v]++;
}

void dfsBridge(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = timer;
    timer++;

    for (int i = 0; i < degree[u]; i++) {
        int v = adj[u][i];

        if (v == parent) continue;

        if (visited[v]) {
            // Back edge
            low[u] = min(low[u], disc[v]);
        } else {
            // Tree edge
            dfsBridge(v, u);
            low[u] = min(low[u], low[v]);

            // Bridge condition: low[v] > disc[u]
            if (low[v] > disc[u]) {
                bridges[bridgeCount].u = u;
                bridges[bridgeCount].v = v;
                bridgeCount++;
            }
        }
    }
}

int main() {
    cout << "=== Bridges (Critical Edges) ===" << endl;
    cout << endl;

    /*
     * Graph:
     *   0 -- 1 -- 2 -- 3
     *        |    |
     *        4 --- 5
     *
     * Bridges: (0,1) and (1,2)
     * (0,1): removing disconnects {0} from rest
     * (1,2): removing disconnects {0,1,4,5} from {3}
     * Edges in cycle (1-4-5-2-1) are NOT bridges
     */

    V = 6;
    for (int i = 0; i < V; i++) {
        degree[i] = 0;
        visited[i] = false;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(1, 4);
    addEdge(4, 5);
    addEdge(5, 2); // creates cycle 1-4-5-2-1

    bridgeCount = 0;
    timer = 0;
    dfsBridge(0, -1);

    cout << "Bridges found:" << endl;
    if (bridgeCount == 0) {
        cout << "  None" << endl;
    } else {
        for (int i = 0; i < bridgeCount; i++) {
            cout << "  (" << bridges[i].u << ", " << bridges[i].v << ")" << endl;
        }
    }

    cout << endl;
    cout << "--- What is a Bridge? ---" << endl;
    cout << "An edge whose removal DISCONNECTS the graph." << endl;
    cout << "Also called 'cut edge' or 'critical edge'." << endl;
    cout << "Edges in a cycle are NEVER bridges." << endl;
    cout << endl;

    cout << "--- Bridge Condition ---" << endl;
    cout << "  low[v] > disc[u] means:" << endl;
    cout << "  v CANNOT reach u or above through any back edge" << endl;
    cout << "  So (u,v) is the ONLY path = BRIDGE" << endl;
    cout << endl;
    cout << "Note the DIFFERENCE from articulation point:" << endl;
    cout << "  Bridge:  low[v] > disc[u]  (strictly greater)" << endl;
    cout << "  AP:      low[v] >= disc[u] (greater or equal)" << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;
    cout << "Use: Network reliability, single points of failure" << endl;

    return 0;
}
