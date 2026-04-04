/*
 * File: 04_MST_Properties.cpp
 * Topic: MST properties and Prim vs Kruskal comparison
 * Description: Cut property, cycle property, when to use each
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== MST - Properties & Summary ===" << endl;
    cout << endl;

    cout << "--- What is MST? ---" << endl;
    cout << "Minimum Spanning Tree:" << endl;
    cout << "  - Connects ALL vertices" << endl;
    cout << "  - Uses MINIMUM total edge weight" << endl;
    cout << "  - Has EXACTLY V-1 edges" << endl;
    cout << "  - Has NO cycles" << endl;
    cout << endl;

    cout << "--- MST Properties ---" << endl;
    cout << endl;

    cout << "1. Cut Property:" << endl;
    cout << "   If you split vertices into two groups (a cut)," << endl;
    cout << "   the LIGHTEST edge crossing the cut MUST be in MST." << endl;
    cout << endl;

    cout << "2. Cycle Property:" << endl;
    cout << "   In any cycle, the HEAVIEST edge is NOT in MST." << endl;
    cout << "   (You can skip it and still connect everything)" << endl;
    cout << endl;

    cout << "3. Uniqueness:" << endl;
    cout << "   If all edge weights are DISTINCT, MST is UNIQUE." << endl;
    cout << "   If some weights are same, multiple MSTs possible" << endl;
    cout << "   (but all have same total weight)." << endl;
    cout << endl;

    cout << "4. Number of edges:" << endl;
    cout << "   MST always has exactly V-1 edges for V vertices." << endl;
    cout << endl;

    cout << "--- Prim vs Kruskal ---" << endl;
    cout << endl;
    cout << "Feature      | Prim's           | Kruskal's" << endl;
    cout << "-------------|------------------|------------------" << endl;
    cout << "Approach     | Grow from vertex | Sort all edges" << endl;
    cout << "Time         | O((V+E)log V)   | O(E log E)" << endl;
    cout << "Best for     | Dense graphs     | Sparse graphs" << endl;
    cout << "Uses         | Priority queue   | Union-Find" << endl;
    cout << "Starts from  | Any vertex       | Smallest edge" << endl;
    cout << "Result       | Same total weight| Same total weight" << endl;
    cout << endl;

    cout << "--- Topics Covered in 7.4 ---" << endl;
    cout << "01. Prim's Algorithm    - Greedy vertex expansion" << endl;
    cout << "02. Kruskal's Algorithm - Sort edges + DSU" << endl;
    cout << "03. Union-Find (DSU)    - Path compression + rank" << endl;
    cout << "04. MST Properties      - Cut, cycle, uniqueness" << endl;

    return 0;
}
