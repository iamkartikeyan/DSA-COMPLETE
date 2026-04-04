/*
 * File: 03_DFS_Recursive.cpp
 * Topic: Depth-First Search using recursion
 * Description: Go as deep as possible, then backtrack
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV];
int V;
bool visited[MAXV];

void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

void dfs(int u) {
    visited[u] = true;
    cout << u << " ";

    for (int v = 0; v < V; v++) {
        if (adj[u][v] == 1 && visited[v] == false) {
            dfs(v); // go deeper
        }
    }
}

int main() {
    cout << "=== DFS Traversal (Recursive) ===" << endl;
    cout << endl;

    /*
     * Graph:
     *   0 -- 1 -- 2
     *   |         |
     *   3 -- 4    5
     */

    V = 6;

    for (int i = 0; i < V; i++) {
        visited[i] = false;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    addEdge(0, 1);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(2, 5);
    addEdge(3, 4);

    cout << "DFS from 0: ";
    dfs(0);
    cout << endl;

    cout << endl;
    cout << "--- How DFS Works ---" << endl;
    cout << "  1. Start from a vertex, mark visited" << endl;
    cout << "  2. Visit first unvisited neighbor (go DEEP)" << endl;
    cout << "  3. Repeat step 2 until no unvisited neighbors" << endl;
    cout << "  4. Backtrack and try other neighbors" << endl;
    cout << endl;

    cout << "--- DFS Order for this graph ---" << endl;
    cout << "  Start at 0" << endl;
    cout << "  Go to 1 (first neighbor)" << endl;
    cout << "  Go to 2 (first neighbor of 1)" << endl;
    cout << "  Go to 5 (first neighbor of 2)" << endl;
    cout << "  5 has no unvisited neighbors -> backtrack to 2" << endl;
    cout << "  2 has no more unvisited -> backtrack to 1" << endl;
    cout << "  1 has no more unvisited -> backtrack to 0" << endl;
    cout << "  Go to 3 (next unvisited neighbor of 0)" << endl;
    cout << "  Go to 4 (first neighbor of 3)" << endl;
    cout << "  Done!" << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;
    cout << "Space: O(V) for recursion stack + visited" << endl;
    cout << endl;
    cout << "Use: Reachability, cycle detection, topological sort" << endl;

    return 0;
}
