/*
 * File: 07_Advanced_Graphs_Summary.cpp
 * Topic: Complete summary of all advanced graph algorithms
 * Description: Quick reference for all graph topics
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Advanced Graph Algorithms - Summary ===" << endl;
    cout << endl;

    cout << "--- Topological Sort ---" << endl;
    cout << "Linear ordering where edges go FORWARD only." << endl;
    cout << "Kahn's (BFS): Use in-degree, process 0 in-degree vertices" << endl;
    cout << "DFS: Post-order + reverse" << endl;
    cout << "Time: O(V + E), Only works on DAGs" << endl;
    cout << endl;

    cout << "--- Kosaraju's SCC ---" << endl;
    cout << "3 steps:" << endl;
    cout << "  1. DFS on G, record finish order" << endl;
    cout << "  2. Reverse G" << endl;
    cout << "  3. DFS on G^T in reverse finish order" << endl;
    cout << "Time: O(V + E), each DFS tree = one SCC" << endl;
    cout << endl;

    cout << "--- Articulation Points ---" << endl;
    cout << "Vertices whose removal disconnects graph." << endl;
    cout << "DFS + disc[] and low[] arrays" << endl;
    cout << "Condition: low[v] >= disc[u]" << endl;
    cout << "Time: O(V + E)" << endl;
    cout << endl;

    cout << "--- Bridges ---" << endl;
    cout << "Edges whose removal disconnects graph." << endl;
    cout << "Same DFS approach as AP" << endl;
    cout << "Condition: low[v] > disc[u] (strictly greater)" << endl;
    cout << "Time: O(V + E)" << endl;
    cout << endl;

    cout << "--- Bipartite Check ---" << endl;
    cout << "Can graph be 2-colored?" << endl;
    cout << "BFS/DFS coloring: each vertex gets opposite color of parent" << endl;
    cout << "Conflict = NOT bipartite" << endl;
    cout << "No odd-length cycles = bipartite" << endl;
    cout << "Time: O(V + E)" << endl;
    cout << endl;

    cout << "--- Complete Graph Topics Map ---" << endl;
    cout << endl;
    cout << "7.1 Graph Fundamentals:" << endl;
    cout << "  01. Graph Terminology" << endl;
    cout << "  02. Adjacency Matrix" << endl;
    cout << "  03. Adjacency List" << endl;
    cout << "  04. Edge List" << endl;
    cout << "  05. Representation Comparison" << endl;
    cout << endl;
    cout << "7.2 Graph Traversals:" << endl;
    cout << "  01. BFS Traversal" << endl;
    cout << "  02. BFS Shortest Path" << endl;
    cout << "  03. DFS Recursive" << endl;
    cout << "  04. DFS Iterative" << endl;
    cout << "  05. Connected Components" << endl;
    cout << "  06. Cycle Detection (Undirected)" << endl;
    cout << "  07. Cycle Detection (Directed)" << endl;
    cout << "  08. BFS vs DFS Comparison" << endl;
    cout << endl;
    cout << "7.3 Shortest Path:" << endl;
    cout << "  01. Dijkstra Algorithm" << endl;
    cout << "  02. Dijkstra with Path" << endl;
    cout << "  03. Bellman-Ford" << endl;
    cout << "  04. Negative Cycle Demo" << endl;
    cout << "  05. Floyd-Warshall" << endl;
    cout << "  06. Shortest Path Summary" << endl;
    cout << endl;
    cout << "7.4 Minimum Spanning Tree:" << endl;
    cout << "  01. Prim's Algorithm" << endl;
    cout << "  02. Kruskal's Algorithm" << endl;
    cout << "  03. Union-Find (DSU)" << endl;
    cout << "  04. MST Properties" << endl;
    cout << endl;
    cout << "7.5 Advanced Graphs:" << endl;
    cout << "  01. Topological Sort (Kahn's)" << endl;
    cout << "  02. Topological Sort (DFS)" << endl;
    cout << "  03. Kosaraju's SCC" << endl;
    cout << "  04. Articulation Points" << endl;
    cout << "  05. Bridges" << endl;
    cout << "  06. Bipartite Check" << endl;
    cout << "  07. Advanced Graphs Summary" << endl;

    return 0;
}
