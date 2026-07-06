#include <vector>




// we must define the data structures that save the already satisfied digits among other stuff.

int main()
{
    // Define a 9x9 Sudoku grid using a vector of vectors. Each inner vector represents a row in the grid, and each integer represents a cell in that row. A value of 0 indicates an empty cell, while values from 1 to 9 represent filled cells.
std::vector<std::vector<int>> sudoku = {
    {5, 6, 0,  7, 0, 0,  0, 0, 0},
    {2, 0, 0,  8, 4, 0,  5, 0, 0},
    {0, 0, 0,  1, 0, 0,  0, 0, 4},

    {0, 0, 7,  9, 0, 0,  0, 1, 0},
    {6, 0, 3,  0, 0, 0,  2, 0, 7},
    {0, 1, 0,  0, 0, 2,  9, 0, 0},

    {3, 0, 0,  2, 0, 0,  0, 0, 0},
    {0, 0, 8,  6, 1, 0,  0, 0, 2},
    {0, 0, 0,  4, 0, 0,  0, 5, 6}
};

    // The Sudoku grid is now defined and can be used for further processing, such as solving the puzzle or validating the grid.
    return 0; // Return 0 to indicate successful execution of the program.
}