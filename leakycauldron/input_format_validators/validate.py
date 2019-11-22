#!/usr/bin/env python3
from sys import stdin
import re
import sys

N_LIM = 200
M_LIM = 200
H_LIM = 2500

integer = "(0|[1-9]\d*)"
three = re.compile(integer + ' ' + integer + ' ' + integer + "\n")

line = stdin.readline()
assert three.match(line)
n,m,h = line.split(" ")
n = int(n)
m = int(m)
h = int(h)
assert 1 <= n <= N_LIM 
assert 1 <= m <= M_LIM 
assert 1 <= h <= H_LIM 

assert n % 2 == 1
assert m % 2 == 1

for i in range(0, n):
	line = stdin.readline()	
	arr = [int(j) for j in line.split(' ')]
	assert len(arr) == m
	for j in arr:
		assert 0 <= j <= H_LIM	
	if i == n//2:
		assert arr[m//2] == 0


line = stdin.readline()
assert line == ""

sys.exit(42)
