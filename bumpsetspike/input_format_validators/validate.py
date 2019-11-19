from sys import stdin
import re
import sys

MAXN = 100000

integer = "(0|[1-9]\d*)"
intregex = re.compile(integer + '\n')
touch = "([AB][1-6][MW])"
touchregex = re.compile(touch + '\n')

line = stdin.readline()
assert intregex.match(line)
n = int(line)

assert 2 <= n <= MAXN

for _ in range(n):
    line = stdin.readline()
    assert touchregex.match(line)

assert not stdin.readline()

sys.exit(42)
