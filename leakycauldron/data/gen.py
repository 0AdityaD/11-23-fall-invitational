import random
import os
import shutil
import subprocess
import time
import zipfile
from random import randint


random.seed(12383)
tc = 0

def writeTestCase(data, sample=False, desc=None):
    global tc
    tc += 1
    print(tc)
    basename = '%02d' % tc if desc is None else '%02d-%s' % (tc, desc)
    if sample:
        filename = 'sample/%s.in' % basename
        outputfilename = 'sample/%s.ans' % basename
    else:
        filename = 'secret/%s.in' % basename
        outputfilename = 'secret/%s.ans' % basename

    n, m, h, grid = data
    with open(filename, 'w') as fout:
        print(n, m, h, file=fout)
        for row in grid:
            print(' '.join([str(x) for x in row]), file=fout)
    with open(outputfilename, 'w') as outf:
        with open(filename, 'r') as inf:
            subprocess.call(['./kevin.out'], stdin=inf, stdout=outf)


def prep():
    #samplepath = os.getcwd() + '/sample'
    secretpath = os.getcwd() + '/secret'
    #shutil.rmtree(samplepath, True)
    shutil.rmtree(secretpath, True)
    #os.mkdir(samplepath)
    os.mkdir(secretpath)
    time.sleep(1)
    subprocess.call(['g++', '-std=c++17', '-O3', '-o', 'kevin.out', '../submissions/accepted/kevinl.cpp'])


def gen_grid(n, m, h):
    grid = [[0 for _ in range(m)] for _ in range(n)]
    for i in range(n):
        for j in range(m):
            grid[i][j] = randint(randint(1, h), h)
    grid[n // 2][m // 2] = 0
    return (n, m, h, grid)


def main():
    global tc
    prep()
    tc = 0
    for _ in range(5):
        writeTestCase(gen_grid(randint(10, 20), randint(10, 20), randint(100, 500)))
    for _ in range(15):
        writeTestCase(gen_grid(randint(150, 200), randint(150, 200), randint(2000, 2500)))
    for _ in range(2):
        writeTestCase(gen_grid(200, 200, 2500))
    
if __name__ == '__main__':
    main()
