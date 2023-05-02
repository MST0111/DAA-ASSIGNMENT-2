import networkx as nx
import matplotlib.pyplot as plt
import sys
# Define the network points
points = []
f=open('plot.txt')
V=int(f.readline())
for j in range(V):
    str=f.readline()
    str_list=str.split()
    temp=[]
    for i in range(3):
        temp.append(int(str_list[i]))
    points.append(tuple(temp))

#print(points)
#Create a directed graph
G = nx.DiGraph()
if len(sys.argv)==1:
    # Add edges to the graph
    f.readline()
    s=f.readline().split()
    marker_points=[int(i) for i in s]
    marker_points.append(1)
    flow=int(f.readline())
    G.add_weighted_edges_from(points)
    colormap=[]
    for i in G.nodes():
        if i in set(marker_points):
            colormap.append('blue')
        else:
            colormap.append('red')
    # Set the positions of the nodes
    pos = nx.circular_layout(G)
    # Draw the nodes and edges
    
    nx.draw_networkx_nodes(G, pos, node_size=300,node_color=colormap)
    nx.draw_networkx_edges(G, pos, width=1)
    nx.draw_networkx_edge_labels(G, pos, edge_labels={(u, v): d['weight'] for u, v, d in G.edges(data=True)})
    nx.draw_networkx_labels(G, pos)
    ax = plt.gca()
    ax.set_title(f'min cut is formed between {set(marker_points)} and {G.nodes()-marker_points}\n and flow is {flow}')
    #G.graph['title'] = f'min cut is formed between {marker_points} and {G.nodes()-marker_points}'
elif sys.argv[1]=='b':
    left_points=[points[i][0] for i in range(len(points))]
    right_points=[points[i][1] for i in range(len(points))]
    edges=[]
    for i in range(len(points)):
        edges.append(tuple([left_points[i],right_points[i]]))
    G.add_nodes_from(left_points,bipartite=0,node_size=500)
    G.add_nodes_from(right_points,bipartite=1,node_size=500)
    G.add_edges_from(edges)
    pos = nx.bipartite_layout(G, left_points)
    nx.draw(G, pos, with_labels=True)
    # plt.show()






# Show the plot
plt.axis('off')
plt.show()