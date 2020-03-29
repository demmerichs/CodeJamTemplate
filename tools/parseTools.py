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
