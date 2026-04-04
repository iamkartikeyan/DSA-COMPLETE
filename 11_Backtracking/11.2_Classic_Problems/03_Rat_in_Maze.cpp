// 03_Rat_in_Maze.cpp
// Find all paths from top-left (0,0) to bottom-right (n-1,n-1)
// in an n x n maze. The maze has obstacles (0 = blocked, 1 = open).
// The rat can move in 4 directions: Down, Left, Right, Up.
// Paths are returned in lexicographic order: D < L < R < U.
//
// Time Complexity: O(4^(n^2)) worst case (every cell has 4 choices).
// Space Complexity: O(n^2) for visited array + O(n^2) recursion depth.

#include <iostream>
using namespace std;

const int MAX_N = 10;
int pathCount = 0;

/*
 * isSafe - Check if moving to cell (i, j) is valid.
 *
 * A move is safe if:
 *   1. (i, j) is within the board boundaries.
 *   2. The cell is not an obstacle (maze[i][j] == 1).
 *   3. The cell has not been visited in the current path.
 */
bool isSafe(int maze[][MAX_N], int i, int j, int n, bool visited[][MAX_N]) {
    return i >= 0 && i < n && j >= 0 && j < n
           && maze[i][j] == 1 && !visited[i][j];
}

/*
 * printPath - Display a path as a sequence of moves.
 */
void printPath(char path[], int pathLen) {
    cout << "  Path " << ++pathCount << ": ";
    for (int i = 0; i < pathLen; i++) {
        cout << path[i];
    }
    cout << endl;
}

/*
 * findPaths - Find all paths from (i, j) to (n-1, n-1).
 *
 * Parameters:
 *   maze[][]    - the maze grid (1 = open, 0 = blocked)
 *   n           - maze size
 *   i, j        - current position
 *   path[]      - buffer storing the sequence of moves so far
 *   pathLen     - current length of the path
 *   visited[][] - tracks which cells are in the current path
 *
 * Backtracking flow:
 *   CHOICE:     Move in one of 4 directions (D, L, R, U).
 *   CONSTRAINT: isSafe() checks boundaries, obstacles, and visited.
 *   GOAL:       (i, j) == (n-1, n-1) (reached destination).
 *   PRUNING:    Implicit - unsafe moves are skipped.
 *   BACKTRACK:  Mark visited[i][j] = false when returning from recursion.
 */
void findPaths(int maze[][MAX_N], int n, int i, int j,
               char path[], int pathLen, bool visited[][MAX_N]) {
    // GOAL: reached bottom-right corner
    if (i == n - 1 && j == n - 1) {
        path[pathLen] = '\0';  // null-terminate for safety
        printPath(path, pathLen);
        return;
    }

    // Mark current cell as visited (part of current path)
    visited[i][j] = true;

    // Direction arrays: Down, Left, Right, Up (lexicographic order)
    int di[] = {1, 0, 0, -1};
    int dj[] = {0, -1, 1, 0};
    char dirs[] = {'D', 'L', 'R', 'U'};

    // Try all 4 directions
    for (int d = 0; d < 4; d++) {
        int ni = i + di[d];
        int nj = j + dj[d];

        // CONSTRAINT: check if move is safe
        if (isSafe(maze, ni, nj, n, visited)) {
            path[pathLen] = dirs[d];              // CHOICE: record move
            findPaths(maze, n, ni, nj, path, pathLen + 1, visited);  // recurse
            // BACKTRACK: no explicit undo needed for path (overwritten)
        }
    }

    // BACKTRACK: unmark current cell so it can be used in other paths
    visited[i][j] = false;
}

/*
 * solveRatInMaze - Entry point: initialize and call findPaths.
 */
void solveRatInMaze(int maze[][MAX_N], int n) {
    // Check if start or end is blocked
    if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) {
        cout << "  No path possible (start or end is blocked)." << endl;
        return;
    }

    bool visited[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = false;
        }
    }

    char path[MAX_N * MAX_N];  // buffer for path (max length = n*n)
    pathCount = 0;

    cout << "Paths from (0,0) to (" << n - 1 << "," << n - 1 << "):" << endl;
    findPaths(maze, n, 0, 0, path, 0, visited);

    if (pathCount == 0) {
        cout << "  (no paths found)" << endl;
    } else {
        cout << "Total: " << pathCount << " paths" << endl;
    }
}

int main() {
    cout << "=== Rat in a Maze ===" << endl;
    cout << endl;

    cout << "Problem: Find all paths from (0,0) to (n-1,n-1)" << endl;
    cout << "  1 = open cell, 0 = obstacle" << endl;
    cout << "  Directions: D(own), L(eft), R(ight), U(p)" << endl;
    cout << "  Each cell used at most once per path" << endl;
    cout << endl;

    // ---- Example 1: Standard 4x4 maze ----
    cout << "--- Example 1: 4x4 Maze ---" << endl;
    int maze1[MAX_N][MAX_N] = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    int n1 = 4;

    // Print maze
    cout << "Maze:" << endl;
    for (int i = 0; i < n1; i++) {
        cout << "  ";
        for (int j = 0; j < n1; j++) {
            cout << maze1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    solveRatInMaze(maze1, n1);
    cout << endl;

    // ---- Example 2: All open 3x3 maze ----
    cout << "--- Example 2: All Open 3x3 Maze ---" << endl;
    int maze2[MAX_N][MAX_N] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    int n2 = 3;

    cout << "Maze: all cells open" << endl;
    cout << endl;
    solveRatInMaze(maze2, n2);
    cout << endl;

    // ---- Example 3: No path possible ----
    cout << "--- Example 3: No Path Possible ---" << endl;
    int maze3[MAX_N][MAX_N] = {
        {1, 0},
        {0, 1}
    };
    int n3 = 2;

    cout << "Maze:" << endl;
    cout << "  1 0" << endl;
    cout << "  0 1" << endl;
    cout << endl;
    solveRatInMaze(maze3, n3);
    cout << endl;

    cout << "Backtracking approach:" << endl;
    cout << "  1. Start at (0,0), mark as visited" << endl;
    cout << "  2. Try moves in order: D, L, R, U (lexicographic)" << endl;
    cout << "  3. For each safe move: record direction, recurse" << endl;
    cout << "  4. At destination: print the path" << endl;
    cout << "  5. Backtrack: unmark cell, try next direction" << endl;
    cout << endl;
    cout << "Key: visited[][] ensures no cell is used twice in one path." << endl;
    cout << "When backtracking, we unmark the cell so it can appear in other paths." << endl;

    return 0;
}
