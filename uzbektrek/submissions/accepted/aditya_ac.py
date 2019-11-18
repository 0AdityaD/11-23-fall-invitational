from __future__ import division, print_function

MOD = 1000000007
n, p = map(int, raw_input().split())

A = [None for _ in range(n + 1)]
A[0] = 1
for i in range(1, n + 1):
    if i % p > 0:
        A[i] = A[i - 1]
    else:
        A[i] = (A[i - 1] + A[i // p]) % MOD
print(A[n])
