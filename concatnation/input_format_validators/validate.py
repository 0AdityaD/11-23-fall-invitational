#!/usr/bin/env python3
from sys import stdin
import re
import sys

N_LIM = 100000
S_LIM = 20

integer = "(0|[1-9]\d*)"
three = re.compile(integer + ' ' + integer + ' ' + integer + "\n")

line = stdin.readline()
assert three.match(line)
n,mn,mx = line.split(' ')
n = int(n)
mn = int(mn)
mx = int(mx)
assert 1 <= n <= N_LIM 
assert 0 <= mn <= S_LIM 
assert mn <= mx <= S_LIM 

for i in range(0, 26):
	line = stdin.readline()
	l,s = line.split(' ')
	assert len(str(s)) == int(l) + 1

for i in range(0, n):
	line = stdin.readline()
	assert 0 < len(line) - 1 <= S_LIM

sys.exit(42)
