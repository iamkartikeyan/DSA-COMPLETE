/*
 * File: 05_Floyd_Warshall.cpp
 * Topic: Floyd-Warshall - All pairs shortest path
 * Description: DP approach, finds shortest path between ALL pairs
 */
#include <iostream>
using namespace std;

const int INF = 999999999;
const int MAXV = 100;

int main() {
    cout << "=== Floyd-Warshall Algorithm ===" << endl;
    cout << endl;

    /*
     * Graph (directed, weighted):
     *   0 -> 1 (weight 3)
     *   0 -> 3 (weight 7)
     *   1 -> 2 (weight 2)
     *   2 -> 0 (weight 5)
     *   2 -> 3 (weight 1)
     *   3 -> 0 (weight 2)
     */

    int V = 4;
    int dist[MAXV][MAXV];

    // Initialize with edge weights
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    // Add edges
    dist[0][1] = 3;
    dist[0][3] = 7;
    dist[1][2] = 2;
    dist[2][0] = 5;
    dist[2][3] = 1;
    dist[3][0] = 2;

    cout << "--- Initial Distance Matrix ---" << endl;
    cout << "     0    1    2    3" << endl;
    for (int i = 0; i < V; i++) {
        cout << "  " << i << " ";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) cout << "  inf";
            else cout << "  " << dist[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // Floyd-Warshall: try each vertex as intermediate
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    cout << "--- All-Pairs Shortest Paths ---" << endl;
    cout << "     0    1    2    3" << endl;
    for (int i = 0; i < V; i++) {
        cout << "  " << i << " ";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) cout << "  inf";
            else cout << "  " << dist[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  For each vertex k, try using k as intermediate:" << endl;
    cout << "  Is going i -> k -> j shorter than direct i -> j?" << endl;
    cout << "  If yes, update dist[i][j]" << endl;
    cout << endl;

    cout << "Key formula:" << endl;
    cout << "  dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])" << endl;
    cout << endl;
    cout << "Time: O(V^3) - three nested loops" << endl;
    cout << "Space: O(V^2) - distance matrix" << endl;
    cout << endl;
    cout << "Use: All-pairs shortest path, dense graphs" << endl;
    cout << "Handles negative weights (but not negative cycles)" << endl;

    return 0;
}
