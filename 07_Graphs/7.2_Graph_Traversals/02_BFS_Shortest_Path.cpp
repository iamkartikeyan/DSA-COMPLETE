/*
 * File: 02_BFS_Shortest_Path.cpp
 * Topic: BFS for shortest path in unweighted graph
 * Description: Distance from source to all vertices
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV];
int V;
bool visited[MAXV];
int dist[MAXV];    // distance from source
int parent[MAXV];  // for path reconstruction

void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

void bfsShortestPath(int start) {
    int queue[MAXV];
    int front = 0;
    int rear = 0;

    // Initialize
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        dist[i] = -1;      // -1 means unreachable
        parent[i] = -1;
    }

    visited[start] = true;
    dist[start] = 0;
    queue[rear] = start;
    rear++;

    while (front < rear) {
        int u = queue[front];
        front++;

        for (int v = 0; v < V; v++) {
            if (adj[u][v] == 1 && visited[v] == false) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                parent[v] = u;
                queue[rear] = v;
                rear++;
            }
        }
    }
}

void printPath(int target) {
    if (parent[target] == -1) {
        cout << target;
        return;
    }
    printPath(parent[target]);
    cout << " -> " << target;
}

int main() {
    cout << "=== BFS Shortest Path (Unweighted) ===" << endl;
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

    bfsShortestPath(0);

    cout << "--- Distances from 0 ---" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == -1) {
            cout << "Distance to " << i << ": unreachable" << endl;
        } else {
            cout << "Distance to " << i << ": " << dist[i] << endl;
        }
    }

    cout << endl;
    cout << "--- Paths from 0 ---" << endl;
    for (int i = 1; i < V; i++) {
        cout << "Path to " << i << ": ";
        printPath(i);
        cout << endl;
    }

    cout << endl;
    cout << "--- Key Insight ---" << endl;
    cout << "BFS finds SHORTEST PATH in UNWEIGHTED graphs." << endl;
    cout << "Why? Because it explores vertices level by level." << endl;
    cout << "The first time we reach a vertex, it's via shortest path." << endl;
    cout << endl;
    cout << "For WEIGHTED graphs, use Dijkstra's algorithm instead." << endl;

    return 0;
}
