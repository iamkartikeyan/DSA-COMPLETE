// Unique Paths in Grid
// Robot starts at (0,0), can only move right or down
// Goal: reach cell (m-1, n-1)
// dp[i][j] = number of paths to reach cell (i,j)
// Transition: dp[i][j] = dp[i-1][j] + dp[i][j-1]
// Base case: first row and first column = 1 (only one way: all right or all down)

#include <iostream>

using namespace std;

// Function to find unique paths in a grid of size m x n
int uniquePaths(int m, int n) {
    int dp[100][100];

    // Base case: first row - only one way (move right)
    for (int j = 0; j < n; j++) {
        dp[0][j] = 1;
    }

    // Base case: first column - only one way (move down)
    for (int i = 0; i < m; i++) {
        dp[i][0] = 1;
    }

    // Fill the DP table
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            // Paths from above + paths from left
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    return dp[m - 1][n - 1];
}

// Function to find unique paths with obstacles
// obstacleGrid[i][j] = 1 means obstacle, 0 means free cell
int uniquePathsWithObstacles(int obstacleGrid[][3], int m, int n) {
    int dp[100][100];

    // If start or end has obstacle, no path exists
    if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) {
        return 0;
    }

    // Base case: first row
    for (int j = 0; j < n; j++) {
        if (obstacleGrid[0][j] == 1) {
            dp[0][j] = 0;
            // All cells after obstacle in same row also unreachable
            for (int k = j + 1; k < n; k++) {
                dp[0][k] = 0;
            }
            break;
        } else {
            dp[0][j] = 1;
        }
    }

    // Base case: first column
    for (int i = 0; i < m; i++) {
        if (obstacleGrid[i][0] == 1) {
            dp[i][0] = 0;
            // All cells after obstacle in same column also unreachable
            for (int k = i + 1; k < m; k++) {
                dp[k][0] = 0;
            }
            break;
        } else {
            dp[i][0] = 1;
        }
    }

    // Fill the DP table
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[i][j] == 1) {
                dp[i][j] = 0;  // Obstacle: no paths through this cell
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }

    return dp[m - 1][n - 1];
}

int main() {
    cout << "=== Unique Paths in Grid ===" << endl;

    // Example 1: 3x7 grid
    int m1 = 3, n1 = 7;
    cout << "Grid size: " << m1 << " x " << n1 << endl;
    cout << "Unique paths: " << uniquePaths(m1, n1) << endl;

    // Example 2: 3x3 grid
    int m2 = 3, n2 = 3;
    cout << "\nGrid size: " << m2 << " x " << n2 << endl;
    cout << "Unique paths: " << uniquePaths(m2, n2) << endl;

    // Example 3: 1x1 grid (already at destination)
    cout << "\nGrid size: 1 x 1" << endl;
    cout << "Unique paths: " << uniquePaths(1, 1) << endl;

    // Example 4: 7x3 grid
    cout << "\nGrid size: 7 x 3" << endl;
    cout << "Unique paths: " << uniquePaths(7, 3) << endl;

    cout << "\n=== Unique Paths with Obstacles ===" << endl;

    // Example 5: 3x3 grid with one obstacle at (1,1)
    int grid1[3][3] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    cout << "\nGrid with obstacle at center (1,1):" << endl;
    cout << "0 0 0" << endl;
    cout << "0 1 0" << endl;
    cout << "0 0 0" << endl;
    cout << "Unique paths: " << uniquePathsWithObstacles(grid1, 3, 3) << endl;

    // Example 6: 3x3 grid with obstacle blocking all paths
    int grid2[3][3] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    cout << "\nGrid with wall of obstacles:" << endl;
    cout << "0 1 0" << endl;
    cout << "0 1 0" << endl;
    cout << "0 0 0" << endl;
    cout << "Unique paths: " << uniquePathsWithObstacles(grid2, 3, 3) << endl;

    // Example 7: 3x3 grid with obstacle at (1,2)
    int grid3[3][3] = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 0, 0}
    };
    cout << "\nGrid with obstacle at (1,2):" << endl;
    cout << "0 0 0" << endl;
    cout << "0 0 1" << endl;
    cout << "0 0 0" << endl;
    cout << "Unique paths: " << uniquePathsWithObstacles(grid3, 3, 3) << endl;

    return 0;
}
