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
INV_PHI = (np.sqrt(ld(5)) - 1) / 2  # 1 / phi
INV_PHI2 = (3 - np.sqrt(ld(5))) / 2  # 1 / phi^2
# #endregion constants

# #endregion abbr
