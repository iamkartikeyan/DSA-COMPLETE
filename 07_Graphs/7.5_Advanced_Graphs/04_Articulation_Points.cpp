/*
 * File: 04_Articulation_Points.cpp
 * Topic: Find articulation points (cut vertices)
 * Description: Removing them disconnects the graph
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV];
int degree[MAXV];
int V;

int disc[MAXV];   // discovery time
int low[MAXV];    // lowest discovery reachable
bool isAP[MAXV];  // is articulation point
bool visited[MAXV];
int timer;

void addEdge(int u, int v) {
    adj[u][degree[u]] = v;
    degree[u]++;
    adj[v][degree[v]] = u;
    degree[v]++;
}

void dfsAP(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = timer;
    timer++;
    int children = 0;

    for (int i = 0; i < degree[u]; i++) {
        int v = adj[u][i];

        if (v == parent) continue; // skip parent

        if (visited[v]) {
            // Back edge: update low
            low[u] = min(low[u], disc[v]);
        } else {
            // Tree edge: DFS
            children++;
            dfsAP(v, u);

            // Update low after return
            low[u] = min(low[u], low[v]);

            // AP condition: low[v] >= disc[u]
            if (parent != -1 && low[v] >= disc[u]) {
                isAP[u] = true;
            }
        }
    }

    // Root is AP if it has more than 1 child in DFS tree
    if (parent == -1 && children > 1) {
        isAP[u] = true;
    }
}

int main() {
    cout << "=== Articulation Points ===" << endl;
    cout << endl;

    /*
     * Graph:
     *   0 -- 1 -- 2 -- 3
     *        |
     *        4 -- 5
     *
     * Articulation points: 1 and 2
     * Removing 1 disconnects {0} from {2,3,4,5}
     * Removing 2 disconnects {0,1} from {3} and {4,5}
     */

    V = 6;
    for (int i = 0; i < V; i++) {
        degree[i] = 0;
        visited[i] = false;
        isAP[i] = false;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(1, 4);
    addEdge(4, 5);

    timer = 0;
    dfsAP(0, -1);

    cout << "Articulation Points: ";
    bool found = false;
    for (int i = 0; i < V; i++) {
        if (isAP[i]) {
            cout << i << " ";
            found = true;
        }
    }
    if (found == false) {
        cout << "None";
    }
    cout << endl;

    cout << endl;
    cout << "--- What is Articulation Point? ---" << endl;
    cout << "A vertex whose removal DISCONNECTS the graph." << endl;
    cout << "Also called 'cut vertex' or 'critical node'." << endl;
    cout << endl;

    cout << "--- How it Works ---" << endl;
    cout << "  Uses DFS with two values per vertex:" << endl;
    cout << "  disc[u] = when was u first discovered" << endl;
    cout << "  low[u]  = earliest disc reachable via back edges" << endl;
    cout << endl;
    cout << "  AP condition: low[v] >= disc[u]" << endl;
    cout << "  (v cannot reach above u through back edges)" << endl;
    cout << endl;
    cout << "  Special case: root is AP if > 1 child in DFS tree" << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;
    cout << "Use: Network reliability, finding critical nodes" << endl;

    return 0;
}
