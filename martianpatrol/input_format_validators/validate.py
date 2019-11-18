#!/usr/bin/env python3
from sys import stdin
import re
import sys

N_LIM = 1000000
T_LIM = 10

integer = "(0|[1-9]\d*)"
twoints = re.compile(integer + ' ' + integer + "\n")

line = stdin.readline()
assert twoints.match(line)
n,t = line.split(' ')
n = int(n)
t = int(t)
assert 1 <= n <= N_LIM 
assert 1 <= t <= T_LIM 

arr = [0 for i in range(0,n+1)]

arr[1] = 1
for i in range(1, n+1):
	line = stdin.readline()
	print(line)
	l,r = line.split(' ')
	print(line)
	l = int(l)
	r = int(r)
	assert l != i
	assert r != i
	if l != 0:
		assert arr[l] == 0
		arr[l] = 1
	if r != 0:
		assert arr[r] == 0
		arr[r] = 1

for i in range(2,n+1):
	assert arr[i] == 1

sys.exit(42)
