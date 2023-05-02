import random
import sys
num_vertices = 640  # the total number of vertices in the bipartite graph
num_edges = 1280  # the total number of edges in the bipartite graph
start_vertex = 1  # the starting vertex number

# generate a list of vertices for each bipartite set
vertices1 = [i for i in range(start_vertex, num_vertices+1)]
vertices2 = [i for i in range(num_vertices+1, 2*num_vertices+1)]

# create a list of all possible edges
edges = [(i, j) for i in vertices1 for j in vertices2]

# shuffle the list of edges randomly
random.shuffle(edges)

# write the edges to a file in the format "from, to"
with open('bipartite.txt', 'w') as f:
    for i in range(num_edges):
        edge = edges[i]
        f.write("{} {}\n".format(edge[0], edge[1]))
