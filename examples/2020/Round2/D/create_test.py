#!/usr/bin/env python3

import numpy as np

K = 20
Q = 3
print(K, Q)
br = K // 2

P = ""
level = 0
open = 0
while len(P) < K:
    if level == 0:
        P += "("
        level += 1
        open += 1
    elif open == br:
        P += ")"
        level -= 1
    else:
        P += "()"[np.random.randint(2)]
        if P[-1] == "(":
            level += 1
            open += 1
        else:
            level -= 1
assert open == br
assert level == 0
print(P)
print(" ".join(map(str, np.random.randint(1, 1000001, [K]))))
print(" ".join(map(str, np.random.randint(1, 1000001, [K]))))
print(" ".join(map(str, np.random.randint(1, 1000001, [K]))))
print(" ".join(map(str, np.random.randint(1, K + 1, [Q]))))
print(" ".join(map(str, np.random.randint(1, K + 1, [Q]))))
