//#define DEFAULT_VAL    //remove comment on this line, to activate default value trigger
#define OUT_TYPE ll

//#region template code
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
//#endregion types
//#region members and functions
#define mp make_pair
#define x first
#define y second
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
#define INF 9000000000000000000L
#define EPS 1e-15
#define PI 3.14159265358979323846264338328L
#define MOD 1000000007
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
 *  declares faculty (facll and facld)  IMPORTANT: facll works only for n<=20
 *  declares power on integers (powll and powmod)
 *  declares log2 on integers (log2ll)
 *  declares vmin (returns v[i]=min(a[i] , b[i]) )
 */
//#region mathTools
namespace mathTools{
unsigned long long facll(unsigned long long n){
    if (n)
        return n * facll(n - 1);
    return 1;
}

long double facld(unsigned long long n){
    if(n)
        return (long double)n * facld(n-1);
    return 1.;
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

unsigned long long log2ll(unsigned long long n){
    assert(n > 0);
    if (n == 1)
        return 0;
    return 1 + log2ll(n >> 1);
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

std::deque<long long> vmin(std::deque<long long> a, std::deque<long long> b)
{
    std::deque<long long> out;
    for (unsigned i = 0; i < a.size(); ++i)
        out.push_back(std::min(a[i], b[i]));
    return out;
}
} // namespace mathTools
using namespace mathTools;
//#endregion mathTools

//#region main
namespace task{
void init();
void readInput();
void calcFunction();
}

OUT_TYPE result;
int main() {
    task::init();
    std::ofstream outfile("output.txt");
    std::cout << std::setprecision(4);
    outfile << std::setprecision(10);
    long long unsigned tests = 0;
    std::cin >> tests;
    for(long long unsigned test=1; test<=tests; ++test){
        //read input
        task::readInput();
        //calc result
        task::calcFunction();
        //write output
        outfile << "Case #" << test << ": ";
        std::cout << "Case #" << test << ": ";
#ifndef DEFAULT_VAL
        outfile << result << std::endl;
        std::cout << result << std::endl;
#endif /*DEFAULT_VAL*/
#ifdef DEFAULT_VAL
        if(result>=0){
            outfile << result << std::endl;
            std::cout << result << std::endl;
        }
        else{
            std::string errorWord = "IMPOSSIBLE";
            outfile << errorWord << std::endl;
            std::cout << errorWord << std::endl;
        }
#endif /*DEFAULT_VAL*/
    }
    outfile.close();
    return 0;
}
//#endregion main

using namespace std;

//#endregion template code

namespace task {

void init(){
}

void readInput(){
}

// write to OUT_TYPE result
void calcFunction() {
}

} // namespace task
