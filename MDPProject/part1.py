"""
    part1.py

    MDP Project part 1

    Calculates the total utility when starting at state s, following policy pi,
    with user-determined reward, 0.95 discount factor for 20 iterations
    on a 3x4 board with one unreachable state, 
    1 goal state (reward = 1), and 1 bad state (reward = -1)

    [ -0.04 ] [ -0.04 ] [ -0.04 ] [  +1   ]
    [ -0.04 ] [ -0.04 ] [ -0.04 ] [  -1   ]
    [ start ] [ -0.04 ] [ -0.04 ] [ -0.04 ]

"""

# For reading .csv files
import csv

# For command line arguments
import sys

# First arg is the default reward
reward = float(sys.argv[1])

# Second is the input file
inputFile = sys.argv[2]

# Read policy input file into a 3x4 matrix
policy = []
with open(inputFile) as csv_file:
    csv_reader = csv.reader(csv_file)
    for row in csv_reader:
        column = []
        for x in row:
            column.append(int(x))
        policy.append(column)

# swap rows so that policay coordinates line up with other matrices
temp = policy[0]
policy[0] = policy[2]
policy[2] = temp

# for holding updated utility values
vSupN = []

# for holding last utility values
vSupN_Minus1 = []

# Initialize Utilities to 0
for x in range(3):
    col1 = []
    col2 = []
    for y in range(4):
        col1.append(0)
        col2.append(0)
    vSupN.append(col1)
    vSupN_Minus1.append(col2)

# Matrix of rewards
rewards = [[reward, reward, reward, reward],[reward, reward, reward, -1],[reward, reward, reward, 1]]

# list of ordered pairs that cannot be visited
outOfBounds = []

# Left Bound
outOfBounds.append((0,-1))
outOfBounds.append((1,-1))
outOfBounds.append((2,-1))

# Right Bound
outOfBounds.append((0,4))
outOfBounds.append((1,4))
outOfBounds.append((2,4))

# Lower Bound
outOfBounds.append((-1,0))
outOfBounds.append((-1,1))
outOfBounds.append((-1,2))
outOfBounds.append((-1,3))

# Upper Bound
outOfBounds.append((3,0))
outOfBounds.append((3,1))
outOfBounds.append((3,2))
outOfBounds.append((3,3))

# Pillar
outOfBounds.append((1,1))

# Given a coordinate, check the neighbor spaces for what's free
def checkBound(x, y):
    # 4 bools, [up, down, left, right]
    avail = []
    if (x + 1, y) in outOfBounds:
        avail.append(False)
    else:
        avail.append(True)
    if (x - 1, y) in outOfBounds:
        avail.append(False)
    else:
        avail.append(True)
    if (x, y - 1) in outOfBounds:
        avail.append(False)
    else:
        avail.append(True)
    if (x, y + 1) in outOfBounds:
        avail.append(False)
    else:
        avail.append(True)
    return avail

# Handles some of the more repetitive parts of the getQ function below (value calculation constants)
def getQPiece(x, y, tProb): 
    return tProb * (rewards[x][y] + 0.95 * vSupN_Minus1[x][y])

# Branching if structure for implementing policy following and calculating policy evaluation
def getQ(x, y):

    # These three states have no utility.
    if x == 2 and y == 3:
        return 0
    if x == 1 and y == 3:
        return 0
    if x == 1 and y == 1:
        return 0

    # Check for walls
    avail = checkBound(x, y)

    # Save the current utility in the n-1 matrix unless goal state (always zero utility)
    vSupN_Minus1[x][y] = vSupN[x][y]

    # Var to hold the new utility
    newUtil = 0

    # Logic for calculating new utility based on map bounds, rewards, and policy
    if policy[x][y] == 1:
        if avail[0]:
            newUtil += getQPiece(x + 1, y, 0.8)
        else:
            newUtil += getQPiece(x, y, 0.8)
        if avail[2]:
            newUtil += getQPiece(x, y - 1, 0.1)
        else:
            newUtil += getQPiece(x, y, 0.1)
        if avail[3]:
            newUtil += getQPiece(x, y + 1, 0.1)
        else:
            newUtil += getQPiece(x, y, 0.1)
    elif policy[x][y] == -1:
        if avail[1]:
            newUtil += getQPiece(x - 1, y, 0.8)
        else:
            newUtil += getQPiece(x, y, 0.8)
        if avail[2]:
            newUtil += getQPiece(x, y - 1, 0.1)
        else:
            newUtil += getQPiece(x, y, 0.1)
        if avail[3]:
            newUtil += getQPiece(x, y + 1, 0.1)
        else:
            newUtil += getQPiece(x, y, 0.1)
    elif policy[x][y] == 2:
        if avail[3]:
            newUtil += getQPiece(x, y + 1, 0.8)
        else:
            newUtil += getQPiece(x, y, 0.8)
        if avail[0]:
            newUtil += getQPiece(x + 1, y, 0.1)
        else:
            newUtil += getQPiece(x, y, 0.1)
        if avail[1]:
            newUtil += getQPiece(x - 1, y, 0.1)
        else:
            newUtil += getQPiece(x, y, 0.1)
    else:
        if avail[2]:
            newUtil += getQPiece(x, y - 1, 0.8)
        else:
            newUtil += getQPiece(x, y, 0.8)
        if avail[0]:
            newUtil += getQPiece(x + 1, y, 0.1)
        else:
            newUtil += getQPiece(x, y, 0.1)
        if avail[1]:
            newUtil += getQPiece(x - 1, y, 0.1)
        else:
            newUtil += getQPiece(x, y, 0.1)

    # New utility is returned
    return newUtil

# Update each utility based on the previous iteration 20 times
for n in range(2000):
    for x in range(3):
        for y in range(4):
            vSupN[x][y] = getQ(x, y)

# Output result to console
print(vSupN[0][0])
