/*
 * File: 03_Adjacency_List.cpp
 * Topic: Adjacency List representation
 * Description: Array of lists, each stores neighbors of a vertex
 */
#include <iostream>
using namespace std;

// Maximum vertices
const int MAXV = 100;

// Adjacency list: each vertex has a list of neighbors
struct Neighbor {
    int vertex;
    int weight;
};

struct NodeList {
    Neighbor neighbors[MAXV];
    int count;
};

NodeList adjList[MAXV];
int V;

void addEdge(int u, int v, int w, bool directed) {
    // Add u -> v
    adjList[u].neighbors[adjList[u].count].vertex = v;
    adjList[u].neighbors[adjList[u].count].weight = w;
    adjList[u].count++;

    // If undirected, also add v -> u
    if (directed == false) {
        adjList[v].neighbors[adjList[v].count].vertex = u;
        adjList[v].neighbors[adjList[v].count].weight = w;
        adjList[v].count++;
    }
}

void printGraph() {
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << " -> ";
        for (int j = 0; j < adjList[i].count; j++) {
            cout << "(" << adjList[i].neighbors[j].vertex;
            cout << ", w=" << adjList[i].neighbors[j].weight << ") ";
        }
        cout << endl;
    }
}

int main() {
    cout << "=== Adjacency List ===" << endl;
    cout << endl;

    /*
     * Adjacency List: Array of lists
     * adjList[i] = list of neighbors of vertex i
     *
     * Graph (undirected, weighted):
     *       2
     *   0 ----- 1
     *   | \     |
     *  3|  \1   | 4
     *   |   \   |
     *   2 ----- 3
     *       5
     */

    V = 4;

    // Initialize
    for (int i = 0; i < V; i++) {
        adjList[i].count = 0;
    }

    // Add edges
    addEdge(0, 1, 2, false);
    addEdge(0, 2, 3, false);
    addEdge(1, 3, 4, false);
    addEdge(2, 3, 5, false);
    addEdge(0, 3, 1, false);

    // Print
    printGraph();

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "Each vertex stores ONLY its neighbors (not all V vertices)." << endl;
    cout << "Vertex 0: neighbors are 1(w=2), 2(w=3), 3(w=1)" << endl;
    cout << "Vertex 1: neighbors are 0(w=2), 3(w=4)" << endl;
    cout << endl;

    cout << "--- Properties ---" << endl;
    cout << "Space: O(V + E) - only stores actual edges" << endl;
    cout << "Edge check: O(degree) - scan neighbor list" << endl;
    cout << "Add edge: O(1) - append to list" << endl;
    cout << "Find neighbors: O(degree) - iterate list" << endl;
    cout << endl;
    cout << "Best for: SPARSE graphs (few edges compared to V^2)" << endl;
    cout << "MOST COMMONLY used representation in practice!" << endl;

    return 0;
}
