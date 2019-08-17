2c2
< // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
---
> #define IA_MODE        //remove comment on this line, to activate interactive problem mode
4,5c4,5
< #define COMM_TYPE str
< #define IA_ERROR_CODE "ERROR"
---
> #define COMM_TYPE ll
> #define IA_ERROR_CODE -1
602a603,604
> ll N, m;
> 
603a606
>     cin >> N >> m;
608a612,621
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
610a624,631
>     assert(N>=7);
>     v(ll) p = {17, 16, 13, 11, 9, 7, 5};
>     v(ll) ans;
>     forn(i, 7){
>         ans.pb(ask(p[i]));
>     }
>     out(crt(ans, p));
>     in();
