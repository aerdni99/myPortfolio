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
State queenPlacer(State&, int, int);

int main() {

    State startState = readInput();

    State endState = queenPlacer(startState, 0, 0);

    // Determine a solution or no solution. A blank board signifies a no solution.
    if (endState.isBlank()) {
        std::cout << "No Solution!\n";
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
    std::string fileName;
    while (!input.is_open()) {
        std::cout << "copy the name of the input file from the current directory here.\n";
        std::cout << "ex: \"input.csv\"\n";
        std::cin >> fileName;
        input.open(fileName);
        if (!input.is_open()) {
            std::cout << "\nfile not found\n";
            std::cout << fileName << "\n";
            std::cin.get();
            std::cin.get();
        }
    }
}

// Try to place a queen on every valid (n, n) coordinate.
State queenPlacer(State& oldBoard, int x, int y) {
    State newBoard(oldBoard, x, y);
    if (oldBoard.valid(x, y)) {
        if (newBoard.isGoal()) {
            return newBoard;
        } else if (x == oldBoard.size() - 1) {
            newBoard.makeBlank();
            return newBoard;
        } else {
            newBoard = queenPlacer(newBoard, x + 1, 0);
        }
    }
    if (newBoard.isGoal() && oldBoard.valid(x, y)) {
        return newBoard;
    }
    if (y != newBoard.size() - 1) {
        newBoard = queenPlacer(oldBoard, x, y + 1);
        if (newBoard.isGoal()) {
            return newBoard;
        }
    }
    newBoard.makeBlank();
    return newBoard;
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
