/*
 * File: 02_Topological_Sort_DFS.cpp
 * Topic: Topological Sort using DFS
 * Description: Post-order traversal + reverse = topological order
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV];
int V;
bool visited[MAXV];
int topoOrder[MAXV];
int topoIdx;

void addEdge(int u, int v) {
    adj[u][v] = 1;
}

void dfs(int u) {
    visited[u] = true;

    for (int v = 0; v < V; v++) {
        if (adj[u][v] == 1 && visited[v] == false) {
            dfs(v);
        }
    }

    // Add to order AFTER processing all neighbors (post-order)
    topoOrder[topoIdx] = u;
    topoIdx++;
}

void topologicalSortDFS() {
    topoIdx = 0;
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (visited[i] == false) {
            dfs(i);
        }
    }

    // Reverse the post-order
    cout << "Topological Order: ";
    for (int i = topoIdx - 1; i >= 0; i--) {
        cout << topoOrder[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Topological Sort - DFS ===" << endl;
    cout << endl;

    /*
     * DAG:
     *   0 -> 1 -> 3
     *   |    |
     *   v    v
     *   2 -> 4
     */

    V = 5;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 4);

    topologicalSortDFS();

    cout << endl;
    cout << "--- How DFS Topological Sort Works ---" << endl;
    cout << "  1. Run DFS from each unvisited vertex" << endl;
    cout << "  2. When a vertex's DFS is COMPLETE, add it to list" << endl;
    cout << "     (post-order: after all neighbors processed)" << endl;
    cout << "  3. REVERSE the list = topological order" << endl;
    cout << endl;
    cout << "Why reverse?" << endl;
    cout << "  DFS finishes sinks (no outgoing edges) first." << endl;
    cout << "  They should be at the END of topological order." << endl;
    cout << "  Reversing puts them at the end." << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;

    return 0;
}
