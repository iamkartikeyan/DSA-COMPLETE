// 06_Classic_Backtracking_Summary.cpp
// Complete summary table of all classic backtracking problems.
// Acts as a quick reference for the problems covered in this folder.

#include <iostream>
using namespace std;

/*
 * ============================================================
 * SUMMARY TABLE: Classic Backtracking Problems
 * ============================================================
 *
 * +----------------------+----------------------+------------------+
 * | Problem              | Choice               | Constraint       |
 * +----------------------+----------------------+------------------+
 * | N-Queens             | Place queen in col   | isSafe(): no     |
 * |                      | for current row      | row/col/diag     |
 * |                      |                      | conflict         |
 * +----------------------+----------------------+------------------+
 * | Sudoku Solver        | Try digit 1-9 in     | isValid(): no    |
 * |                      | empty cell           | row/col/box      |
 * |                      |                      | conflict         |
 * +----------------------+----------------------+------------------+
 * | Rat in Maze          | Move D/L/R/U from    | isSafe(): in     |
 * |                      | current cell         | bounds, not      |
 * |                      |                      | blocked, not     |
 * |                      |                      | visited          |
 * +----------------------+----------------------+------------------+
 * | Word Search          | Move to adjacent     | In bounds, not   |
 * |                      | cell matching next   | visited, char    |
 * |                      | character            | matches word[idx]|
 * +----------------------+----------------------+------------------+
 * | Palindrome           | Split at position i  | s[idx..i] must   |
 * | Partitioning         | (take s[idx..i])     | be a palindrome  |
 * +----------------------+----------------------+------------------+
 *
 * ============================================================
 * COMPLEXITY SUMMARY
 * ============================================================
 *
 * Problem              | Time              | Space       | Key Idea
 * ---------------------+-------------------+-------------+------------------
 * N-Queens             | O(n!)             | O(n^2)      | Row-by-row placement
 * Sudoku Solver        | O(9^m) m=blanks   | O(1) 9x9    | Fill blanks, 1-9
 * Rat in Maze          | O(4^(n^2))        | O(n^2)      | 4 dirs, visited[]
 * Word Search          | O(R*C*4^L)        | O(R*C)      | DFS from each cell
 * Palindrome Partition | O(2^n * n)        | O(n)        | Split at palindromes
 *
 * ============================================================
 * COMMON PATTERNS
 * ============================================================
 *
 * 1. Board/Grid Problems (N-Queens, Sudoku, Rat in Maze, Word Search):
 *    - Use a 2D array to represent the board state.
 *    - Make a move (place queen, fill digit, move to cell).
 *    - Recurse to the next state.
 *    - Undo the move (backtrack).
 *
 * 2. String Problems (Palindrome Partitioning):
 *    - Use an index to track progress through the string.
 *    - Try every possible split point.
 *    - Constraint: the split must satisfy a property (palindrome).
 *    - Recurse on the remaining suffix.
 *
 * 3. Visited Tracking:
 *    - Most problems need a visited[] or visited[][] array.
 *    - Mark BEFORE recursing, unmark AFTER returning.
 *    - This ensures the current path does not reuse cells.
 *
 * ============================================================
 * BACKTRACKING TEMPLATE (Applied to Grid Problems)
 * ============================================================
 *
 * void solve(Board& board, State& state) {
 *     if (isGoal(state)) {
 *         recordSolution(board);
 *         return;
 *     }
 *
 *     for (each possible move) {
 *         if (isValid(move, board, state)) {
 *             applyMove(board, move, state);   // CHOICE
 *             solve(board, state);             // RECURSE
 *             undoMove(board, move, state);    // BACKTRACK
 *         }
 *     }
 * }
 *
 * ============================================================
 * TIPS FOR BEGINNERS
 * ============================================================
 *
 * 1. Identify the CHOICE: What decision am I making at each step?
 *    - N-Queens: Which column to place the queen?
 *    - Sudoku: Which digit to put in the empty cell?
 *    - Rat in Maze: Which direction to move?
 *
 * 2. Identify the CONSTRAINT: What makes a choice invalid?
 *    - Write an isValid / isSafe function.
 *    - Call it BEFORE recursing (prune early).
 *
 * 3. Identify the GOAL: When is the solution complete?
 *    - N-Queens: All n queens placed (row == n).
 *    - Sudoku: No empty cells remain.
 *    - Rat in Maze: Reached (n-1, n-1).
 *
 * 4. Identify what to BACKTRACK:
 *    - Board problems: undo the placement/move.
 *    - String problems: the index naturally advances.
 *    - Always unmark visited cells after recursion returns.
 *
 * 5. Draw the State Space Tree:
 *    - Helps visualize the recursion.
 *    - Shows where pruning happens.
 *    - Reveals the branching factor and depth.
 */

int main() {
    cout << "=== Classic Backtracking Problems Summary ===" << endl;
    cout << endl;

    cout << "Problem              | Choice              | Constraint" << endl;
    cout << "---------------------+---------------------+-------------------" << endl;
    cout << "N-Queens             | Col for current row | No attack" << endl;
    cout << "Sudoku Solver        | Digit 1-9 in cell   | Row/col/box valid" << endl;
    cout << "Rat in Maze          | Direction D/L/R/U   | In bounds, open" << endl;
    cout << "Word Search          | Adjacent cell       | Char matches" << endl;
    cout << "Palindrome Partition | Split point i       | s[idx..i] is palin." << endl;
    cout << endl;

    cout << "Problem              | Time             | Space" << endl;
    cout << "---------------------+------------------+--------" << endl;
    cout << "N-Queens             | O(n!)            | O(n^2)" << endl;
    cout << "Sudoku Solver        | O(9^m)           | O(1)" << endl;
    cout << "Rat in Maze          | O(4^(n^2))       | O(n^2)" << endl;
    cout << "Word Search          | O(R*C*4^L)       | O(R*C)" << endl;
    cout << "Palindrome Partition | O(2^n * n)       | O(n)" << endl;
    cout << endl;

    cout << "Files in this folder:" << endl;
    cout << "  01_N_Queens.cpp              - N-Queens with isSafe check" << endl;
    cout << "  02_Sudoku_Solver.cpp         - 9x9 Sudoku with backtracking" << endl;
    cout << "  03_Rat_in_Maze.cpp           - All paths with 4 directions" << endl;
    cout << "  04_Word_Search.cpp           - Find word in 2D grid" << endl;
    cout << "  05_Palindrome_Partitioning.cpp - All palindrome partitions" << endl;
    cout << "  06_Classic_Backtracking_Summary.cpp - This file" << endl;
    cout << endl;

    cout << "The backtracking pattern is universal:" << endl;
    cout << "  CHOICE -> CONSTRAINT -> GOAL -> PRUNE -> BACKTRACK" << endl;
    cout << endl;
    cout << "Once you recognize this pattern, you can solve" << endl;
    cout << "any backtracking problem by identifying the 5 components." << endl;

    return 0;
}
