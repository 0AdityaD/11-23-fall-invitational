input = raw_input
from collections import defaultdict

def solve():
    n, x, y = map(int, input().split())
    mp = {}
    for i in range(26):
        _, s = input().split()
        mp[chr(ord('a') + i)] = s

    def works(idd):
        for i in range(1, len(idd)):
            if idd[i] not in mp[idd[i - 1]]:
                return False
        return True

    ls = []
    ids = defaultdict(set)
    for _ in range(n):
        idd = input()
        ls.append(idd)
        if works(idd):
            ids[idd[0]].add(len(idd))
    res = []
    for idd in ls:
        if not works(idd):
            res.append(False)
            continue
        if x <= len(idd) <= y:
            res.append(True)
            continue
        if len(idd) > y:
            res.append(False)
            continue
        mn = max(0, len(idd) - x)
        mx = y - len(idd)
        assert(mx >= 0)
        worked = False
        for nxt in mp[idd[-1]]:
            for i in range(1, 21):
                if x <= i + len(idd) <= y and i in ids[nxt]:
                    worked = True
                    break
            if worked:
                break
        if worked:
            res.append(True)
        else:
            res.append(False)
    return res

for x in solve():
    if x == True:
        print('Feline good!')
    else:
        print('Get meowt!')

