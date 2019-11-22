from sys import stdin
import re
import sys

integer = "(0|[1-9]\d*)"
intregex = re.compile(integer + '\n')

line = stdin.readline()
assert intregex.match(line)
n = int(line)

assert not stdin.readline()

sys.exit(42)
