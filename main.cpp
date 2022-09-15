/*

COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Assignment. Artificial Intelligence: NQueens
Author. Angelo Indre
        adi19@zips.uakron.edu
Purpose. Solve the N-Queens problem using a backtracking algorithm

*/

#include <iostream>
#include <fstream>
#include "State.hpp"
#include <string>

// calls openFile() and associates a Start state with an input file. Returns startState.
State readInput();

// Prompts user for .csv input file name. Associates input file with an fstream object.
void openFile(std::ifstream&);

// Opens a file and outputs the NQueens solution to it.
void writeOutput(State&);

// Try to place a queen on every (n, n) coordinate with recursion. 
State queenPlacer(State&, int);

int main() {
    
    State startState = readInput();

    State endState = queenPlacer(startState, 0);

    // Determine a solution or no solution. A blank board signifies a no solution.
    if (endState.isBlank()) {
        std::cout << "No Solution\n";
    } else {
        writeOutput(endState);
    }
    return 0;
}

// calls openFile() and associates a Start state with an input file. Returns startState.
State readInput() {
    std::ifstream input;   
    openFile(input);
    auto startState = State(input);
    input.close();
    return startState;
}

// Prompts user for .csv input file name. calls validateInput() Associates input file with an fstream object.
void openFile(std::ifstream& input) {
    input.open("input.csv");
    if (!input.is_open()) {
        std::cout << "\nfile not found\n";
        exit(1);
    }
}

// Try to place a queen on every valid (n, n) coordinate.
State queenPlacer(State& oldBoard, int x) {
    if (x == oldBoard.size()) {
        return oldBoard;
    }
    for (int i = 0; i < oldBoard.size(); i++) {
        if (oldBoard.valid(x, i)) {
            State newBoard(oldBoard, x, i);
            newBoard = queenPlacer(newBoard, x + 1);
            if (newBoard.isGoal()) {
                return newBoard;
            }
        }
    }
    oldBoard.makeBlank();
    return oldBoard;
}

// Opens a file and outputs the NQueens solution to it.
void writeOutput(State& endState) {
    std::ofstream output;
    output.open("output.csv");
    if (output.fail()) {
        std::cout << "output file failed to create/open\n";
    } else {
        endState.output2CSV(output);
        std::cout << "Solution has been written to output.csv in the current directory\n";
    }
}
