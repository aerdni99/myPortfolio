"""
    HMMpart2.py

    Python code for hidden markov model project # 3 part 2 for Artificial Intelligence class
"""
"""
Instructions to run:

Enter the following on a command line
python3 HMMpart1.py carReading.csv transitionProb.csv 20

Where carReading.csv is a file for sensor readings
and transitionProb.csv is a file for transition probabilities for each space on the grid.
and 20 represents a target time step.

The readings file has 4 columns. each column represents agentX,agentY,eDist,gridSize in that order.
The tProb file has 6 columns (X, Y, N, E, S, W) a row for each space and the probability
of moving in either of the four cardinal directions.

The first row of each csv is headers and is therefore skipped in parsing.
"""

# For command line args
import sys

# For parsing a .csv file
import csv

# For pdf function
from scipy.stats import norm

# For square root
from math import sqrt

# 2D object for holding reading data from the csv
readings = []

# 2D object for holding transition probs from csv
tProbs = []

# Size of the grid (acquired during parsing)
gridSize = 0

# Time step we are concerned with
targetStep = int(sys.argv[3])

# Create an output file name using targetStep
oFileName = "pMap_atTime" + str(targetStep) + ".csv"

# Parsing!

# Readings
with open(sys.argv[1]) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    rowCount = 0
    for row in csv_reader:
        rowData = []
        rowCount += 1
        if (rowCount == 1):
            continue
        if (rowCount == 2):
            gridSize = int(row[3])
        cell = 0
        for x in row:
            if (cell == 2):
                rowData.append(float(x))
                break
            else:
                rowData.append(int(x))
                cell += 1
        readings.append(rowData)

# Transition probabilities (stored and accessible with (x, y) coordinate indices)
with open(sys.argv[2]) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    rowCount = 0
    firstRow = True
    rowData = []
    for row in csv_reader:
        cellData = []
        if firstRow:
            firstRow = False
            continue
        cell = 0
        for x in row:
            if cell > 1:
                cellData.append(float(x))
            cell += 1
        rowData.append(cellData)
        if len(rowData) == gridSize:
            tProbs.append(rowData)
            rowData = []


# Create 2 2D structures to hold the probability map.
pMap = []
prevMap = []

# Initialize pMap cells
for i in range(gridSize):
    mapRow = []
    for i in range(gridSize):
        mapRow.append(1)
    pMap.append(mapRow)
    prevMap.append(mapRow)

# Compute probability for each time step for each space
for i in range(targetStep):

    # Save the probs from the last timestep for reference in calculating the new ones
    for x in range(gridSize):
        for y in range(gridSize):
            prevMap[x][y] = pMap[x][y]
    
    # Update the current map with the current timestep's probs
    for x in range(gridSize):
        for y in range(gridSize):

            # Compute the probability the car is in the target space based solely on the emission and distance
            xdist = readings[i][0] - x 
            ydist = readings[i][1] - y
            trueDist = sqrt(xdist * xdist + ydist * ydist) 
            pTheCarIsHere = norm.pdf(readings[i][2], trueDist, 2/3)

            # Compute the sum of probabilities from the last round times transitions for each adjacent space
            N = prevMap[x][(y + 1) % gridSize] * tProbs[x][(y + 1) % gridSize][2]
            E = prevMap[(x + 1) % gridSize][y] * tProbs[(x + 1) % gridSize][y][3]
            S = prevMap[x][(y - 1) % gridSize] * tProbs[x][(y - 1) % gridSize][0]
            W = prevMap[(x - 1) % gridSize][y] * tProbs[(x - 1) % gridSize][y][1]
            news = N + E + S + W

            # Update the map with the pieces computed above
            pMap[x][y] = news * pTheCarIsHere

# Normalize pMap

# Compute sum of all pMap cells
pMapSum = 0
for x in range(gridSize):
    for y in range(gridSize):
        pMapSum += pMap[x][y]

# Normalize each data cell
for x in range(gridSize):
    for y in range(gridSize):
        pMap[x][y] = (pMap[x][y] / pMapSum)

# Get estimated location
maxP = 0
for x in range(gridSize):
    for y in range(gridSize):
        if pMap[x][y] > maxP:
            maxP = pMap[x][y]
            estX = x
            estY = y
estLoc = "I think the car is at (" + str(estX) + ", " + str(estY) + ")"
print(estLoc)

# Write pMap to output file
headers = [1,2,3,4,5,6,7,8,9,10]
with open(oFileName, 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(headers)
    writer.writerows(pMap)   

print("Probability map was saved to " + oFileName + " in the current directory")
