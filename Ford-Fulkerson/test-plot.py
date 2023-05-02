# import networkx as nx
# import matplotlib.pyplot as plt
# points = []
# f=open('temp.txt')
# V=int(f.readline())
# for j in range(V):
#     str=f.readline()
#     str_list=str.split()
#     temp=[]
#     for i in range(3):
#         temp.append(int(str_list[i]))
#     points.append(tuple(temp))
# G = nx.DiGraph()
# pos = nx.circular_layout(G)
#     # Draw the nodes and edges
    
# nx.draw_networkx_nodes(G, pos, node_size=300)
# nx.draw_networkx_edges(G, pos, width=1)
# nx.draw_networkx_edge_labels(G, pos, edge_labels={(u, v): d['weight'] for u, v, d in G.edges(data=True)})
# nx.draw_networkx_labels(G, pos)

# plt.axis('off')
# plt.show()