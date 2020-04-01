#!/usr/bin/env python3

FLAGS = set()
# FLAGS.add("DEFAULT_VAL")  #remove comm, to activate default value trigger
FLAGS.add("IA_MODE")  # remove comm, to activate interactive problem mode
ERROR_WORD = "IMPOSSIBLE"
IA_ERROR_CODE = -1

# The maintained and empty code template can be found at:
# https://github.com/DavidS3141/CodeJamTemplate
# #region template code
import functools as ft  # noqa: E402,F401
import itertools as it  # noqa: E402,F401
import numpy as np  # noqa: E402,F401
import scipy as sp  # noqa: E402,F401
import sys  # noqa: E402,F401
from math import factorial as fac  # noqa: E402,F401
import math  # noqa: E402,F401

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


def lassert(*args):
    pass


"""
m4 macro expansions
define(`lpdb', `ifdef(`PDB',`local_pdb($@)',`pass')')# define(`lpdb', `ifdef(`PDB',`local_pdb($@)',`pass')')
define(`llog', `ifdef(`LOCAL',`local_log($@)',`pass')')# define(`llog', `ifdef(`LOCAL',`local_log($@)',`pass')')
define(`lassert', `ifdef(`LOCAL',`local_assert($@)',`pass')')# define(`lassert', `ifdef(`LOCAL',`local_assert($@)',`pass')')
undefine(`eval')# undefine(`eval')
undefine(`len')# undefine(`len')
undefine(`index')# undefine(`index')
undefine(`substr')# undefine(`substr')
"""


def local_pdb():
    sys.stdin.readlines()
    sys.stdin = open("/dev/tty")
    import pdb

    pdb.set_trace()


def local_log(*args):
    cerr(*list(map(str, args)))


def local_assert(*args):
    if not args[0]:
        llog(args[1:])
        lpdb()


# #endregion debugTools

# #region parseTools
# TODO add documentation


def convert_input(val):
    try:
        result = eval(val)
        assert type(result) in [float, int]
    except (NameError, SyntaxError):
        result = val
    return result


def cin():
    if len(cin.cached_vals) > 0:
        val = cin.cached_vals[0]
        del cin.cached_vals[0]
        return val
    else:
        v = input()
        v = v.strip().split(" ")
        cin.cached_vals = list(convert_input(val) for val in v)
        return cin()


cin.cached_vals = []


def cint():
    v = input()
    v = v.strip().split(" ")
    return tuple(convert_input(val) for val in v)


def cinl():
    v = input()
    v = v.strip().split(" ")
    try:
        v = list(map(int, v))
        return v
    except Exception:
        pass
    try:
        v = list(map(float, v))
        return v
    except Exception:
        pass
    return v


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


def gss(f, a, b, tol=1e-5, c=None, d=None, fc=None, fd=None):
    """ Golden section search, recursive.

    Given a function f with a single local minimum in
    the interval [a,b], gss returns a subset interval
    [c,d] that contains the minimum with d-c <= tol.

    Example:
    >>> f = lambda x: (x-2)**2
    >>> a = 1
    >>> b = 5
    >>> tol = 1e-5
    >>> (c,d) = gss(f, a, b, tol)
    >>> print (c, d)
    1.9999959837979107 2.0000050911830893
    """

    (a, b) = (min(a, b), max(a, b))
    h = b - a
    t = type(h)
    if c is None:
        c = t(a + INV_PHI2 * h)
    if d is None:
        d = t(a + INV_PHI * h)
    if fc is None:
        fc = f(c)
    if fd is None:
        fd = f(d)
    if h <= tol:
        if fc < fd:
            return (a, c, b)
        else:
            return (a, d, b)
    if fc < fd:
        return gss(f, a, d, tol, c=None, fc=None, d=c, fd=fc)
    else:
        return gss(f, c, b, tol, c=d, fc=fd, d=None, fd=None)


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
        # read input
        readInput()
        # calc result
        calcFunction()
        if "IA_MODE" not in FLAGS:
            # write output
            cout("Case #%d: " % test_id, end=False)
            cerr("Case #%d: " % test_id, end=False)
            if "DEFAULT_VAL" not in FLAGS:
                cout(result)
                cerr(result)
            if "DEFAULT_VAL" in FLAGS:
                if len(result) > 0:
                    cout(len(result))
                    cerr(len(result))
                    for s in result:
                        cout(s)
                        cerr(s)
                else:
                    errorWord = ERROR_WORD
                    cout(errorWord)
                    cerr(errorWord)


# #endregion main

# #endregion template code


def init():
    global result, N, m
    N = get_in()
    m = get_in()


def readInput():
    global result


def ask(p):
    ps = [p] * 18
    out(" ".join(map(str, ps)))
    sum = 0
    for i in range(18):
        sum += get_in()
    return sum % p


#  write to result
def calcFunction():
    global result, N, m
    lassert(N >= 7, "N was smaller than 7")
    p = [17, 16, 13, 11, 9, 7, 5]
    ans = []
    for i in range(7):
        ans.append(ask(p[i]))
    out(crt(ans, p))
    get_in()


if __name__ == "__main__":
    main()
