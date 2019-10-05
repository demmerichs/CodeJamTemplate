665a666,710
> class emp{
> public:
>     v(ll) s;
> 
>     emp(){}
> 
>     emp(bool read_from_std){
>         lassert(read_from_std, "read from std");
>         ll C;
>         cin >> C;
>         forn(i, C){
>             ll t;
>             cin >> t;
>             s.pb(t);
>         }
>         sort(all(s));
>     }
> 
>     emp(const emp& c){
>         s = c.s;
>     }
> 
>     emp(v(ll) i){
>         s = i;
>     }
> 
>     bool operator==(const emp& other) const{
>         return s == other.s;
>     }
> };
> 
> ll N, S;
> 
> size_t hash_emp(const emp& e){
>     size_t r = 0;
>     forn(i, e.s.sz){
>         // r ^= std::hash<ll>(e.s[i]);
>         // r ^= e.s[i];
>         r *= (S+1);
>         // r *= 1000;
>         r += e.s[i];
>     }
>     return r;
> }
> 
668a714,716
> dict(ll, ll) counts;
> dict(ll, emp) emps;
> 
669a718,729
>     cin >> N >> S;
>     counts.clear();
>     emps.clear();
>     forn(i, N){
>         emp t(true);
>         ll h = hash_emp(t);
>         counts[h]++;
>         emps[h] = t;
>     }
>     foreach(it, emps){
>         llog(it->st, it->nd.s, counts[it->st]);
>     }
673a734,746
>     result = 0;
>     foreach(it, emps){
>         ll unteachable=0;
>         forn(i, 1<<it->nd.s.sz){
>             v(ll) cur = getSelection(it->nd.s, i);
>             emp t(cur);
>             ll h = hash_emp(t);
>             if(counts.count(h)==0)
>                 continue;
>             unteachable += counts[h];
>         }
>         result += (N - unteachable) * counts[it->st];
>     }
