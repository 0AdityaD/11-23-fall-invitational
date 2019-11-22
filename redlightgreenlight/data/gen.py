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

    n, t, edges = data
    with open(filename, 'w') as fout:
        print(n, len(edges), t, file=fout)
        for u, v, l, g, r, ti in edges:
            print(u, v, l, g, r, ti, file=fout)
    with open(outputfilename, 'w') as outf:
        with open(filename, 'r') as inf:
            subprocess.call(['./kevin.out'], stdin=inf, stdout=outf)


def prep():
    samplepath = os.getcwd() + '/sample'
    secretpath = os.getcwd() + '/secret'
    shutil.rmtree(samplepath, True)
    shutil.rmtree(secretpath, True)
    os.mkdir(samplepath)
    os.mkdir(secretpath)
    time.sleep(1)
    subprocess.call(['g++', '-std=c++17', '-O3', '-o', 'kevin.out', '../submissions/accepted/kevin.cpp'])


def gen_graph(n, m, lmin, lmax, gmin, gmax):
    # first guarantee a path from 1 to N
    path = list(random.sample(range(2, n), min(m // 2, n - 3)))
    path = [1] + path + [n]
    edges = []
    seen = set()
    for i in range(len(path) - 1):
        u, v = path[i], path[i + 1]
        l = randint(lmin, lmax)
        g, r = randint(gmin, gmax), randint(gmin, gmax)
        t = randint(0, r)
        edges.append((u, v, l, g, r, t))
        seen.add((u, v))
    while len(edges) < m:
        u, v = randint(1, n), randint(1, n)
        if (u, v) in seen or u == v:
            continue
        l = randint(lmin, lmax)
        g, r = randint(gmin, gmax), randint(gmin, gmax)
        t = randint(0, r)
        edges.append((u, v, l, g, r, t))
        seen.add((u, v))
    return n, edges


def gen_linked_list(n, m, lmin, lmax, gmin, gmax):
    edges = []
    for i in range(1, n):
        u, v = i, i + 1
        l = randint(lmin, lmax)
        g, r = randint(gmin, gmax), randint(gmin, gmax)
        t = randint(0, r)
        edges.append((u, v, l, g, r, t))
    return n, edges


def gen_linked_list_with_edge():
    n = 50000
    edges = []
    for i in range(1, n):
        u, v = i, i + 1
        l = 1
        g, r = 10000, 1
        t = 0
        edges.append((u, v, l, g, r, t))
    edges.append((1, n, 100000, 1, 10000, 10000))
    return n, edges


def sample1():
    n, t = 4, 12
    edges = [(1, 2, 4, 1, 1, 0), (1, 3, 6, 2, 2, 1), (2, 4, 8, 3, 4, 2), (3, 4, 4, 4, 6, 3)]
    return n, t, edges


def main():
    global tc
    prep()
    writeTestCase(sample1(), True)
    tc = 0
    # generate small, dense random graphs
    for _ in range(3):
        n, edges = gen_graph(100, 1000, 10, 100, 1, 10)
        t = randint(10, 100)
        writeTestCase((n, t, edges))
    # generate large, dense random graphs
    for _ in range(6):
        n, edges = gen_graph(10000, 50000, 100000, 1000000, 100, 10000)
        t = randint(1000000, 1000000000)
        writeTestCase((n, t, edges))
    # generate large, sparse random graphs
    for _ in range(3):
        n, edges = gen_graph(45000, 50000, 100000, 1000000, 100, 10000)
        t = randint(1000000, 1000000000)
        writeTestCase((n, t, edges))
    # generate linkedlist
    n, edges = gen_linked_list(50000, -1, 100000, 1000000, 100, 10000)
    t = randint(1000000, 1000000000)
    writeTestCase((n, t, edges), desc='linkedlist')
    # generate linkedlist with edge from 1 to n
    n, edges = gen_linked_list_with_edge()
    t = randint(1000000, 1000000000)
    writeTestCase((n, t, edges), desc='linkedlist_edge')


if __name__ == '__main__':
    main()
