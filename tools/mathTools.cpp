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

#pragma region bigint
struct bint;
bint abs(const bint& v);
std::uint64_t log2(const bint& v);

struct bint {
    std::vector<std::uint64_t> z;
    bool pos;

    bint() : pos(true) {}
    bint(const std::string& s) : pos(true) {
        if(s[0]== '-'){
            *this = -bint(s.substr(1, s.size() - 1));
            return;
        }
        if(s=="0"){
            return;
        }
        std::stringstream ss;
        std::uint64_t start, end, cur_number;
        for(std::uint64_t end = 1 + ((s.size() + 17) % 18); end <= s.size(); end+=18){
            if(z.size()) *this *= 1'000'000'000'000'000'000;
            start = std::max(UINT64_C(18), end) - 18;
            ss.clear();
            ss.str(s.substr(start, end-start));
            ss >> cur_number;
            *this += bint(cur_number);
        }
    }
    bint(const char* const & ca) {
        *this = bint(std::string(ca));
    }
    template <typename T>
    bint(const T& v) {
        *this = v;
    }

    void operator=(const bint& v){
        pos = v.pos;
        z = v.z;
    }
    template <typename T>
    void operator=(const T& v){
        pos = v >= 0;
        z.clear();
        if(v!=0)
            z.push_back(pos?v:-v);
    }
    void trim() {
        while(!z.empty() && z.back() == 0){
            z.pop_back();
        }
        pos |= z.empty();
    }

    bint operator-() const{
        bint ans;
        ans.pos = !(pos && z.sz);
        ans.z = z;
        return ans;
    }
    bint operator>>(const std::uint64_t& s) const {
        std::uint64_t bigshifts = s / 64;
        std::uint8_t small_shifts = s % 64;
        std::uint8_t inverse_small_shifts = 64 - small_shifts;
        bint ans;
        ans.pos = pos;
        for(std::uint64_t i = bigshifts; i < z.size(); ++i){
            std::uint64_t next = i + 1 < z.size() ? z[i+1] : 0;
            ans.z.push_back(z[i]>>small_shifts);
            if(small_shifts)
                ans.z.back() += next<<inverse_small_shifts;
        }
        ans.trim();
        return ans;
    }
    bint& operator>>=(const std::uint64_t& s) {
        *this = (*this) >> s;
        return *this;
    }
    bint operator<<(const std::uint64_t& s) const {
        std::uint64_t bigshifts = s / 64;
        std::uint8_t small_shifts = s % 64;
        bint ans;
        if(z.size() == 0) return ans;
        ans.pos = pos;
        if(small_shifts){
            for(std::uint64_t i = 0; i < bigshifts + 1; ++i)
                ans.z.push_back(0);
            for(std::uint64_t i = 0; i < z.size(); ++i)
                ans.z.push_back(z[i]);
            return ans >> (UINT64_C(64) - small_shifts);
        }
        for(std::uint64_t i = 0; i < bigshifts; ++i)
            ans.z.push_back(0);
        for(std::uint64_t i = 0; i < z.size(); ++i)
            ans.z.push_back(z[i]);
        return ans;
    }
    bint& operator<<=(const std::uint64_t& s) {
        *this = (*this) << s;
        return *this;
    }
    bint trailing_bits(const std::uint64_t& s) const {
        std::uint64_t big_chunks = (s+63) / 64;
        bint ans;
        ans.pos = pos;
        for(std::uint64_t i = 0; i < big_chunks && i < z.size(); ++i)
            ans.z.push_back(z[i]);
        std::uint8_t last_chunk_bits = s % 64;
        if(last_chunk_bits && big_chunks <= z.size()){
            ans.z.back() &= (UINT64_C(1)<<last_chunk_bits) - 1;
        }
        ans.trim();
        return ans;
    }
    bint& operator&=(const bint& o) {
        pos &= o.pos;
        if(o.z.size() < z.size()) z.resize(o.z.size());
        for(std::uint64_t i = 0; i < z.size(); ++i)
            z[i] &= o.z[i];
        trim();
        return *this;
    }
    bint operator&(const bint& o) const {
        bint ans = o;
        return (ans &= *this);
    }
    bint operator+(const bint& o) const{
        if(!pos)
            return o - (-*this);
        if(!o.pos)
            return *this - (-o);
        bint ans = *this;
        bool carry = false;
        std::uint64_t oi;
        for(std::uint64_t i = 0; i < o.z.size() || carry; ++i){
            if(i==ans.z.size())
                ans.z.push_back(0);
            oi = i < o.z.size() ? o.z[i] : 0;
            ans.z[i] += oi + carry;
            carry = ans.z[i] < oi + carry || (carry && oi + carry == 0);
        }
        return ans;
    }
    bint& operator+=(const bint& o){
        *this = (*this) + o;
        return *this;
    }
    bint operator-(const bint& o) const{
        if(!pos)
            return -(-(*this)+o);
        if(!o.pos)
            return *this + (-o);
        if(*this < o)
            return -(o - *this);
        bint res = *this;
        bool carry = false;
        bool next_carry;
        std::uint64_t oi;
        for(std::uint64_t i = 0; i < o.z.size() || carry; ++i){
            oi = i < o.z.size() ? o.z[i] : 0;
            next_carry = (res.z[i] == 0 && carry) || (res.z[i] - carry < oi);
            res.z[i] -= carry + oi;
            carry = next_carry;
        }
        res.trim();
        return res;
    }
    bint& operator-=(const bint& o){
        *this = (*this) - o;
        return *this;
    }
    bint operator*(const bint& o) const{
        if(z.size() == 0 || o.z.size() == 0)
            return bint();
        if(!pos){
            return (-*this)*(-o);
        }
        if(!o.pos){
            return -(*this * (-o));
        }
        std::uint64_t maxsize = std::max(z.size(), o.z.size());
        // for the following lines, look up Karatsuba algorithm:
        // https://en.wikipedia.org/wiki/Karatsuba_algorithm
        if(maxsize<=1){
            // o = o1*2^32 + o2, o1,o2 < 2^32
            std::uint64_t t1 = z[0]>>32;
            std::uint64_t t2 = z[0] & ((UINT64_C(1)<<32)-1);
            std::uint64_t o1 = o.z[0]>>32;
            std::uint64_t o2 = o.z[0] & ((UINT64_C(1)<<32)-1);
            std::uint64_t z0 = t1 * o1; // <= (2^32 - 1)^2 = 2^64 - 2^33 + 1
            std::uint64_t z11 = t1 * o2;
            std::uint64_t z12 = t2 * o1;
            std::uint64_t z1 = z11 + z12; // could be >= 2^64, so handle carry
            if(z1<z11) z0+=(UINT64_C(1)<<32); // handling carry
            std::uint64_t z2 = t2 * o2;
            bint result = (bint(z0) << UINT64_C(64)) + (bint(z1) << UINT64_C(32)) + bint(z2);
            return result;
        }

        // total bits = maxsize * 64, splitting numbers in half
        bint t1 = (*this) >> (maxsize * 32);
        bint t2 = trailing_bits(maxsize * 32);
        bint o1 = o >> (maxsize * 32);
        bint o2 = o.trailing_bits(maxsize * 32);

        bint z0 = t1 * o1;
        bint z2 = t2 * o2;
        // bint z1 = t1 * o2 + t2 * o1; <- trick of Karatsuba, using only one multiplication
        bint z1 = (t1 + t2) * (o1 + o2) - z2 - z0;
        bint result = (z0 << (maxsize * 64)) + (z1 << (maxsize * 32)) + z2;
        return result;
    }
    bint& operator*=(const bint& o){
        *this = (*this) * o;
        return *this;
    }
    std::pair<bint, bint> divmod(const bint& o) const{
        if(!pos || !o.pos){
            bool divpos = pos == o.pos;
            bool modpos = pos;
            std::pair<bint, bint> posresult = (abs(*this)).divmod(abs(o));
            return std::make_pair(
                divpos?posresult.first:-posresult.first,
                modpos?posresult.second:-posresult.second
            );
        }
        if((*this)<o)
            return std::make_pair(0, *this);
        if(z.size() == 1){
            return std::make_pair(bint(z.back()/o.z.back()), bint(z.back() % o.z.back()));
        }

        std::uint64_t obits = log2(o) + 1;
        std::uint64_t oshift = std::max(obits, UINT64_C(32)) - 32;
        std::uint64_t osignificant_upper = (o>>oshift).z[0] + (oshift >= 1);
        std::uint64_t tbits = log2(*this) + 1;
        std::uint64_t tshift = tbits - 64;
        std::uint64_t tsignificant_lower = ((*this)>>tshift).z[0];
        // div_lower = tsignificant_lower * 2^tshift / osignificant_upper / 2^oshift
        bint div_lower = tsignificant_lower / osignificant_upper;
        if(tshift > oshift) div_lower <<= tshift-oshift;
        else div_lower >>= oshift-tshift;
        if(div_lower.z.size()==0) div_lower.z.pb(1);
        std::pair<bint, bint> result = ((*this)-div_lower*o).divmod(o);
        return std::make_pair(result.first + div_lower, result.second);
    }
    bint operator/(const bint& o) const {
        return divmod(o).first;
    }
    bint& operator/=(const bint& o){
        *this = (*this) / o;
        return *this;
    }
    bint operator%(const bint& o) const {
        return divmod(o).second;
    }
    bint& operator%=(const bint& o){
        *this = (*this) % o;
        return *this;
    }
    operator bool() const {
        return (bool) z.size();
    }
    bool operator==(const bint& o) const {
        if(pos != o.pos) return false;
        if(z.size() != o.z.size()) return false;
        for(std::uint64_t i = 0; i < z.size(); ++i){
            if(z[i] != o.z[i]) return false;
        }
        return true;
    }
    bool operator<(const bint& o) const {
        if(pos){
            if(!o.pos) return false;
            if(z.size() > o.z.size()) return false;
            if(z.size() < o.z.size()) return true;
            for(std::uint64_t i = z.size(); i>0; --i){
                if(z[i-1]<o.z[i-1]) return true;
                if(z[i-1]>o.z[i-1]) return false;
            }
            return false;
        }
        if(o.pos) return true;
        return (-o) < (-(*this));
    }
    bool operator>(const bint& o) const {
        return o < (*this);
    }
    bool operator<=(const bint& o) const {
        return !(o<(*this));
    }
    bool operator>=(const bint& o) const {
        return !((*this)<o);
    }
};

std::ostream& operator<<(std::ostream& os, const bint& v) {
    if(!v.pos){
        os << "-" << (-v);
        return os;
    }
    if(v.z.size() == 0){
        os << "0";
        return os;
    }
    std::vector<std::string> digits;
    bint t = v;
    while(t.z.size()){
        std::pair<bint, bint> temp = t.divmod(UINT64_C(1'000'000'000'000'000'000));
        digits.push_back(std::to_string(temp.second.z[0]));
        t = temp.first;
    }
    os << digits.back();
    digits.pop_back();
    while(!digits.empty()) {
        os << std::setw(18) << std::setfill('0') << digits.back();
        digits.pop_back();
    }
    return os;
}
std::istream& operator>>(std::istream& is, bint& v) {
    std::string s;
    is >> s;
    v = bint(s);
    return is;
}
bint abs(const bint& v){
    if(v.z.size())
        return v.pos ? v : -v;
    return v;
}
std::uint64_t log2(const bint& v){
    lassert(v.z.size(), "bigint: log2 can only be computed for non-zero numbers");
    lassert(v.pos, "bigint: log2 can only be computed for positive numbers");
    std::uint8_t lower=0, upper=64;
    while(upper - lower >= 2){
        std::uint8_t mid = (lower + upper) / 2;
        if(v.z.back()>>mid)
            lower = mid;
        else
            upper = mid;
    }
    std::uint64_t ans = 64 * (v.z.size() - 1) + lower;
    return ans;
}
#pragma endregion bigint

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
    if (k > n)
        return 0;
    if ( n-k < k)
        return choosell(n, n-k);
    lassert(n<=61 || log2ll(n) <= 64/k, "values too large for long long choose version");
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

#pragma region frac
template <typename T>
struct nnfrac {
    T num, den;

    nnfrac(): num(0), den(1) {}
    nnfrac(const nnfrac<T>& o): num(o.num), den(o.den) {}
    nnfrac(const T& n): num(n), den(1) {}
    nnfrac(const T& p, const T& q): num(p), den(q) {}

    nnfrac operator-() const {
        nnfrac ans;
        ans.num = -num;
        ans.den = den;
        return ans;
    }
    nnfrac& operator+=(const nnfrac& o) {
        num *= o.den;
        num += den * o.num;
        den *= o.den;
        return *this;
    }
    nnfrac operator+(const nnfrac& o) const {
        nnfrac ans = *this;
        ans += o;
        return ans;
    }
    nnfrac& operator-=(const nnfrac& o) {
        num *= o.den;
        num -= den * o.num;
        den *= o.den;
        return *this;
    }
    nnfrac operator-(const nnfrac& o) const {
        nnfrac ans = *this;
        ans -= o;
        return ans;
    }
    nnfrac& operator*=(const nnfrac& o) {
        num *= o.num;
        den *= o.den;
        return *this;
    }
    nnfrac operator*(const nnfrac& o) const {
        nnfrac ans = *this;
        ans *= o;
        return ans;
    }
    nnfrac& operator/=(const nnfrac& o) {
        lassert(o.num != 0, "nnfrac: cannot divide by zero");
        num *= o.den;
        den *= o.num;
        return *this;
    }
    nnfrac operator/(const nnfrac& o) const {
        nnfrac ans = *this;
        ans /= o;
        return ans;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const nnfrac<T>& f) {
    os << f.num << "/" << f.den;
    return os;
}

template <typename T>
struct frac : nnfrac<T> {

    frac(): nnfrac<T>() {}
    frac(const frac<T>& o): nnfrac<T>(o) {}
    frac(const T& n): nnfrac<T>(n) {}
    frac(const T& p, const T& q): nnfrac<T>(p, q) {
        normalize_sign();
        reduce();
    }

    void normalize_sign() {
        if(this->den<0){
            this->num *= -1;
            this->den *= -1;
        }
    }

    void reduce() {
        T g = gcd<T>(this->num, this->den);
        lassert(g>0, "frac: gcd should be positive");
        this->num /= g;
        this->den /= g;
    }

    frac& operator+=(const frac& o) {
        this->nnfrac<T>::operator+=(o);
        this->reduce();
        return *this;
    }
    frac operator+(const frac& o) const {
        frac ans = *this;
        ans += o;
        return ans;
    }
    frac& operator-=(const frac& o) {
        this->nnfrac<T>::operator-=(o);
        this->reduce();
        return *this;
    }
    frac operator-(const frac& o) const {
        frac ans = *this;
        ans -= o;
        return ans;
    }
    frac& operator*=(const frac& o) {
        this->nnfrac<T>::operator*=(o);
        this->reduce();
        return *this;
    }
    frac operator*(const frac& o) const {
        frac ans = *this;
        ans *= o;
        return ans;
    }
    frac& operator/=(const frac& o) {
        this->nnfrac<T>::operator/=(o);
        this->normalize_sign();
        this->reduce();
        return *this;
    }
    frac operator/(const frac& o) const {
        frac ans = *this;
        ans /= o;
        return ans;
    }

    bool operator==(const frac& o) const {
        return this->num == o.num && this->den == o.den;
    }
    bool operator<(const frac& o) const {
        return this->num * o.den < o.num * this->den;
    }
    bool operator>(const frac& o) const {
        return this->num * o.den > o.num * this->den;
    }
};

template <typename T>
frac<T> abs(const frac<T>& f){
    return f.num < 0 ? -f : f;
}

typedef frac<ll> fracll;
typedef frac<bint> bfrac;

#pragma endregion frac

} // namespace mathTools
using namespace mathTools;

namespace std{

template <typename T>
bool operator<(const std::complex<T> &lhs, const std::complex<T> &rhs){
    return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag() : lhs.real() < rhs.real();
}

} // namespace std
#pragma endregion mathTools
