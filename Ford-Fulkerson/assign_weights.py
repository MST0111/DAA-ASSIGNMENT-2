# import random

# low = 1  # the lower bound of the weight range
# high = 10  # the upper bound of the weight range

# # read input from file, generate random weight for each line, and write to output file
# with open('input.txt', 'r') as input_file, open('output.txt', 'w') as output_file:
#     for line in input_file:
#         input_data = line.strip()
#         weight = random.randint(low, high)
#         output_line = f"{input_data} {weight}\n"
#         output_file.write(output_line)
import random

low = 1  # the lower bound of the weight range
high = 10  # the upper bound of the weight range

# read input from file, generate random weight for each line, and overwrite the input file with the modified data
with open('input.txt', 'r+') as f:
    lines = f.readlines()  # read all lines into a list
    f.seek(0)  # move the file pointer back to the beginning
    for line in lines:
        input_data = line.strip()
        weight = random.randint(low, high)
        output_line = f"{input_data} {weight}\n"
        f.write(output_line)  # write the modified line to the file
    f.truncate()  # truncate any remaining content after the last line

