#!/usr/bin/env python3

import numpy as np

ri = np.random.randint
rf = np.random.rand

K = ri(1, 11)
Ai = [str(ri(1, 1000001)) for _ in range(K)]
print(K)
print(" ".join(Ai))
