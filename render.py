import matplotlib.pyplot as plt
import csv
file = open ('test.csv')

type(file)

csvreader = csv.reader(file)

rows = []
for row in csvreader:
    rows.append(row)

file.close()


cleanedPoints = []

for i in range (1, len(rows)):
    cleanedPoints.append([])

    for j in range (0, len(rows[i])-1):
        cleanedPoints[i-1].append(float(rows[i][j]))


print(cleanedPoints)
