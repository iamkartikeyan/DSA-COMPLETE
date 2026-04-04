/*
 * File: 04_Edge_List.cpp
 * Topic: Edge List representation
 * Description: Simple list of all edges as (u, v, weight) tuples
 */
#include <iostream>
using namespace std;

struct Edge {
    int u;      // source vertex
    int v;      // destination vertex
    int weight; // edge weight
};

int main() {
    cout << "=== Edge List ===" << endl;
    cout << endl;

    /*
     * Edge List: Simple array/list of all edges
     * Each edge stored as (u, v, weight)
     *
     * Graph:
     *   0 --1-- 1
     *   | \     |
     *  4|  \6   | 2
     *   |   \   |
     *   3 --3-- 2
     */

    Edge edges[6];
    int edgeCount = 0;

    // Add edges
    edges[edgeCount].u = 0; edges[edgeCount].v = 1; edges[edgeCount].weight = 1; edgeCount++;
    edges[edgeCount].u = 0; edges[edgeCount].v = 3; edges[edgeCount].weight = 4; edgeCount++;
    edges[edgeCount].u = 0; edges[edgeCount].v = 2; edges[edgeCount].weight = 6; edgeCount++;
    edges[edgeCount].u = 1; edges[edgeCount].v = 2; edges[edgeCount].weight = 2; edgeCount++;
    edges[edgeCount].u = 1; edges[edgeCount].v = 3; edges[edgeCount].weight = 5; edgeCount++;
    edges[edgeCount].u = 2; edges[edgeCount].v = 3; edges[edgeCount].weight = 3; edgeCount++;

    cout << "Edge List:" << endl;
    cout << "Index | u | v | weight" << endl;
    cout << "------|---|---|-------" << endl;
    for (int i = 0; i < edgeCount; i++) {
        cout << "  " << i << "   | " << edges[i].u << " | " << edges[i].v << " | " << edges[i].weight << endl;
    }

    cout << endl;
    cout << "--- Properties ---" << endl;
    cout << "Space: O(E) - one entry per edge" << endl;
    cout << "Edge check: O(E) - must scan entire list" << endl;
    cout << "Add edge: O(1) - append to list" << endl;
    cout << "Find neighbors: O(E) - must scan entire list" << endl;
    cout << endl;
    cout << "Best for: Algorithms that process ALL edges" << endl;
    cout << "  - Kruskal's MST (sort edges by weight)" << endl;
    cout << "  - Bellman-Ford (relax all edges V-1 times)" << endl;
    cout << endl;

    cout << "--- When to Use Each Representation ---" << endl;
    cout << endl;
    cout << "Representation     | Space    | Edge Check | Best For" << endl;
    cout << "-------------------|----------|------------|------------------" << endl;
    cout << "Adjacency Matrix   | O(V^2)   | O(1)       | Dense graphs" << endl;
    cout << "Adjacency List     | O(V+E)   | O(degree)  | Sparse graphs (MOST COMMON)" << endl;
    cout << "Edge List          | O(E)     | O(E)       | Process all edges" << endl;

    return 0;
}
