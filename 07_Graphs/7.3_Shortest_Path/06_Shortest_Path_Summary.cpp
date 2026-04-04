/*
 * File: 06_Shortest_Path_Summary.cpp
 * Topic: Complete shortest path algorithms summary
 * Description: Comparison of all shortest path algorithms
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Shortest Path - Summary ===" << endl;
    cout << endl;

    cout << "--- Algorithm Comparison ---" << endl;
    cout << endl;
    cout << "Algorithm      | Type        | Time          | Negative Weights" << endl;
    cout << "---------------|-------------|---------------|-----------------" << endl;
    cout << "BFS            | Unweighted  | O(V + E)      | N/A" << endl;
    cout << "Dijkstra       | Single-src  | O((V+E)log V) | NO" << endl;
    cout << "Bellman-Ford   | Single-src  | O(V * E)      | YES" << endl;
    cout << "Floyd-Warshall | All-pairs   | O(V^3)        | YES" << endl;
    cout << endl;

    cout << "--- When to Use ---" << endl;
    cout << "BFS:            Unweighted graph, shortest path" << endl;
    cout << "Dijkstra:       Weighted, NO negative edges, fastest" << endl;
    cout << "Bellman-Ford:   Weighted, MAY have negative edges" << endl;
    cout << "Floyd-Warshall: Need ALL pairs shortest paths" << endl;
    cout << endl;

    cout << "--- Key Properties ---" << endl;
    cout << "Dijkstra is GREEDY: picks closest vertex" << endl;
    cout << "Bellman-Ford relaxes ALL edges V-1 times" << endl;
    cout << "Floyd-Warshall uses DP: try each vertex as intermediate" << endl;
    cout << endl;

    cout << "--- Negative Cycle ---" << endl;
    cout << "Bellman-Ford and Floyd-Warshall can DETECT negative cycles" << endl;
    cout << "Dijkstra gives WRONG answer with negative weights" << endl;
    cout << "BFS only works for unweighted graphs" << endl;
    cout << endl;

    cout << "--- Topics Covered in 7.3 ---" << endl;
    cout << "01. Dijkstra Algorithm       - Greedy, non-negative weights" << endl;
    cout << "02. Dijkstra with Path       - Reconstruct shortest path" << endl;
    cout << "03. Bellman-Ford             - Handles negative weights" << endl;
    cout << "04. Negative Cycle Demo      - Detection demo" << endl;
    cout << "05. Floyd-Warshall           - All-pairs shortest path" << endl;
    cout << "06. Shortest Path Summary    - This file" << endl;

    return 0;
}
