#!/usr/bin/env python3

import numpy as np

ri = np.random.randint  # produces random numbers from [l, r)
rf = np.random.rand
perm = np.random.permutation

E = 100
W = 100
for e in range(E):
    numbers = ri(0, 101, size=W).tolist()
    print(' '.join(map(str, numbers)))