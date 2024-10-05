#include <iostream>
#include <vector>

using namespace std;

#define N 9 // size of the Sudoku grid

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in a specific position
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num)
            return false;
    }

    // Check the column
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num)
            return false;
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// Backtracking function to solve the Sudoku
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;
    bool emptySpot = false;

    // Find an empty spot in the grid
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                emptySpot = true;
                break;
            }
        }
        if (emptySpot)
            break;
    }

    // No empty spot means the Sudoku is solved
    if (!emptySpot)
        return true;

    // Try placing digits from 1 to 9 in the empty spot
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively try to solve the rest of the grid
            if (solveSudoku(grid))
                return true;

            // If placing num didn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    // Example Sudoku grid (0 represents empty cells)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}
