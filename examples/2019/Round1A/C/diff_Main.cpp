669a670,672
> ll N;
> v(str) words;
> 
670a674,683
>     cin >> N;
>     words.clear();
>     forn(i,N){
>         str word;
>         cin >> word;
>         reverse(all(word));
>         words.pb(word);
>     }
>     sort(all(words));
>     llog(words);
674a688,736
>     v(ll) matches;
>     forn(i, N-1){
>         ll match = 0;
>         forn(k, words[i].size()){
>             if(words[i][k] == words[i+1][k])
>                 ++match;
>             else
>                 break;
>         }
>         matches.pb(match);
>     }
>     llog(matches);
> 
>     result = 0;
>     forn(_, N/2){
>         ll max_match=0;
>         ll max_idx = -1;
>         forn(i, matches.size()){
>             if(matches[i] > max_match){
>                 max_idx = i;
>                 max_match=matches[i];
>             }
>         }
>         llog("max match:", max_idx, max_match);
>         if(max_match == 0)
>             break;
>         result += 2;
>         matches.erase(matches.bn + max_idx);
>         forn(k, matches.size()){
>             if(max_idx + k >= matches.size())
>                 break;
>             if(matches[max_idx + k] == max_match){
>                 matches[max_idx + k] = max_match - 1;
>             } else
>                 break;
>         }
>         if(matches.size() == 0)
>             break;
>         if(max_idx == matches.size()){
>             matches.erase(matches.bn + max_idx - 1);
>         } else if(max_idx == 0){
>             matches.erase(matches.bn);
>         } else{
>             ll val = min(matches[max_idx], matches[max_idx - 1]);
>             matches[max_idx - 1] = val;
>             matches.erase(matches.bn + max_idx);
>         }
>         llog(matches);
>     }
