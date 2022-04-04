// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
#define DEFAULT_VAL_TRIGGER result.sz == 0
#define DEFAULT_VAL "IMPOSSIBLE"
// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
#define IA_ERROR_CODE -1
#define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
#define COMM_TYPE ll

// The maintained and empty code template can be found at:
// https://github.com/demmerichs/CodeJamTemplate
#pragma region template code
#include <bits/stdc++.h>

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

#pragma region printerTools
/*  <<-operator for deque and pair class
 */
namespace printerTools{

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> iteratable);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> iteratable);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::set<T> iteratable);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::unordered_set<T> iteratable);

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::map<S, T> iteratable);

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::unordered_map<S, T> iteratable);

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::pair<S,T> pa);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::complex<T> c);

template <typename T>
std::ostream& _outstream_iteratables(std::ostream& os, T iteratable){
    if(iteratable.begin() == iteratable.end())
        return os;
    os << *iteratable.begin();
    for(auto it = (++iteratable.begin()); it != iteratable.end(); ++it)
        os << ' ' << *it;
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::set<T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::unordered_set<T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::map<S, T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::unordered_map<S, T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::pair<S,T> pa){
    os << pa.first << ' ' << pa.second;
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::complex<T> c){
    os << c.real() << ' ' << c.imag();
    return os;
}

} // namespace printerTools
using namespace printerTools;
#pragma endregion printerTools

#pragma region debugTools
namespace debugTools{

#ifdef LOCAL
    #include <chrono>

    auto start=std::chrono::high_resolution_clock::now(), stop=std::chrono::high_resolution_clock::now();

    inline void start_timer(){start=std::chrono::high_resolution_clock::now();}
    inline void stop_timer(){stop=std::chrono::high_resolution_clock::now();}
    inline double get_time(){return std::chrono::duration<double>(stop - start).count();}
#else
    #define start_timer()
    #define stop_timer()
    #define get_time()
#endif /*LOCAL*/

inline void local_log(){
    std::cerr << std::endl;
}

template<typename T>
inline void local_log(T t){
    std::cerr << t << std::endl;
}

template<typename T, typename... Args>
inline void local_log(T t, Args... args){
    std::cerr << t << "\t";
    local_log(args...);
}

#ifdef LOCAL
    #define llog(args...) local_log(args)
#else
    #define llog(args...)
#endif /*LOCAL*/

template<typename T>
void local_assert(T t, std::string message){
    if(!t)
        llog(message);
    assert(t);
}

#ifdef LOCAL
    #define lassert(args...) local_assert(args)
#else
    #define lassert(args...)
#endif /*LOCAL*/

} // namespace debugTools
using namespace debugTools;
#pragma endregion debugTools

#pragma region selectionTools
/*  SelectionIterator class (abbr. seliter)
 *          iterates over every possible selection of k elements out of the vector
 *      use as following:
 *          for(seliter<T> si(vector,k); !si.final(); ++si) { something with *si }
 *          si.getNotSelected() returns a vector of the n-k not selected elements
 *  getSelection-Function (abbr. gsel)
 *          select from elements, indicated by the ones "1" in the binary representation
 *      use as following:
 *          gsel(vector,binaryRepresentationOfSelection) returns vector
 */
namespace selectionTools{

template <typename T>
class SelectionIterator{
private:
    unsigned long long k;
    unsigned long long n;
    v(T) vector;
    v(T) selection;
    v(unsigned long long) selectionNumbers;
    bool finalState;
public:
    SelectionIterator<T>(v(T) vector, unsigned long long k):k(k), n(vector.size()), vector(vector), finalState(false){
        if(k>n){
            finalState = true;
            return;
        }
        for(unsigned long long i=0;i<k;++i){
            selection.push_back(vector[i]);
            selectionNumbers.push_back(i);
        }
    }

    void operator++(){
        for(unsigned long long i=k-1;i<k;--i){
            if(selectionNumbers[i]==n+i-k)
                continue;
            else{
                ++selectionNumbers[i];
                selection[i]=vector[selectionNumbers[i]];
                for(unsigned long long j=i+1;j<k;++j){
                    selectionNumbers[j]=selectionNumbers[i]+j-i;
                    selection[j]=vector[selectionNumbers[j]];
                }
                return;
            }
        }
        finalState=true;
    }

    v(T) operator*(){
        return selection;
    }

    v(T) getNotSelected(){
        v(T) notSelected;
        unsigned long long cur = 0;
        for(unsigned long long i=0; i<k; ++i){
            for(unsigned long long j=cur; j<selectionNumbers[i]; ++j)
                notSelected.push_back(vector[j]);
            cur = selectionNumbers[i] + 1;
        }
        for(unsigned long long j=cur; j<n; ++j)
            notSelected.push_back(vector[j]);
        return notSelected;
    }

    bool final(){
        return finalState;
    }
};
#define seliter SelectionIterator

template <typename T>
v(T) getSelection(v(T) elements, unsigned long long binaryRepresentationOfSelection){
    v(T) result;
    for(unsigned long long i=0;i<elements.size();++i)
        if( (binaryRepresentationOfSelection>>i)%2 )
            result.push_back(elements[i]);
    return result;
}
#define gsel getSelection

} // namespace selectionTools
using namespace selectionTools;
#pragma endregion selectionTools

#pragma region mathTools
/*  TODO add documentation for operators and euclideanAlgo
 *  faculty (facll, facmod and facld)  IMPORTANT: facll works only for n<=20
 *  choose (choosell, choosemod and chooseld)  IMPORTANT: choosell works only for n<=62
 *  power on integers (powll and powmod)
 *  log2 on integers (log2ll)
 *  ceill(p,q)/floorll (returns ceil(p/q)/floorll(p/q) for integers)
 *  <-operator for std::complex
 */
namespace mathTools{

template <typename T>
T maxOp(T a, T b){
    return a<b?b:a;
}

template <typename T>
T minOp(T a, T b){
    return a>b?b:a;
}

template <typename T>
T mposOp(T a){
    return (a%MOD + MOD) %MOD;
}

template <typename T>
T mplusOp(T a, T b){
    return (a+b)%MOD;
}

template <typename T>
T mmulOp(T a, T b){
    return ((__int128_t) a * (__int128_t) b)%MOD;
}

unsigned long long log2ll(unsigned long long n){
    assert(n > 0);
    if (n == 1)
        return 0;
    return 1 + log2ll(n >> 1);
}

unsigned long long sqrtll(unsigned long long n){
    unsigned long long result = (unsigned long long) std::sqrt((double) n);
    while(result*result < n) ++result;
    while(result*result > n) --result;
    return result;
}

unsigned long long facll(unsigned long long n){
    if (n)
        return n * facll(n - 1);
    return 1;
}

unsigned long long facmod(unsigned long long n){
    static std::vector<unsigned long long> memorize;
    if (n>=MOD)
        return 0;
    if(n < memorize.size()) return memorize[n];
    if(n == 0) {
        memorize.push_back(1);
        return 1;
    }
    memorize.push_back(mmulOp(n, facmod(n - 1)));
    return memorize[n];
}

long double facld(unsigned long long n){
    if(n)
        return (long double)n * facld(n-1);
    return 1.;
}

// use this only up to n^k < 2^64 (size of long)
// usually k is often iterated through 1..n, and the largest binomial coefficient is for k=n/2
// with choose(n, n/2) < 2^64 we get as upper bound n <= 61
unsigned long long choosell(unsigned long long n, unsigned long long k){
    lassert(n<=61 || log2ll(n) <= 64/k, "values too large for long long choose version");
    if (k > n)
        return 0;
    if ( n-k < k)
        return choosell(n, n-k);
    unsigned long long result = 1;
    for(unsigned long long i = 0; i < k; ++i){
        result *= n - i;
        result /= i + 1;
    }
    return result;
}

long double chooseld(unsigned long long n, unsigned long long k){
    if (k > n)
        return 0;
    if ( n-k < k)
        return chooseld(n, n-k);
    long double result = 1;
    for(unsigned long long i = 0; i < k; ++i){
        result *= n - i;
        result /= i + 1;
    }
    return result;
}

long long powll(long long base, unsigned long long exp){
    if (exp == 0)
        return 1;
    else if (exp & 1)
        return powll(base, exp - 1) * base;
    else{
        long long t = powll(base, exp / 2);
        return t * t;
    }
}

long long powmod(long long base, long long exp)
{
    if (exp == 0)
        return 1;
    else if (exp & 1)
        return mmulOp(powmod(base, exp - 1), base);
    else{
        long long t = powmod(base, exp / 2);
        return mmulOp(t, t);
    }
}

template <typename T>
v(T) vecOp(v(T) a, v(T) b, const std::function<T (T, T)> &op = std::plus<T>()){
    assert(a.size() == b.size());
    v(T) out;
    for (unsigned i = 0; i < a.size(); ++i)
        out.push_back(op(a[i], b[i]));
    return out;
}

// Implementation works in place by returning the values for a, b by reference
// a_in * a_out + b_in * b_out = gcd(a, b) (> 0, trivial solution =0 excluded)
// it is guaranteed that |a_out| <= |b_in/gcd| if b_in > 0
// (and symmetric the other way round), so no modulo version is needed
template <typename T>
void euclideanAlgo(T &a, T &b){
    // only process, a,b >= 0, a<=b transform all other cases to this
    if(a<0){
        a = -a;
        euclideanAlgo(a,b);
        a = -a;
        return;
    }
    if(b<0){
        b = -b;
        euclideanAlgo(a,b);
        b = -b;
        return;
    }
    if(a>b){
        euclideanAlgo(b,a);
        return;
    }
    if(a==0){
        assert(b>0);
        b = 1;
        return;
    }
    T s = b/a;
    T r = b - s*a;
    euclideanAlgo(r, a);
    a = a - s*r;
    b = r;
}

template <typename T>
T gcd(const T &a, const T &b){
    T a_ = a;
    T b_ = b;
    euclideanAlgo(a_, b_);
    return a * a_ + b * b_;
}

// chinese remainder theorem in application
template <typename T>
T crt(v(T) remainders, v(T) moduli){
    lassert(remainders.size() == moduli.size(), "Chinese remainder theorem: remainders and moduli must be of same size!");
    long long int n = remainders.size();
    T m = moduli.back();
    moduli.pop_back();
    T r = remainders.back();
    remainders.pop_back();
    for(unsigned int i = 0; i < n - 1; ++i){
        // solve a*m1 + b*m2 == 1
        T cur_modulo = moduli.back();
        moduli.pop_back();
        T cur_remainder = remainders.back();
        remainders.pop_back();
        T a = m;
        T b = cur_modulo;
        euclideanAlgo(a, b);
        // make sure, that m1 and m2 are indeed coprime
        lassert(a * m + b * cur_modulo == 1, "Chinese remainder theorem: euclidean algorithm delivered unexpected result! Are your factors coprime?");
        // crt: find x == r1 (m1) and x == r2 (m2)
        // solved by x = r1 + (r2 - r1) * a * m1 == r2 + (r1 - r2) * b * m2
        // proof (for first expression): x == r1 (m1) trivial, x == r1 + (r2 - r1) * (a * m1 (m2)) == r1 + (r2 - r1) * 1 == r2 (m2)
        r = r + (cur_remainder - r) * a * m;
        m *= cur_modulo;
        r = (r % m + m) % m;
    }
    lassert(remainders.size() == 0, "Chinese remainder theorem: Something went wrong!");
    return r;
}

#ifdef MOD_IS_PRIME
template <typename T>
T mInvOp(T n){
    lassert(n>0, "cannot divide by 0");
    return powmod(n, MOD-2);
}
#else
template <typename T>
T mInvOp(T div){
    div %= MOD;
    T m = MOD;
    T a = m;
    T b = div;
    euclideanAlgo(a, b);
    assert(a*m + b*div == 1); // gcd == 1 so that multiplicative inverse is unambigous
    return mposOp(b);
}
#endif /*MOD_IS_PRIME*/

template <typename T>
T mdivOp(T num, T div){
    return mmulOp(mInvOp(div), num);
}

#ifdef MOD_IS_PRIME
unsigned long long choosemod(unsigned long long n, unsigned long long k){
    if(k==0 || k==n) return 1;
    unsigned long long nfac = facmod(n);
    unsigned long long invnkfac = mInvOp(facmod(n-k));
    unsigned long long invkfac = mInvOp(facmod(k));
    return mmulOp(nfac, mmulOp(invnkfac, invkfac));
}
#else
unsigned long long choosemod(unsigned long long n, unsigned long long k){
    static std::vector<std::vector<unsigned long long> > memorize;
    if (k > n)
        return 0;
    if (memorize.size() > n){
        if (memorize[n].size() > k){
            return memorize[n][k];
        } else{
            choosemod(n, k-1);
            memorize[n].push_back((choosemod(n-1,k-1) + choosemod(n-1,k)) % MOD);
            return memorize[n][k];
        }
    } else{
        while (memorize.size() <= n){
            memorize.push_back(std::vector<unsigned long long>());
            memorize.back().push_back(1LL);
        }
        return choosemod(n,k);
    }
}
#endif /*MOD_IS_PRIME*/

long long ceill(long long p, long long q){
    if (q<0)
        return ceill(-p,-q);
    if (p<0)
        return p/q;
    return (p+q-1)/q;
}

long long floorll(long long p, long long q){
    if (q<0)
        return floorll(-p,-q);
    if (p<0)
        return (p-q+1)/q;
    return p/q;
}

void frac_reduce(cell& frac){
    ll g = gcd(frac.real(), frac.imag());
    frac /= g;
}

cell frac_add(const cell& lhs, const cell& rhs){
    cell res(lhs.real()*rhs.imag()+lhs.imag()*rhs.real(), lhs.imag()*rhs.imag());
    frac_reduce(res);
    return res;
}

cell frac_sub(const cell& lhs, const cell& rhs){
    cell res(lhs.real()*rhs.imag()-lhs.imag()*rhs.real(), lhs.imag()*rhs.imag());
    frac_reduce(res);
    return res;
}

cell frac_mul(const cell& lhs, const cell& rhs){
    cell res(lhs.real()*rhs.real(), lhs.imag()*rhs.imag());
    frac_reduce(res);
    return res;
}

cell frac_div(const cell& lhs, const cell& rhs){
    cell res(lhs.real()*rhs.imag(), lhs.imag()*rhs.real());
    frac_reduce(res);
    return res;
}

} // namespace mathTools
using namespace mathTools;

namespace std{

template <typename T>
bool operator<(const std::complex<T> &lhs, const std::complex<T> &rhs){
    return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag() : lhs.real() < rhs.real();
}

} // namespace std
#pragma endregion mathTools

#pragma region algoTools
/* TODO write doc
 */
namespace algoTools{

// does an argsort (increasing values) over the provided vector
template <typename T>
v(long long int) argsort(const v(T) &v) {
    // initialize original index locations
    v(long long int) idxs(v.size());
    std::iota(idxs.begin(), idxs.end(), 0);

    // sort indexes based on comparing values in v
    std::sort(idxs.begin(), idxs.end(),
              [&v](long long int i1, long long int i2) {return v[i1] < v[i2];});

    return idxs;
}

// returns the average of 2 values without generating overflow and always rounding down
template <typename T>
T middle(T l, T u){
    T mid = (l/2)+(u/2);
    T r = ((l-mid) + (u-mid))/2;
    return mid + r;
}

template <typename Tidx, typename Tval>
Tidx lower_bound_function(const Tval &val, const std::function<Tval (Tidx)> &f, const Tidx &length, const Tidx &start = 0, const Tidx &resolution = 1){
    Tidx l = start - resolution;
    Tidx u = start + length;
    while(u>l+resolution){
        Tidx mid = middle(l, u);
        if(f(mid) >= val) u=mid;
        else l=mid;
    }
    return u;
}

template <typename Tidx, typename Tval>
Tidx upper_bound_function(const Tval &val, const std::function<Tval (Tidx)> &f, const Tidx &length, const Tidx &start = 0, const Tidx &resolution = 1){
    Tidx l = start - resolution;
    Tidx u = start + length;
    while(u>l+resolution){
        Tidx mid = middle(l, u);
        if(f(mid) > val) u=mid;
        else l=mid;
    }
    return u;
}


template <typename T>
class BalancedRangeTree{
private:
    const v(v(T)) &values;
    ll dimension;
    v(ll) argsorted;
    unsigned short max_depth;
    v(BalancedRangeTree<T>) subtrees;

    T get_sort(ll idx){
        return values[dimension][argsorted[idx]];
    }

    ll get_nbr_values_smaller_thresh(T thresh){
        return lower_bound_function<ll,T>(thresh, [&](ll idx){ return this->get_sort(idx); }, argsorted.size());
    }

    v(ll) get_tree_path_idxs(ll leaf_idx){
        if(leaf_idx == -1){
            return v(ll)(max_depth, -1);
        }
        lassert(0 <= leaf_idx, "leaf idx has invalid negative value");
        lassert(leaf_idx <= 1<<(max_depth-1), "leaf idx has too large value");
        v(ll) result;
        forn(d, max_depth){
            result.pb(leaf_idx >> (max_depth-d-1));
        }
        return result;
    }

    static ll tree_to_vec_idx(unsigned int level, ll idx_in_level){
        lassert(idx_in_level < 1<<level, "invalid tree idx");
        return (1<<level) - 1 + idx_in_level;
    }

    v(ll) get_idxs_of_subtrees_in_idx_range(ll low_idx, ll up_idx){
        v(ll) low_tree_path = get_tree_path_idxs(low_idx);
        v(ll) up_tree_path = get_tree_path_idxs(up_idx);
        v(ll) subtree_idxs;
        forn(d, max_depth){
            if(low_tree_path[d] % 2 == 0){ // went left in tree so right is possible
                if(low_tree_path[d] + 1 < up_tree_path[d]){
                    ll st_idx = tree_to_vec_idx(d, low_tree_path[d] + 1);
                    subtree_idxs.pb(st_idx);
                }
            }
            if(up_tree_path[d] % 2 == 1){ // went right in tree so left is possible
                if(up_tree_path[d] - 1 > low_tree_path[d]){
                    ll st_idx = tree_to_vec_idx(d, up_tree_path[d] - 1);
                    subtree_idxs.pb(st_idx);
                }
            }
        }
        return subtree_idxs;
    }

    void create_subtrees(){
        max_depth = argsorted.size() >= 4 ? 2 + log2ll(argsorted.size() -1) : argsorted.size();

        if(values.size()-1 > dimension){
            forn(d, max_depth){
                forn(i, 1<<d){
                    v(ll) subtree_idxs;
                    fornn(j, i*(1<<(max_depth-d-1)), std::min<ll>(argsorted.size(), (i+1)*(1<<(max_depth-d-1)))){
                        subtree_idxs.pb(argsorted[j]);
                    }
                    subtrees.pb(BalancedRangeTree(values, dimension+1, subtree_idxs));
                }
            }
        }

        lassert((subtrees.size()>=1) == (dimension+1 != values.size()), "last dimension has subtrees or non_last_dimension has no subtrees");
    }

public:
    BalancedRangeTree<T>(const v(v(T)) &values, ll dimension, v(ll) idxs): values(values), dimension(dimension){
        v(T) cur_values;
        foreach(idx, idxs){
            cur_values.pb(values[dimension][idx]);
        }
        v(ll) cur_argsorted = argsort(cur_values);
        foreach(cur_arg_idx, cur_argsorted){
            argsorted.pb(idxs[cur_arg_idx]);
        }

        create_subtrees();
    }

    BalancedRangeTree<T>(const v(v(T)) &values): values(values), dimension(0){
        argsorted = argsort(values[0]);

        create_subtrees();
    }

    v(ll) get_range(v(T) l, v(T) u){
        if(argsorted.size() == 0)
            return v(ll)();
        ll low_idx = get_nbr_values_smaller_thresh(l[0]);
        ll up_idx = get_nbr_values_smaller_thresh(u[0]);
        v(ll) result;
        if(dimension + 1 < values.size()){
            v(T) rest_range_l(msel(l, 1, l.size()));
            v(T) rest_range_u(msel(u, 1, u.size()));
            v(ll) idxs_of_subtrees_in_range = get_idxs_of_subtrees_in_idx_range(low_idx-1, up_idx == argsorted.size() ? 1<<(max_depth-1):up_idx);
            foreach(subtree_idx, idxs_of_subtrees_in_range){
                v(ll) cur_result_idxs = subtrees[subtree_idx].get_range(rest_range_l, rest_range_u);
                result.insert(result.ed, all(cur_result_idxs));
            }
        } else {
            result.insert(result.ed, msel(argsorted, low_idx, up_idx));
        }
        return result;
    }

    ll get_range_count(v(T) l, v(T) u){
        if(argsorted.size() == 0)
            return 0;
        ll low_idx = get_nbr_values_smaller_thresh(l[0]);
        ll up_idx = get_nbr_values_smaller_thresh(u[0]);
        ll result = 0;
        if(dimension + 1 < values.size()){
            v(T) rest_range_l(msel(l, 1, l.size()));
            v(T) rest_range_u(msel(u, 1, u.size()));
            v(ll) idxs_of_subtrees_in_range = get_idxs_of_subtrees_in_idx_range(low_idx-1, up_idx == argsorted.size() ? 1<<(max_depth-1):up_idx);
            foreach(subtree_idx, idxs_of_subtrees_in_range){
                ll cur_result = subtrees[subtree_idx].get_range_count(rest_range_l, rest_range_u);
                result += cur_result;
            }
        } else {
            result += up_idx - low_idx;
        }
        return result;
    }
};

bool find_match(unsigned long long r, const std::vector<std::vector<bool> > &connected, std::vector<long long> &matched_rows, std::vector<long long> &matched_cols, std::vector<bool> &seen) {
    for(unsigned long long c = 0; c < connected[r].size(); c++){
        if(connected[r][c] && !seen[c]){
            seen[c] = true;
            if(matched_cols[c] < 0 || find_match(matched_cols[c], connected, matched_rows, matched_cols, seen)){
                matched_rows[r] = c;
                matched_cols[c] = r;
                return true;
            }
        }
    }
    return false;
}

unsigned long long maximal_bipartite_matching(const std::vector<std::vector<bool> > &connected, std::vector<long long> &matched_rows, std::vector<long long> &matched_cols) {
    matched_rows = std::vector<long long>(connected.size(), -1);
    matched_cols = std::vector<long long>(connected[0].size(), -1);

    unsigned long long num_matches = 0;
    for(unsigned long long r = 0; r < connected.size(); r++){
        std::vector<bool> seen(connected[0].size(), false);
        if(find_match(r, connected, matched_rows, matched_cols, seen)) num_matches++;
    }
    return num_matches;
}

template <typename T>
class RangeMinMaxTable{
private:
    const bool query_min;
    const v(T) &values;
    v(v(ll)) lookup_idxs;

    bool comp(const T& lhs, const T& rhs){
        if(query_min) return lhs <= rhs;
        else return lhs >= rhs;
    }

    void create_lookup_table(){
        ll n = values.size();
        ll logn = log2ll(n);
        lookup_idxs.clear();
        lookup_idxs.resize(n);
        forn(i, n){
            lookup_idxs[i].push_back(i);
        }
        fornn(j, 1, logn+1){
            forn(i, n + 1 - (1<<j)){
                if(comp(values[lookup_idxs[i][j-1]], values[lookup_idxs[i+(1<<(j-1))][j-1]]))
                    lookup_idxs[i].push_back(lookup_idxs[i][j-1]);
                else
                    lookup_idxs[i].push_back(lookup_idxs[i + (1<<(j-1))][j-1]);
            }
        }
    }

public:
    RangeMinMaxTable<T>(const v(T) &values, const bool &query_min=true): values(values), query_min(query_min){
        create_lookup_table();
    }

    ll query(ll lower, ll upper){
        ll n = upper - lower;
        lassert(n>0, "invalid range max query");
        ll logn = log2ll(n);
        ll first = lookup_idxs[lower][logn];
        ll second = lookup_idxs[upper - (1<<logn)][logn];
        if(comp(values[first], values[second]))
            return first;
        return second;
    }
};

void strongly_connected_components_tarjan_recursive(
    const v(s(ll))& adjacency_list,
    v(ll) &discovered,
    v(ll) &lowest,
    v(bool) &on_stack,
    v(ll) &stack,
    ll &discover_counter,
    v(ll) &scc,
    ll next_to_discover
){
    discovered[next_to_discover] = discover_counter;
    lowest[next_to_discover] = discover_counter;
    on_stack[next_to_discover] = true;
    stack.pb(next_to_discover);
    discover_counter++;
    foreach(neigh, adjacency_list[next_to_discover]){
        if(discovered[neigh]==-1){
            strongly_connected_components_tarjan_recursive(
                adjacency_list, discovered, lowest, on_stack, stack, discover_counter, scc, neigh
            );
        }
        if(on_stack[neigh]){
            lowest[next_to_discover] = std::min(lowest[next_to_discover], lowest[neigh]);
        }
    }
    if(discovered[next_to_discover] == lowest[next_to_discover]){
        while(stack.bk != next_to_discover){
            scc[stack.bk] = discovered[next_to_discover];
            on_stack[stack.bk] = false;
            stack.popb;
        }
        scc[next_to_discover] = discovered[next_to_discover];
        on_stack[next_to_discover] = false;
        stack.popb;
    }
}

v(ll) strongly_connected_components_tarjan(v(s(ll)) adjacency_list){
    ll n = adjacency_list.sz;
    v(ll) discovered(n, -1), lowest(n, -1), stack;
    v(bool) on_stack(n, false);
    ll discover_counter = 0;
    v(ll) scc(n, -1);
    forn(i, n){
        if(discovered[i] >= 0) continue;
        strongly_connected_components_tarjan_recursive(
            adjacency_list, discovered, lowest, on_stack, stack, discover_counter, scc, i
        );
    }
    return scc;
}

} // namespace algoTools
using namespace algoTools;
#pragma endregion algoTools

#pragma region interactiveTools

namespace interactiveTools{

#ifdef IA_MODE

COMM_TYPE in(){
    COMM_TYPE in_value;
    std::cin >> in_value;
    #ifdef IA_COMM_LOG
    llog("reading value:", in_value);
    #endif /*IA_COMM_LOG*/
    if(in_value == IA_ERROR_CODE){
        exit(0);
    }
    return in_value;
}

template<typename T>
void out(T t){
    #ifdef IA_COMM_LOG
    llog("sending output:", t);
    #endif /*IA_COMM_LOG*/
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void out(T t, Args... args){
    #ifdef IA_COMM_LOG
    llog("sending output:", t);
    #endif /*IA_COMM_LOG*/
    std::cout << t << std::endl;
    out(args...);
}

#endif /*IA_MODE*/

} // namespace interactiveTools
using namespace interactiveTools;
#pragma endregion interactiveTools

#pragma region main
namespace task{
long long unsigned T;
void init();
void readInput();
void calcFunction();
}

COMM_TYPE result;
int main() {
    std::ios::sync_with_stdio(false);  // don't use scanf when sync turned off -> https://www.geeksforgeeks.org/cincout-vs-scanfprintf/
    std::cerr << std::setprecision(4);
    std::cout << std::setprecision(10);
    task::init();
    for(long long unsigned test=1; test<=task::T; ++test){
        llog();
        llog();
        llog();
        llog();
        llog("################################################");
        llog("################################################");
        llog("################################################");
        llog("################", test, "################");
        llog("################################################");
        llog("################################################");
        llog("################################################");
        llog();
        llog("============      reading input     ============");
        start_timer();
        task::readInput();
        stop_timer();
        llog("-----------", get_time(), "secs -----------");
        llog();
        llog("============    doing computation   ============");
        start_timer();
        task::calcFunction();
        stop_timer();
        llog("-----------", get_time(), "secs -----------");
        llog();
#ifndef IA_MODE
        //write output
        std::cout << "Case #" << test << ": ";
#ifndef DEFAULT_VAL_MODE
        std::cout << result << std::endl;
#else
        if(DEFAULT_VAL_TRIGGER){
            llog("default val triggered");
            std::cout << DEFAULT_VAL << std::endl;
        }
        else{
            llog("default val NOT triggered");
            std::cout << result << std::endl;
        }
#endif /*DEFAULT_VAL_MODE*/
#endif /*IA_MODE*/
    }
    return 0;
}
#pragma endregion main

using namespace std;
#pragma endregion template code

namespace task {

void init(){
    cin >> T;
}

const ll MAXLOG2N = 17;
// const ll MAXLOG2N = 2;
ll N;
v(int) Vi;
v(int) st_amin;

void readInput(){
    cin >> N;
    Vi.resize(N);
    forn(i, N) cin >> Vi[i];
    st_amin.assign(1<<(MAXLOG2N+1), -1);
}

ll argmin(ll l, ll r, ll node=0, ll nl=0, ll nr=(1<<MAXLOG2N)-1){
    if(l>r) return -1;
    if(l==nl && r==nr) return st_amin[node];
    ll nm = (nl+nr)/2;
    ll ql = argmin(l, min(r, nm), 2*node+1, nl, nm);
    ll qr = argmin(max(l, nm+1), r, 2*node+2, nm+1, nr);
    if(ql==-1) return qr;
    if(qr==-1) return ql;
    if(Vi[ql] < Vi[qr]) return ql;
    return qr;
}


void recur(ll l, ll r, ll mi){
    if(l>r) return;
    ll pos = argmin(l, r);
    if(Vi[pos] != mi){
        result = 0;
        return;
    }
    ll lcount = pos - l;
    ll rcount = r - pos;
    lg(lcount+rcount);
    lg(rcount);
    result = mmulOp(result, (ll) choosemod(lcount+rcount, rcount));
    recur(l, pos-1, mi);
    recur(pos+1, r, mi+1);
}

// write to COMM_TYPE result
void calcFunction() {
    forn(i, N){
        st_amin[i+(1<<MAXLOG2N)-1] = i;
    }
    forn(ii, (1<<MAXLOG2N)-1){
        ll i = (1<<MAXLOG2N)-2-ii;
        ll lidx = st_amin[2*i+1];
        ll ridx = st_amin[2*i+2];
        if(lidx==-1) st_amin[i]=ridx;
        else if(ridx==-1) st_amin[i]=lidx;
        else if(Vi[lidx]<Vi[ridx]) st_amin[i] = lidx;
        else st_amin[i] = ridx;
    }
    // lg(st_amin);
    // lg(argmin(0,3));

    result = 1;
    recur(0, N-1, 1);
    // lg(choosemod(5000, 2500));
    // lg(choosemod(50000, 25000));
}

} // namespace task
