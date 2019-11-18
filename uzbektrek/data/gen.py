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
            subprocess.call(['python2', '../submissions/accepted/aditya_ac.py'],
                            stdin=inf, stdout=outf)


def prep():
    path = os.getcwd() + '/secret'
    assert 'uzbektrek/data/'
    shutil.rmtree(path, True)
    os.mkdir(path)
    time.sleep(1)


def randGen():
    N = random.randint(1000000, 10000000)
    P = random.randint(1, 100)
    return (N, P)


def main():
    global tc
    prep()
    for i in range(20):
        writeTestCase(*randGen())


if __name__ == '__main__':
    main()
