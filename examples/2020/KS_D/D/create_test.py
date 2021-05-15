#!/usr/bin/env python3

import numpy as np

ri = np.random.randint
rf = np.random.rand

N = 1000
Q = 1000

Di = np.arange(N - 1) + 1
Di = Di[np.random.permutation(N - 1)]
Si = np.random.randint(1, N + 1, size=Q)
Ki = np.random.randint(1, N + 1, size=Q)

print(N, Q)
print(" ".join(map(str, Di.tolist())))
for s, k in zip(Si, Ki):
    print(s, k)
