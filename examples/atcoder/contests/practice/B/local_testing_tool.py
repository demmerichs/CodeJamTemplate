import numpy as np
import sys

if int(sys.argv[1]) >= 10:
    quit()

merge_insert_worst_case_Q = [0, 1, 3, 5, 7, 10, 13, 16, 19, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 71, 76, 81, 86, 91, 96, 101, 106, 111, 116, 121, 126, 131, 136, 141, 146, 151, 156, 161, 166, 171, 177, 183, 189, 195, 201, 207, 213, 219, 225, 231, 237, 243, 249, 255]

N = np.random.randint(1, 27)
Q = merge_insert_worst_case_Q[N - 1]

gt = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ'[:N])
np.random.shuffle(gt)
gt = ''.join(gt)
print(N, Q, flush=True)

while True:
    qora = input().split()

    if qora[0] == '?':
        assert Q > 0
        Q -= 1
        assert len(qora) == 3, qora
        a = qora[1]
        b = qora[2]
        assert a != b, qora
        if gt.index(a) > gt.index(b):
            print(">", flush=True)
            continue
        else:
            print("<", flush=True)
            continue

    else:
        assert qora[0] == '!', qora
        assert len(qora) == 2, qora
        assert qora[1] == gt, (qora, gt)
        break
