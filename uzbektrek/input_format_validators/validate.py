from sys import stdin
import re
import sys

integer = "(0|[1-9]\d*)"
twoints = re.compile(integer + ' ' + integer + "\n")

line = stdin.readline()
assert twoints.match(line)
n, p = line.split(' ')
n = int(n)
p = int(p)

assert 1 <= n <= 1000000000
assert 100 <= p <= 1000000000

assert not stdin.readline()

sys.exit(42)
