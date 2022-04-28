#!/usr/bin/env python3

import numpy as np
import itertools as it
from fractions import Fraction

ri = np.random.randint  # produces random numbers from [l, r)
rf = np.random.rand
perm = np.random.permutation

mags = [2**0, 2**1, 2**3, 2**7, 2**15, 2**31]

Apos = [False, True]
Bpos = [False, True]
Apmag = mags
Aqmag = mags
Bpmag = mags
Bqmag = mags
repeats = 20

values = list(it.product(Apos, Bpos, Apmag, Aqmag, Bpmag, Bqmag))

with open('sample.txt', 'w') as fsample:
    with open('result.txt', 'w') as fresult:
        fsample.write('%d\n' % (len(values) * repeats))
        for t, (apos, bpos, apmag, aqmag, bpmag, bqmag) in enumerate(values):
            for r in range(repeats):
                ap = ri(0, apmag)
                aq = ri(1, 1 + aqmag)
                if not apos:
                    ap *= -1
                bp = ri(0, bpmag)
                bq = ri(1, 1 + bqmag)
                if not bpos:
                    bp *= -1

                a = Fraction(ap, aq)
                b = Fraction(bp, bq)
                ans = a + b

                fsample.write('%d %d %d %d\n' % (ap, aq, bp, bq))
                fresult.write('Case #%d: %d/%d\n' % (t*repeats + r + 1, ans.numerator, ans.denominator))
