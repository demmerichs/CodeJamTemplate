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
