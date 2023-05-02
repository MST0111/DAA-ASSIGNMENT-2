import random
import math

# Generate points
points = []
for i in range(100):
    x = random.randint(-10, 10)
    y = int(10*math.sin(x))
    #int(1000 / (1 + math.exp(-x)))
    #x** + random.randint(-1, 1)
    points.append((x, y))

# Write points to file
with open("input.txt", "w") as f:
    for point in points:
        f.write(f"{point[0]} {point[1]}\n")
