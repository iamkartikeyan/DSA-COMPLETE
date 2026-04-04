// 01_N_Queens.cpp
// Place n queens on an n x n chessboard so that no two queens attack each other.
// Queens attack along rows, columns, and both diagonals.
//
// Approach: Place queens row by row. For each row, try every column.
// Check if placing a queen at (row, col) is safe. If yes, place it and
// recurse to the next row. Backtrack by removing the queen.
//
// Time Complexity: O(n!) - at most n choices for row 0, n-1 for row 1, etc.
// Space Complexity: O(n^2) for the board + O(n) recursion depth.

#include <iostream>
using namespace std;

const int MAX_N = 12;
int solutionCount = 0;

/*
 * isSafe - Check if placing a queen at (row, col) is valid.
 *
 * We only need to check ABOVE the current row because:
 *   - Rows below are empty (not filled yet).
 *   - The current row has no other queen (we place one at a time).
 *
 * Checks needed:
 *   1. Same column: any queen in column col above row?
 *   2. Upper-left diagonal: any queen on diagonal going up-left?
 *   3. Upper-right diagonal: any queen on diagonal going up-right?
 *
 * Note: We do NOT check the current row because we place exactly
 * one queen per row (guaranteed by the loop structure).
 */
bool isSafe(char board[][MAX_N], int row, int col, int n) {
    // Check column above
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }

    return true;
}

/*
 * printBoard - Display the chessboard with queens marked 'Q'.
 */
void printBoard(char board[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        cout << "  ";
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
 * solveNQueens - Place queens row by row using backtracking.
 *
 * Parameters:
 *   board[][] - the chessboard ('Q' = queen, '.' = empty)
 *   row       - current row we are placing a queen in
 *   n         - board size
 *
 * Backtracking flow:
 *   CHOICE:     Place queen in any safe column of current row.
 *   CONSTRAINT: isSafe() checks column and diagonal conflicts.
 *   GOAL:       row == n (all n queens placed successfully).
 *   PRUNING:    Implicit - unsafe columns are skipped.
 *   BACKTRACK:  Remove queen (set board[row][col] = '.') after recursion.
 */
void solveNQueens(char board[][MAX_N], int row, int n) {
    // GOAL: all queens placed
    if (row == n) {
        solutionCount++;
        cout << "Solution " << solutionCount << ":" << endl;
        printBoard(board, n);
        return;
    }

    // Try every column in this row
    for (int col = 0; col < n; col++) {
        // CONSTRAINT: check if placing queen at (row, col) is safe
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';          // CHOICE: place queen
            solveNQueens(board, row + 1, n); // recurse for next row
            board[row][col] = '.';          // BACKTRACK: remove queen
        }
    }
}

/*
 * countNQueens - Just count solutions (no printing) for larger n.
 */
void countNQueens(char board[][MAX_N], int row, int n) {
    if (row == n) {
        solutionCount++;
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';
            countNQueens(board, row + 1, n);
            board[row][col] = '.';
        }
    }
}

int main() {
    cout << "=== N-Queens Problem ===" << endl;
    cout << endl;

    cout << "Problem: Place n queens on an n x n board" << endl;
    cout << "Constraint: No two queens attack each other" << endl;
    cout << "Attack directions: same row, same column, same diagonal" << endl;
    cout << endl;

    // ---- n = 4 (show solutions) ----
    int n = 4;
    char board[MAX_N][MAX_N];

    cout << "--- N-Queens (n = 4) ---" << endl;
    cout << "Expected: 2 solutions" << endl;
    cout << endl;

    // Initialize board
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }

    solutionCount = 0;
    solveNQueens(board, 0, n);
    cout << "Total solutions for n=4: " << solutionCount << endl;
    cout << endl;

    // ---- n = 8 (count only) ----
    cout << "--- N-Queens (n = 8) ---" << endl;
    cout << "Counting solutions (not printing)..." << endl;

    int n8 = 8;
    for (int i = 0; i < n8; i++) {
        for (int j = 0; j < n8; j++) {
            board[i][j] = '.';
        }
    }

    solutionCount = 0;
    countNQueens(board, 0, n8);
    cout << "Total solutions for n=8: " << solutionCount << endl;
    cout << endl;

    cout << "Known solution counts:" << endl;
    cout << "  n=1: 1" << endl;
    cout << "  n=2: 0" << endl;
    cout << "  n=3: 0" << endl;
    cout << "  n=4: 2" << endl;
    cout << "  n=5: 10" << endl;
    cout << "  n=6: 4" << endl;
    cout << "  n=7: 40" << endl;
    cout << "  n=8: 92" << endl;
    cout << endl;

    cout << "Backtracking approach:" << endl;
    cout << "  - Place one queen per row (eliminates row conflicts)" << endl;
    cout << "  - For each row, try every column" << endl;
    cout << "  - isSafe() checks column and both diagonals above" << endl;
    cout << "  - If safe: place queen, recurse to next row" << endl;
    cout << "  - If not safe or recursion fails: remove queen (backtrack)" << endl;

    return 0;
}
