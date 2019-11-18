import random
import os
import shutil
import subprocess
import time
import zipfile
import string

random.seed(23891)
tc = 2 

class Node:
    def __init__(self, n):
        self.name = n
        self.adj = []

def genGraph(sz):
    nodes = []
    gen = {}

    for i in range(sz):
        s = ''.join(random.choices(string.ascii_uppercase, k=4))
        while s in gen:
            s = ''.join(random.choices(string.ascii_uppercase, k=4))

        gen[s] = True
        nodes.append(Node(s))

    for i in range(sz):
        ri = random.randint(0, min(sz - i - 1, 10))
        edges = random.sample(range(i + 1, sz), ri)
        for e in edges:
            nodes[i].adj.append(e)

    return nodes

def writeTestCase(data, sample):
    global tc
    tc += 1
    print(tc)
    if sample:
        filename = 'data/sample/%02d.in' % tc
        outputfilename = 'data/sample/%02d.ans' % tc
    else:
        filename = 'data/secret/%02d.in' % tc
        outputfilename = 'data/secret/%02d.ans' % tc

    with open(filename, 'w') as fout:
        sz = len(data)
        sub = 0
        vis = [False for i in range(sz)]

        for datum in data:
            if len(datum.adj) == 0:
               sub += 1

        print(sz - sub, file=fout)
        order = [i for i in range(0, sz)]
        random.shuffle(order)

        for i in order:
            if len(data[i].adj) > 0:
                vis[i] = True
                print(f'{data[i].name} {len(data[i].adj)}', file=fout)
                for j in data[i].adj:
                    vis[j] = True
                    print(f'{random.randint(1, 10)} {data[j].name}', file=fout)
        
        desIndex = random.randint(0, sz - 1)
        while not vis[desIndex]:
            desIndex = random.randint(0, sz - 1)

        des = data[desIndex]
        print(des.name, file=fout)
        
    with open(outputfilename, 'w') as outf:
        with open(filename, 'r') as inf:
            subprocess.call(['java', 'ChemicalEquation'],
                            stdin=inf, stdout=outf)


def prep():
    inpath = os.getcwd() + '/data'
    shutil.rmtree(inpath, True)
    os.mkdir(inpath)
    os.mkdir(inpath + '/sample')
    os.mkdir(inpath + '/secret')
    subprocess.call(['javac', 'ChemicalEquation.java'])
    time.sleep(1)

def main():
    global tc
    prep()

    for i in range(0, 5):
        writeTestCase(genGraph(5), False)

    for i in range(0, 10):
        writeTestCase(genGraph(12), False)

    for i in range(0, 20):
        writeTestCase(genGraph(1000), False)


if __name__ == '__main__':
    main()
