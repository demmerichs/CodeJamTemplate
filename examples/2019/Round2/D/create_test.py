#!/usr/bin/env python3

import numpy as np

M = np.random.randint(2, 11)
maxG = 10
zero_G_prob = np.random.rand()

print(M)
for i in range(1, M + 1):
    a = np.random.randint(1, M + 1)
    b = np.random.randint(1, M + 1)
    while b == a:
        b = np.random.randint(1, M + 1)
    print("%d %d" % tuple(sorted((a, b))))
Gi = []
for _ in range(M):
    b = np.random.randint(1, maxG + 1)
    b *= np.random.rand() > zero_G_prob
    Gi.append(str(b))
print(" ".join(Gi))
