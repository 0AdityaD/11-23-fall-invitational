import random
import os
import shutil
import subprocess
import time
import zipfile


random.seed(12383)
tc = 0

def writeTestCase(data, sample=False):
    global tc
    tc += 1
    print(tc)
    if sample:
        filename = 'sample/%02d.in' % tc
        outputfilename = 'sample/%02d.ans' % tc
    else:
        filename = 'secret/%02d.in' % tc
        outputfilename = 'secret/%02d.ans' % tc

    with open(filename, 'w') as fout:
        print(data, file=fout)
    with open(outputfilename, 'w') as outf:
        with open(filename, 'r') as inf:
            subprocess.call(['./aditya.out'],
                            stdin=inf, stdout=outf)


def prep():
    samplepath = os.getcwd() + '/sample'
    secretpath = os.getcwd() + '/secret'
    shutil.rmtree(samplepath, True)
    shutil.rmtree(secretpath, True)
    os.mkdir(samplepath)
    os.mkdir(secretpath)
    time.sleep(1)
    subprocess.call(['g++', '-std=c++17', '-O3', '-o', 'aditya.out', '../submissions/accepted/aditya.cpp'])


def sample1():
    return 1


def sample2():
    return 2


def main():
    global tc
    prep()
    writeTestCase(1, True)
    writeTestCase(2, True)

    tc = 0
    writeTestCase(0, False)
    for i in [10, 100, 1000]:
        writeTestCase(i, False)
    for _ in range(20):
        writeTestCase(random.randint(45000, 50000), False)



if __name__ == '__main__':
    main()
