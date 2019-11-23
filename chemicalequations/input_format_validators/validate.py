#!/usr/bin/python3

from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
name = "[A-Z0-9]*"

l = stdin.readline()

assert re.match(integer + "\n", l)

n = int(l)

assert 1 <= n <= 50

for i in range(n):
    l = stdin.readline()
    assert re.match(name + " " + integer + "\n", l)

    (n, sz) = l.split()
    sz = int(sz)

    print(sz)

    for j in range(sz):
        l = stdin.readline()
        assert re.match(integer + " " + name + "\n", l)


l = stdin.readline()
assert re.match(name + "\n", l)
assert len(stdin.readline()) == 0
sys.exit(42)
