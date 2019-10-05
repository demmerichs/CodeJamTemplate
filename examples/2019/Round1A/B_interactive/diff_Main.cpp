2c2
< // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
---
> #define IA_MODE        //remove comment on this line, to activate interactive problem mode
6c6
< #define IA_ERROR_CODE "ERROR"
---
> #define IA_ERROR_CODE -1
610a611,612
> ll N, m;
> 
611a614
>     cin >> N >> m;
616a620,629
> ll ask(ll p){
>     v(ll) ps(18, p);
>     out(ps);
>     ll sum = 0;
>     forn(i, 18){
>         sum += in();
>     }
>     return sum % p;
> }
> 
618a632,639
>     lassert(N>=7, "N was smaller than 7");
>     v(ll) p = {17, 16, 13, 11, 9, 7, 5};
>     v(ll) ans;
>     forn(i, 7){
>         ans.pb(ask(p[i]));
>     }
>     out(crt(ans, p));
>     in();
