5c5
< #define COMM_TYPE ll
---
> #define COMM_TYPE v(ll)
669a670,672
> ll N;
> v(ll) cits;
> 
670a674,680
>     cin >> N;
>     cits.clear();
>     forn(i, N){
>         ll t;
>         cin >> t;
>         cits.pb(t);
>     }
674a685,693
>     multiset<ll> tops;
>     result.clear();
>     forn(i, N){
>         tops.insert(cits[i]);
>         if(*tops.begin() < tops.sz){
>             tops.erase(tops.begin());
>         }
>         result.pb(tops.sz);
>     }
