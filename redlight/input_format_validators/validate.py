from sys import stdin
import re
import sys
from collections import defaultdict, deque

MAXN = 50000
MAXT = int(1e9)
MAXG = 10000
MAXL = 1000000

integer = "(0|[1-9]\d*)"
threeints = re.compile(integer + " " + integer + " " + integer + '\n')
sixints = integer
for _ in range(5):
    sixints += ' ' + integer
sixints = re.compile(sixints + '\n')

line = stdin.readline()
assert threeints.match(line)
n, m, t = map(int, line.split())

assert 2 <= n <= MAXN
assert 1 <= m <= MAXN
assert 1 <= t <= MAXT

graph = defaultdict(list)
seen = set()
for _ in range(m):
    line = stdin.readline()
    assert sixints.match(line)
    u, v, l, g, r, ti = map(int, line.split())
    assert 1 <= u <= n
    assert 1 <= v <= n
    assert u != v
    assert (u, v) not in seen
    seen.add((u, v))
    assert 1 <= l <= MAXL
    assert 1 <= g <= MAXG
    assert 1 <= r <= MAXG
    assert 0 <= ti <= r
    graph[u].append(v)
    
# bfs from u to reach v
q = deque([1])
visited = set()
while len(q) > 0:
    cur = q.popleft()
    if cur in visited:
        continue
    visited.add(cur)
    for node in graph[cur]:
        q.append(node)
assert n in visited

assert not stdin.readline()

sys.exit(42)
