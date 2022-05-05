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
unsigned short log2i(const T& value){
    unsigned short l=0, u=64;
    unsigned short mid;
    while(u-l>1){
        mid = (l+u)/2;
        if(value>>mid)
            l = mid;
        else
            u = mid;
    }
    return l;
}

template <typename T>
T powi(const T& base, const unsigned long long& exp){
    T ans = 1;
    unsigned short bitpos = log2i(exp);
    while(true){
        ans *= ans;
        if((exp>>bitpos)&1)
            ans *= base;
        if(bitpos == 0)
            break;
        --bitpos;
    }
    return ans;
}

template <typename T>
T maxOp(T a, T b){
    return a<b?b:a;
}

template <typename T>
T minOp(T a, T b){
    return a>b?b:a;
}

#pragma region bigint
struct bint;
bint abs(const bint& v);
std::uint64_t log2i(const bint& v);

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

        std::uint64_t obits = log2i(o) + 1;
        std::uint64_t oshift = std::max(obits, UINT64_C(32)) - 32;
        std::uint64_t osignificant_upper = (o>>oshift).z[0] + (oshift >= 1);
        std::uint64_t tbits = log2i(*this) + 1;
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
std::uint64_t log2i(const bint& v){
    lassert(v.z.size(), "bigint: log2i can only be computed for non-zero numbers");
    lassert(v.pos, "bigint: log2i can only be computed for positive numbers");
    // std::uint8_t lower=0, upper=64;
    // while(upper - lower >= 2){
    //     std::uint8_t mid = (lower + upper) / 2;
    //     if(v.z.back()>>mid)
    //         lower = mid;
    //     else
    //         upper = mid;
    // }
    std::uint64_t ans = 64 * (v.z.size() - 1) + log2i(v.z.back());
    return ans;
}
#pragma endregion bigint

unsigned long long sqrtll(unsigned long long n){
    unsigned long long result = (unsigned long long) std::sqrt((double) n);
    while(result*result < n) ++result;
    while(result*result > n) --result;
    return result;
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
// a_in * a_out + b_in * b_out = gcd(a_in, b_in) (> 0, trivial solution =0 excluded)
// it is guaranteed that |a_out| <= |b_in/gcd| if b_in > 0
// (and symmetric the other way round), so no modulo version is needed
template <typename T>
void euclideanAlgo(T &a, T &b){
    // only process, a,b >= 0, a<=b transform all other cases to this
    if(0 < a && a <= b){
        T s = b/a;
        T r = b - s*a;
        euclideanAlgo(r, a);
        a = a - s*r;
        b = r;
        return;
    }
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
    lassert(false, "euclideanAlog: invalid case, internal logic error");
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

#pragma region mint
struct mint{
    unsigned long long value;

    mint(): value(0){}
    mint(const mint& a): value(a.value){}
    mint(const unsigned int& a): value(a % MOD){}
    mint(const unsigned long& a): value(a % MOD){}
    mint(const unsigned long long& a): value(a % MOD){}
    mint(const int& a): value(a<0?(a%MOD)+MOD:a%MOD){}
    mint(const long& a): value(a<0?(a%MOD)+MOD:a%MOD){}
    mint(const long long& a): value(a<0?(a%MOD)+MOD:a%MOD){}

    #ifdef MOD_IS_PRIME
    mint inverse() const {
        lassert(value>0, "cannot divide by 0");
        return powi(*this, MOD-2);
    }
    #else
    mint inverse() const{
        long long m = MOD;
        long long a = m;
        long long b = value;
        euclideanAlgo(a, b);
        assert(a*m + b*value == 1); // gcd == 1 so that multiplicative inverse is unambigous
        return mint(b);
    }
    #endif /*MOD_IS_PRIME*/

    mint& operator+=(const mint& o){
        value += o.value;
        value %= MOD;
        return *this;
    }
    mint operator+(const mint& o) const{
        mint ans = *this;
        ans += o;
        return ans;
    }
    mint& operator-=(const mint& o){
        *this += MOD - o.value;
        return *this;
    }
    mint operator-(const mint& o) const{
        mint ans = *this;
        ans -= o;
        return ans;
    }
    mint& operator*=(const mint& o){
        if(o.value == 0){
            value = 0;
            return *this;
        }
        if((value>>32) || (o.value>>32)){
            unsigned long long base = value;
            unsigned short bitpos = log2i(o.value)-1;
            while(bitpos != (unsigned short) -1){
                value <<= 1;
                value %= MOD;
                if((o.value>>bitpos)&1){
                    value += base;
                    value %= MOD;
                }
                --bitpos;
            }
            return *this;
        }
        value *= o.value;
        value %= MOD;
        return *this;
    }
    mint operator*(const mint& o) const{
        mint ans = *this;
        ans *= o;
        return ans;
    }
    mint& operator/=(const mint& o) {
        *this *= o.inverse();
        return *this;
    }
    mint operator/(const mint& o) const{
        mint ans = *this;
        ans /= o;
        return ans;
    }

    bool operator!=(const mint& o) const{
        return value != o.value;
    }
    bool operator==(const mint& o) const{
        return value == o.value;
    }
};

std::ostream& operator<<(std::ostream& os, const mint& v){
    os << v.value;
    return os;
}
#pragma endregion mint

template <typename T>
T fac(const unsigned long long &n){
    static std::vector<T> memorize;
    if(n < memorize.size()) return memorize[n];
    if(n == 0) {
        memorize.push_back(1);
        return 1;
    }
    memorize.push_back(fac<T>(n-1) * n);
    return memorize[n];
}

template <>
mint fac<mint>(const unsigned long long &n){
    static std::vector<mint> memorize;
    if(n >= MOD) return 0;
    if(n < memorize.size()) return memorize[n];
    if(n == 0) {
        memorize.push_back(1);
        return 1;
    }
    memorize.push_back(fac<mint>(n-1) * n);
    return memorize[n];
}

template <typename T>
T choose(const unsigned long long &n, const unsigned long long &k){
    static std::map<unsigned long long, std::vector<T> > memorize;
    if(k > n) return 0;
    if( n-k < k) return choose<T>(n, n-k);
    // memorize[n];
    if(k < memorize[n].size()) return memorize[n][k];
    if(k == 0){
        memorize[n].push_back(1);
        return 1;
    }
    memorize[n].push_back(choose<T>(n, k-1) * (n-k+1) / k);
    return memorize[n][k];
}

#ifdef MOD_IS_PRIME
template <>
mint choose<mint>(const unsigned long long &n, const unsigned long long &k){
    if(k==0 || k==n) return 1;
    mint nfac = fac<mint>(n);
    mint nkfac = fac<mint>(n-k);
    mint kfac = fac<mint>(k);
    return nfac / (nkfac * kfac);
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
typedef nnfrac<mint> mfrac;

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
