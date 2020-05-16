#!/usr/bin/env python3

import numpy as np

R = np.random.randint(1, 101)
C = np.random.randint(1, 100 // R + 1)
lovers = list(range(2 * (R + C)))
# lovers = np.random.permutation(lovers)
permuted_lovers = []
while len(lovers):
    i = np.random.randint(len(lovers) - 1)
    permuted_lovers += lovers[i : i + 2]
    lovers = lovers[i + 2 :] + lovers[:i]
print(R, C)
print(" ".join(map(str, permuted_lovers)))
