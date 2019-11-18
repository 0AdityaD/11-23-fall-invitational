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
        print(len(data), file=fout)
        print('\n'.join(data), file=fout)
    with open(outputfilename, 'w') as outf:
        with open(filename, 'r') as inf:
            subprocess.call(['python3', '../submissions/accepted/kevin.py'],
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
    # violation of two touch rule
    data = ['A1M', 'A1M', 'B5W']
    return data


def sample2():
    # violation of gender rule
    data = ['A1M', 'A2M', 'B2M']
    return data


def sample3():
    # no violation
    data = ['A4W', 'A5W', 'A1M', 'B3M', 'A2M']
    return data


players = ['A1M', 'A2M', 'A3W', 'A4M', 'A5W', 'A6W', 'B1W', 'B2M', 'B3W', 'B4M', 'B5W', 'B6M']


def is_valid(player, sequence):
    if len(sequence) == 0:
        return True
    if player == sequence[-1]:
        return False
    if len(sequence) >= 3 and player[0] == sequence[-1][0] == sequence[-2][0] == sequence[-3][0]:
        return False
    if (len(sequence) >= 2 and sequence[-1][0] == sequence[-2][0] and sequence[-1][2] == sequence[-2][2] and
            (player[0] != sequence[-1][0] and (len(sequence) == 2 or sequence[-3][0] != sequence[-2][0])  or
            player[0] == sequence[-1][0] and player[2] == sequence[-1][2])):
        return False
    return True


def gen_valid_sequence(n, sequence):
    # extend sequence of hits with n hits with no violations
    while len(sequence) < n:
        sequence.append(random.choice([player for player in players if is_valid(player, sequence)]))
    return sequence


def gen_invalid_sequence(n, sequence):
    # sequence will be slightly longer than length n
    sequence = gen_valid_sequence(n, sequence)
    sequence.append(random.choice([player for player in players if not is_valid(player, sequence)]))
    return sequence


def gen_double_touch_violation(sequence):
    sequence.append(sequence[-1])
    return sequence


def gen_four_touch_violation(sequence):
    if sequence[-1][0] == 'A':
        sequence.extend(list(random.sample(players[6:], 4)))
    else:
        sequence.extend(list(random.sample(players[:6], 4)))
    return sequence


def main():
    global tc
    prep()
    writeTestCase(sample1(), True)
    writeTestCase(sample2(), True)
    writeTestCase(sample3(), True)

    tc = 0
    # test violation of four touches rule
    writeTestCase(['B1W', 'A1M', 'A2M', 'A3W', 'A4M'], False)
    # test violation of gender rule at end of rally
    writeTestCase(['B1W', 'A1M', 'A2M'], False)
    # test two violations
    writeTestCase(['A1M', 'A1M', 'B1W', 'B2M', 'B3W', 'B4M'])
    writeTestCase(['A1M', 'A4W', 'A1M', 'B1W', 'B3W', 'A3M', 'A3M'])
    writeTestCase(['A1M', 'A2M', 'A3M', 'A4W', 'B1W', 'B3W', 'A1M'])
    # generate long sequences with no violations
    for _ in range(3):
        writeTestCase(gen_valid_sequence(100000, []), False)
    # generate long sequences with violations at the end
    writeTestCase(gen_double_touch_violation(gen_valid_sequence(90000, [])), False)
    writeTestCase(gen_four_touch_violation(gen_valid_sequence(90000, [])), False)
    writeTestCase(
        gen_four_touch_violation(gen_four_touch_violation(gen_valid_sequence(90000, []))),
        False,
    )
    # generate long sequences with violations
    for _ in range(5):
        sequence = gen_invalid_sequence(95000, [])
        for i in range(10):
            sequence = gen_valid_sequence(100, sequence)
            sequence = gen_invalid_sequence(0, sequence)
        writeTestCase(sequence)


if __name__ == '__main__':
    main()
