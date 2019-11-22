# OEIS solution

from __future__ import print_function

input = raw_input

MOD = int(1e9 + 7)


def solve():
    n = int(input())
    if n == 0:
        print(1)
        return
    ans = (12 * pow(11, n - 1, MOD)) % MOD
    print(ans)
    

solve()
