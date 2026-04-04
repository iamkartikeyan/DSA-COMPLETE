/*
 * File: 03_Kosaraju_SCC.cpp
 * Topic: Kosaraju's Algorithm for Strongly Connected Components
 * Description: 2 DFS passes + graph reversal
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV];
int revAdj[MAXV][MAXV]; // reversed graph
int V;
bool visited[MAXV];
int finishOrder[MAXV];
int finishIdx;

void addEdge(int u, int v) {
    adj[u][v] = 1;
    revAdj[v][u] = 1; // reversed
}

// First DFS: fill finish order
void dfs1(int u) {
    visited[u] = true;
    for (int v = 0; v < V; v++) {
        if (adj[u][v] == 1 && visited[v] == false) {
            dfs1(v);
        }
    }
    finishOrder[finishIdx] = u;
    finishIdx++;
}

// Second DFS on reversed graph
void dfs2(int u, int component[], int& compSize) {
    visited[u] = true;
    component[compSize] = u;
    compSize++;
    for (int v = 0; v < V; v++) {
        if (revAdj[u][v] == 1 && visited[v] == false) {
            dfs2(u, component, compSize);
        }
    }
}

int main() {
    cout << "=== Kosaraju's SCC Algorithm ===" << endl;
    cout << endl;

    /*
     * Graph with 3 SCCs:
     * SCC 1: {0, 1, 2}  (cycle: 0->1->2->0)
     * SCC 2: {3}         (single node)
     * SCC 3: {4, 5, 6}  (cycle: 4->5->6->4)
     *
     * Connections: 2->3, 3->4
     */

    V = 7;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
            revAdj[i][j] = 0;
        }
    }

    // SCC 1
    adj[0][1] = 1; revAdj[1][0] = 1;
    adj[1][2] = 1; revAdj[2][1] = 1;
    adj[2][0] = 1; revAdj[0][2] = 1;

    // Connection to SCC 2
    adj[2][3] = 1; revAdj[3][2] = 1;

    // Connection to SCC 3
    adj[3][4] = 1; revAdj[4][3] = 1;

    // SCC 3
    adj[4][5] = 1; revAdj[5][4] = 1;
    adj[5][6] = 1; revAdj[6][5] = 1;
    adj[6][4] = 1; revAdj[4][6] = 1;

    // Step 1: DFS and fill finish order
    finishIdx = 0;
    for (int i = 0; i < V; i++) visited[i] = false;
    for (int i = 0; i < V; i++) {
        if (visited[i] == false) {
            dfs1(i);
        }
    }

    cout << "Finish order: ";
    for (int i = finishIdx - 1; i >= 0; i--) {
        cout << finishOrder[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Step 2: DFS on reversed graph in reverse finish order
    for (int i = 0; i < V; i++) visited[i] = false;

    int numSCC = 0;
    int components[MAXV][MAXV];
    int compSizes[MAXV];

    cout << "--- SCCs Found ---" << endl;
    for (int i = finishIdx - 1; i >= 0; i--) {
        int v = finishOrder[i];
        if (visited[v] == false) {
            dfs2(v, components[numSCC], compSizes[numSCC]);

            cout << "SCC " << numSCC << ": ";
            for (int j = 0; j < compSizes[numSCC]; j++) {
                cout << components[numSCC][j] << " ";
            }
            cout << endl;
            numSCC++;
        }
    }

    cout << endl;
    cout << "--- How Kosaraju's Works ---" << endl;
    cout << "  Step 1: DFS on original graph, record finish order" << endl;
    cout << "  Step 2: Reverse all edges" << endl;
    cout << "  Step 3: DFS on reversed graph in REVERSE finish order" << endl;
    cout << "          Each DFS tree = one SCC" << endl;
    cout << endl;
    cout << "Time: O(V + E) - three passes over the graph" << endl;
    cout << endl;
    cout << "SCC = group of vertices where each can reach every other" << endl;
    cout << "Use: Find cycles, social network clusters, web page clusters" << endl;

    return 0;
}
