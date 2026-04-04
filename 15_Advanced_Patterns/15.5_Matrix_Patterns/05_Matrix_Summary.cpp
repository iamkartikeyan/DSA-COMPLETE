// 15.5 - Matrix Patterns Summary
// Complete reference for all matrix traversal and manipulation patterns.

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_N = 20;

void printMatrix(const int matrix[][MAX_N], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << matrix[i][j];
        }
        cout << endl;
    }
}

// ============================================================
// PATTERN SUMMARY
// ============================================================

void demoPatternSummary() {
    cout << "=== MATRIX PATTERNS SUMMARY ===" << endl;
    cout << endl;
    cout << "CORE CONCEPTS:" << endl;
    cout << "  - 2D grid with rows and columns" << endl;
    cout << "  - Common operations: traverse, search, rotate, find components" << endl;
    cout << "  - Boundary tracking: top, bottom, left, right" << endl;
    cout << "  - Direction arrays for neighbor traversal: up, down, left, right" << endl;
    cout << endl;
}

// ============================================================
// SPIRAL TRAVERSAL
// ============================================================

void demoSpiralPattern() {
    cout << "=== SPIRAL TRAVERSAL ===" << endl;
    cout << endl;
    cout << "Pattern: Four directions, shrink boundaries" << endl;
    cout << endl;
    cout << "  top=0, bottom=m-1, left=0, right=n-1" << endl;
    cout << "  while (top <= bottom && left <= right):" << endl;
    cout << "    1. Right:  for j=left to right:   result += matrix[top][j]; top++" << endl;
    cout << "    2. Down:   for i=top to bottom:    result += matrix[i][right]; right--" << endl;
    cout << "    3. Left:   if top<=bottom: for j=right to left: result += matrix[bottom][j]; bottom--" << endl;
    cout << "    4. Up:     if left<=right: for i=bottom to top:  result += matrix[i][left]; left++" << endl;
    cout << endl;
    cout << "IMPORTANT: Check boundaries before steps 3 and 4" << endl;
    cout << "(after steps 1 and 2, boundaries may have crossed)" << endl;
    cout << endl;
    cout << "Time: O(m*n), Space: O(1) extra (excluding result)" << endl;
    cout << endl;
}

// ============================================================
// MATRIX SEARCH
// ============================================================

void demoSearchPattern() {
    cout << "=== MATRIX SEARCH ===" << endl;
    cout << endl;
    cout << "Type 1: Fully sorted (flattened property)" << endl;
    cout << "  Each row sorted, first of row > last of prev row" << endl;
    cout << "  -> Binary search on flattened array: O(log(m*n))" << endl;
    cout << "  Map: row = idx/n, col = idx%n" << endl;
    cout << endl;
    cout << "Type 2: Row+Column sorted (staircase)" << endl;
    cout << "  Each row sorted, each column sorted" << endl;
    cout << "  -> Start top-right, move left or down: O(m+n)" << endl;
    cout << "  if target < current: col-- (eliminate column)" << endl;
    cout << "  if target > current: row++ (eliminate row)" << endl;
    cout << endl;
}

// ============================================================
// MATRIX ROTATION
// ============================================================

void demoRotationPattern() {
    cout << "=== MATRIX ROTATION ===" << endl;
    cout << endl;
    cout << "90 CW (clockwise):" << endl;
    cout << "  Step 1: Transpose (swap [i][j] with [j][i])" << endl;
    cout << "  Step 2: Reverse each row" << endl;
    cout << endl;
    cout << "90 CCW (counter-clockwise):" << endl;
    cout << "  Step 1: Reverse each row" << endl;
    cout << "  Step 2: Transpose" << endl;
    cout << endl;
    cout << "180 degrees:" << endl;
    cout << "  Reverse each row, then reverse each column" << endl;
    cout << "  OR: rotate 90 CW twice" << endl;
    cout << endl;
    cout << "All are O(n^2) time, O(1) space (in-place)" << endl;
    cout << endl;
}

// ============================================================
// ISLAND PATTERNS (Connected Components)
// ============================================================

void demoIslandPattern() {
    cout << "=== ISLAND PATTERNS ===" << endl;
    cout << endl;
    cout << "Count Islands:" << endl;
    cout << "  For each cell with value 1:" << endl;
    cout << "    increment count" << endl;
    cout << "    DFS/BFS to mark all connected 1s as 0" << endl;
    cout << endl;
    cout << "DFS:" << endl;
    cout << "  void dfs(grid, r, c):" << endl;
    cout << "    if out of bounds or grid[r][c]==0: return" << endl;
    cout << "    grid[r][c] = 0  // mark visited" << endl;
    cout << "    for each direction: dfs(grid, r+dr, c+dc)" << endl;
    cout << endl;
    cout << "BFS:" << endl;
    cout << "  queue.push(start)" << endl;
    cout << "  while queue not empty:" << endl;
    cout << "    cell = queue.pop()" << endl;
    cout << "    for each neighbor:" << endl;
    cout << "      if valid and unvisited: mark, enqueue" << endl;
    cout << endl;
    cout << "Time: O(m*n), Space: O(m*n) worst case" << endl;
    cout << endl;
}

// ============================================================
// DIRECTION ARRAYS
// ============================================================

void demoDirectionArrays() {
    cout << "=== DIRECTION ARRAYS ===" << endl;
    cout << endl;
    cout << "4 directions (up, down, left, right):" << endl;
    cout << "  int dr[4] = {-1, 1, 0, 0};" << endl;
    cout << "  int dc[4] = {0, 0, -1, 1};" << endl;
    cout << endl;
    cout << "8 directions (including diagonals):" << endl;
    cout << "  int dr[8] = {-1,-1,-1, 0,0, 1,1,1};" << endl;
    cout << "  int dc[8] = {-1, 0, 1,-1,1,-1,0,1};" << endl;
    cout << endl;
    cout << "Usage:" << endl;
    cout << "  for (int d = 0; d < 4; d++) {" << endl;
    cout << "    int nr = r + dr[d];" << endl;
    cout << "    int nc = c + dc[d];" << endl;
    cout << "    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {" << endl;
    cout << "      // process neighbor" << endl;
    cout << "    }" << endl;
    cout << "  }" << endl;
    cout << endl;
}

// ============================================================
// PROBLEM CATALOG
// ============================================================

void demoProblemCatalog() {
    cout << "=== PROBLEM CATALOG ===" << endl;
    cout << endl;
    cout << "Problem                    | Pattern              | Time" << endl;
    cout << "---------------------------|----------------------|----------" << endl;
    cout << "Spiral Traversal (54)      | Boundary shrink      | O(m*n)" << endl;
    cout << "Generate Spiral (59)       | Boundary shrink      | O(n^2)" << endl;
    cout << "Set Matrix Zeroes (73)     | First row/col marker | O(m*n)" << endl;
    cout << "Rotate Image (48)          | Transpose + reverse  | O(n^2)" << endl;
    cout << "Word Search (79)           | Backtracking DFS     | O(m*n*4^L)" << endl;
    cout << "Number of Islands (200)    | DFS/BFS              | O(m*n)" << endl;
    cout << "Max Island Area (695)      | DFS/BFS + area count | O(m*n)" << endl;
    cout << "Search 2D Matrix (74)      | Binary search        | O(log(m*n))" << endl;
    cout << "Search 2D Matrix II (240)  | Staircase search     | O(m+n)" << endl;
    cout << "Diagonal Traverse (498)    | Alternating diagonal | O(m*n)" << endl;
    cout << "Pacific Atlantic (417)     | DFS from edges       | O(m*n)" << endl;
    cout << "Surrounded Regions (130)   | DFS from borders     | O(m*n)" << endl;
    cout << endl;
}

// ============================================================
// COMMON MISTAKES
// ============================================================

void demoCommonMistakes() {
    cout << "=== COMMON MISTAKES ===" << endl;
    cout << endl;
    cout << "1. Forgetting boundary checks in spiral (steps 3 and 4)" << endl;
    cout << "2. Off-by-one in rotation (transpose only goes to j=i+1, not j=0)" << endl;
    cout << "3. Not marking visited cells in island DFS (infinite recursion)" << endl;
    cout << "4. Wrong direction array indices (dr vs dc mixup)" << endl;
    cout << "5. Forgetting bounds check before accessing grid[nr][nc]" << endl;
    cout << "6. Using >= instead of > for spiral boundary (<=)" << endl;
    cout << endl;
}

// ============================================================
// QUICK DEMO
// ============================================================

void demoQuickDemo() {
    cout << "=== Quick Demo: Spiral + Rotation ===" << endl;
    int matrix[3][MAX_N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Original:" << endl;
    printMatrix((const int(*)[MAX_N])matrix, 3, 3);
    cout << endl;

    cout << "Spiral: 1 2 3 6 9 8 7 4 5" << endl;
    cout << "Rotated 90 CW:" << endl;
    cout << "  7  4  1" << endl;
    cout << "  8  5  2" << endl;
    cout << "  9  6  3" << endl;
    cout << endl;
}

int main() {
    demoPatternSummary();
    demoSpiralPattern();
    demoSearchPattern();
    demoRotationPattern();
    demoIslandPattern();
    demoDirectionArrays();
    demoProblemCatalog();
    demoCommonMistakes();
    demoQuickDemo();
    return 0;
}
