import csv
import matplotlib.pyplot as plt

fileName = input("Enter file name: ")
file = open (f"{fileName}.csv")

type(file)

csvreader = csv.reader(file)

rows = []
for row in csvreader:
    rows.append(row)

file.close()

# cleanedPoints = []
#
# for i in range(1, len(rows)):
#     cleanedPoints.append([])
#
#     for j in range(0, len(rows[i]) - 1):
#         cleanedPoints[i - 1].append(float(rows[i][j]))


cleanedPoints = []

for i in range(1, len(rows)):
    cleanedPoints.append([])

    for j in range(1, len(rows[i]) - 2):
        cleanedPoints[i - 1].append(float(rows[i][j]))


x = []
y = []
for i in range(0, len(cleanedPoints)):
    x.append(cleanedPoints[i][0])
    y.append(cleanedPoints[i][1])

print(cleanedPoints)
print(x)
print(y)


plt.plot(x, y, color = 'g', linestyle = 'dashed',
         marker = 'o',label = "Path")

plt.xticks(rotation = 25)
plt.xlabel('x (in)')
plt.ylabel('y (in)')
plt.title('Path', fontsize = 20)
plt.grid()
plt.legend()
plt.show()