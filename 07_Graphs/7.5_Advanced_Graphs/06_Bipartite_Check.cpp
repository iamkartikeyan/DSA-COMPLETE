/*
 * File: 06_Bipartite_Check.cpp
 * Topic: Check if graph is bipartite (2-colorable)
 * Description: No two adjacent vertices have same color
 */
#include <iostream>
using namespace std;

const int MAXV = 100;

int adj[MAXV][MAXV];
int V;
int color[MAXV]; // -1 = uncolored, 0 = color A, 1 = color B

void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

bool isBipartite() {
    for (int start = 0; start < V; start++) {
        if (color[start] != -1) continue; // already colored

        // BFS coloring
        int queue[MAXV];
        int front = 0;
        int rear = 0;

        color[start] = 0; // start with color 0
        queue[rear] = start;
        rear++;

        while (front < rear) {
            int u = queue[front];
            front++;

            for (int v = 0; v < V; v++) {
                if (adj[u][v] == 1) {
                    if (color[v] == -1) {
                        // Color with opposite color
                        color[v] = 1 - color[u];
                        queue[rear] = v;
                        rear++;
                    } else if (color[v] == color[u]) {
                        // Adjacent vertices have same color = NOT bipartite
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void printColors() {
    for (int i = 0; i < V; i++) {
        cout << "  Vertex " << i << ": Color " << color[i] << endl;
    }
}

int main() {
    cout << "=== Bipartite Check ===" << endl;
    cout << endl;

    // --- Graph that IS bipartite ---
    cout << "--- Bipartite Graph (Even Cycle) ---" << endl;
    /*
     * 0 -- 1
     * |    |
     * 3 -- 2
     *
     * Square cycle (4 vertices = even) = bipartite
     */

    V = 4;
    for (int i = 0; i < V; i++) {
        color[i] = -1;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 0);

    cout << "Bipartite? " << (isBipartite() ? "YES" : "NO") << endl;
    printColors();

    cout << endl;

    // --- Graph that is NOT bipartite ---
    cout << "--- Non-Bipartite (Triangle) ---" << endl;
    /*
     *   0
     *  / \
     * 1---2
     *
     * Triangle (3 vertices = odd cycle) = NOT bipartite
     */

    V = 3;
    for (int i = 0; i < V; i++) {
        color[i] = -1;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 0);

    cout << "Bipartite? " << (isBipartite() ? "YES" : "NO") << endl;

    cout << endl;
    cout << "--- What is Bipartite? ---" << endl;
    cout << "A graph is bipartite if vertices can be divided into" << endl;
    cout << "TWO groups such that no two vertices in same group" << endl;
    cout << "are connected by an edge." << endl;
    cout << "Equivalently: graph is 2-colorable." << endl;
    cout << endl;

    cout << "--- Key Rule ---" << endl;
    cout << "A graph is bipartite IF AND ONLY IF it has NO odd-length cycle." << endl;
    cout << "Even cycles = OK, Odd cycles = NOT bipartite" << endl;
    cout << endl;

    cout << "--- How it Works ---" << endl;
    cout << "  1. Start BFS from uncolored vertex" << endl;
    cout << "  2. Color it with color 0" << endl;
    cout << "  3. Color all neighbors with opposite color (1)" << endl;
    cout << "  4. Continue: each new vertex gets opposite of its parent" << endl;
    cout << "  5. If conflict (neighbor has same color) -> NOT bipartite" << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;
    cout << "Use: Matching problems, scheduling, 2-coloring" << endl;

    return 0;
}
