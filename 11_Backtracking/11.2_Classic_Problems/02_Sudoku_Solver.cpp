// 02_Sudoku_Solver.cpp
// Solve a 9x9 Sudoku puzzle using backtracking.
//
// Rules:
//   - Each row must contain digits 1-9 exactly once.
//   - Each column must contain digits 1-9 exactly once.
//   - Each 3x3 box must contain digits 1-9 exactly once.
//
// Approach: Find the first empty cell ('.'), try digits 1-9,
// check if the digit is valid (no conflict in row/col/box),
// place it, and recurse. If no digit works, backtrack.
//
// Time Complexity: O(9^(n)) where n = number of empty cells.
// Space Complexity: O(1) fixed 9x9 board + O(n) recursion depth.

#include <iostream>
using namespace std;

/*
 * isValid - Check if placing digit ch at board[row][col] is valid.
 *
 * Checks three constraints simultaneously:
 *   1. Row conflict: is ch already in this row?
 *   2. Column conflict: is ch already in this column?
 *   3. 3x3 Box conflict: is ch already in this box?
 *
 * The 3x3 box containing (row, col) has:
 *   - Top-left corner at (3*(row/3), 3*(col/3))
 *   - We iterate through all 9 cells of this box.
 */
bool isValid(char board[9][9], int row, int col, char ch) {
    for (int i = 0; i < 9; i++) {
        // Row conflict
        if (board[row][i] == ch) return false;

        // Column conflict
        if (board[i][col] == ch) return false;

        // 3x3 Box conflict
        // boxRow = top row of the box + offset within box
        // boxCol = left col of the box + offset within box
        int boxRow = 3 * (row / 3) + i / 3;
        int boxCol = 3 * (col / 3) + i % 3;
        if (board[boxRow][boxCol] == ch) return false;
    }
    return true;
}

/*
 * printBoard - Display the 9x9 Sudoku grid.
 */
void printBoard(char board[9][9]) {
    for (int i = 0; i < 9; i++) {
        cout << "  ";
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
            // Add vertical separator between boxes
            if (j == 2 || j == 5) cout << "| ";
        }
        cout << endl;
        // Add horizontal separator between boxes
        if (i == 2 || i == 5) {
            cout << "  ---------------------" << endl;
        }
    }
    cout << endl;
}

/*
 * solveSudoku - Solve the puzzle using backtracking.
 *
 * Returns true if the puzzle is solvable, false otherwise.
 *
 * Algorithm:
 *   1. Scan the board for the first empty cell ('.').
 *   2. If no empty cell found -> puzzle is solved!
 *   3. Try digits '1' through '9' in the empty cell.
 *   4. For each digit, check if it is valid (isValid).
 *   5. If valid: place digit, recurse. If recursion succeeds, return true.
 *   6. If recursion fails: remove digit (backtrack), try next digit.
 *   7. If no digit works: return false (trigger backtrack to caller).
 *
 * Backtracking flow:
 *   CHOICE:     Place digit d ('1'-'9') in empty cell.
 *   CONSTRAINT: isValid() checks row, column, and 3x3 box.
 *   GOAL:       No empty cells remain (puzzle solved).
 *   PRUNING:    Implicit - invalid digits are skipped.
 *   BACKTRACK:  Reset cell to '.' after failed recursion.
 */
bool solveSudoku(char board[9][9]) {
    // Find first empty cell
    int row = -1, col = -1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                row = i;
                col = j;
                i = 9;  // break outer loop
                break;
            }
        }
    }

    // GOAL: no empty cell found -> puzzle solved
    if (row == -1) return true;

    // Try digits 1-9
    for (char ch = '1'; ch <= '9'; ch++) {
        // CONSTRAINT: check if digit ch is valid at (row, col)
        if (isValid(board, row, col, ch)) {
            board[row][col] = ch;     // CHOICE: place digit

            if (solveSudoku(board)) { // Recurse
                return true;          // Solved!
            }

            board[row][col] = '.';   // BACKTRACK: remove digit
        }
    }

    // No valid digit works -> backtrack to caller
    return false;
}

int main() {
    cout << "=== Sudoku Solver ===" << endl;
    cout << endl;

    cout << "Rules:" << endl;
    cout << "  Each row, column, and 3x3 box must contain digits 1-9." << endl;
    cout << "  '.' represents an empty cell." << endl;
    cout << endl;

    // Sample puzzle (medium difficulty)
    // '.' = empty cell, digits 1-9 = pre-filled clues
    char board[9][9] = {
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

    cout << "Puzzle:" << endl;
    printBoard(board);

    cout << "Solving..." << endl;
    cout << endl;

    if (solveSudoku(board)) {
        cout << "Solution found!" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists for this puzzle." << endl;
    }

    cout << "Backtracking approach:" << endl;
    cout << "  1. Find first empty cell (scan top-left to bottom-right)" << endl;
    cout << "  2. Try digits '1' through '9'" << endl;
    cout << "  3. isValid() checks row, column, and 3x3 box" << endl;
    cout << "  4. If valid: place digit, recurse" << endl;
    cout << "  5. If recursion succeeds: return true (solved)" << endl;
    cout << "  6. If recursion fails: reset to '.', try next digit" << endl;
    cout << "  7. If no digit works: return false (backtrack to previous cell)" << endl;
    cout << endl;

    cout << "Why backtracking works:" << endl;
    cout << "  Sudoku has a unique solution (well-formed puzzles)." << endl;
    cout << "  Backtracking systematically tries all possibilities." << endl;
    cout << "  isValid() prunes invalid digits early." << endl;
    cout << "  The first solution found is THE solution." << endl;

    return 0;
}
