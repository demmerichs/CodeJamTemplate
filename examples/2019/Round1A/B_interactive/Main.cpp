// #define DEFAULT_VAL    //remove comment on this line, to activate default value trigger
#define IA_MODE        //remove comment on this line, to activate interactive problem mode
#define SUBMIT         //remove comment on this line, when submitting solution
#define ERROR_WORD "IMPOSSIBLE"
#define COMM_TYPE ll
#define IA_ERROR_CODE -1

// The maintained and empty code template can be found at:
// https://github.com/DavidS3141/CodeJamTemplate
//#region template code
#include <bits/stdc++.h>

//#region abbr

//#region types
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::complex<long long> cell;
typedef std::complex<long double> pnt;
typedef std::string str;
#define hash unordered_map
#define v(type) std::deque<type >
#define p(type1,type2) std::pair<type1, type2 >
#define c(type) std::complex<type >
//#endregion types
//#region members and functions
#define mp make_pair
#define mt make_tuple
#define st first
#define nd second
#define x real()
#define y imag()
#define bk back()
#define ft front()
#define pb push_back
#define pf push_front
#define popb pop_back()
#define popf pop_front()
#define sz size()
//#endregion members and functions
//#region iterators
#define bn begin()
#define ed end()
#define all(x) (x).begin(), (x).end()
#define ssel(x,i) (x).begin()+(i), (x).begin()+(i)+1
#define msel(x,i,j) (x).begin()+(i), (x).begin()+(j)
#define foreach(cit,container) for(auto cit = (container).begin(); cit != (container).end(); cit++)
#define foreachc(c,cit,container) ll c=0;for(auto cit = (container).begin(); cit != (container).end(); c++, cit++)
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
//#endregion constants

//#endregion abbr

//#region printerTools
/*  <<-operator for deque and pair class
 */
namespace printerTools{

template <typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> vector);

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::pair<S,T> pa);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> vector){
    if(vector.size()==0)
        return os;
    os << vector[0];
    for(unsigned long long i=1;i<vector.size();++i)
        os << ' ' << vector[i];
    return os;
}

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::pair<S,T> pa){
    os << pa.first << ' ' << pa.second;
    return os;
}

template<typename T>
void log(T t){
#ifndef SUBMIT
    std::cerr << t << std::endl;
#endif /*SUBMIT*/
    return;
}

template<typename T, typename... Args>
void log(T t, Args... args){
#ifndef SUBMIT
    std::cerr << t;
    log(args...);
#endif /*SUBMIT*/
    return;
}

} // namespace printerTools
using namespace printerTools;
//#endregion printerTools

//#region selectionTools
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
    std::deque<T> vector;
    std::deque<T> selection;
    std::deque<unsigned long long> selectionNumbers;
    bool finalState;
public:
    SelectionIterator<T>(std::deque<T> vector, unsigned long long k):k(k), n(vector.size()), vector(vector), finalState(false){
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

    std::deque<T> operator*(){
        return selection;
    }

    std::deque<T> getNotSelected(){
        std::deque<T> notSelected;
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
std::deque<T> getSelection(std::deque<T> elements, unsigned long long binaryRepresentationOfSelection){
    std::deque<T> result;
    for(unsigned long long i=0;i<elements.size();++i)
        if( (binaryRepresentationOfSelection>>i)%2 )
            result.push_back(elements[i]);
    return result;
}
#define gsel getSelection

} // namespace selectionTools
using namespace selectionTools;
//#endregion selectionTools

//#region mathTools
/*  TODO add documentation for operators and euclideanAlgo
 *  faculty (facll, facmod and facld)  IMPORTANT: facll works only for n<=20
 *  choose (choosell, choosemod and chooseld)  IMPORTANT: choosell works only for n<=62
 *  power on integers (powll and powmod)
 *  log2 on integers (log2ll)
 *  ceill(p,q)/floorll (returns ceil(p/q)/floorll(p/q) for integers)
 *  <-operator for std::complex
 */
namespace mathTools{

unsigned long long facll(unsigned long long n){
    if (n)
        return n * facll(n - 1);
    return 1;
}

unsigned long long facmod(unsigned long long n){
    if (n)
        return (n * facmod(n - 1)) % MOD;
    return 1;
}

long double facld(unsigned long long n){
    if(n)
        return (long double)n * facld(n-1);
    return 1.;
}

unsigned long long choosell(unsigned long long n, unsigned long long k){
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
        return powmod(base, exp - 1) * base % MOD;
    else{
        long long t = powmod(base, exp / 2);
        return t * t % MOD;
    }
}

unsigned long long log2ll(unsigned long long n){
    assert(n > 0);
    if (n == 1)
        return 0;
    return 1 + log2ll(n >> 1);
}

template <typename T>
std::deque<T> vecOp(std::deque<T> a, std::deque<T> b, const std::function<T (T, T)> &op = std::plus<T>()){
    assert(a.size() == b.size());
    std::deque<T> out;
    for (unsigned i = 0; i < a.size(); ++i)
        out.push_back(op(a[i], b[i]));
    return out;
}

template <typename T>
T maxOp(T a, T b){
    return a<b?b:a;
}

template <typename T>
T minOp(T a, T b){
    return a>b?b:a;
}

template <typename T>
T mplusOp(T a, T b){
    return (a+b)%MOD;
}

template <typename T>
T mmulOp(T a, T b){
    return (a%MOD * b%MOD)%MOD;
}

// Implementation works in place by returning the values for a, b by reference
// a_in * a_out + b_in * b_out = gcd(a, b) (> 0, trivial solution =0 excluded)
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
T crt(std::deque<T> remainders, std::deque<T> moduli){
    assert(remainders.size() == moduli.size());
    long long int n = remainders.size();
    for(unsigned int i = 0; i < n - 1; ++i){
        // solve a*m1 + b*m2 == 1
        T a = moduli[0];
        T b = moduli[1];
        euclideanAlgo(a, b);
        assert(a * moduli[0] + b * moduli[1] == 1); // make sure, that m1 and m2 are indeed coprime
        // crt: find x == r1 (m1) and x == r2 (m2)
        // solved by x = r1 + (r2 - r1) * a * m1 == r2 + (r1 - r2) * b * m2
        // proof (for first expression): x == r1 (m1) trivial, x == r1 + r2 * (a * m1 (m2)) == r1 + r2 * 1 == r2 (m2)
        T r = remainders[0] + (remainders[1] - remainders[0]) * a * moduli[0];
        T m = moduli[0] * moduli[1];
        r = (r % m + m) % m;
        remainders.pop_front();
        remainders.pop_front();
        moduli.pop_front();
        moduli.pop_front();
        remainders.push_back(r);
        moduli.push_back(m);
    }
    assert(remainders.size() == 1);
    return remainders[0];
}

template <typename T>
T mdivOp(T num, T div){
    div %= MOD;
    T m = MOD;
    T a = m;
    T b = div;
    euclideanAlgo(a, b);
    assert(a*m + b*div == 1); // gcd == 1 so that multiplicative inverse is unambigous
    return (b%MOD * num%MOD) % MOD;
}

template <typename T>
T mposOp(T a){
    return (a%MOD + MOD) %MOD;
}

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

} // namespace mathTools
using namespace mathTools;

namespace std{

template <typename T>
bool operator<(const std::complex<T> &lhs, const std::complex<T> &rhs){
    return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag() : lhs.real() < rhs.real();
}

} // namespace std
//#endregion mathTools

//#region algoTools
/* TODO write doc
 */
namespace algoTools{

// does an argsort (increasing values) over the provided vector
template <typename T>
std::deque<long long int> argsort(const std::deque<T> &v) {
    // initialize original index locations
    std::deque<long long int> idxs(v.size());
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
    T r = l%2 + u%2 + 2;
    return mid + r/2 - 1;
}

// returns the number of elements which are strict smaller/larger than val if start = 0
// otherwise returns the smallest index for which f(idx) >/<= val and start+length if this index does not exist
template <typename T>
long long binSearchDisc(const T &val, const std::function<T (long long)> &f, const unsigned long long &length, const long long &start = 0, bool increasing = true){
    long long l = start - 1;
    long long u = start + length;
    if(increasing){
        while(u>l+1){
            long long mid = middle(l,u);
            if(f(mid)<val)
                l=mid;
            else
                u=mid;
        }
    } else {
        while(u>l+1){
            long long mid = middle(l,u);
            if(f(mid)>val)
                l=mid;
            else
                u=mid;
        }
    }
    return u;
}

} // namespace algoTools
using namespace algoTools;
//#endregion algoTools

//#region interactiveTools

namespace interactiveTools{

#ifdef IA_MODE

COMM_TYPE in(){
    COMM_TYPE in_value;
    std::cin >> in_value;
    log("reading value:\t", in_value);
    if(in_value == IA_ERROR_CODE){
        exit(-1);
    }
    return in_value;
}

template<typename T>
void out(T t){
    log("sending output:\t", t);
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void out(T t, Args... args){
    log("sending output:\t", t);
    std::cout << t << std::endl;
    out(args...);
}

#endif /*IA_MODE*/

} // namespace interactiveTools
using namespace interactiveTools;
//#endregion interactiveTools

//#region main
namespace task{
void init();
void readInput();
void calcFunction();
}

COMM_TYPE result;
int main() {
    std::cerr << std::setprecision(4);
    std::cout << std::setprecision(10);
    long long unsigned tests = 0;
    std::cin >> tests;
    task::init();
    for(long long unsigned test=1; test<=tests; ++test){
        //read input
        task::readInput();
        //calc result
        task::calcFunction();
#ifndef IA_MODE
        //write output
        std::cout << "Case #" << test << ": ";
        std::cerr << "Case #" << test << ": ";
#ifndef DEFAULT_VAL
        std::cout << result << std::endl;
        std::cerr << result << std::endl;
#endif /*DEFAULT_VAL*/
#ifdef DEFAULT_VAL
        if(result>=0){
            std::cout << result << std::endl;
            std::cerr << result << std::endl;
        }
        else{
            std::string errorWord = ERROR_WORD;
            std::cout << errorWord << std::endl;
            std::cerr << errorWord << std::endl;
        }
#endif /*DEFAULT_VAL*/
#endif /*IA_MODE*/
    }
    return 0;
}
//#endregion main

using namespace std;
//#endregion template code

namespace task {

ll N, m;

void init(){
    cin >> N >> m;
}

void readInput(){
}

ll ask(ll p){
    v(ll) ps(18, p);
    out(ps);
    ll sum = 0;
    forn(i, 18){
        sum += in();
    }
    return sum % p;
}

// write to COMM_TYPE result
void calcFunction() {
    assert(N>=7);
    v(ll) p = {17, 16, 13, 11, 9, 7, 5};
    v(ll) ans;
    forn(i, 7){
        ans.pb(ask(p[i]));
    }
    out(crt(ans, p));
    in();
}

} // namespace task
