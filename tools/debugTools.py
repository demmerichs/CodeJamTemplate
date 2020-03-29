# #region debugTools


def pdb():
    if "LOCAL" in FLAGS:
        import ipdb

        ipdb.set_trace()


def llog(*args):
    if "LOCAL" in FLAGS:
        cerr(*list(map(str, args)))


def lassert(*args):
    if "LOCAL" in FLAGS:
        if not args[0]:
            llog(args[1:])
            pdb()


# #endregion debugTools
