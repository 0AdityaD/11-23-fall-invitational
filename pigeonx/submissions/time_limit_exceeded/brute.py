from itertools import permutations

INF = 20000000
N = 500
M = 255

d = [[INF for i in range(0,N)] for j in range(0,N)]

try:
	input = raw_input
except NameError:
	pass

n,m = input().split(' ') 
n = int(n)
m = int(m)

for i in range(0, n):
	d[i] = [int(j) for j in input().split(" ")]

pig = [int(i) for i in input().split(" ")]
seed = [int(i) for i in input().split(" ")]


# fwarshall
for k in range(0, n):
	for i in range(0, n):
		for j in range(0, n):
			d[i][j] = min(d[i][j], d[i][k] + d[k][j])

# brute force matching
ans = INF
for perm in permutations(range(m)):
    tot = 0
    for i in range(m):
        p, s = pig[i], seed[perm[i]]
        tot += d[p][s]
    ans = min(ans, tot)

print(tot)
