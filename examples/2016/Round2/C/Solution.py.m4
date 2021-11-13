#!/usr/bin/env python3

FLAGS = set()
FLAGS.add("DEFAULT_VAL_MODE")  # remove comm, to activate default value trigger
DEFAULT_VAL_TRIGGER = lambda result: result is None  # noqa: E731
DEFAULT_VAL = "\nIMPOSSIBLE"
# FLAGS.add("IA_MODE")  # remove comm, to activate interactive problem mode
IA_ERROR_CODE = "ERROR"

# The maintained and empty code template can be found at:
# https://github.com/demmerichs/CodeJamTemplate
# #region template code
import functools as ft  # noqa: E402,F401
import itertools as it  # noqa: E402,F401
import math  # noqa: E402,F401
import sys  # noqa: E402,F401
import time  # noqa: E402,F401
from fractions import Fraction  # noqa: E402,F401
from math import factorial as fac  # noqa: E402,F401

import numpy as np  # noqa: E402,F401
import scipy as sp  # noqa: E402,F401

# #region abbr

# #region types
ld = np.float128
v = np.array
# #endregion types
# #region constants: INF, EPS, PI, MOD
INF = 2 ** 64 - 1
EPS = ld(1e-15)
PI = ld("3.14159265358979323846264338328")
MOD = 1000000007
DIRECTIONS = [v([1, 0]), v([0, 1]), v([-1, 0]), v([0, -1])]
DIR_NAMES = "ENWS"
INV_PHI = (np.sqrt(ld(5)) - 1) / 2  # 1 / phi
INV_PHI2 = (3 - np.sqrt(ld(5))) / 2  # 1 / phi^2
# #endregion constants

# #endregion abbr

# #region printerTools


def to_str(val, precision=10):
    local_to_str = ft.partial(to_str, precision=precision)
    if isinstance(val, (list, tuple, np.ndarray)):
        return " ".join(map(local_to_str, val))
    if isinstance(val, np.float):
        return ("%%.%df" % precision) % val
    return str(val)


def cout(*args, end=True, error=False):
    kwargs = dict()
    precision = 10
    if not end:
        kwargs["end"] = ""
    if error:
        kwargs["file"] = sys.stderr
        precision = 4
    local_to_str = ft.partial(to_str, precision=precision)
    s = "".join(map(local_to_str, args))
    print(s, **kwargs)


def cerr(*args, **kwargs):
    kwargs["error"] = True
    cout(*args, **kwargs)


# #endregion printerTools

# #region debugTools


# the following definitions are just for the linter to be satiesfied
# as it cannot detect the m4 macro expansions
def lpdb():
    pass


def llog(*args):
    pass


def lg(var):
    pass


def lassert(*args):
    pass


def start_timer():
    pass


def stop_timer():
    pass


def get_time():
    pass


"""
m4 macro expansions
define(`start_timer', `ifdef(`LOCAL',`local_start_timer($@)',`pass')')# define(`start_timer', `ifdef(`LOCAL',`local_start_timer($@)',`pass')')
define(`stop_timer', `ifdef(`LOCAL',`local_stop_timer($@)',`pass')')# define(`stop_timer', `ifdef(`LOCAL',`local_stop_timer($@)',`pass')')
define(`get_time', `ifdef(`LOCAL',`local_get_time($@)',`pass')')# define(`get_time', `ifdef(`LOCAL',`local_get_time($@)',`pass')')
define(`lpdb', `ifdef(`PDB',`local_pdb($@)',`pass')')# define(`lpdb', `ifdef(`PDB',`local_pdb($@)',`pass')')
define(`llog', `ifdef(`LOCAL',`local_log($@)',`pass')')# define(`llog', `ifdef(`LOCAL',`local_log($@)',`pass')')
define(`lg', `ifdef(`LOCAL',`local_log("$@", $@)',`pass')')# define(`lg', `ifdef(`LOCAL',`local_log("$@", $@)',`pass')')
define(`lassert', `ifdef(`LOCAL',`local_assert($@)',`pass')')# define(`lassert', `ifdef(`LOCAL',`local_assert($@)',`pass')')
undefine(`__file__',`__gnu__',`__line__',`__os2__',`__program__',`__unix__',`__windows__',`argn',`array',`array_set',`builtin',`capitalize',`changecom',`changequote',`changeword',`cleardivert',`cond',`copy',`curry',`debugfile',`debugmode',`decr',`define',`define_blind',`defn',`divert',`divnum',`dnl',`downcase',`dquote',`dquote_elt',`dumpdef',`errprint',`esyscmd',`eval',`example',`exch',`fatal_error',`foreach',`foreachq',`forloop',`format',`ifelse',`include',`incr',`index',`indir',`join',`joinall',`len',`m4exit',`m4wrap',`maketemp',`mkstemp',`nargs',`os2',`patsubst',`popdef',`pushdef',`quote',`regexp',`rename',`reverse',`shift',`sinclude',`stack_foreach',`stack_foreach_lifo',`stack_foreach_sep',`stack_foreach_sep_lifo',`substr',`syscmd',`sysval',`traceoff',`traceon',`translit',`undefine',`undivert',`unix',`upcase',`windows')# undefine(`__file__',`__gnu__',`__line__',`__os2__',`__program__',`__unix__',`__windows__',`argn',`array',`array_set',`builtin',`capitalize',`changecom',`changequote',`changeword',`cleardivert',`cond',`copy',`curry',`debugfile',`debugmode',`decr',`define',`define_blind',`defn',`divert',`divnum',`dnl',`downcase',`dquote',`dquote_elt',`dumpdef',`errprint',`esyscmd',`eval',`example',`exch',`fatal_error',`foreach',`foreachq',`forloop',`format',`ifelse',`include',`incr',`index',`indir',`join',`joinall',`len',`m4exit',`m4wrap',`maketemp',`mkstemp',`nargs',`os2',`patsubst',`popdef',`pushdef',`quote',`regexp',`rename',`reverse',`shift',`sinclude',`stack_foreach',`stack_foreach_lifo',`stack_foreach_sep',`stack_foreach_sep_lifo',`substr',`syscmd',`sysval',`traceoff',`traceon',`translit',`undefine',`undivert',`unix',`upcase',`windows')
"""


def local_start_timer():
    global start
    start = time.time()


def local_stop_timer():
    global stop
    stop = time.time()


def local_get_time():
    global start, stop
    return stop - start


def local_pdb():
    sys.stdin.readlines()
    sys.stdin = open("/dev/tty")
    import pdb

    pdb.set_trace()


def local_log(*args):
    cerr("\t".join(map(str, args)))


def local_assert(*args):
    if not args[0]:
        llog(args[1:])
        lpdb()


# #endregion debugTools

# #region parseTools
# TODO add documentation


def convert_input(val):
    try:
        return int(val)
    except ValueError:
        pass
    try:
        return float(val)
    except ValueError:
        pass
    return val


def cin(n=None):
    k = 1 if n is None else n
    if len(cin.cached_vals) >= k:
        val = cin.cached_vals[:k]
        del cin.cached_vals[:k]
        if n is None:
            return val[0]
        return val
    else:
        v = input()
        v = v.strip().split(" ")
        cin.cached_vals += list(map(convert_input, v))
        return cin(n)


cin.cached_vals = []


# #endregion parseTools

# #region mathTools
# TODO add documentation for operators and euclideanAlgo
# faculty (facll, facmod and facld)  IMPORTANT: facll works only for n<=20
# choose (choosell, choosemod and chooseld)
# power on integers (powll and powmod)
# log2 on integers (log2ll)
# ceill(p,q)/floorll (returns ceil(p/q)/floorll(p/q) for integers)
def facmod(n):
    if n > 0:
        return (n * facmod(n - 1)) % MOD
    return 1


def choosell(n, k):
    if k > n:
        return 0
    if n - k < k:
        return choosell(n, n - k)
    result = 1
    for i in range(k):
        result *= n - i
        result //= i + 1
    return result


def choosemod(n, k):
    if k > n:
        return 0
    if len(choosemod.memomrize) > n:
        if len(choosemod.memorize[n]) > k:
            return choosemod.memorize[n][k]
        else:
            choosemod(n, k - 1)
            choosemod.memorize[n].append(
                (choosemod(n - 1, k - 1) + choosemod(n - 1, k)) % MOD
            )
            return choosemod.memorize[n][k]
    else:
        while len(choosemod.memorize) <= n:
            choosemod.memorize.append([1])
        return choosemod(n, k)


choosemod.memorize = []


def chooseld(n, k):
    if k > n:
        return 0
    if n - k < k:
        return choosell(n, n - k)
    result = 1
    for i in range(k):
        result *= n - i
        result /= i + 1
    return result


def powmod(base, exp):
    if exp == 0:
        return 1
    elif exp & 1:
        return (powmod(base, exp - 1) * base) % MOD
    else:
        t = powmod(base, exp // 2)
        return (t * t) % MOD


def log2ll(n):
    assert n > 0
    if n == 1:
        return 0
    return 1 + log2ll(n >> 1)


# Implementation returns the values corresponding values for a, b
# a_in * a_out + b_in * b_out = gcd(a, b) (> 0, trivial solution =0 excluded)
def euclideanAlgo(a, b):
    # only process, a,b >= 0, a<=b; transform all other cases to this
    if a < 0:
        a = -a
        a, b = euclideanAlgo(a, b)
        a = -a
        return a, b
    if b < 0:
        b = -b
        a, b = euclideanAlgo(a, b)
        b = -b
        return a, b
    if a > b:
        b, a = euclideanAlgo(b, a)
        return a, b
    if a == 0:
        lassert(b >= 0, "euclideanAlgo: Logic error")
        lassert(b > 0, "euclideanAlgo: Both numbers are zero")
        b = 1
        return a, b
    s = b // a
    r = b - s * a
    r, a = euclideanAlgo(r, a)
    a = a - s * r
    b = r
    return a, b


def gcd(a, b):
    c, d = euclideanAlgo(a, b)
    return a * c + b * d


# chinese remainder theorem in application
def crt(remainders, moduli):
    lassert(
        len(remainders) == len(moduli),
        "Chinese remainder theorem: remainders and moduli must be of same size!",
    )
    idxs = np.argsort(moduli)[::-1]
    m = 1
    r = 0
    for idx in idxs:
        # solve a*m1 + b*m2 == 1
        cur_modulo = moduli[idx]
        cur_remainder = remainders[idx]
        a, b = euclideanAlgo(m, cur_modulo)
        # make sure, that m1 and m2 are indeed coprime
        lassert(
            a * m + b * cur_modulo == 1,
            "Chinese remainder theorem: euclidean algorithm delivered unexpected result! Are your factors coprime?",
        )
        # crt: find x == r1 (m1) and x == r2 (m2)
        # solved by x = r1 + (r2 - r1) * a * m1 == r2 + (r1 - r2) * b * m2
        # proof (for first expression): x == r1 (m1) trivial, x == r1 + (r2 - r1) * (a * m1 (m2)) == r1 + (r2 - r1) * 1 == r2 (m2)
        r = r + (cur_remainder - r) * a * m
        m *= cur_modulo
        r = (r % m + m) % m
    return r


# #endregion mathTools

# #region algoTools


def gss(
    f,
    a,
    b,
    *,
    upper=False,
    tol=1e-5,
    c=None,
    d=None,
    fa=None,
    fb=None,
    fc=None,
    fd=None
):
    """Golden section search, recursive.

    Given a strictly unimodal function f with an interval local minimum [c,d] in
    the interval [a,b], gss returns (depending on upper) a value pair x, y=f(x)
    with x being within tolerance of either the upper interval bound d or the lower c.
    """

    (a, b) = (min(a, b), max(a, b))
    fa = f(a) if fa is None else fa
    fb = f(b) if fb is None else fb
    h = b - a
    t = type(h)
    c = t(a + INV_PHI2 * h) if c is None else c
    if c == a:
        c += tol
        fc = None
    d = t(a + INV_PHI * h) if d is None else d
    if d == b:
        d -= tol
        fd = None
    fc = f(c) if fc is None else fc
    fd = f(d) if fd is None else fd
    if h < tol:
        return [(a, fa), (b, fb)][upper]

    if d < c:
        if fc < fd:
            return c, fc
        return d, fd

    m = min(fa, fb, fc, fd)
    if fa == m and fc > m and fd > m:
        return a, fa
    if fb == m and fc > m and fd > m:
        return b, fb

    if fc < fd or (not upper and fc == fd):
        return gss(f, a, d, upper=upper, tol=tol, fa=fa, fb=fd, d=c, fd=fc)
    return gss(f, c, b, upper=upper, tol=tol, fa=fc, fb=fb, c=d, fc=fd)


# #endregion algoTools

# #region main
if "IA_MODE" in FLAGS:

    def get_in():
        in_value = cin()
        if in_value == IA_ERROR_CODE:
            quit()
        llog("reading value:\t", in_value)
        return in_value

    def out(t):
        llog("sending output:\t", t)
        cout(t)


result = ""


def main():
    nbr_tests = cin()
    init()
    for test_id in range(1, 1 + nbr_tests):
        llog()
        llog()
        llog()
        llog()
        llog("`################################################'")
        llog("`################################################'")
        llog("`################################################'")
        llog("`################", test_id, "################'")
        llog("`################################################'")
        llog("`################################################'")
        llog("`################################################'")
        llog()
        llog("============      reading input     ============")
        start_timer()
        readInput()
        stop_timer()
        llog("-----------", get_time(), "secs -----------")
        llog()
        llog("============    doing computation   ============")
        start_timer()
        calcFunction()
        stop_timer()
        llog("-----------", get_time(), "secs -----------")
        llog()

        if "IA_MODE" not in FLAGS:
            # write output
            cout("Case #%d: " % test_id, end=False)
            if "DEFAULT_VAL_MODE" not in FLAGS:
                cout(result)
            if "DEFAULT_VAL_MODE" in FLAGS:
                if DEFAULT_VAL_TRIGGER(result):
                    llog("default val triggered")
                    cout(DEFAULT_VAL)
                else:
                    llog("default val NOT triggered")
                    cout(result)


# #endregion main

# #endregion template code


def init():
    global result


def readInput():
    global result, R, C, permutation
    R, C = cin(2)
    permutation = cin(2 * (R + C))


def get_start_position(lover):
    global R, C
    # Map from outer cell number to a direction facing into the maze
    # and the position of the outer cell
    # 0->downwards, 1->rightwards, 2->upwards, 3->leftwards
    #  W
    # S N
    #  E
    if lover <= C:
        return 0, v([-1, lover - 1])
    lover -= C
    if lover <= R:
        return 3, v([lover - 1, C])
    lover -= R
    if lover <= C:
        return 2, v([R, C - lover])
    lover -= C
    return 1, v([R - lover, -1])


#  write to result
def calcFunction():
    global result, R, C, permutation
    hedges = {0: "/", 1: "\\", 3: "/"}

    maze = np.zeros((R, C), dtype=np.uint8)
    size = 2 * (R + C)
    permutation = list(zip(permutation[::2], permutation[1::2]))
    permutation.sort(key=lambda ab: min((ab[1] - ab[0]) % size, (ab[0] - ab[1]) % size))
    for start, end in permutation:

        if (end - start) % size > R + C:
            start, end = end, start

        direction, pos = get_start_position(start)
        pos += DIRECTIONS[direction]

        while np.all(pos >= 0) and np.all(pos < v([R, C])):
            if maze[(*pos,)] == 0:
                maze[(*pos,)] = (direction & 1) * 2 + 1
            direction ^= maze[(*pos,)]
            pos += DIRECTIONS[direction]

        if not np.all(pos == get_start_position(end)[1:]):
            result = None
            return

    result = "\n" + "\n".join("".join(hedges[c] for c in row) for row in maze)


if __name__ == "__main__":
    main()
