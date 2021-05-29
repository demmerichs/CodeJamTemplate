#!/usr/bin/env python3

import numpy as np

ri = np.random.randint  # produces random numbers from [l, r)
rf = np.random.rand
perm = np.random.permutation

print(ri(3, 1000001))
# for i in range(3, 1001):
#     print(i)
