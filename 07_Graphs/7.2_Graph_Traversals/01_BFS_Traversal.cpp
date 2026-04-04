/*
 * File: 01_BFS_Traversal.cpp
 * Topic: Breadth-First Search - Level by level traversal
 * Description: Uses queue, visits nearest unvisited neighbors first
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV]; // adjacency matrix for simplicity
int V;
bool visited[MAXV];

void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1; // undirected
}

void bfs(int start) {
    // Queue for BFS
    int queue[MAXV];
    int front = 0;
    int rear = 0;

    // Mark start as visited and enqueue
    visited[start] = true;
    queue[rear] = start;
    rear++;

    cout << "BFS: ";

    while (front < rear) {
        // Dequeue
        int u = queue[front];
        front++;
        cout << u << " ";

        // Visit all unvisited neighbors
        for (int v = 0; v < V; v++) {
            if (adj[u][v] == 1 && visited[v] == false) {
                visited[v] = true;
                queue[rear] = v;
                rear++;
            }
        }
    }
    cout << endl;
}

int main() {
    cout << "=== BFS Traversal ===" << endl;
    cout << endl;

    /*
     * Graph:
     *   0 -- 1 -- 2
     *   |         |
     *   3 -- 4    5
     */

    V = 6;

    // Initialize
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    // Add edges
    addEdge(0, 1);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(2, 5);
    addEdge(3, 4);

    bfs(0);

    cout << endl;
    cout << "--- How BFS Works ---" << endl;
    cout << "  1. Start from a vertex, mark it visited" << endl;
    cout << "  2. Add to queue" << endl;
    cout << "  3. While queue not empty:" << endl;
    cout << "     a. Remove front vertex" << endl;
    cout << "     b. Visit it (print)" << endl;
    cout << "     c. Add all unvisited neighbors to queue" << endl;
    cout << endl;
    cout << "Order for this graph:" << endl;
    cout << "  Level 0: 0" << endl;
    cout << "  Level 1: 1, 3" << endl;
    cout << "  Level 2: 2, 4" << endl;
    cout << "  Level 3: 5" << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;
    cout << "Space: O(V) for queue + visited array" << endl;
    cout << endl;
    cout << "Use: Shortest path (unweighted), level-order traversal" << endl;

    return 0;
}
