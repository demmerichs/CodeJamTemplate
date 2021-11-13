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
