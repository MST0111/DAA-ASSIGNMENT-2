import random

n = int(input("No. of points: "))

f = open("input.txt", "w")
f.write("")
f.close()

f = open("input.txt", "a")

for i in range(n):
    x, y = random.randint(-45, 45), random.randint(-45, 45)
    inpstr = str(x) + " " + str(y) + "\n"
    f.write(inpstr)

f.close()