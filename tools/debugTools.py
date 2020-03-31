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
