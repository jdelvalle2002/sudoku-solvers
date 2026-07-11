cmake_minimum_required(VERSION 3.10)
project(SudokuSolvers CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(sudoku_solver
    src/main.cpp
    src/Sudoku.cpp
    src/SudokuLoader.cpp
    src/BacktrackingSolver.cpp
)
