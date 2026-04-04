/*
 * File: 02_Kruskal_Algorithm.cpp
 * Topic: Kruskal's Algorithm - MST using sorted edges + Union-Find
 * Description: Sort edges, add smallest that doesn't create cycle
 */
#include <iostream>
using namespace std;

struct Edge {
    int u, v, w;
};

// Union-Find (DSU)
int parent[MAXV];
int rankArr[MAXV];

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }
}

int findSet(int x) {
    if (parent[x] != x) {
        parent[x] = findSet(parent[x]); // path compression
    }
    return parent[x];
}

void unionSets(int a, int b) {
    int rootA = findSet(a);
    int rootB = findSet(b);
    if (rootA != rootB) {
        // Union by rank
        if (rankArr[rootA] < rankArr[rootB]) {
            parent[rootA] = rootB;
        } else if (rankArr[rootA] > rankArr[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rankArr[rootA]++;
        }
    }
}

void swapEdges(Edge& a, Edge& b) {
    Edge temp = a;
    a = b;
    b = temp;
}

void sortEdges(Edge edges[], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                swapEdges(edges[j], edges[j + 1]);
            }
        }
    }
}

int main() {
    cout << "=== Kruskal's Algorithm ===" << endl;
    cout << endl;

    /*
     * Graph edges:
     * (0,1,1), (0,3,4), (0,2,6), (1,2,2), (2,3,5), (1,3,5)
     */

    int V = 4;
    Edge edges[6];
    int E = 6;

    edges[0].u = 0; edges[0].v = 1; edges[0].w = 1;
    edges[1].u = 0; edges[1].v = 3; edges[1].w = 4;
    edges[2].u = 0; edges[2].v = 2; edges[2].w = 6;
    edges[3].u = 1; edges[3].v = 2; edges[3].w = 2;
    edges[4].u = 2; edges[4].v = 3; edges[4].w = 5;
    edges[5].u = 1; edges[5].v = 3; edges[5].w = 5;

    // Step 1: Sort edges by weight
    sortEdges(edges, E);

    cout << "Sorted edges: ";
    for (int i = 0; i < E; i++) {
        cout << "(" << edges[i].u << "," << edges[i].v << "," << edges[i].w << ") ";
    }
    cout << endl;
    cout << endl;

    // Step 2: Process edges in sorted order
    makeSet(V);

    int totalWeight = 0;
    int edgesCount = 0;

    cout << "--- Building MST ---" << endl;

    for (int i = 0; i < E && edgesCount < V - 1; i++) {
        int rootU = findSet(edges[i].u);
        int rootV = findSet(edges[i].v);

        if (rootU != rootV) {
            // No cycle - add this edge
            unionSets(rootU, rootV);
            totalWeight += edges[i].w;
            edgesCount++;

            cout << "  Add edge: " << edges[i].u << " --" << edges[i].w << "-- " << edges[i].v << endl;
        } else {
            cout << "  Skip edge: " << edges[i].u << " --" << edges[i].w << "-- " << edges[i].v << " (would create cycle)" << endl;
        }
    }

    cout << endl;
    cout << "Total MST weight: " << totalWeight << endl;
    cout << "MST edges: " << edgesCount << endl;

    cout << endl;
    cout << "--- How Kruskal's Works ---" << endl;
    cout << "  1. Sort ALL edges by weight (smallest first)" << endl;
    cout << "  2. Process each edge:" << endl;
    cout << "     - If adding edge doesn't create cycle -> ADD it" << endl;
    cout << "     - If it creates cycle -> SKIP it" << endl;
    cout << "  3. Stop when MST has V-1 edges" << endl;
    cout << endl;
    cout << "Uses Union-Find (DSU) to detect cycles efficiently." << endl;
    cout << endl;
    cout << "Time: O(E log E) for sorting + O(E * alpha(V)) for DSU" << endl;
    cout << "Best for: SPARSE graphs" << endl;

    return 0;
}
