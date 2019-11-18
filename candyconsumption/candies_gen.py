import random
import os
import shutil
import subprocess
import time
import zipfile


random.seed(12383)
tc = 0

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
        print(data, file=fout)
    with open(outputfilename, 'w') as outf:
        with open(filename, 'r') as inf:
            subprocess.call(['java', 'Candies'],
                            stdin=inf, stdout=outf)


def prep():
    inpath = os.getcwd() + '/data'
    shutil.rmtree(inpath, True)
    os.mkdir(inpath)
    os.mkdir(inpath + '/sample')
    os.mkdir(inpath + '/secret')
    subprocess.call(['javac', 'Candies.java'])
    time.sleep(1)

def sample1():
    return 1

def sample2():
    return 2

def highCase1():
    return 1000000

def highCase2():
    return 999998

def main():
    global tc
    prep()
    writeTestCase(sample1(), True)
    writeTestCase(sample2(), True)

    numbers = random.sample(range(3, 20000), 10)
    for num in numbers:
        writeTestCase(num, False)

    numbers = random.sample(range(20001, 999997), 30)
    for num in numbers:
        writeTestCase(num, False)

    writeTestCase(highCase1(), False)
    writeTestCase(highCase2(), False)

if __name__ == '__main__':
    main()
