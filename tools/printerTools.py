# #region printerTools


def to_str(val, precision=10):
    local_to_str = ft.partial(to_str, precision=precision)
    if isinstance(val, (list, tuple, np.ndarray)):
        return " ".join(map(local_to_str, val))
    if isinstance(val, np.float):
        return ("%%.%df" % precision) % val
    if isinstance(val, (str, np.integer)):
        return str(val)
    lassert(False, "could not convert %s of type %s to string" % (val, type(val)))
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
