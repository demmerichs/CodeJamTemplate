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


# #endregion mathTools
