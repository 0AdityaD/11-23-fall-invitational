from __future__ import print_function, division
from collections import defaultdict
import heapq
input = raw_input

N, M, T = map(int, input().split())
graph = defaultdict(list)
for _ in range(M):
    u, v, l, g, r, t = map(int, input().split())
    graph[u].append((v, l, g, r, t))
    graph[v].append((u, l, g, r, t))

def firstGreenAfter(time, g, r, t):
    time -= t
    rem = time - (time // (g + r)) * (g + r)
    if rem >= g:
        time += g + r - rem
    time += t
    return time

def works(speed):
    paths = {}
    q = [(0, 1)]
    while len(q) > 0:
        time, node = heapq.heappop(q)
        if node in paths:
            continue
        paths[node] = time
        for nxt, l, g, r, t in graph[node]:
            ntime = firstGreenAfter(time, g, r, t)
            ntime += l / speed
            heapq.heappush(q, (ntime, nxt))
    return paths[N] <= T

low = 0
high = 1000000000
while low + 1e-12 < high:
    mid = (low + high) / 2
    if works(mid):
        high = mid
    else:
        low = mid
print('%.30f' % high)
