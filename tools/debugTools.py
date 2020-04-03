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
undefine(`__file__',`__gnu__',`__line__',`__os2__',`__program__',`__unix__',`__windows__',`argn',`array',`array_set',`builtin',`capitalize',`changecom',`changequote',`changeword',`cleardivert',`cond',`copy',`curry',`debugfile',`debugmode',`decr',`define',`define_blind',`defn',`divert',`divnum',`dnl',`downcase',`dquote',`dquote_elt',`dumpdef',`errprint',`esyscmd',`eval',`example',`exch',`fatal_error',`foreach',`foreachq',`forloop',`format',`ifelse',`include',`incr',`index',`indir',`join',`joinall',`len',`m4exit',`m4wrap',`maketemp',`mkstemp',`nargs',`os2',`patsubst',`popdef',`pushdef',`quote',`regexp',`rename',`reverse',`shift',`sinclude',`stack_foreach',`stack_foreach_lifo',`stack_foreach_sep',`stack_foreach_sep_lifo',`substr',`syscmd',`sysval',`traceoff',`traceon',`translit',`undefine',`undivert',`unix',`upcase',`windows')# undefine(`__file__',`__gnu__',`__line__',`__os2__',`__program__',`__unix__',`__windows__',`argn',`array',`array_set',`builtin',`capitalize',`changecom',`changequote',`changeword',`cleardivert',`cond',`copy',`curry',`debugfile',`debugmode',`decr',`define',`define_blind',`defn',`divert',`divnum',`dnl',`downcase',`dquote',`dquote_elt',`dumpdef',`errprint',`esyscmd',`eval',`example',`exch',`fatal_error',`foreach',`foreachq',`forloop',`format',`ifelse',`include',`incr',`index',`indir',`join',`joinall',`len',`m4exit',`m4wrap',`maketemp',`mkstemp',`nargs',`os2',`patsubst',`popdef',`pushdef',`quote',`regexp',`rename',`reverse',`shift',`sinclude',`stack_foreach',`stack_foreach_lifo',`stack_foreach_sep',`stack_foreach_sep_lifo',`substr',`syscmd',`sysval',`traceoff',`traceon',`translit',`undefine',`undivert',`unix',`upcase',`windows')
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
