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

# build arr
a = [[0 for i in range(0,m+1)] for i in range(0,m+1)]

for i in range(0, m):
	for j in range(0, m):
		a[i+1][j+1]  = d[pig[i]][seed[j]]	

# hungarian
u = [0 for i in range(0,m+1)]
v = [0 for i in range(0,m+1)]
p = [0 for i in range(0,m+1)]
way = [0 for i in range(0,m+1)]

for i in range(1,m+1):
	p[0] = i;
	j0 = 0
	minv = [INF for i in range(0, m+1)]
	used = [False for i in range(0, m+1)]
	while(1):
		used[j0] = True
		i0 = p[j0]
		delta = INF
		j1 = 0
		for j in range(1, m+1):
			if used[j] == False:
				cur = a[i0][j] - u[i0] - v[j]
				if cur < minv[j]:
					minv[j] = cur
					way[j] = j0
				if minv[j] < delta:
					delta = minv[j]
					j1 = j
		for j  in range(0, m+1):
			if used[j]:
				u[p[j]] += delta
				v[j] -= delta
			else:
				minv[j] -= delta
		j0 = j1
		if p[j0] == 0:
			break
	
	while(1):
		j1 = way[j0]
		p[j0] = p[j1]
		j0 = j1
		if j0 == 0:
			break

print(-v[0])
