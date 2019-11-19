#! /usr/bin/python3
import random
import os
import shutil
import subprocess
import time
import zipfile


random.seed(123123)
tc = 0


def writeTestCase(G, P, F):
    global tc
    tc += 1
    print(tc)
    filename = 'secret/%02d.in' % tc
    with open(filename, 'w') as fout:
        N = len(G)
        M = len(P)
        print(N, M, file=fout)
        for line in G:
            print(' '.join(map(str, line)), file=fout)
        print(' '.join(map(str, P)), file=fout)
        print(' '.join(map(str, F)), file=fout)
    with open('secret/%02d.ans' % tc, 'w') as outf:
        with open(filename, 'r') as inf:
            subprocess.call(['./aditya.out'],
                            stdin=inf, stdout=outf)


def prep():
    path = os.getcwd() + '/secret'
    assert 'economicalpigeonfeeding/data/' in path
    shutil.rmtree(path, True)
    os.mkdir(path)
    time.sleep(1)
    subprocess.call(['g++', '-std=c++17', '-O3', '-o', 'aditya.out', '../submissions/accepted/aditya.cpp'])


def randGen(N=500, M=200):
    G = [[random.randint(1, 10000) for _ in range(N)] for _ in range(N)]
    for i in range(N):
        G[i][i] = 0
        for j in range(i + 1, N):
            G[j][i] = G[i][j]
    LS = [i for i in range(N)]
    random.shuffle(LS)
    P = [LS[i] for i in range(M)]
    assert len(P) == len(set(P)) == M
    F = [LS[i] for i in range(M, 2 * M)]
    assert len(F) == len(set(F)) == M
    assert set(P).intersection(set(F)) == set()
    return G, P, F


def main():
    global tc
    prep()
    for i in range(20):
        writeTestCase(*randGen())


if __name__ == '__main__':
    main()
