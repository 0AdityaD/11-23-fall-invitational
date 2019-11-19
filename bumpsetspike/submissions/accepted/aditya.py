input = raw_input

def solve():
    n = int(input())
    A = [input() for _ in range(n)]
    violations = []
    for i in range(n):
        if i + 4 <= n:
            if A[i][0] == A[i + 1][0] == A[i + 2][0] == A[i + 3][0] and (i == 0 or A[i - 1][0] != A[i][0]):
                violations.append((i + 3, A[i][0]))
    for i in range(n):
        if i + 2 <= n:
            if A[i][:2] == A[i + 1][:2] and (i == 0 or A[i - 1][:2] != A[i][:2]):
                violations.append((i + 1, A[i][0]))
    for i in range(n): 
        if i + 3 <= n and A[i][0] == A[i + 1][0] == A[i + 2][0] and (i == 0 or A[i - 1][0] != A[i][0]):
            if A[i][-1] == A[i + 1][-1] == A[i + 2][-1]:
                violations.append((i + 2, A[i][0]))
        elif i + 2 <= n and A[i][0] == A[i + 1][0] and (i == 0 or A[i - 1][0] != A[i][0]):
            if A[i][-1] == A[i + 1][-1]:
                violations.append((i + 1, A[i][0]))
    if len(violations) == 0:
        print('No violation')
        return
    violations.sort()
    print(violations[0][1])

solve()
