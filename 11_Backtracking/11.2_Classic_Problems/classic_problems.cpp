// 11.2 Classic Backtracking Problems
// N-Queens, Sudoku Solver, Rat in a Maze, Word Search, Palindrome Partitioning

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 1. N-QUEENS PROBLEM
// Place n queens on n x n board so none attack each other
// Constraints: no two queens share row, col, or diagonal
// Complexity: O(n!)
// ============================================================
bool isSafe(const vector<string>& board, int row, int col) {
    int n = board.size();
    // Check column above
    for (int i = 0; i < row; i++)
        if (board[i][col] == 'Q') return false;
    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q') return false;
    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j] == 'Q') return false;
    return true;
}

void solveNQueens(vector<string>& board, int row, vector<vector<string>>& result) {
    int n = board.size();
    if (row == n) {                           // Goal: all queens placed
        result.push_back(board);
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {        // Constraint check
            board[row][col] = 'Q';            // Choice: place queen
            solveNQueens(board, row + 1, result);
            board[row][col] = '.';            // Backtrack
        }
    }
}

// Optimized with sets for O(1) safety checks
void solveNQueensFast(int n, int row, int colMask, int d1Mask, int d2Mask,
                      vector<string>& board, int& count) {
    if (row == n) { count++; return; }         // Found valid arrangement
    for (int col = 0; col < n; col++) {
        // Check conflicts using bitmasks
        if ((colMask & (1 << col)) || (d1Mask & (1 << (row + col)))
            || (d2Mask & (1 << (row - col + n - 1))))
            continue;
        board[row][col] = 'Q';
        solveNQueensFast(n, row + 1,
                         colMask | (1 << col),
                         d1Mask | (1 << (row + col)),
                         d2Mask | (1 << (row - col + n - 1)),
                         board, count);
        board[row][col] = '.';
    }
}

// ============================================================
// 2. SUDOKU SOLVER
// Fill 9x9 grid: each row, col, 3x3 box has digits 1-9 exactly once
// Constraint propagation + backtracking
// ============================================================
bool isValidSudoku(const vector<vector<char>>& board, int row, int col, char ch) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == ch) return false;   // Row conflict
        if (board[i][col] == ch) return false;   // Col conflict
        // 3x3 box conflict
        int br = 3 * (row / 3) + i / 3, bc = 3 * (col / 3) + i % 3;
        if (board[br][bc] == ch) return false;
    }
    return true;
}

bool solveSudoku(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                for (char ch = '1'; ch <= '9'; ch++) {
                    if (isValidSudoku(board, i, j, ch)) {
                        board[i][j] = ch;              // Choice
                        if (solveSudoku(board)) return true; // Recurse
                        board[i][j] = '.';              // Backtrack
                    }
                }
                return false;  // No valid digit, backtrack
            }
        }
    }
    return true;  // Solved
}

// ============================================================
// 3. RAT IN A MAZE
// Find path from (0,0) to (n-1,n-1) in maze with obstacles
// Directions: D, L, R, U (sorted lexicographically)
// ============================================================
bool isSafeMaze(const vector<vector<int>>& maze, int i, int j, int n,
                const vector<vector<bool>>& visited) {
    return i >= 0 && i < n && j >= 0 && j < n
           && maze[i][j] == 1 && !visited[i][j];
}

void findPaths(const vector<vector<int>>& maze, int n, int i, int j,
               string path, vector<string>& result,
               vector<vector<bool>>& visited) {
    if (i == n - 1 && j == n - 1) {           // Goal: reached destination
        result.push_back(path);
        return;
    }
    visited[i][j] = true;                     // Mark current cell

    // Try all 4 directions in lexicographic order
    int di[] = {1, 0, 0, -1}, dj[] = {0, -1, 1, 0};
    char dirs[] = {'D', 'L', 'R', 'U'};
    for (int d = 0; d < 4; d++) {
        int ni = i + di[d], nj = j + dj[d];
        if (isSafeMaze(maze, ni, nj, n, visited)) {
            findPaths(maze, n, ni, nj, path + dirs[d], result, visited);
        }
    }
    visited[i][j] = false;                    // Backtrack: unmark
}

// ============================================================
// 4. WORD SEARCH
// Find word in 2D grid moving in 4 directions, each cell used at most once
// ============================================================
bool wordSearchDFS(const vector<vector<char>>& board, const string& word,
                   int i, int j, int idx, vector<vector<bool>>& visited) {
    if (idx == (int)word.size()) return true;  // Goal: matched entire word
    if (i < 0 || i >= (int)board.size() || j < 0 || j >= (int)board[0].size())
        return false;
    if (visited[i][j] || board[i][j] != word[idx]) return false;

    visited[i][j] = true;                      // Mark as visited
    // Explore 4 directions
    bool found = wordSearchDFS(board, word, i + 1, j, idx + 1, visited) ||
                 wordSearchDFS(board, word, i - 1, j, idx + 1, visited) ||
                 wordSearchDFS(board, word, i, j + 1, idx + 1, visited) ||
                 wordSearchDFS(board, word, i, j - 1, idx + 1, visited);
    visited[i][j] = false;                     // Backtrack
    return found;
}

bool exist(const vector<vector<char>>& board, const string& word) {
    int rows = board.size(), cols = board[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (wordSearchDFS(board, word, i, j, 0, visited)) return true;
    return false;
}

// ============================================================
// 5. PALINDROME PARTITIONING
// Split string into substrings that are all palindromes
// ============================================================
bool isPalindrome(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}

void partitionPalindrome(const string& s, int idx,
                         vector<string>& current,
                         vector<vector<string>>& result) {
    if (idx == (int)s.size()) {                // Goal: partitioned entire string
        result.push_back(current);
        return;
    }
    for (int i = idx; i < (int)s.size(); i++) {
        if (isPalindrome(s, idx, i)) {         // Constraint: must be palindrome
            current.push_back(s.substr(idx, i - idx + 1));  // Choice
            partitionPalindrome(s, i + 1, current, result);
            current.pop_back();                // Backtrack
        }
    }
}

// --- Print Helpers ---
void printBoard(const vector<string>& board, const string& label) {
    cout << label << "\n";
    for (auto& row : board) cout << "  " << row << "\n";
    cout << "\n";
}

void printGrid(const vector<vector<char>>& board, const string& label) {
    cout << label << "\n";
    for (auto& row : board) {
        cout << "  ";
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cout << "=== 11.2 Classic Backtracking Problems ===\n\n";

    // --- N-Queens ---
    int n = 4;
    cout << "N-Queens (n=" << n << "):\n";
    vector<string> board(n, string(n, '.'));
    vector<vector<string>> solutions;
    solveNQueens(board, 0, solutions);
    for (size_t k = 0; k < solutions.size(); k++)
        printBoard(solutions[k], "Solution " + to_string(k + 1) + ":");

    // Fast count for n=8
    int count8 = 0;
    board.assign(8, string(8, '.'));
    solveNQueensFast(8, 0, 0, 0, 0, board, count8);
    cout << "Total solutions for n=8: " << count8 << "\n\n";

    // --- Sudoku ---
    cout << "Sudoku Solver:\n";
    vector<vector<char>> sudoku = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    printGrid(sudoku, "Before:");
    if (solveSudoku(sudoku)) printGrid(sudoku, "After:");
    else cout << "  No solution found.\n\n";

    // --- Rat in a Maze ---
    cout << "Rat in a Maze:\n";
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    int mazeN = maze.size();
    vector<vector<bool>> visited(mazeN, vector<bool>(mazeN, false));
    vector<string> paths;
    findPaths(maze, mazeN, 0, 0, "", paths, visited);
    cout << "  Paths from (0,0) to (" << mazeN-1 << "," << mazeN-1 << "): ";
    for (auto& p : paths) cout << p << " ";
    if (paths.empty()) cout << "(none)";
    cout << "\n\n";

    // --- Word Search ---
    cout << "Word Search:\n";
    vector<vector<char>> grid = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    printGrid(grid, "Board:");
    vector<string> words = {"ABCCED", "SEE", "ABCB"};
    for (auto& w : words)
        cout << "  \"" << w << "\" -> " << (exist(grid, w) ? "Found" : "Not found") << "\n";
    cout << "\n";

    // --- Palindrome Partitioning ---
    string s = "aab";
    cout << "Palindrome Partitioning of \"" << s << "\":\n";
    vector<vector<string>> partitions;
    vector<string> cur;
    partitionPalindrome(s, 0, cur, partitions);
    for (size_t k = 0; k < partitions.size(); k++) {
        cout << "  [";
        for (size_t i = 0; i < partitions[k].size(); i++)
            cout << "\"" << partitions[k][i] << "\""
                 << (i + 1 < partitions[k].size() ? ", " : "");
        cout << "]\n";
    }

    return 0;
}
