with open('temp.txt', 'r') as input_file, open('bipartite.txt', 'w') as output_file:
    for line in input_file:
        x, y = map(int, line.split())
        new_x, new_y = x + 1, y + 1
        output_file.write(f'{new_x} {new_y}\n')
