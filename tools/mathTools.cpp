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
//#endregion mathTools
