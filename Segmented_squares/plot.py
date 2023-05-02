import matplotlib.pyplot as plt

# Read input file
with open('input1.txt') as f:
    lines = f.readlines()

# Extract x and y values from each line
x = []
y = []
for line in lines:
    point = line.split()
    x.append(float(point[0]))
    y.append(float(point[1]))

# Plot the points
plt.scatter(x, y, color='red')
plt.show()
# Open the file for reading
with open('output.txt', 'r') as f:

    # Read the file line by line
    for line in f:
        
        # Stop reading if line starts with '#'
        if line.startswith('#'):
            break
        
        # Extract the coordinates from the line
        coords = line.strip().split(':')
        x1, y1 = map(int, coords[0].split())
        x2, y2 = map(int, coords[1].split())
        
        # Plot the line segment
        plt.plot([x1, x2], [y1, y2], 'b')
        plt.scatter(x, y, color='red')
# Show the plot
plt.show()