//#define DEFAULT_VAL	//remove comment on this line, to activate default value trigger
#define OUT_TYPE ll



/*** START OF TEMPLATE CODE ***/

#include <bits/stdc++.h>

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

//goes through the selection possibilites of k elements of the vector
//use: ++si for next selection and *si for a vector of the currently selected elements
//use: for(seliter<T> si(vector,k);!si.final();++si){something with *si}
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

//select from elements, indicated by the ones "1" in the binary representation
template <typename T>
std::deque<T> getSelection(std::deque<T> elements, unsigned long long binaryRepresentationOfSelection){
	std::deque<T> result;
	for(unsigned long long i=0;i<elements.size();++i)
		if( (binaryRepresentationOfSelection>>i)%2 )
			result.push_back(elements[i]);
	return result;
}
#define gsel getSelection

//calculating faculty of n, only valid for n<=20
unsigned long long facll(unsigned long long n){
	if(n)
		return n*facll(n-1);
	return 1;
}

//calculating faculty of n, floating point calulations
long double facld(unsigned long long n){
	if(n)
		return (long double)n * facld(n-1);
	return 1.;
}

//calculating the power of base to the exp
long long powll(long long base, unsigned long long exp){
	long long result=1;
	for(unsigned long long i=0;i<exp;++i)
		result*=base;
	return result;
}

//calculating the binary log of n
unsigned long long log2ll(unsigned long long n){
	assert(n>0);
	if(n==1)
		return 0;
	return 1+log2ll(n>>1);
}

using namespace std;
typedef long long ll;
typedef long double ld;
typedef complex<double> pnt;
typedef string str;
#define hash unordered_map
#define v(type) deque<type >
#define p(type1,type2) pair<type1, type2 >

void init();
void readInput();
void calcFunction();

OUT_TYPE result;
int main() {
	init();
	ofstream outfile("output.txt");
	cout << setprecision(4);
	outfile << setprecision(10);
	ll tests = 0;
	cin >> tests;
	for(ll test=1; test<=tests; ++test){
		//read input
		readInput();
		//calc result
		calcFunction();
		//write output
		outfile << "Case #" << test << ": ";
		cout << "Case #" << test << ": ";
#ifndef DEFAULT_VAL
		outfile << result << endl;
		cout << result << endl;
#endif /*DEFAULT_VAL*/
#ifdef DEFAULT_VAL
		if(result>=0){
			outfile << result << endl;
			cout << result << endl;
		}
		else{
			str errorWord = "IMPOSSIBLE";
			outfile << errorWord << endl;
			cout << errorWord << endl;
		}
#endif /*DEFAULT_VAL*/
	}
	outfile.close();
	return 0;
}

#define mp make_pair
#define x first
#define y second
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define sz size()
#define bn begin()
#define ed end()

#define all(x) (x).begin(), (x).end()
#define ssel(x,i) (x).begin()+(i), (x).begin()+(i)+1
#define msel(x,i,j) (x).begin()+(i), (x).begin()+(j)
#define foreach(cit,container) for(auto cit = (container).begin(); cit != (container).end(); cit++)
#define foreachc(c,cit,container) ll c=0;for(auto cit = (container).begin(); cit != (container).end(); c++, cit++)
#define forn(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define fornn(i, a, b) for (ll i = (ll)(a); i < (ll)(b); ++i)
#define fore(i, a, b) for (ll i = (ll)(a); i <= (ll)(b); ++i)

#define INF 9000000000000000000L
#define EPS 1e-15
#define PI 3.14159265358979323846264338328L
#define MOD 1000000007

namespace task {

void init(){
}

void readInput(){
}

// write to OUT_TYPE result
void calcFunction() {
}

} // namespace task
