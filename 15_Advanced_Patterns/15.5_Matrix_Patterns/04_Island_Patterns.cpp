// 15.5 - Island Patterns
// Count islands (connected components of 1s) in a binary matrix.
// Also covers: max island area, number of distinct islands.
//
// APPROACHES:
//   1. DFS: recursively visit all connected 1s, mark as visited
//   2. BFS: use a queue to visit all connected 1s level by level
//
// KEY IDEA:
//   When you find a 1, it's a new island. DFS/BFS from that cell
//   to find and mark all connected 1s (mark as 0 to avoid revisiting).
//
// Time: O(m*n) - each cell visited at most once.
// Space: O(m*n) worst case for recursion stack / queue.

#include <iostream>

using namespace std;

const int MAX_N = 20;

void printMatrix(const int matrix[][MAX_N], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << " " << matrix[i][j];
        }
        cout << endl;
    }
}

void copyMatrix(int dest[][MAX_N], const int src[][MAX_N], int m, int n) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            dest[i][j] = src[i][j];
}

// ============================================================
// COUNT ISLANDS - DFS
// Modifies the matrix in-place (marks visited cells as 0).
// ============================================================

void dfs(const int directions[][2], int grid[][MAX_N], int m, int n, int r, int c) {
    // Boundary check and water check
    if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) {
        return;
    }

    // Mark as visited (set to 0)
    grid[r][c] = 0;

    // Visit all 4 neighbors
    for (int i = 0; i < 4; i++) {
        dfs(directions, grid, m, n, r + directions[i][0], c + directions[i][1]);
    }
}

int countIslandsDFS(int grid[][MAX_N], int m, int n) {
    int count = 0;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // up, down, left, right

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                count++;
                dfs((const int(*)[2])directions, grid, m, n, i, j);
            }
        }
    }

    return count;
}

// ============================================================
// COUNT ISLANDS - BFS
// Uses a simple array-based queue.
// ============================================================

int countIslandsBFS(int grid[][MAX_N], int m, int n) {
    int count = 0;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Simple queue using arrays
    int qRow[MAX_N * MAX_N];
    int qCol[MAX_N * MAX_N];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                count++;
                // BFS from (i, j)
                int front = 0, back = 0;
                qRow[back] = i;
                qCol[back] = j;
                back++;
                grid[i][j] = 0;  // Mark visited

                while (front < back) {
                    int r = qRow[front];
                    int c = qCol[front];
                    front++;

                    // Visit all 4 neighbors
                    for (int d = 0; d < 4; d++) {
                        int nr = r + directions[d][0];
                        int nc = c + directions[d][1];

                        if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                            grid[nr][nc] = 0;
                            qRow[back] = nr;
                            qCol[back] = nc;
                            back++;
                        }
                    }
                }
            }
        }
    }

    return count;
}

// ============================================================
// MAXIMUM ISLAND AREA
// Find the largest connected component of 1s.
// ============================================================

int maxIslandArea(int grid[][MAX_N], int m, int n) {
    int maxArea = 0;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Simple queue for BFS
    int qRow[MAX_N * MAX_N];
    int qCol[MAX_N * MAX_N];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                int area = 0;
                int front = 0, back = 0;
                qRow[back] = i;
                qCol[back] = j;
                back++;
                grid[i][j] = 0;
                area++;

                while (front < back) {
                    int r = qRow[front];
                    int c = qCol[front];
                    front++;

                    for (int d = 0; d < 4; d++) {
                        int nr = r + directions[d][0];
                        int nc = c + directions[d][1];

                        if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                            grid[nr][nc] = 0;
                            qRow[back] = nr;
                            qCol[back] = nc;
                            back++;
                            area++;
                        }
                    }
                }

                if (area > maxArea) maxArea = area;
            }
        }
    }

    return maxArea;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoCountIslands() {
    cout << "=== Count Islands ===" << endl;
    int grid[4][MAX_N] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1}
    };
    int m = 4, n = 5;

    cout << "Grid:" << endl;
    printMatrix((const int(*)[MAX_N])grid, m, n);
    cout << endl;

    int gridCopy[MAX_N][MAX_N];
    copyMatrix((int(*)[MAX_N])gridCopy, (const int(*)[MAX_N])grid, m, n);
    int countDFS = countIslandsDFS((int(*)[MAX_N])gridCopy, m, n);
    cout << "Islands (DFS): " << countDFS << endl;
    cout << "Expected: 3" << endl;
    cout << endl;

    copyMatrix((int(*)[MAX_N])gridCopy, (const int(*)[MAX_N])grid, m, n);
    int countBFS = countIslandsBFS((int(*)[MAX_N])gridCopy, m, n);
    cout << "Islands (BFS): " << countBFS << endl;
    cout << "Expected: 3" << endl;
    cout << endl;
}

void demoMaxIslandArea() {
    cout << "=== Maximum Island Area ===" << endl;
    int grid[4][MAX_N] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 0, 1, 1}
    };
    int m = 4, n = 5;

    cout << "Grid:" << endl;
    printMatrix((const int(*)[MAX_N])grid, m, n);
    cout << endl;

    int gridCopy[MAX_N][MAX_N];
    copyMatrix((int(*)[MAX_N])gridCopy, (const int(*)[MAX_N])grid, m, n);
    int area = maxIslandArea((int(*)[MAX_N])gridCopy, m, n);

    cout << "Max island area: " << area << endl;
    cout << "Expected: 5 (the cross-shaped island in the middle)" << endl;
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Count Islands ===" << endl;
    cout << "Grid:" << endl;
    cout << "  1  1  0  0  0" << endl;
    cout << "  1  1  0  0  1" << endl;
    cout << "  0  0  1  0  1" << endl;
    cout << "  0  0  0  1  1" << endl;
    cout << endl;
    cout << "Scan (0,0): found 1 -> island #1" << endl;
    cout << "  DFS from (0,0): visit (0,0),(0,1),(1,0),(1,1). Mark all as 0." << endl;
    cout << "Scan (1,4): found 1 -> island #2" << endl;
    cout << "  DFS from (1,4): visit (1,4),(2,4),(3,4),(3,3). Mark all as 0." << endl;
    cout << "Scan (2,2): found 1 -> island #3" << endl;
    cout << "  DFS from (2,2): visit (2,2). Mark as 0." << endl;
    cout << "Total: 3 islands" << endl;
    cout << endl;
}

void demoSingleCellIsland() {
    cout << "=== Single Cell Islands ===" << endl;
    int grid[3][MAX_N] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };
    int m = 3, n = 3;

    cout << "Grid:" << endl;
    printMatrix((const int(*)[MAX_N])grid, m, n);
    cout << endl;

    int gridCopy[MAX_N][MAX_N];
    copyMatrix((int(*)[MAX_N])gridCopy, (const int(*)[MAX_N])grid, m, n);
    int count = countIslandsDFS((int(*)[MAX_N])gridCopy, m, n);

    cout << "Islands (all single cells): " << count << endl;
    cout << "Expected: 5" << endl;
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoCountIslands();
    demoMaxIslandArea();
    demoSingleCellIsland();
    return 0;
}
