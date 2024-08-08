import sys
from typing import Dict, List, Tuple


def input_graph():
    graph: Dict[str, List[str]] = {}
    cost: Dict[Tuple[str, str], int] = {}
    start, end = sys.stdin.readline().split(' ')
    start, end = start.strip(), end.strip()
    while True:
        line = sys.stdin.readline()
        if not line:
            break
        a, b, c = line.split(' ')
        c = int(c)
        if a in graph:
            p = graph[a]
        else:
            p = []
        p.append(b)
        cost[(a, b)] = c
        graph[a] = p

    return graph, cost, start, end


def make_path(path, end):
    result = []
    while path[end]:
        result.append(end)
        end = path[end]
    result.append(end)
    result.reverse()
    return result


def ucs(graph, cost, start, end):
    queue: List[Tuple[int, str, str]] = []
    queue.append((0, start, ''))
    visited = set()
    path: Dict[str, str] = {}

    while queue:
        queue.sort(reverse=True)
        d, s, f = queue.pop()
        path[s] = f
        if s == end:
            return d, make_path(path, end)
        visited.add(s)
        for n in graph[s]:
            if n not in visited:
                queue.append((d + cost[(s, n)], n, s))


def main():
    import sys
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 1
    graph, cost, s, e = input_graph()
    for _ in range(n):
        d, p = ucs(graph, cost, s, e)
        print(d, ' -> '.join(p), sep='\n')


if __name__ == "__main__":
    main()
