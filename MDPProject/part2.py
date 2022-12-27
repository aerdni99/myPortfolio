"""
    part2.py

    MDP Project part 2

    Calculates the optimal policy with user-determined transition probability,
    user-determined reward, 0.95 discount factor at the 20th iteration
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

tProb = float(sys.argv[1])
slipProb = (1 - tProb) / 2
reward = float(sys.argv[2])

# Matrix of rewards
rewards = [[reward, reward, reward, reward], [reward, reward, reward, -1], [reward, reward, reward, 1]]

# Holds the current max utility and the respective optimal policy
vSupN = [[(0, 0), (0, 0), (0, 0), (0, 0)], [(0, 0), (0, 0), (0, 0), (0, 0)], [(0, 0), (0, 0), (0, 0), (0, 0)]]

# Holds the last recorded max utility
vSupN_minus1 = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]

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

# This function plugs in x and y to the Q-val equation so that we dont have to write it over and over down below
# Transition probabilities are not applied here so these values are general use for multiple policies
def calcRawQ(x, y):
    return rewards[x][y] + 0.95 * vSupN_minus1[x][y]

# Function for trying each policy and comparing their utility
def valIter(x, y):

    # These states have no utility or policy
    if x == 2 and y == 3:
        return 0
    if x == 1 and y == 3:
        return 0
    if x == 1 and y == 1:
        return 0

    # Each of the three lists below follow the format:
    # [up, down, left, right]

    # "rawQ" is each of 4 q-vals for neighboring spaces
    # # The transition probability has not been applied yet.
    #  We apply them per-policy below
    rawQ = [0, 0, 0, 0]

    # Q val for each action with transition probabilities applied
    qVals = [0, 0, 0, 0]

    # Check for wall collisions. a list of 4 bool values
    avail = checkBound(x, y)

    # Stay is like a 5th pseudo-action that takes the place of any action that attempts to pass a wall
    stay = calcRawQ(x, y)


    # Get "rawQ's"
    if avail[0]:
        rawQ[0] = calcRawQ(x + 1, y)
    else:
        rawQ[0] = stay
    if avail[1]:
        rawQ[1] = calcRawQ(x - 1, y)
    else:
        rawQ[1] = stay
    if avail[2]:
        rawQ[2] = calcRawQ(x, y - 1)
    else:
        rawQ[2] = stay
    if avail[3]:
        rawQ[3] = calcRawQ(x, y + 1)
    else:
        rawQ[3] = stay

    # Apply transition probabilities
    qVals[0] = tProb * rawQ[0] + slipProb * rawQ[2] + slipProb * rawQ[3]
    qVals[1] = tProb * rawQ[1] + slipProb * rawQ[2] + slipProb * rawQ[3]
    qVals[2] = tProb * rawQ[2] + slipProb * rawQ[1] + slipProb * rawQ[0]
    qVals[3] = tProb * rawQ[3] + slipProb * rawQ[1] + slipProb * rawQ[0]

    # store the max qVal and policy
    max = qVals[0]
    pol = 1
    if qVals[1] > max:
        max = qVals[1]
        pol = -1
    if qVals[2] > max:
        max = qVals[2]
        pol = -2
    if qVals[3] > max:
        max = qVals[3]
        pol = 2

    # Final max & policy are written to our table
    vSupN[x][y] = (max, pol)

# Iterate through the board updating policy and max utility 20 times
for n in range(20):
    for x in range(3):
        for y in range(4):
            # Store old V value in last recorded
            vSupN_minus1[x][y] = vSupN[x][y][0]
    for x in range(3):
        for y in range(4):
            valIter(x, y)

# transfer final policy to a matrix with one dimensional values so it can be written to file
for x in range(3):
        for y in range(4):
            # Store old V value in last recorded
            vSupN_minus1[x][y] = vSupN[x][y][1]

# Write policy to output file
with open("expectimax.csv", "w") as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(vSupN_minus1[2])
    writer.writerow(vSupN_minus1[1])
    writer.writerow(vSupN_minus1[0])
