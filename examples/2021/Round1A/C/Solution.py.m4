#!/usr/bin/env python3

FLAGS = set()
# FLAGS.add("DEFAULT_VAL_MODE")  # remove comm, to activate default value trigger
DEFAULT_VAL_TRIGGER = lambda result: result is None  # noqa: E731
DEFAULT_VAL = "IMPOSSIBLE"
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
    global result, N, Q, Ai, Si
    N, Q = cin(2)
    Ai = []
    Si = []
    for _ in range(N):
        Ai.append(cin())
        Si.append(int(cin()))
    lg(Ai)
    lg(Si)


def invert(c):
    return "TF"[c == "T"]


#  write to result
def calcFunction():
    global result, N, Q, Ai, Si
    result = ["T" * Q, 0]
    if N == 1:
        result[0] = Ai[0]
        result[1] = str(Si[0]) + "/1"
        if Si[0] * 2 < Q:
            for q in range(Q):
                result[0] = result[0][:q] + invert(result[0][q]) + result[0][q + 1 :]
            result[1] = str(Q - Si[0]) + "/1"
    elif N == 2:
        expscore = 0
        diff = 0
        for q in range(Q):
            if Ai[0][q] != Ai[1][q]:
                diff += 1
        same = Q - diff
        score_on_same = (Si[0] + Si[1] - diff) // 2
        score_on_diff = (Si[0] - Si[1] + diff) // 2
        lg(diff)
        lg(score_on_diff)
        lg(same)
        lg(score_on_same)
        if score_on_diff * 2 < diff:
            result[0] = Ai[1]
            expscore += diff - score_on_diff
        else:
            result[0] = Ai[0]
            expscore += score_on_diff

        if score_on_same * 2 < same:
            for q in range(Q):
                if Ai[0][q] == Ai[1][q]:
                    result[0] = (
                        result[0][:q] + invert(result[0][q]) + result[0][q + 1 :]
                    )
            expscore += same - score_on_same
        else:
            expscore += score_on_same
        result[1] = str(expscore) + "/1"
    else:
        best_prob = Fraction(0, 1)
        ab = ""
        ac = ""
        bc = ""
        same = ""
        for q in range(Q):
            ab += " "
            ac += " "
            bc += " "
            same += " "
            if Ai[0][q] == Ai[1][q] == Ai[2][q]:
                same = same[:-1] + Ai[0][q]
            elif Ai[0][q] == Ai[1][q]:
                ab = ab[:-1] + Ai[0][q]
            elif Ai[0][q] == Ai[2][q]:
                ac = ac[:-1] + Ai[0][q]
            else:
                lassert(Ai[1][q] == Ai[2][q], "logic error")
                bc = bc[:-1] + Ai[1][q]
        lg(ab)
        lg(ac)
        lg(bc)
        lg(same)
        AB = sum(s != " " for s in ab)
        AC = sum(s != " " for s in ac)
        BC = sum(s != " " for s in bc)
        SAME = sum(s != " " for s in same)
        counts = 0
        exp_counts_AB = 0
        exp_counts_AC = 0
        exp_counts_BC = 0
        exp_counts_SAME = 0
        for curS in range(SAME + 1):
            # curAB + curAC + BC - curBC + curS = Si[0]
            # curAB + curAC - curBC = Si[0] - BC - curS
            # inv = (np.linalg.inv([[1, 1, -1], [1, -1, 1], [-1, 1, 1]]) * 2).astype(
            #     np.int32
            # )

            curAB = (Si[0] + Si[1] - AC - BC) // 2 - curS
            curAC = (Si[0] + Si[2] - BC - AB) // 2 - curS
            curBC = (Si[1] + Si[2] - AB - AC) // 2 - curS

            if curAB < 0 or curAB > AB:
                continue
            if curAC < 0 or curAC > AC:
                continue
            if curBC < 0 or curBC > BC:
                continue

            cur_counts = (
                choosell(AB, curAB)
                * choosell(AC, curAC)
                * choosell(BC, curBC)
                * choosell(SAME, curS)
            )
            lg(curS)
            lg(curAB)
            lg(curAC)
            lg(curBC)
            lg(cur_counts)
            counts += cur_counts
            exp_counts_AB += cur_counts * curAB
            exp_counts_AC += cur_counts * curAC
            exp_counts_BC += cur_counts * curBC
            exp_counts_SAME += cur_counts * curS

        answer_build = [" " for _ in range(Q)]
        if exp_counts_AB * 2 >= counts * AB:
            for q in range(Q):
                if ab[q] != " ":
                    answer_build[q] = ab[q]
        else:
            exp_counts_AB = counts * AB - exp_counts_AB
            for q in range(Q):
                if ab[q] != " ":
                    answer_build[q] = invert(ab[q])
        if exp_counts_AC * 2 >= counts * AC:
            for q in range(Q):
                if ac[q] != " ":
                    answer_build[q] = ac[q]
        else:
            exp_counts_AC = counts * AC - exp_counts_AC
            for q in range(Q):
                if ac[q] != " ":
                    answer_build[q] = invert(ac[q])
        if exp_counts_BC * 2 >= counts * BC:
            for q in range(Q):
                if bc[q] != " ":
                    answer_build[q] = bc[q]
        else:
            exp_counts_BC = counts * BC - exp_counts_BC
            for q in range(Q):
                if bc[q] != " ":
                    answer_build[q] = invert(bc[q])
        if exp_counts_SAME * 2 >= counts * SAME:
            for q in range(Q):
                if same[q] != " ":
                    answer_build[q] = same[q]
        else:
            exp_counts_SAME = counts * SAME - exp_counts_SAME
            for q in range(Q):
                if same[q] != " ":
                    answer_build[q] = invert(same[q])
        result[0] = "".join(answer_build)
        lg(exp_counts_SAME)
        lg(exp_counts_AB)
        lg(exp_counts_AC)
        lg(exp_counts_BC)
        result[1] = Fraction(
            exp_counts_SAME + exp_counts_AB + exp_counts_AC + exp_counts_BC, counts,
        )
        result[1] = "/".join(map(str, [result[1].numerator, result[1].denominator]))

    result = " ".join(result)


if __name__ == "__main__":
    main()
