/*
 * File: 08_BFS_vs_DFS_Comparison.cpp
 * Topic: When to use BFS vs DFS
 * Description: Comparison table and use cases
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== BFS vs DFS - Comparison ===" << endl;
    cout << endl;

    cout << "--- BFS (Breadth-First Search) ---" << endl;
    cout << "Data structure: Queue" << endl;
    cout << "Approach: Explore level by level" << endl;
    cout << "Finds: Shortest path in UNWEIGHTED graphs" << endl;
    cout << endl;

    cout << "--- DFS (Depth-First Search) ---" << endl;
    cout << "Data structure: Stack (or recursion)" << endl;
    cout << "Approach: Go deep first, then backtrack" << endl;
    cout << "Finds: Reachability, paths, cycles" << endl;
    cout << endl;

    cout << "--- Comparison Table ---" << endl;
    cout << endl;
    cout << "Feature          | BFS              | DFS" << endl;
    cout << "-----------------|------------------|------------------" << endl;
    cout << "Data Structure   | Queue            | Stack/Recursion" << endl;
    cout << "Order            | Level by level   | Deep first" << endl;
    cout << "Shortest Path    | Yes (unweighted) | No" << endl;
    cout << "Time             | O(V + E)         | O(V + E)" << endl;
    cout << "Space            | O(V)             | O(V)" << endl;
    cout << endl;

    cout << "--- Use BFS For ---" << endl;
    cout << "1. Shortest path (unweighted graph)" << endl;
    cout << "2. Level-order traversal" << endl;
    cout << "3. Finding connected components" << endl;
    cout << "4. Bipartite check" << endl;
    cout << "5. Finding nearest target" << endl;
    cout << endl;

    cout << "--- Use DFS For ---" << endl;
    cout << "1. Cycle detection" << endl;
    cout << "2. Topological sort" << endl;
    cout << "3. Finding paths" << endl;
    cout << "4. Strongly connected components" << endl;
    cout << "5. Maze solving" << endl;
    cout << "6. Articulation points and bridges" << endl;
    cout << endl;

    cout << "--- Example ---" << endl;
    cout << "Finding shortest path from A to B: USE BFS" << endl;
    cout << "Checking if maze has a solution: USE DFS" << endl;
    cout << "Finding all connected groups: USE BFS or DFS" << endl;
    cout << "Detecting deadlock in tasks: USE DFS (cycle detection)" << endl;

    return 0;
}
