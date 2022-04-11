#!/usr/bin/env python3

import numpy as np
import itertools as it

ri = np.random.randint  # produces random numbers from [l, r)
rf = np.random.rand
perm = np.random.permutation


def bigri(bits):
    if bits % 32:
        morebits = (bits // 32 + 1) * 32
        result = bigri(morebits)
        excessbits = morebits - bits
        return result >> excessbits

    result = 0
    while bits > 0:
        newbits = ri(0, 1 << 32)
        result <<= 32
        result += newbits
        bits -= 32
    assert bits == 0
    return result


bits = [0, 1, 2, 3, 30, 31, 32, 33, 34, 35, 60, 61, 62, 63, 64, 65, 66, 67, 68, 94, 95, 96, 97, 98, 99, 125, 126, 127, 128, 129, 130, 131, 256]

with open('sample.txt', 'w') as fsample:
    with open('result.txt', 'w') as fresult:
        fsample.write('%d\n' % (64 * len(bits)**2))
        for tA, bA in enumerate(bits):
            As = [1 << bA, (1 << bA) + 1, (1 << bA) - 1, bigri(bA)]
            As += [-a for a in As]
            for tB, bB in enumerate(bits):
                Bs = [1 << bB, (1 << bB) + 1, (1 << bB) - 1, bigri(bB) + 1]
                Bs += [-b for b in Bs]
                for ti, (a, b) in enumerate(it.product(As, Bs)):
                    t = tA * len(bits) + tB
                    t *= 64
                    t += ti + 1
                    fsample.write('%d %d\n' % (a, b))
                    fresult.write('Case #%d: %d\n' % (t, a - b))
