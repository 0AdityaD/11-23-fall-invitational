# TLE - any N^2 approach should time out.

from sys import stdin


def solve():
    n = int(stdin.readline())
    team, player, gender = [], [], []
    for _ in range(n):
        touch = stdin.readline()
        team.append(touch[0])
        player.append(touch[1])
        gender.append(touch[2])
    for i in range(n):
        for j in range(n):
            t = team[j]
            p = player[j]
            g = gender[j]
    for i in range(1, n + 1):
        if i != n and team[i] == team[i - 1] and player[i] == player[i - 1]:
            print(team[i])
            return
        if i >= 3 and i != n:
            if team[i] == team[i - 1] and team[i] == team[i - 2] and team[i] == team[i - 3]:
                print(team[i])
                return
        if i >= 2:
            if i == n or team[i] != team[i - 1]:
                touches = 1
                male, female = gender[i - 1] == 'M', gender[i - 1] == 'W'
                for j in range(1, 4):
                    if i - j - 1 < 0:
                        break
                    if team[i - j] != team[i - j - 1]:
                        break
                    touches += 1
                    male = male or gender[i - j - 1] == 'M'
                    female = female or gender[i - j - 1] == 'W'
                if touches > 1 and (not male or not female):
                    print(team[i - 1])
                    return
    print('No violation')


solve()
