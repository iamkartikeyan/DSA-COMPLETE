/*
 * File: 04_DFS_Iterative.cpp
 * Topic: DFS using stack (no recursion)
 * Description: Same as recursive but uses explicit stack
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

void dfsIterative(int start) {
    int stack[MAXV];
    int top = 0;

    stack[top] = start;
    top++;

    cout << "DFS (iterative): ";

    while (top > 0) {
        // Pop
        top--;
        int u = stack[top];

        // Skip if already visited
        if (visited[u]) continue;

        visited[u] = true;
        cout << u << " ";

        // Push neighbors (in reverse order for same result as recursive)
        for (int v = V - 1; v >= 0; v--) {
            if (adj[u][v] == 1 && visited[v] == false) {
                stack[top] = v;
                top++;
            }
        }
    }
    cout << endl;
}

int main() {
    cout << "=== DFS Traversal (Iterative) ===" << endl;
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

    dfsIterative(0);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Push start vertex onto stack" << endl;
    cout << "  2. While stack not empty:" << endl;
    cout << "     a. Pop top vertex" << endl;
    cout << "     b. If not visited, mark visited and print" << endl;
    cout << "     c. Push all unvisited neighbors onto stack" << endl;
    cout << endl;
    cout << "Recursive DFS = implicit call stack" << endl;
    cout << "Iterative DFS = explicit stack variable" << endl;
    cout << "Both produce same order (with careful neighbor ordering)" << endl;
    cout << endl;
    cout << "Time: O(V + E)" << endl;
    cout << "Space: O(V) for stack + visited" << endl;

    return 0;
}
