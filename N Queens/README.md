# NQueens

**C++** (Fall 2022)

This project for my Artificial Intelligence class has students code a program that can solve the classic N-Queens problem. Briefly stated, On a chess board of dimensions NxN, place N queens so that none of them can attack each other in the next move. The constraints for solving the problem were for us to use a backtracking algorithm as well as run a 20x20 board in < 15 seconds. Mine finds the solution in less than 3 seconds.

### Files

main.cpp - Driver code for parsing input file, algorithm implementation, and writing to output file.

State.cpp - Implementation of my class "State" which represents the board and can have operations performed on it.

State.hpp - Header file for State class.

input.csv - Properly formatted imput file.