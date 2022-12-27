"""
Sudoku solver for fun

python3 sudoku.py puzzle.csv
"""
import pandas as pd

p = pd.read_csv('puzzle.csv', header=None)

puzzle = p.to_numpy()

BOX1 = [(0, 0), (0, 1), (0, 2), (1, 0), (1, 1), (1, 2), (2, 0), (2, 1), (2, 2)]
BOX2 = [(0, 3), (0, 4), (0, 5), (1, 3), (1, 4), (1, 5), (2, 3), (2, 4), (2, 5)]
BOX3 = [(0, 6), (0, 7), (0, 8), (1, 6), (1, 7), (1, 8), (2, 6), (2, 7), (2, 8)]
BOX4 = [(3, 0), (3, 1), (3, 2), (4, 0), (4, 1), (4, 2), (5, 0), (5, 1), (5, 2)]
BOX5 = [(3, 3), (3, 4), (3, 5), (4, 3), (4, 4), (4, 5), (5, 3), (5, 4), (5, 5)]
BOX6 = [(3, 6), (3, 7), (3, 8), (4, 6), (4, 7), (4, 8), (5, 6), (5, 7), (5, 8)]
BOX7 = [(6, 0), (6, 1), (6, 2), (7, 0), (7, 1), (7, 2), (8, 0), (8, 1), (8, 2)]
BOX8 = [(6, 3), (6, 4), (6, 5), (7, 3), (7, 4), (7, 5), (8, 3), (8, 4), (8, 5)]
BOX9 = [(6, 6), (6, 7), (6, 8), (7, 6), (7, 7), (7, 8), (8, 6), (8, 7), (8, 8)]

def valid(x, y, num):
    for i in range(9):
        if num == puzzle[x][i]:
            return False
        if num == puzzle[i][y]:
            return False
    box = whichBox(x, y)
    for i in range(9):
        if (num == puzzle[box[i][0]][box[i][1]]):
            return False
    return True

def whichBox(x, y):
    if x > 2:
        if y > 2:
            if x > 5:
                if y > 5:
                    return BOX9
                return BOX8
            if y > 5:
                return BOX6
            return BOX5
        if x > 5:
            return BOX7
        return BOX4
    if y > 2:
        if y > 5:
            return BOX3
        return BOX2
    return BOX1
    
def goal():
    for x in range(9):
        for y in range(9):
            if puzzle[x][y] == 0:
                return False
    return True

def solver(x, y):
    if y == 9:
        return
    if puzzle[x][y] != 0:
        # print("There is already a %d here at (%d, %d)" % (puzzle[x][y], x, y))
        if x == 8:
            solver(0, y + 1)
            return
        else:
            solver(x + 1, y)
            return
    for i in range(9):
        # print("Trying %d at (%d,%2d)" % (i + 1, x, y))
        if valid(x, y, i + 1):
            # print("%d worked" % (i + 1))
            puzzle[x][y] = i + 1
            if x == 8:
                solver(0, y + 1)
                if goal():
                    return
                puzzle[x][y] = 0
            else:
                solver(x + 1, y)
                if goal():
                    return
                puzzle[x][y] = 0
        
    # print("Couldn't place anything at (%d,%2d)" % (x, y))

solver(0, 0)

p = pd.DataFrame(puzzle)
p.to_csv('solution.csv', header=False, index=False)
