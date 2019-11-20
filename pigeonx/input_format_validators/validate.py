from sys import stdin
import re
import sys

def integer0Check(line):
    for x in line.split():
        if str(int(x)) != x:
            return False
    return True

line = stdin.readline()
n, m = map(int, line.split())
assert integer0Check(line)

assert 1 <= n <= 500
assert 1 <= m <= 200
assert m * 2 <= n

graph = [None for _ in range(n)]
for i in range(n):
    line = stdin.readline()
    assert integer0Check(line)
    graph[i] = list(map(int, line.split()))

for i in range(n):
    assert graph[i][i] == 0
    for j in range(n):
        assert graph[i][j] == graph[j][i]

line = stdin.readline()
assert integer0Check(line)
P = set(map(int, line.split()))
assert len(P) == m

line = stdin.readline()
assert integer0Check(line)
F = set(map(int, line.split()))
assert len(F) == m

assert P.intersection(F) == set()

assert not stdin.readline()

sys.exit(42)
