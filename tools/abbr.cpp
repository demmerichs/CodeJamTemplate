#pragma region abbr

#pragma region types
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
#define dq(type) std::deque<type >
#define p(type1,type2) std::pair<type1, type2 >
#define c(type) std::complex<type >
#pragma endregion types
#pragma region members and functions
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
#pragma endregion members and functions
#pragma region iterators
#define bn begin()
#define ed end()
#define all(x) (x).begin(), (x).end()
#define ssel(x,i) (x).begin()+(i), (x).begin()+(i)+1
#define msel(x,i,j) (x).begin()+(i), (x).begin()+(j)
#define foreach(elem,container) for(auto &elem : container)
#define foreachc(elem,container) for(const auto &elem : container)
#pragma endregion iterators
#pragma region for-loops
#define forn(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define fornn(i, a, b) for (ll i = (ll)(a); i < (ll)(b); ++i)
#define fore(i, a, b) for (ll i = (ll)(a); i <= (ll)(b); ++i)
#pragma endregion for-loops
#pragma region constants: INF, EPS, PI, MOD
#define INF std::numeric_limits<long long>::max()
#define EPS 1e-15L
#define PI 3.14159265358979323846264338328L
#define MOD 1000000007LL
#define MOD_IS_PRIME    //add commment on this line, when MOD is changed to non-prime number
#define DIR_NAMES "ENWS"
v(cell) DIRECTIONS = {cell(1, 0), cell(0, 1), cell(-1, 0), cell(0, -1)};
d(char, ll) DIR_IDX = {{'E', 0}, {'N', 1}, {'W', 2}, {'S', 3}};
#pragma endregion constants
#pragma region small conveniance functions
#define lg(var_name) llog(#var_name, var_name)
template <typename K, typename V>
const V& dget(const std::map<K, V>& dict, const K& key, const V& def=0){
    auto found = dict.find(key);
    if(found == dict.end()){
        return def;
    }
    return found->second;
}
#pragma endregion small conveniance functions

#pragma endregion abbr
