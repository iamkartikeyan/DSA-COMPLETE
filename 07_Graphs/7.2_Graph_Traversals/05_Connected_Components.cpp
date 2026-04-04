/*
 * File: 05_Connected_Components.cpp
 * Topic: Find connected components in undirected graph
 * Description: Separate "islands" of connected vertices
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

// DFS to find all vertices in this component
void dfs(int u, int component[], int& compSize) {
    visited[u] = true;
    component[compSize] = u;
    compSize++;

    for (int v = 0; v < V; v++) {
        if (adj[u][v] == 1 && visited[v] == false) {
            dfs(v, component, compSize);
        }
    }
}

int main() {
    cout << "=== Connected Components ===" << endl;
    cout << endl;

    /*
     * Graph with 3 components:
     *
     * Component 1: 0 -- 1 -- 2
     * Component 2: 3 -- 4
     * Component 3: 5 (isolated)
     */

    V = 6;

    for (int i = 0; i < V; i++) {
        visited[i] = false;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    // Component 1
    addEdge(0, 1);
    addEdge(1, 2);

    // Component 2
    addEdge(3, 4);

    // Component 3: vertex 5 is isolated (no edges)

    // Find all connected components
    int components[MAXV][MAXV];
    int compSizes[MAXV];
    int numComponents = 0;

    for (int i = 0; i < V; i++) {
        if (visited[i] == false) {
            // Found a new component
            dfs(i, components[numComponents], compSizes[numComponents]);
            numComponents++;
        }
    }

    // Print results
    cout << "Number of connected components: " << numComponents << endl;
    cout << endl;

    for (int i = 0; i < numComponents; i++) {
        cout << "Component " << i << " (size " << compSizes[i] << "): ";
        for (int j = 0; j < compSizes[i]; j++) {
            cout << components[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Loop through all vertices" << endl;
    cout << "  2. If vertex not visited:" << endl;
    cout << "     - Start DFS from it" << endl;
    cout << "     - All reachable vertices = one component" << endl;
    cout << "  3. Count = number of times we started a new DFS" << endl;
    cout << endl;
    cout << "Time: O(V + E) - each vertex and edge visited once" << endl;
    cout << "Space: O(V) for visited array + recursion stack" << endl;
    cout << endl;
    cout << "Use: Social network groups, island counting, cluster detection" << endl;

    return 0;
}
