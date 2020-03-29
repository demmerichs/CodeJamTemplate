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
