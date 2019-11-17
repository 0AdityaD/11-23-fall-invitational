#!/usr/bin/env python3
from sys import stdin
import re
import sys

N_LIM = 1000000

integer = "(0|[1-9]\d*)"
twoints = re.compile(integer + ' ' + integer + "\n")

line = stdin.readline()
assert twoints.match(line)
n,k = line.split(' ')
n = int(n)
k = int(k)
assert 1 <= n <= N_LIM 
assert 1 <= k <= N_LIM 
line = stdin.readline()
a = line.split(' ')
assert len(a) == n
for i in range(0, n):
	assert 0 <= int(a[i]) < k
sys.exit(42)
