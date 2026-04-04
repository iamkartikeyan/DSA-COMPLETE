// 04_Word_Search.cpp
// Given a 2D grid of characters and a word, determine if the word
// exists in the grid. The word can be formed by moving in 4 directions
// (up, down, left, right) through adjacent cells. Each cell can be
// used at most once in a single word formation.
//
// Approach: For each cell that matches the first character of the word,
// start a DFS. At each step, check if the current cell matches the
// current character, then try all 4 directions. Mark cells as visited
// during the current search and unmark them when backtracking.
//
// Time Complexity: O(rows * cols * 4^L) where L = word length.
// Space Complexity: O(rows * cols) for visited array + O(L) recursion.

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_R = 10;
const int MAX_C = 10;

/*
 * wordDFS - Search for word[idx..] starting from grid cell (i, j).
 *
 * Parameters:
 *   board[][]  - the character grid
 *   rows, cols - grid dimensions
 *   word[]     - the word to find (null-terminated string)
 *   i, j       - current cell position
 *   idx        - current character index in word we are trying to match
 *   visited[][]- tracks cells used in the current search path
 *
 * Returns true if word[idx..] can be found starting from (i, j).
 *
 * Backtracking flow:
 *   CHOICE:     Move to an adjacent cell (up/down/left/right).
 *   CONSTRAINT: Cell must be in bounds, not visited, and match word[idx].
 *   GOAL:       idx == word length (entire word matched).
 *   PRUNING:    Out of bounds, visited, or character mismatch -> return false.
 *   BACKTRACK:  Unmark visited[i][j] after exploring all directions.
 */
bool wordDFS(char board[][MAX_C], int rows, int cols,
             const char word[], int i, int j, int idx,
             bool visited[][MAX_C]) {
    // GOAL: matched entire word
    if (word[idx] == '\0') return true;

    // CONSTRAINT checks
    if (i < 0 || i >= rows || j < 0 || j >= cols) return false;  // out of bounds
    if (visited[i][j]) return false;                              // already used
    if (board[i][j] != word[idx]) return false;                   // character mismatch

    // Mark current cell as visited (part of current path)
    visited[i][j] = true;

    // Explore 4 directions: down, up, right, left
    bool found = wordDFS(board, rows, cols, word, i + 1, j, idx + 1, visited) ||  // down
                 wordDFS(board, rows, cols, word, i - 1, j, idx + 1, visited) ||  // up
                 wordDFS(board, rows, cols, word, i, j + 1, idx + 1, visited) ||  // right
                 wordDFS(board, rows, cols, word, i, j - 1, idx + 1, visited);    // left

    // BACKTRACK: unmark current cell so it can be used in other searches
    visited[i][j] = false;

    return found;
}

/*
 * exist - Check if word exists anywhere in the grid.
 *
 * Try starting from every cell. If the cell matches the first character,
 * launch a DFS from that cell.
 */
bool exist(char board[][MAX_C], int rows, int cols, const char word[]) {
    bool visited[MAX_R][MAX_C];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
        }
    }

    // Try every starting cell
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Optimization: only start DFS if first character matches
            if (board[i][j] == word[0]) {
                if (wordDFS(board, rows, cols, word, i, j, 0, visited)) {
                    return true;
                }
            }
        }
    }

    return false;
}

/*
 * printGrid - Display the character grid.
 */
void printGrid(char board[][MAX_C], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        cout << "  ";
        for (int j = 0; j < cols; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    cout << "=== Word Search ===" << endl;
    cout << endl;

    cout << "Problem: Find a word in a 2D grid" << endl;
    cout << "  - Move in 4 directions (up, down, left, right)" << endl;
    cout << "  - Each cell used at most once per word" << endl;
    cout << "  - Adjacent cells only (no diagonal)" << endl;
    cout << endl;

    // Sample grid
    char board[MAX_R][MAX_C] = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    int rows = 3;
    int cols = 4;

    cout << "Board:" << endl;
    printGrid(board, rows, cols);

    // Test words
    const char* words[] = {"ABCCED", "SEE", "ABCB"};
    int numWords = 3;

    for (int w = 0; w < numWords; w++) {
        const char* word = words[w];
        bool found = exist(board, rows, cols, word);
        cout << "  \"" << word << "\" -> " << (found ? "Found" : "Not found") << endl;
    }
    cout << endl;

    // Explain results
    cout << "Explanation:" << endl;
    cout << "  ABCCED: A(0,0) -> B(0,1) -> C(0,2) -> C(1,2) -> E(2,2) -> D(2,1)" << endl;
    cout << "  SEE:    S(1,3) -> E(2,3) -> E(2,2)" << endl;
    cout << "  ABCB:   A(0,0) -> B(0,1) -> C(0,2) -> B(0,1) -- B already used!" << endl;
    cout << endl;

    // ---- Additional example ----
    cout << "--- Additional Example ---" << endl;
    char board2[MAX_R][MAX_C] = {
        {'C', 'A', 'T'},
        {'X', 'B', 'Y'},
        {'D', 'O', 'G'}
    };
    int rows2 = 3;
    int cols2 = 3;

    cout << "Board:" << endl;
    printGrid(board2, rows2, cols2);

    const char* words2[] = {"CAT", "DOG", "CAB", "CODY"};
    int numWords2 = 4;

    for (int w = 0; w < numWords2; w++) {
        const char* word = words2[w];
        bool found = exist(board2, rows2, cols2, word);
        cout << "  \"" << word << "\" -> " << (found ? "Found" : "Not found") << endl;
    }
    cout << endl;

    cout << "Backtracking approach:" << endl;
    cout << "  1. For each cell matching word[0], start DFS" << endl;
    cout << "  2. At each step, check: in bounds? not visited? character matches?" << endl;
    cout << "  3. If all checks pass: mark visited, recurse to 4 neighbors" << endl;
    cout << "  4. If any neighbor leads to full word: return true" << endl;
    cout << "  5. If no neighbor works: unmark visited (backtrack)" << endl;
    cout << "  6. If all starting cells fail: word not found" << endl;

    return 0;
}
