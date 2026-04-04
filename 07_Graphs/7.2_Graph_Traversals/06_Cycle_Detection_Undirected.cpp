/*
 * File: 06_Cycle_Detection_Undirected.cpp
 * Topic: Detect cycle in undirected graph
 * Description: If visited neighbor != parent, cycle exists
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

// BFS cycle detection
bool hasCycleBFS() {
    for (int start = 0; start < V; start++) {
        if (visited[start]) continue;

        int queue[MAXV];
        int parent[MAXV];
        int front = 0;
        int rear = 0;

        visited[start] = true;
        queue[rear] = start;
        parent[rear] = -1;
        rear++;

        while (front < rear) {
            int u = queue[front];
            int par = parent[front];
            front++;

            for (int v = 0; v < V; v++) {
                if (adj[u][v] == 1) {
                    if (visited[v] == false) {
                        visited[v] = true;
                        queue[rear] = v;
                        parent[rear] = u;
                        rear++;
                    } else if (v != par) {
                        // Visited neighbor that's not our parent = cycle
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    cout << "=== Cycle Detection (Undirected) ===" << endl;
    cout << endl;

    // --- Graph WITH cycle ---
    cout << "--- Graph with Cycle ---" << endl;
    /*
     * 0 -- 1 -- 2
     *  \        /
     *   \ ---- 3
     *
     * Cycle: 0-1-2-3-0
     */

    V = 4;
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 0); // creates cycle

    cout << "Has cycle? " << (hasCycleBFS() ? "YES" : "NO") << endl;

    cout << endl;

    // --- Graph WITHOUT cycle (tree) ---
    cout << "--- Tree (No Cycle) ---" << endl;
    /*
     * 0 -- 1 -- 2
     *       \
     *        3
     */

    V = 4;
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(1, 3);

    cout << "Has cycle? " << (hasCycleBFS() ? "YES" : "NO") << endl;

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  In undirected graph, every edge goes both ways." << endl;
    cout << "  So when we visit neighbor v from u, v will see u as visited." << endl;
    cout << "  That's normal (it's the edge we just came from)." << endl;
    cout << "  But if we see a visited neighbor that is NOT our parent," << endl;
    cout << "  it means there's ANOTHER path to that vertex = CYCLE!" << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;
    cout << "Space: O(V) for queue + visited" << endl;

    return 0;
}
