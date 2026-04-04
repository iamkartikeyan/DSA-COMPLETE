/*
 * File: 02_Adjacency_Matrix.cpp
 * Topic: Adjacency Matrix representation
 * Description: 2D array where matrix[i][j] = 1 if edge exists
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Adjacency Matrix ===" << endl;
    cout << endl;

    /*
     * Adjacency Matrix: V x V 2D array
     * matrix[i][j] = 1  if edge exists from i to j
     * matrix[i][j] = 0  if no edge
     *
     * For weighted graph: matrix[i][j] = weight
     *
     * Graph (undirected):
     *   0 -- 1
     *   |    |
     *   2 -- 3
     *
     * Matrix:
     *     0  1  2  3
     *   0  0  1  1  0
     *   1  1  0  0  1
     *   2  1  0  0  1
     *   3  0  1  1  0
     */

    int V = 4;
    int matrix[4][4] = {0}; // all zeros

    // Add edges (undirected = both directions)
    // 0-1
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    // 0-2
    matrix[0][2] = 1;
    matrix[2][0] = 1;
    // 1-3
    matrix[1][3] = 1;
    matrix[3][1] = 1;
    // 2-3
    matrix[2][3] = 1;
    matrix[3][2] = 1;

    // Print matrix
    cout << "Adjacency Matrix:" << endl;
    cout << "    0  1  2  3" << endl;
    for (int i = 0; i < V; i++) {
        cout << "  " << i << " ";
        for (int j = 0; j < V; j++) {
            cout << " " << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // Check if edge exists
    cout << "--- Edge Checks ---" << endl;
    cout << "Edge 0->1 exists: " << (matrix[0][1] == 1 ? "Yes" : "No") << endl;
    cout << "Edge 0->3 exists: " << (matrix[0][3] == 1 ? "Yes" : "No") << endl;
    cout << "Edge 2->3 exists: " << (matrix[2][3] == 1 ? "Yes" : "No") << endl;
    cout << endl;

    // Weighted adjacency matrix
    cout << "--- Weighted Adjacency Matrix ---" << endl;
    int wMatrix[3][3] = {0};
    wMatrix[0][1] = 5;  // edge 0->1 weight 5
    wMatrix[1][2] = 10; // edge 1->2 weight 10
    wMatrix[0][2] = 3;  // edge 0->2 weight 3

    cout << "    0   1   2" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  " << i << " ";
        for (int j = 0; j < 3; j++) {
            if (wMatrix[i][j] == 0) {
                cout << " inf";
            } else {
                cout << " " << wMatrix[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << endl;
    cout << "--- Properties ---" << endl;
    cout << "Space: O(V^2) - always uses V*V memory" << endl;
    cout << "Edge check: O(1) - just look up matrix[i][j]" << endl;
    cout << "Add edge: O(1)" << endl;
    cout << "Find neighbors: O(V) - scan entire row" << endl;
    cout << endl;
    cout << "Best for: DENSE graphs (many edges)" << endl;
    cout << "Worst for: SPARSE graphs (wastes memory on zeros)" << endl;

    return 0;
}
