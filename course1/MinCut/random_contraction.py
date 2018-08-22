import random
import copy

def contraction(edges, nodes):
    fuse = random.choice(edges)
    edges = [x for x in edges if not x == fuse]
    for edge in edges:
        if edge[0] == fuse[1]:
            edge[0] = fuse[0]
        if edge[1] == fuse[1]:
            edge[1] = fuse[0]
            if edge[0] > edge[1]:
                edge[0], edge[1] = edge[1], edge[0]
    # print(len(edges))
    nodes.remove(fuse[1])
    return edges

if __name__ == "__main__":
    filename = 'kargerMinCut.txt'
    with open(filename) as file:
        edges = []
        for line in file:
            ls = line.split()
            cur = int(ls[0])
            for node in ls[1:]:
                pt = int(node)
                if pt <= cur: continue
                edge = [cur, pt]
                edges.append(edge)

        min_cut = 9999
        max_it = 100
        for i in range(max_it):
            new_edges = copy.deepcopy(edges)
            nodes = [j for j in range(1,201)]
            while len(nodes) > 2:
                new_edges = contraction(new_edges, nodes)
            if len(new_edges) < min_cut:
                min_cut = len(new_edges)

        print(min_cut)
