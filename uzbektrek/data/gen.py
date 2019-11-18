#! /usr/bin/python3
import random
import os
import shutil
import subprocess
import time
import zipfile


random.seed(123123)
tc = 0


def writeTestCase(N, P):
    global tc
    tc += 1
    print(tc)
    filename = 'secret/%02d.in' % tc
    with open(filename, 'w') as fout:
        print(N, P, file=fout)
    with open('secret/%02d.ans' % tc, 'w') as outf:
        with open(filename, 'r') as inf:
            subprocess.call(['./aditya.out'],
                            stdin=inf, stdout=outf)


def prep():
    path = os.getcwd() + '/secret'
    assert 'uzbektrek/data/'
    shutil.rmtree(path, True)
    os.mkdir(path)
    time.sleep(1)
    subprocess.call(['g++', '-std=c++17', '-O3', '-o', 'aditya.out', '../submissions/accepted/aditya.cpp'])

def randGenSmall():
    N = random.randint(1000000, 10000000)
    P = random.randint(100, 200)
    return (N, P)


def randGenBig():
    N = random.randint(100000000, 1000000000)
    P = random.randint(100, 200)
    return (N, P)


def main():
    global tc
    prep()
    for i in range(20):
        writeTestCase(*randGenSmall())
    for i in range(20):
        writeTestCase(*randGenBig())


if __name__ == '__main__':
    main()
