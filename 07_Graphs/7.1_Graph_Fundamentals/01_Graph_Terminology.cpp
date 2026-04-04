/*
 * File: 01_Graph_Terminology.cpp
 * Topic: What is Graph, basic terms
 * Description: Vertices, edges, directed/undirected, weighted/unweighted
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Graph Terminology ===" << endl;
    cout << endl;

    cout << "--- What is a Graph? ---" << endl;
    cout << "A graph = collection of POINTS (vertices) connected by LINES (edges)." << endl;
    cout << "Used to model relationships: social networks, road maps, web pages." << endl;
    cout << endl;

    cout << "--- Key Terms ---" << endl;
    cout << endl;

    cout << "1. Vertex (Node):" << endl;
    cout << "   A point in the graph." << endl;
    cout << "   Example: cities in a road map." << endl;
    cout << endl;

    cout << "2. Edge:" << endl;
    cout << "   A connection between two vertices." << endl;
    cout << "   Example: road between two cities." << endl;
    cout << endl;

    cout << "3. Directed Graph:" << endl;
    cout << "   Edges have DIRECTION (one-way)." << endl;
    cout << "   Example: 0 -> 1 means you can go from 0 to 1 but not back." << endl;
    cout << endl;

    cout << "4. Undirected Graph:" << endl;
    cout << "   Edges are BIDIRECTIONAL (two-way)." << endl;
    cout << "   Example: 0 - 1 means you can go both ways." << endl;
    cout << endl;

    cout << "5. Weighted Graph:" << endl;
    cout << "   Edges have WEIGHTS/COSTS." << endl;
    cout << "   Example: distance between cities." << endl;
    cout << endl;

    cout << "6. Unweighted Graph:" << endl;
    cout << "   All edges treated equally (no weights)." << endl;
    cout << endl;

    cout << "7. Degree:" << endl;
    cout << "   Number of edges connected to a vertex." << endl;
    cout << "   In directed: in-degree (incoming) + out-degree (outgoing)." << endl;
    cout << endl;

    cout << "8. Path:" << endl;
    cout << "   Sequence of vertices connected by edges." << endl;
    cout << "   Example: 0 -> 1 -> 3 is a path." << endl;
    cout << endl;

    cout << "9. Cycle:" << endl;
    cout << "   A path that starts and ends at the SAME vertex." << endl;
    cout << "   Example: 0 -> 1 -> 2 -> 0 is a cycle." << endl;
    cout << endl;

    cout << "10. Connected Graph:" << endl;
    cout << "    A path exists between EVERY pair of vertices." << endl;
    cout << endl;

    cout << "11. DAG (Directed Acyclic Graph):" << endl;
    cout << "    Directed graph with NO cycles." << endl;
    cout << "    Used in: task scheduling, build systems." << endl;
    cout << endl;

    cout << "12. Complete Graph:" << endl;
    cout << "    Every pair of vertices has an edge." << endl;
    cout << "    Number of edges = V * (V-1) / 2" << endl;

    return 0;
}
