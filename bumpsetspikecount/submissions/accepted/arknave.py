MOD = int(1e9 + 7)

def solve(n):
    if n == 0:
        return 1
    elif n == 1:
        return 12

    # dp[i][j] = number of sequences where team i is the last team to hit
    # j means if the same team has hit twice
    dp = [[6, 0], [6, 0]]

    for _ in range(1, n):
        ndp = [[0, 0], [0, 0]]
        for i in range(2):
            for j in range(2):
                # swap teams
                ndp[i ^ 1][0] += 6 * dp[i][j] % MOD
                if j == 0:
                    ndp[i][1] += 5 * dp[i][j] % MOD
        dp = ndp

    return sum(map(sum, ndp)) % MOD

n = int(input())

print(solve(n))
