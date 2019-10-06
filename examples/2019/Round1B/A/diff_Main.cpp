5c5
< #define COMM_TYPE ll
---
> #define COMM_TYPE str
669a670,676
> ll P, Q;
> v(cell) persons;
> v(cell) directions;
> v(char) dirnames;
> ordered_dict(ll, ll) xcounts;
> ordered_dict(ll, ll) ycounts;
> 
670a678,702
>     cin >> P >> Q;
>     xcounts.clear();
>     ycounts.clear();
>     persons.clear();
>     directions.clear();
>     dirnames.clear();
>     forn(i, P){
>         ll xi, yi;
>         char dir;
>         cin >> xi >> yi >> dir;
>         persons.pb(cell(xi, yi));
>         directions.pb(DIRECTIONS[dir]);
>         dirnames.pb(dir);
>         if(dir == 'N'){
>             ycounts[yi+1]++;
>         } else if(dir == 'S'){
>             ycounts[yi]--;
>         } else if(dir == 'E'){
>             xcounts[xi + 1]++;
>         } else if(dir == 'W'){
>             xcounts[xi]--;
>         } else {
>             lassert(false, "logic error");
>         }
>     }
674a707,722
>     ll bestx=0, besty=0, cx=0, cy=0, bestcx=0, bestcy=0;
>     foreach(it, xcounts){
>         cx += it->nd;
>         if(cx > bestcx){
>             bestx = it->st;
>             bestcx = cx;
>         }
>     }
>     foreach(it, ycounts){
>         cy += it->nd;
>         if(cy > bestcy){
>             besty = it->st;
>             bestcy = cy;
>         }
>     }
>     result = to_string(bestx) + " " + to_string(besty);
