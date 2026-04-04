/*
 * File: 01_Topological_Sort_Kahn.cpp
 * Topic: Topological Sort using Kahn's Algorithm (BFS)
 * Description: Linear ordering where all edges go forward
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV];
int V;
int inDegree[MAXV];

void addEdge(int u, int v) {
    adj[u][v] = 1;
    inDegree[v]++; // v has one more incoming edge
}

void topologicalSortKahn() {
    int queue[MAXV];
    int front = 0;
    int rear = 0;

    // Add all vertices with in-degree 0
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            queue[rear] = i;
            rear++;
        }
    }

    cout << "Topological Order: ";
    int count = 0;

    while (front < rear) {
        int u = queue[front];
        front++;
        cout << u << " ";
        count++;

        // Reduce in-degree of neighbors
        for (int v = 0; v < V; v++) {
            if (adj[u][v] == 1) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    queue[rear] = v;
                    rear++;
                }
            }
        }
    }
    cout << endl;

    if (count < V) {
        cout << "Graph has a CYCLE! (not a DAG)" << endl;
    }
}

int main() {
    cout << "=== Topological Sort - Kahn's Algorithm ===" << endl;
    cout << endl;

    /*
     * DAG (Directed Acyclic Graph):
     *   0 -> 1 -> 3
     *   |    |
     *   v    v
     *   2 -> 4
     *
     * Edges: 0->1, 0->2, 1->3, 1->4, 2->4
     */

    V = 5;
    for (int i = 0; i < V; i++) {
        inDegree[i] = 0;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 4);

    topologicalSortKahn();

    cout << endl;
    cout << "--- How Kahn's Algorithm Works ---" << endl;
    cout << "  1. Calculate in-degree of all vertices" << endl;
    cout << "  2. Add all vertices with in-degree 0 to queue" << endl;
    cout << "  3. While queue not empty:" << endl;
    cout << "     a. Remove vertex, add to topological order" << endl;
    cout << "     b. Reduce in-degree of its neighbors" << endl;
    cout << "     c. If neighbor's in-degree becomes 0, add to queue" << endl;
    cout << "  4. If fewer vertices processed than V -> graph has CYCLE" << endl;
    cout << endl;

    cout << "--- Applications ---" << endl;
    cout << "1. Task scheduling (dependencies)" << endl;
    cout << "2. Build systems (file dependencies)" << endl;
    cout << "3. Course prerequisites" << endl;
    cout << "4. Package managers (npm, pip)" << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;
    cout << "ONLY works on DAGs (Directed Acyclic Graphs)" << endl;

    return 0;
}
