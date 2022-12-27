"""
    HMMpart1.py

    Python code for hidden markov model project # 3 part 1 for Artificial Intelligence class
"""
"""
Instructions to run:

Enter the following on a command line
python3 HMMpart1.py stationaryCarReading.csv 20

Where stationaryCarReading.csv is a file for sensor readings
and 20 represents a target time step.

the .csv file has 4 columns. each column represents agentX,agentY,eDist,gridSize in that order.
The first row of the csv is headers and is therefore skipped in parsing.
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

# Size of the grid (acquired during parsing)
gridSize = 0

# Time step we are concerned with
targetStep = int(sys.argv[2])

# Create an output file name using targetStep
oFileName = "pMap_atTime" + str(targetStep) + ".csv"

# Parsing!
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

# Create a 2D structure to hold the probability map.
pMap = []

# Initialize pMap cells
for i in range(gridSize):
    mapRow = []
    for i in range(gridSize):
        mapRow.append(1)
    pMap.append(mapRow)

# Compute probability for each time step for each space
for i in range(targetStep):
    for x in range(gridSize):
        for y in range(gridSize):
            xdist = readings[i][0] - x 
            ydist = readings[i][1] - y
            trueDist = sqrt(xdist * xdist + ydist * ydist) 
            pMap[x][y] *= norm.pdf(readings[i][2], trueDist, 2/3)

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

# Print estimated location (Ask about this format)
estLoc = "I think the car is at (" + str(estX) + ", " + str(estY) + ")"
print(estLoc)

# Write pMap to output file
headers = [1,2,3,4,5,6,7,8,9,10]
with open(oFileName, 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(headers)
    writer.writerows(pMap)

print("Probability map was saved to " + oFileName + " in the current directory")
