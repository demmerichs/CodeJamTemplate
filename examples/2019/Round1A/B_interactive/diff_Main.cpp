2,3c2,3
< // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
< // #define SUBMIT         //remove comment on this line, when submitting solution
---
> #define IA_MODE        //remove comment on this line, to activate interactive problem mode
> #define SUBMIT         //remove comment on this line, when submitting solution
541a542,543
> ll N, m;
> 
542a545
>     cin >> N >> m;
549a553,566
>     // This solves only the small test case!
>     v(ll) q(18,18);
>     result = 0;
>     forn(i, N){
>         out(q);
>         ll sum=0;
>         forn(j, 18){
>             ll asdf = in();
>             sum += asdf;
>         }
>         result = max(sum, result);
>     }
>     out(result);
>     in();
