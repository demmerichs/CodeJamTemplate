//#region abbr

//#region types
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::complex<long long> cell;
typedef std::complex<long double> pnt;
typedef std::string str;
typedef std::stringstream sstr;
#define s(type) std::set<type >
#define uos(type) std::unordered_set<type >
#define d(type1, type2) std::map<type1, type2 >
#define uod(type1, type2) std::unordered_map<type1, type2 >
#define v(type) std::vector<type >
#define p(type1,type2) std::pair<type1, type2 >
#define c(type) std::complex<type >
//#endregion types
//#region members and functions
#define mp make_pair
#define mt make_tuple
#define st first
#define nd second
#ifdef XY_NOTATION
#define x real()
#define y imag()
#endif /*XY_NOTATION*/
#define bk back()
#define ft front()
#define pb push_back
#define pf push_front
#define popb pop_back()
#define popf pop_front()
#define sz size()
#define cl clear()
//#endregion members and functions
//#region iterators
#define bn begin()
#define ed end()
#define all(x) (x).begin(), (x).end()
#define ssel(x,i) (x).begin()+(i), (x).begin()+(i)+1
#define msel(x,i,j) (x).begin()+(i), (x).begin()+(j)
#define foreach(elem,container) for(auto &elem : container)
#define foreachc(elem,container) for(const auto &elem : container)
//#endregion iterators
//#region for-loops
#define forn(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define fornn(i, a, b) for (ll i = (ll)(a); i < (ll)(b); ++i)
#define fore(i, a, b) for (ll i = (ll)(a); i <= (ll)(b); ++i)
//#endregion for-loops
//#region constants: INF, EPS, PI, MOD
#define INF std::numeric_limits<long long>::max()
#define EPS 1e-15L
#define PI 3.14159265358979323846264338328L
#define MOD 1000000007L
d(char, cell) DIRECTIONS = {{'E', cell(1, 0)}, {'N', cell(0, 1)}, {'W', cell(-1, 0)}, {'S', cell(0, -1)}};
//#endregion constants

//#endregion abbr
