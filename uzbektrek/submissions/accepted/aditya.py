from __future__ import division, print_function

input = raw_input

MOD = 1000000007

n, P = map(int, input().split())
n //= P
p = 1
dp = [0 for _ in range(10000005)]
dp[0] = 1
while p <= n:
    for i in range(p, n + 1):
        dp[i] = (dp[i] + dp[i - p]) % MOD
    p *= P
res = 0
for i in range(n + 1):
    res = (res + dp[i]) % MOD
print(res)
