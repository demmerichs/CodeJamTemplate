#!/usr/bin/env python3

import numpy as np
import sys

ri = np.random.randint
rf = np.random.rand

print(1)
print("printed nbr test cases", file=sys.stderr)
print(10, 50)

edges = []
n = int(input())
for i in range(2 * n):
    a, b = map(int, input().split())
    edges.append((a, b))

perm = np.random.permutation(n)
print("permutation", perm, file=sys.stderr)
print(n)
for e in edges:
    a = perm[e[0] - 1] + 1
    b = perm[e[1] - 1] + 1
    print(a, b)
ans_perm = list(map(int, input().split()))
assert len(ans_perm) == n
assert np.all(np.array(ans_perm) - 1 == perm)
# assert np.all(np.array(ans_perm) - 2 == perm)
print(ans_perm, file=sys.stderr)
print(perm, file=sys.stderr)
