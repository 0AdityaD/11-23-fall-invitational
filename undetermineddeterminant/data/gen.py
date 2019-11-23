import random
import os
import shutil
import subprocess
import time
import zipfile


random.seed(1337)
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
        print('\n'.join(data), file=fout)
    with open(outputfilename, 'w') as outf:
        with open(filename, 'r') as inf:
            subprocess.call(['python3', '../submissions/accepted/ethan.py'],
                            stdin=inf, stdout=outf)


def prep():
    samplepath = os.getcwd() + '/sample'
    secretpath = os.getcwd() + '/secret'
    shutil.rmtree(samplepath, True)
    shutil.rmtree(secretpath, True)
    os.mkdir(samplepath)
    os.mkdir(secretpath)
    time.sleep(1)


def sample1():
    data = ['1']
    return data


def sample2():
    data = ['2']
    return data

def main():
    global tc
    prep()
    writeTestCase(sample1(), True)
    writeTestCase(sample2(), True)

    tc = 0
    for _ in range(3):
        writeTestCase([str(random.randint(1, 1000))], False)
    for _ in range(24):
        writeTestCase([str(random.randint(1001, 1000000))], False)
    writeTestCase(['1000000'], False)
    writeTestCase(['999999'], False)
    writeTestCase(['999998'], False)
    

if __name__ == '__main__':
    main()
