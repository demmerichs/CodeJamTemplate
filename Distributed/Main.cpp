#include "TODO.h"
#define OUT_TYPE ll

//#region template code
#include <message.h>
#include <bits/stdc++.h>

//#region abbr

//#region types
typedef long long ll;
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
//#region constants: INF, EPS, PI, MOD, M
#define INF 9000000000000000000L
#define EPS 1e-15
#define PI 3.14159265358979323846264338328L
#define MOD 1000000007
#define M 0
//#endregion constants

//#endregion abbr

/* printerTools
 *
 *  declares <<-operator for deque and pair class
 */
//#region printerTools
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
} // namespace printerTools
using namespace printerTools;
//#endregion printerTools

/* selectionTools
 *
 *  declares a SelectionIterator class (abbr seliter)
 *          iterates over every possible selection of k elements out of the vector
 *      use as following:
 *          for(seliter<T> si(vector,k); !si.final(); ++si) { something with *si }
 *          si.getNotSelected() returns a vector of the n-k not selected elements
 *  declares a getSelection-Function (abbr. gsel)
 *          select from elements, indicated by the ones "1" in the binary representation
 *      use as following:
 *          gsel(vector,binaryRepresentationOfSelection) returns vector
 */
//#region selectionTools
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

/* mathTools
 *
 *  declares faculty (facll, facmod and facld)  IMPORTANT: facll works only for n<=20
 *  declares choose (choosell, choosemod and chooseld)  IMPORTANT: choosell works only for n<=62
 *  declares power on integers (powll and powmod)
 *  declares log2 on integers (log2ll)
 *  declares vmin (returns v[i]=min(a[i] , b[i]) )
 *  declares ceill(p,q)/floorll (returns ceil(p/q)/floorll(p/q) for integers)
 *  declares an <-operator for std::complex
 */
//#region mathTools
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

std::deque<long long> vmin(std::deque<long long> a, std::deque<long long> b)
{
    std::deque<long long> out;
    for (unsigned i = 0; i < a.size(); ++i)
        out.push_back(std::min(a[i], b[i]));
    return out;
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

template <typename T>
bool operator<(const std::complex<T> &lhs, const std::complex<T> &rhs){
    if(lhs.real() < rhs.real())
        return true;
    if(rhs.real() < lhs.real())
        return false;
    if(lhs.imag() < rhs.imag())
        return true;
    if(rhs.imag() < lhs.imag())
        return false;
    return false;
}
} // namespace mathTools
using namespace mathTools;
//#endregion mathTools

/* parallelTools
 *
 *  declares partition_work(items, rank, nodes, start, end)
 *      input: items, rank, nodes
 *      output: if the rank node gets work (true or false)
 *          values: if it gets work, nodes is the total number of nodes that get work, and start inclusive, end exclusive is the range the current node needs to work on
 */
//#region parallelTools
namespace parallelTools{
template<typename T>
bool partition_work(long long items, int rank, int &nodes, T &start, T &end)
{
    if (nodes > items)
        nodes = items;
    start = items * rank / nodes;
    end = items * (rank + 1) / nodes;
    return rank < nodes;
}
} // namespace parallelTools
using namespace parallelTools;
//#endregion parallelTools

/* messageTools
 *
 *  TODO insert documentation
 */
//#region messageTools
namespace msg{

/*
    This template provides get(source) and put(target,value) for the types:
        char
        int
        long long
        bool
        vector<T>
        array<T,(int) N>
        pair<A,B>
        complex<T>
        tuple<Args...>
*/
template<typename T> class serialize;
//#region serialize
template<>
class serialize<char>
{
public:
    static char get(int source) { return GetChar(source); }
    static void put(int target, char value) { PutChar(target, value); }
};

template<>
class serialize<int>
{
public:
    static int get(int source) { return GetInt(source); }
    static void put(int target, int value) { PutInt(target, value); }
};

template<>
class serialize<long long>
{
public:
    static long long get(int source) { return GetLL(source); }
    static void put(int target, long long value) { PutLL(target, value); }
};

template<>
class serialize<bool>
{
public:
    static bool get(int source) { return GetChar(source); }
    static void put(int target, bool value) { PutChar(target, char(value)); }
};

template<typename T>
class serialize<std::deque<T> >
{
public:
    static std::deque<T> get(int source)
    {
        long long size = GetLL(source);
        std::deque<T> out;
        for (long long i = 0; i < size; i++)
            out.push_back(serialize<T>::get(source));
        return out;
    }

    static void put(int target, const std::deque<T> &value)
    {
        PutLL(target, value.size());
        for (std::size_t i = 0; i < value.size(); i++)
            serialize<T>::put(target, value[i]);
    }
};

template<typename T, std::size_t N>
class serialize<std::array<T, N> >
{
public:
    static std::array<T, N> get(int source)
    {
        std::array<T, N> out;
        for (std::size_t i = 0; i < N; i++)
            out[i] = serialize<T>::get(source);
        return out;
    }

    static void put(int target, const std::array<T, N> &value)
    {
        for (std::size_t i = 0; i < N; i++)
            serialize<T>::put(target, value[i]);
    }
};

template<typename A, typename B>
class serialize<std::pair<A, B> >
{
public:
    static std::pair<A, B> get(int source)
    {
        A a{serialize<A>::get(source)};
        B b{serialize<B>::get(source)};
        return std::make_pair(std::move(a), std::move(b));
    }

    static void put(int target, const std::pair<A, B> &value)
    {
        serialize<A>::put(target, value.first);
        serialize<B>::put(target, value.second);
    }
};

template<typename T>
class serialize<std::complex<T> >
{
public:
    static std::complex<T> get(int source)
    {
        T x = serialize<T>::get(source);
        T y = serialize<T>::get(source);
        return std::complex<T>(x, y);
    }

    static void put(int target, const std::complex<T> &value)
    {
        serialize<T>::put(target, value.real());
        serialize<T>::put(target, value.imag());
    }
};

namespace detail
{

template<int P, typename... Args>
class serialize_tuple
{
private:
    typedef typename std::tuple_element<P, std::tuple<Args...> >::type element_type;
public:
    static void get(int source, std::tuple<Args...> &out)
    {
        serialize_tuple<P - 1, Args...>::get(source, out);
        std::get<P>(out) = serialize<element_type>::get(source);
    }

    static void put(int target, const std::tuple<Args...> &value)
    {
        serialize_tuple<P - 1, Args...>::put(target, value);
        serialize<element_type>::put(target, std::get<P>(value));
    }
};

template<typename... Args>
class serialize_tuple<-1, Args...>
{
public:
    static void get(int, std::tuple<Args...> &) {}
    static void put(int, const std::tuple<Args...> &) {}
};

} // namespace detail

template<typename... Args>
class serialize<std::tuple<Args...> >
{
public:
    static std::tuple<Args...> get(int source)
    {
        std::tuple<Args...> out;
        detail::serialize_tuple<int(sizeof...(Args)) - 1, Args...>::get(source, out);
        return out;
    }

    static void put(int target, const std::tuple<Args...> &value)
    {
        detail::serialize_tuple<int(sizeof...(Args)) - 1, Args...>::put(target, value);
    }
};
//#endregion serialize

/*
    simple get and put functions:
        T get(source)
        get(source, Args&...)
        put(target, values...)
    simple send and receive functions:
        T receive(source)
        receive(source, Args&...)
        send(target, values...)
*/
//#region communication
template<typename T>
static T get(int source)
{
    return serialize<T>::get(source);
}

template<typename T>
static void get(int source, T &data)
{
    data = serialize<T>::get(source);
}

template<typename T, typename T2, typename... Rest>
static void get(int source, T &data, T2 &data2, Rest&... rest)
{
    data = serialize<T>::get(source);
    get(source, data2, rest...);
}

template<typename T>
static void put(int target, const T &value)
{
    serialize<T>::put(target, value);
}

template<typename T, typename T2, typename... Rest>
static void put(int target, const T &value, const T2 &value2, const Rest&... rest)
{
    serialize<T>::put(target, value);
    put(target, value2, rest...);
}

template<typename T>
static T receive(int source)
{
    source = Receive(source);
    return get<T>(source);
}

template<typename T, typename... Rest>
static int receive(int source, T &data, Rest&... rest)
{
    source = Receive(source);
    get(source, data, rest...);
    return source;
}

template<typename T, typename... Rest>
static void send(int target, const T &value, const Rest&... rest)
{
    put<T>(target, value, rest...);
    Send(target);
}
//#endregion communication

/*
    This class provides advanced communication tools
    using msg::range_comm world(#Number of Nodes):
        T reduce(root, value, op = plus)
        T broadcast(root, value)
        T allreduce(value, op = plus)
        vector<T> gather(root, value)
        vector<T> join(root, vector<T> values)
        vector<T> alljoin(vector<T> values)
        T scatter(root, vector<T> values)
        T prefix_sum(&value, op = plus, identity = 0)
        T prefix_sum_arrays(vector<T> &values, op = plus, identity = 0)
        T suffix_sum(&value, op = plus, identity = 0)
        T suffix_sum_arrays(vector<T> &values, op = plus, identity = 0)
*/
//#region range communication
class range_comm
{
private:
    int first;
    int last;

public:
    explicit range_comm(int last) : first(0), last(last) {}
    range_comm(int first, int last) : first(first), last(last) {}

    void setRange(int p_first, int p_last){
        first = p_first;
        last = p_last;
    }

    template<typename T, typename Op = std::plus<T> >
    T reduce(int root, const T &value, const Op &op = Op()) const
    {
        if (MyNodeId() == root)
        {
            T ans = value;
            for (int i = first; i < last; i++)
                if (i != root)
                    ans = op(ans, receive<T>(i));
            return ans;
        }
        else
        {
            send(root, value);
            return T();
        }
    }

    template<typename T>
    T broadcast(int root, const T &value) const
    {
        if (MyNodeId() == root)
        {
            for (int i = first; i < last; i++)
            {
                if (i != root)
                    send(i, value);
            }
            return value;
        }
        else
            return receive<T>(root);
    }

    template<typename T, typename Op = std::plus<T> >
    T allreduce(const T &value, const Op &op = Op()) const
    {
        T mid = reduce(first, value, op);
        return broadcast(first, mid);
    }

    template<typename T>
    std::deque<T> gather(int root, const T &value)
    {
        std::deque<T> ans;
        if (MyNodeId() == root)
        {
            for (int i = first; i < last; i++)
                if (i == root)
                    ans.push_back(value);
                else
                    ans.push_back(receive<T>(i));
        }
        else
            send(root, value);
        return ans;
    }

    template<typename T>
    std::deque<T> join(int root, const std::deque<T> &value)
    {
        std::deque<T> ans;
        if (MyNodeId() == root)
        {
            for (int i = first; i < last; i++)
            {
                if (i == root)
                    ans.insert(ans.end(), value.begin(), value.end());
                else
                {
                    std::deque<T> in;
                    receive(i, in);
                    ans.insert(ans.end(), in.begin(), in.end());
                }
            }
        }
        else
            send(root, value);
        return ans;
    }

    template<typename T>
    std::deque<T> alljoin(const std::deque<T> &value)
    {
        std::deque<T> ans;
        for (int i = first; i < last; i++)
        {
            if (i != MyNodeId())
                send(i, value);
        }
        for (int i = first; i < last; i++)
        {
            if (i != MyNodeId())
            {
                std::deque<T> in;
                receive(i, in);
                ans.insert(ans.end(), in.begin(), in.end());
            }
            else
                ans.insert(ans.end(), value.begin(), value.end());
        }
        return ans;
    }

    template<typename T>
    T scatter(int root, const std::deque<T> &values)
    {
        if (MyNodeId() == root)
        {
            assert(values.size() == size_t(last - first));
            for (int i = first; i < last; i++)
                if (i != root)
                    send(i, values[i - first]);
            return values[root];
        }
        else
        {
            return receive<T>(root);
        }
    }

    // Exclusive in-place prefix sum, returning the overall total
    template<typename T, typename Op = std::plus<T> >
    T prefix_sum(T &value, const Op &op = Op(), const T &identity = T())
    {
        std::deque<T> all = gather(first, value);
        if (MyNodeId() == first)
        {
            T sum = identity;
            for (T &t : all)
            {
                T next = t;
                t = sum;
                sum = op(sum, next);
            }
            for (int i = first + 1; i < last; i++)
                send(i, all[i - first], sum);
            value = identity;
            return sum;
        }
        else
        {
            T sum;
            receive(first, value, sum);
            return sum;
        }
    }

    // Exclusive, in-place prefix sum, with each rank contributing a vector
    template<typename T, typename Op = std::plus<T> >
    T prefix_sum_arrays(std::deque<T> &values, const Op &op = Op(), const T &identity = T())
    {
        T my_total = accumulate(values.begin(), values.end(), identity, op);
        T total = prefix_sum(my_total, op, identity);
        for (T &t : values)
        {
            T next = t;
            t = my_total;
            my_total = op(my_total, next);
        }
        return total;
    }

    // Exclusive in-place suffix sum, returning the overall total
    template<typename T, typename Op = std::plus<T> >
    T suffix_sum(T &value, const Op &op = Op(), const T &identity = T())
    {
        std::deque<T> all = gather(first, value);
        if (MyNodeId() == first)
        {
            T sum = identity;
            for (auto it = all.rbegin(); it != all.rend(); it++)
            {
                T &t = *it;
                T next = t;
                t = sum;
                sum = op(sum, next);
            }
            for (int i = first + 1; i < last; i++)
                send(i, all[i - first], sum);
            value = all[0];
            return sum;
        }
        else
        {
            T sum;
            receive(first, value, sum);
            return sum;
        }
    }

    // Exclusive, in-place prefix sum, with each rank contributing a vector
    template<typename T, typename Op = std::plus<T> >
    T suffix_sum_arrays(std::deque<T> &values, const Op &op = Op(), const T &identity = T())
    {
        T my_total = accumulate(values.rbegin(), values.rend(), identity, op);
        T total = suffix_sum(my_total, op, identity);
        for (auto it = values.rbegin(); it != values.rend(); it++)
        {
            T &t = *it;
            T next = t;
            t = my_total;
            my_total = op(my_total, next);
        }
        return total;
    }
};
//#endregion range communication

} // namespace msg
//#endregion messageTools

//#region main
namespace task{
OUT_TYPE result;
bool init();
void run_node();
msg::range_comm world(NumberOfNodes());
int rank, nodes;

int main(){
    rank = MyNodeId();
    nodes = NumberOfNodes();
    if(!init())
        return 0;
    run_node();
    if (rank == M){
        std::cout << result << std::endl;
    }
    return 0;
}
}

int main(){
    return task::main();
}
//#endregion main

using namespace std;

//#endregion template code

namespace task{

ll N, start, end;
bool init(){
    N = GetN();
    if (!partition_work(N, rank, nodes, start, end))
        return false;
    world.setRange(0, nodes);
    return true;
}

// write to OUT_TYPE result
void run_node(){
}

} // namespace task
