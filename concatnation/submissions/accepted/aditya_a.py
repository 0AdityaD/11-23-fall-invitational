input = raw_input

n, x, y = map(int, input().split())
successor = {}
lens = {}

curr = 'a'
for i in range(26):
    _, s = input().split()
    successor[curr] = s
    lens[curr] = set()
    curr = chr(ord(curr) + 1)

def valid(s):
    for i in range(len(s) - 1):
        if s[i + 1] not in successor[s[i]]:
            return False
    return True

ids = []
for i in range(n):
    s = input()
    ids.append(s)

    if(valid(s)):
        lens[s[0]].add(len(s))

for i in range(n):
    works = valid(ids[i])
    if works and x <= len(ids[i]) <= y:
        print('Feline good!')
    elif works:
        works = False
        for j in range(x, y + 1):
            desLen = j - len(ids[i])
            for c in successor[ids[i][-1]]:
                if desLen in lens[c]:
                    works = True

        if(works):
            print('Feline good!')
        else:
            print('Get meowt!')

    else:
        print('Get meowt!')
