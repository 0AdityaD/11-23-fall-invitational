import sys
sys.setrecursionlimit(10005)
MOD = 1000000007

def solve(A):
    n = len(A)
    violations = []
    for i in range(n):
        if i + 4 <= n:
            if A[i][0] == A[i + 1][0] == A[i + 2][0] == A[i + 3][0] and (i == 0 or A[i - 1][0] != A[i][0]):
                violations.append((i + 3, A[i][0]))
    for i in range(n):
        if i + 2 <= n:
            if A[i] == A[i + 1]:
                violations.append((i + 1, A[i][0]))
    if len(violations) == 0:
        return True
    return False


poss = []
for c in "AB":
    for i in range(1, 7):
        poss.append(''.join(map(str, (c, i))))


def go(n, ls=[]):
    if n == 0:
        return 1 if solve(ls) else 0
    res = 0
    for p in poss:
        ls.append(p)
        res += go(n - 1, ls)
        res %= MOD
        ls.pop()
    return res
    

print(go(int(input())))
