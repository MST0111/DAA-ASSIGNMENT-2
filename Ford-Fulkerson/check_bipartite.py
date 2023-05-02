from collections import deque

# read the graph from file
edges = []
with open('bipartite.txt', 'r') as f:
    for line in f:
        from_vertex, to_vertex = map(int, line.strip().split())
        edges.append((from_vertex, to_vertex))

# create an adjacency list representation of the graph
adj_list = {}
for edge in edges:
    from_vertex, to_vertex = edge
    if from_vertex not in adj_list:
        adj_list[from_vertex] = []
    if to_vertex not in adj_list:
        adj_list[to_vertex] = []
    adj_list[from_vertex].append(to_vertex)
    adj_list[to_vertex].append(from_vertex)

# initialize vertex colors to -1 (unassigned)
color = [-1] * (max(adj_list.keys()) + 1)

# perform BFS traversal and assign colors to vertices
def bfs(vertex):
    q = deque()
    q.append(vertex)
    color[vertex] = 0
    while q:
        u = q.popleft()
        for v in adj_list[u]:
            if color[v] == -1:
                color[v] = 1 - color[u]
                q.append(v)
            elif color[v] == color[u]:
                return False
    return True

# check if the graph is bipartite
is_bipartite = True
for vertex in adj_list.keys():
    if color[vertex] == -1:
        is_bipartite = bfs(vertex)
        if not is_bipartite:
            break

# print the result
if is_bipartite:
    print("The graph is bipartite.")
else:
    print("The graph is not bipartite.")
