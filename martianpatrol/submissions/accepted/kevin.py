from __future__ import print_function

input = raw_input

MOD = int(1e9) + 7
facts = []
invs = []


def inv(x):
    return pow(x, MOD - 2, MOD)


def prod(x, y):
    return ((x % MOD) * (y % MOD)) % MOD


def fact(n):
    global facts
    facts.append(1)
    invs.append(1)
    for i in range(1, 2 * n + 4):
        facts.append(prod(i, facts[i - 1]))
        invs.append(inv(facts[i]))


def choose(x, k):
    return prod(prod(facts[x], invs[k]), invs[x - k])


def catalan(x):
    return prod(choose(2 * x, x), inv(x + 1))


def solve():
    n = int(input())
    count = 0
    for _ in range(n):
        a, b = map(int, input().split())
        count += (1 if a == 0 else 0) + (1 if b == 0 else 0)
    fact(n)
    ans = 0
    for i in range(0, n + 2, 2):
        ans = (ans + prod(choose(n + 1, i), catalan(i // 2))) % MOD
    print(prod(ans, count))
     

solve()
