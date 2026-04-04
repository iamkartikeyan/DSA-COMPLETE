/*
 * File: 07_Cycle_Detection_Directed.cpp
 * Topic: Detect cycle in directed graph
 * Description: Track recursion stack - back edge = cycle
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV];
int V;
bool visited[MAXV];
bool inStack[MAXV]; // is vertex in current DFS path?

void addEdge(int u, int v) {
    adj[u][v] = 1; // directed only
}

bool dfs(int u) {
    visited[u] = true;
    inStack[u] = true; // mark as in current path

    for (int v = 0; v < V; v++) {
        if (adj[u][v] == 1) {
            if (visited[v] == false) {
                if (dfs(v)) return true; // cycle found in subtree
            } else if (inStack[v]) {
                // v is in current path = back edge = cycle
                return true;
            }
        }
    }

    inStack[u] = false; // backtrack: remove from current path
    return false;
}

bool hasCycle() {
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        inStack[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (visited[i] == false) {
            if (dfs(i)) return true;
        }
    }
    return false;
}

int main() {
    cout << "=== Cycle Detection (Directed) ===" << endl;
    cout << endl;

    // --- Graph WITH cycle ---
    cout << "--- Directed Cycle ---" << endl;
    /*
     * 0 -> 1 -> 2 -> 0  (cycle!)
     */

    V = 3;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[2][0] = 1; // back to 0 = cycle

    cout << "0->1->2->0 has cycle? " << (hasCycle() ? "YES" : "NO") << endl;

    cout << endl;

    // --- Graph WITHOUT cycle (DAG) ---
    cout << "--- DAG (No Cycle) ---" << endl;
    /*
     * 0 -> 1 -> 2
     */

    V = 3;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    adj[0][1] = 1;
    adj[1][2] = 1;
    // No edge back to 0

    cout << "0->1->2 has cycle? " << (hasCycle() ? "YES" : "NO") << endl;

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  Directed graph: edges are one-way." << endl;
    cout << "  We track TWO things:" << endl;
    cout << "    1. visited[v] = was this vertex ever visited?" << endl;
    cout << "    2. inStack[v] = is this vertex in CURRENT DFS path?" << endl;
    cout << endl;
    cout << "  If we see a visited vertex that IS in current path" << endl;
    cout << "  = back edge = CYCLE!" << endl;
    cout << endl;
    cout << "  When we backtrack, we REMOVE from inStack." << endl;
    cout << "  So a visited vertex from a PREVIOUS path won't trigger cycle." << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;
    cout << "Space: O(V) for visited + inStack + recursion" << endl;

    return 0;
}
