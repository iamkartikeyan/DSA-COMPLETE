/*
 * File: 05_Graph_Representation_Comparison.cpp
 * Topic: Complete comparison of all graph representations
 * Description: When to use matrix vs list vs edge list
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Graph Representations - Comparison ===" << endl;
    cout << endl;

    /*
     * Same graph represented 3 ways:
     *
     *     0 ---- 1
     *     |      |
     *     |      |
     *     3 ---- 2
     *
     * Edges: (0,1), (0,3), (1,2), (2,3)
     */

    cout << "--- Adjacency Matrix ---" << endl;
    cout << "    0  1  2  3" << endl;
    cout << "  0  0  1  0  1" << endl;
    cout << "  1  1  0  1  0" << endl;
    cout << "  2  0  1  0  1" << endl;
    cout << "  3  1  0  1  0" << endl;
    cout << endl;
    cout << "Pros: O(1) edge check" << endl;
    cout << "Cons: O(V^2) space even for few edges" << endl;
    cout << endl;

    cout << "--- Adjacency List ---" << endl;
    cout << "  0 -> 1, 3" << endl;
    cout << "  1 -> 0, 2" << endl;
    cout << "  2 -> 1, 3" << endl;
    cout << "  3 -> 0, 2" << endl;
    cout << endl;
    cout << "Pros: O(V+E) space, fast neighbor iteration" << endl;
    cout << "Cons: O(degree) edge check" << endl;
    cout << endl;

    cout << "--- Edge List ---" << endl;
    cout << "  (0, 1), (0, 3), (1, 2), (2, 3)" << endl;
    cout << endl;
    cout << "Pros: O(E) space, easy to sort edges" << endl;
    cout << "Cons: O(E) to find neighbors" << endl;
    cout << endl;

    cout << "--- Detailed Comparison ---" << endl;
    cout << endl;
    cout << "Operation          | Matrix  | List    | Edge List" << endl;
    cout << "-------------------|---------|---------|----------" << endl;
    cout << "Space              | O(V^2)  | O(V+E)  | O(E)" << endl;
    cout << "Add edge           | O(1)    | O(1)    | O(1)" << endl;
    cout << "Remove edge        | O(1)    | O(V)    | O(E)" << endl;
    cout << "Check edge (u,v)   | O(1)    | O(V)    | O(E)" << endl;
    cout << "Find neighbors of u| O(V)    | O(deg)  | O(E)" << endl;
    cout << "Iterate all edges  | O(V^2)  | O(V+E)  | O(E)" << endl;
    cout << endl;

    cout << "--- When to Use ---" << endl;
    cout << "Adjacency Matrix:" << endl;
    cout << "  - Graph is DENSE (many edges)" << endl;
    cout << "  - Need frequent edge checks" << endl;
    cout << "  - V is small (V^2 fits in memory)" << endl;
    cout << endl;
    cout << "Adjacency List:" << endl;
    cout << "  - Graph is SPARSE (few edges)" << endl;
    cout << "  - Need to iterate neighbors often" << endl;
    cout << "  - MOST COMMON choice for competitive programming" << endl;
    cout << endl;
    cout << "Edge List:" << endl;
    cout << "  - Need to process/sort ALL edges" << endl;
    cout << "  - Kruskal's MST, Bellman-Ford" << endl;
    cout << "  - Rarely used alone" << endl;

    return 0;
}
