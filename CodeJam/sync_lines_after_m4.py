#!/usr/bin/env python3

import sys

n = 0
for line in sys.stdin:
    n += 1
    if line[:5] == "#line":
        s = line.strip().split()
        assert len(s) == 2
        assert s[0] == "#line"
        c = int(s[1])
        sys.stdout.write("\n" * (c - n))
        n = c - 1
    else:
        sys.stdout.write(line)
