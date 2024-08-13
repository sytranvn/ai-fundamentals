from argparse import ArgumentParser
from collections import defaultdict
from os import sep

parser = ArgumentParser()
parser.add_argument("alg", choices=("bfs", "dfs"), help="search algorithm")
parser.add_argument("file", help="Input graph")
parser.add_argument("-s", help="start", required=True)
parser.add_argument("-e", help="end", required=True)


def get_input(file):
    graph = defaultdict(list)
    with open(file, "r") as f:
        data = f.readlines()
        for line in data:
            a, b = line.split()
            graph[a].append(b)
    for a in graph:
        # sort alphabet
        graph[a].sort()
    return graph


def bfs(graph, start, end):
    fringe = []
    close_set = []
    fringe.append([start])
    while fringe:
        path = fringe.pop(0)
        s = path[-1]
        if s == end:
            return path
        close_set.append(s)
        for neighbour in graph[s]:
            if neighbour not in close_set:
                new_path = path[:]
                fringe.append(new_path + [neighbour])


def dfs(graph, start, end):
    fringe = []
    close_set = []
    fringe.append([start])
    while fringe:
        path = fringe.pop()
        s = path[-1]
        if s == end:
            return path
        close_set.append(s)
        for neighbour in graph[s]:
            if neighbour not in close_set:
                new_path = path[:]
                fringe.append(new_path + [neighbour])


if __name__ == "__main__":
    args = parser.parse_args()
    graph = get_input(args.file)
    if args.s not in graph:
        print("Start point is not valid")
        exit(1)
    if args.alg == "bfs":
        alg = bfs
    else:
        alg = dfs

    path = alg(graph, args.s, args.e)
    print(*path, sep=" -> ")
