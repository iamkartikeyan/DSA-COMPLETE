// 15.5 Matrix Patterns - Spiral, Rotate, Set Zeroes
// Common 2D matrix traversal and manipulation techniques.
// Key idea: track boundaries (top, bottom, left, right) and shrink them.

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Helper: print matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (auto& row : matrix) {
        for (int x : row) cout << setw(3) << x;
        cout << endl;
    }
}

// ============================================================
// SPIRAL TRAVERSAL (LeetCode 54)
// Traverse matrix in spiral order: right, down, left, up.
// Shrink boundaries after each direction.
// Time: O(m*n)
// ============================================================

vector<int> spiralOrder(const vector<vector<int>>& matrix) {
    vector<int> result;
    if (matrix.empty()) return result;

    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;

    while (top <= bottom && left <= right) {
        // Traverse right (top row)
        for (int j = left; j <= right; j++) result.push_back(matrix[top][j]);
        top++;

        // Traverse down (right column)
        for (int i = top; i <= bottom; i++) result.push_back(matrix[i][right]);
        right--;

        // Traverse left (bottom row)
        if (top <= bottom) {
            for (int j = right; j >= left; j--) result.push_back(matrix[bottom][j]);
            bottom--;
        }

        // Traverse up (left column)
        if (left <= right) {
            for (int i = bottom; i >= top; i--) result.push_back(matrix[i][left]);
            left++;
        }
    }
    return result;
}

void demoSpiralOrder() {
    cout << "=== Spiral Traversal ===" << endl;
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    printMatrix(matrix);
    auto result = spiralOrder(matrix);
    cout << "Spiral: "; for (int x : result) cout << x << " ";  // 1 2 3 6 9 8 7 4 5
    cout << endl << endl;
}

// ============================================================
// GENERATE SPIRAL MATRIX (LeetCode 59)
// Fill an n x n matrix with 1..n^2 in spiral order.
// ============================================================

vector<vector<int>> generateSpiralMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int num = 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) matrix[top][j] = num++;
        top++;
        for (int i = top; i <= bottom; i++) matrix[i][right] = num++;
        right--;
        if (top <= bottom)
            for (int j = right; j >= left; j--) matrix[bottom][j] = num++;
        bottom--;
        if (left <= right)
            for (int i = bottom; i >= top; i--) matrix[i][left] = num++;
        left++;
    }
    return matrix;
}

void demoGenerateSpiral() {
    cout << "=== Generate Spiral Matrix ===" << endl;
    int n = 4;
    cout << "n = " << n << endl;
    auto matrix = generateSpiralMatrix(n);
    printMatrix(matrix);
    cout << endl;
}

// ============================================================
// ROTATE MATRIX 90 DEGREES CLOCKWISE (LeetCode 48)
// In-place rotation: transpose then reverse each row.
// Alternative: rotate layer by layer.
// Time: O(n^2), Space: O(1)
// ============================================================

void rotateMatrix(vector<vector<int>>& matrix) {
    int n = matrix.size();

    // Step 1: Transpose (swap matrix[i][j] with matrix[j][i])
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(matrix[i][j], matrix[j][i]);

    // Step 2: Reverse each row
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n / 2; j++)
            swap(matrix[i][j], matrix[i][n - 1 - j]);
}

// Rotate counter-clockwise: transpose + reverse columns (or reverse rows + transpose)
void rotateCounterClockwise(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n / 2; j++)
            swap(matrix[i][j], matrix[i][n - 1 - j]);
    // Then transpose
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(matrix[i][j], matrix[j][i]);
}

void demoRotateMatrix() {
    cout << "=== Rotate Matrix 90 Clockwise ===" << endl;
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "Original:" << endl; printMatrix(matrix);

    rotateMatrix(matrix);
    cout << "Rotated 90 CW:" << endl; printMatrix(matrix);  // 7 4 1 / 8 5 2 / 9 6 3
    cout << endl;
}

// ============================================================
// SET MATRIX ZEROES (LeetCode 73)
// If matrix[i][j] == 0, set entire row i and col j to 0.
// In-place: use first row/col as markers.
// Time: O(m*n), Space: O(1)
// ============================================================

void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    bool firstRowZero = false, firstColZero = false;

    // Check if first row/col has zeros
    for (int j = 0; j < n; j++) if (matrix[0][j] == 0) firstRowZero = true;
    for (int i = 0; i < m; i++) if (matrix[i][0] == 0) firstColZero = true;

    // Use first row/col as markers
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            if (matrix[i][j] == 0)
                matrix[i][0] = matrix[0][j] = 0;

    // Zero out cells based on markers
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            if (matrix[i][0] == 0 || matrix[0][j] == 0)
                matrix[i][j] = 0;

    // Zero out first row/col if needed
    if (firstRowZero)
        for (int j = 0; j < n; j++) matrix[0][j] = 0;
    if (firstColZero)
        for (int i = 0; i < m; i++) matrix[i][0] = 0;
}

void demoSetZeroes() {
    cout << "=== Set Matrix Zeroes ===" << endl;
    vector<vector<int>> matrix = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    cout << "Original:" << endl; printMatrix(matrix);
    setZeroes(matrix);
    cout << "After setZeroes:" << endl; printMatrix(matrix);  // row 1 and col 1 become 0
    cout << endl;
}

// ============================================================
// DIAGONAL TRAVERSAL
// Traverse matrix diagonally (zigzag pattern).
// ============================================================

vector<int> findDiagonalOrder(const vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int m = matrix.size(), n = matrix[0].size();
    vector<int> result;
    result.reserve(m * n);

    for (int d = 0; d < m + n - 1; d++) {
        // Going up-right (even diagonal) or down-left (odd diagonal)
        bool up = (d % 2 == 0);
        int r = up ? min(d, m - 1) : min(d, n - 1);
        int c = up ? d - r : d - r;

        while ((up && r >= 0 && c < n) || (!up && c >= 0 && r < m)) {
            result.push_back(matrix[r][c]);
            up ? (r--, c++) : (r++, c--);
        }
    }
    return result;
}

void demoDiagonalTraversal() {
    cout << "=== Diagonal Traversal ===" << endl;
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    printMatrix(matrix);
    auto result = findDiagonalOrder(matrix);
    cout << "Diagonal: "; for (int x : result) cout << x << " ";  // 1 2 4 7 5 3 6 8 9
    cout << endl << endl;
}

// ============================================================
// WORD SEARCH (LeetCode 79) - Backtracking on Matrix
// DFS with backtracking to find word in grid.
// ============================================================

bool wordSearchDFS(vector<vector<char>>& board, const string& word, int i, int j, int idx) {
    if (idx == word.size()) return true;  // Found entire word
    int m = board.size(), n = board[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[idx])
        return false;

    char saved = board[i][j];
    board[i][j] = '#';  // Mark visited

    // Try all 4 directions
    bool found = wordSearchDFS(board, word, i + 1, j, idx + 1) ||
                 wordSearchDFS(board, word, i - 1, j, idx + 1) ||
                 wordSearchDFS(board, word, i, j + 1, idx + 1) ||
                 wordSearchDFS(board, word, i, j - 1, idx + 1);

    board[i][j] = saved;  // Backtrack
    return found;
}

bool exist(vector<vector<char>>& board, const string& word) {
    for (int i = 0; i < (int)board.size(); i++)
        for (int j = 0; j < (int)board[0].size(); j++)
            if (board[i][j] == word[0] && wordSearchDFS(board, word, i, j, 0))
                return true;
    return false;
}

void demoWordSearch() {
    cout << "=== Word Search (Backtracking) ===" << endl;
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    cout << "Grid:" << endl;
    for (auto& row : board) {
        for (char c : row) cout << " " << c;
        cout << endl;
    }
    string word = "ABCCED";
    cout << "Find \"" << word << "\": " << (exist(board, word) ? "Yes" : "No") << endl;  // Yes
    cout << endl;
}

int main() {
    demoSpiralOrder();
    demoGenerateSpiral();
    demoRotateMatrix();
    demoSetZeroes();
    demoDiagonalTraversal();
    demoWordSearch();
    return 0;
}
