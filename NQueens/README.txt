3460:460/560 AI, Project 1 - Constrained N-Queens problem

Problem Description: The N-queens is the problem of placing N chess queens on an N�N chessboard so that no two queens 
attack each other. Wiki has detailed description of the problem and the history of the problem. 
https://en.wikipedia.org/wiki/Eight_queens_puzzle

 

The objective of this project is to implement backtracking algorithm to solve the N-queens problem. 
To make your project more interesting, a constrain (the 1st Queen�s position) will be specified. 
You are to solve the problem and obtain a feasible solution that is conforming to the constrain. 
No need to find all feasible solutions. Report "No solution" if there is no compatible solution.


In this directory are the files:

input.csv - an example of the input format this program accepts

main.cpp - driver code for reading input, placing queens, and writing output

State.hpp - header file for my state/environment representation (a chessboard)

State.hpp - implementation of the many methods for checking and manipulating any state of the board.

CMakeLists.txt - a simple cmake file I used to compile my program on a linux distribution

